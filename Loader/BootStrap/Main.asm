;							          _____                   _______                   _____          
;							         /\    \                 /::\    \                 /\    \         
;							        /::\    \               /::::\    \               /::\    \        
;							       /::::\    \             /::::::\    \             /::::\    \       
;							      /::::::\    \           /::::::::\    \           /::::::\    \      
;							     /:::/\:::\    \         /:::/~~\:::\    \         /:::/\:::\    \     
;							    /:::/__\:::\    \       /:::/    \:::\    \       /:::/__\:::\    \    
;							   /::::\   \:::\    \     /:::/    / \:::\    \      \:::\   \:::\    \   
;							  /::::::\   \:::\    \   /:::/____/   \:::\____\   ___\:::\   \:::\    \  
;							 /:::/\:::\   \:::\    \ |:::|    |     |:::|    | /\   \:::\   \:::\    \ 
;							/:::/__\:::\   \:::\____\|:::|____|     |:::|    |/::\   \:::\   \:::\____\
;							\:::\   \:::\   \::/    / \:::\    \   /:::/    / \:::\   \:::\   \::/    /
;							 \:::\   \:::\   \/____/   \:::\    \ /:::/    /   \:::\   \:::\   \/____/ 
;							  \:::\   \:::\    \        \:::\    /:::/    /     \:::\   \:::\    \     
;							   \:::\   \:::\____\        \:::\__/:::/    /       \:::\   \:::\____\    
;							    \:::\   \::/    /         \::::::::/    /         \:::\  /:::/    /    
;							     \:::\   \/____/           \::::::/    /           \:::\/:::/    /     
;							      \:::\    \                \::::/    /             \::::::/    /      
;							       \:::\____\                \::/____/               \::::/    /       
;							        \::/    /                 ~~                      \::/    /        
;							         \/____/  '11 Grad project                         \/____/         
;							                                                                           



;This module serves as bootstrap which is at bootsector!
;It's main function is to load a operating system initializer which in turn initializes the system and load our 32bit kernel :D



.model tiny
.686P


.Data;-----------------------------------------------------------------------------------------
LdMsg             Byte     "Loading EOS operating system initializer", 0
DoneMsg         Byte     " [Done]",0Dh, 0Ah, 0
NewLineMsg    Byte      0Dh, 0Ah, 0
FailMsg           Byte      "oops! fatal error occured in loading operating system initializer",0Dh, 0Ah, 0
RebootMsg     Byte       "press any key to reboot", 0Dh, 0Ah, 0
WaitMsg          Byte      "...",0

;--------------------------------------------------------------------------------------------------------


.code
ORG 0h

Go proc  ;Just jump function to bypass the inluded functions (Remember we use Tiny model !!)
	jmp main
Go endp

;Include Area-------------------------------------------------------------------------
include ..\LIB\Print16.inc
include ..\LIB\Load16.inc
;--------------------------------------------------------------------------------------------

main PROC

	;prepare the DS segment register to 7c00h ->start at 7c0:0=7c00 and es to 0h
	cli
	cld
	mov ax, 7c0h
	mov ds, ax
	xor ax,ax
	mov es, ax
	
	;Setting up the real time kernel stack: revice the memory map  this is the free space between bda and bootloader .. (Marsoma 3andy) - about 30KB
	mov ax, 500h
	mov ss, ax
	mov sp, 7BFFh
	sti
	
	;printing text using interrupt
	mov si, offset LdMsg	
	call print
	
	;Loading system initializer
	mov ax, 1h
	mov Cx, 2h
	mov bx, 7e00h
	call Load

	push 0h		;Cs
	push 7e00h		;IP address=10x0+7f00h=7f00h :D
	retf
	
	;reboot
	mov si, offset rebootmsg
	call print
	mov ah, 0
          int  16h    	; wait key press
          int  19h    	; Reboot computer	

main ENDP

END

