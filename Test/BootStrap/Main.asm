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
.code
ORG 0h


;Definitions::::::::::::::::::::::::::::::::::::::::::::::::
KernelSize				= 5
PMode_KernelBase		= 10000h
RMode_KernelBase		= 9000h
RMode_KernelStackBase		= 500h
RMode_KernelStackPTR		= 7BFFh
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



Go proc  ;Just jump function to bypass the inluded functions (Remember we use Tiny model !!)
	jmp main
Go endp



;Include Area-------------------------------------------------------------------------
include ..\LIB\Print16.inc
include ..\LIB\Load16.inc
include ..\LIB\a20.inc
include ..\LIB\GDT.inc
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
	mov sp, 7bffh 
	sti
	
	
	;printing text using interrupt
	mov si, offset LdMsg	
	call print
	
	;Load kernel temp. to 9000h
	mov cx, KernelSize
	mov Ax, 1h
	mov Bx, RMode_KernelBase
	call Load
	
	
	;1-establish GDT:--------------------------------------
	cli
	call SetGDT
	;--------------------------------------------------------------

	;2-Enable A20:-------------------------------------------------
	call EnableA20
	;-------------------------------------------------------------------

	;3-Change CR0 (PE) bit to 1:--------------------------
	smsw	dx
	OR	dx, 1h
	lmsw	dx
	;-------------------------------------------------------------------

	;Make far jump manually ; ) -----------------------------
	push 8h  				;Cs: selector
	push (7E00h)				;offset
	retf
	;-----------------------------------------------------------------------
	
	
	
	;reboot
	sti
	mov si, offset rebootmsg
	call print
	mov ah, 0
          int  16h    ; wait key press
          int  19h    ; Reboot computer	

main ENDP




;Data;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;Messages**********************************************************************************************************
LdMsg             Byte     "Loading operating system initializer", 0
DoneMsg         Byte     " [Done]",0Dh, 0Ah, 0
NewLineMsg    Byte      0Dh, 0Ah, 0 
FailMsg           Byte      "Oops! fatal error occured",0Dh, 0Ah, 0
RebootMsg     Byte       "Press any key to reboot", 0Dh, 0Ah, 0 
WaitMsg          Byte      ".",0



;GDT Data structure*******************************************************************************************************
NullGD	QWord	0h

CodeGD	QWord	0000000011001111100110100000000000000000000000001111111111111111b

DataGD	QWord	0000000011001111100100100000000000000000000000001111111111111111b



;GDTR Data********************************************************************************************************************
GDT_Info	Word		(offset GDT_Info) - (offset NullGD) -1
		DWord	(offset NullGD) + 7C00h 	;to get absolute address :D

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


END

