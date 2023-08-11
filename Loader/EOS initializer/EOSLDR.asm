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



.model tiny
.686P
.code
org 0h



;Definitions::::::::::::::::::::::::::::::::::::::::::::::::
KernelSize			= 100;sectors :D
RMode_KernelBase	= 1000h ; This is th segment content ! we will load kernel at 10000 = at 64 KiB so max kernel size HERE is 575 KiB, 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;Jumb over inluded code!;;;;;;;;;;;;;;;;;;;;;;;;;
GO:
	jp main
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;Data;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LdMsg             Byte     "Loading EOS operating system initializer", 0
DoneMsg         Byte     " [Done]",0Dh, 0Ah, 0
NewLineMsg    Byte      0Dh, 0Ah, 0 
FailMsg           Byte      "oops! fatal error occured in loading operating system initializer",0Dh, 0Ah, 0
RebootMsg     Byte       "press any key to reboot", 0Dh, 0Ah, 0 
WaitMsg          Byte      "...",0
LdMsg2	   Byte      "Loading EOS operating system kernel loader", 0
InitialMsg	   Byte	      "Initializing system environment.......................................",0Dh, 0Ah, 0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



;Include;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
include ..\LIB\GDT.inc
include ..\LIB\A20.inc
include ..\LIB\Print16.inc
include ..\LIB\Load16.inc
include ..\LIB\MemSize.inc
include ..\LIB\MemMap.inc
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;Structure of data passed to kernel;;;;;;;;;;;;;;;;;;
BootData struct
	MemMapEntriesBase 	Word 		?
	MemMapEntriesCount	Word		?
	MemorySizeBel16MB	Word		?
	MemorySizeAb16MB	Word		?
BootData ENDS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



main PROC
	sti
	
	mov ax, 7e0h
	mov ds, ax
	
	mov ax, RMode_KernelBase
	mov ES, ax				;Now ES hols the segment address for our kernel !
	
	
;*****************************************************************Begin Pmode establishment***********************************************************************

;Load kernel temporarily to 10000h:
	cld
	mov si, offset LdMsg2
	call print
	mov cx, KernelSize
	mov Ax, 5h
	xor Bx, Bx
	call Load
	mov si, offset InitialMsg
	call print
	

;1-establish GDT:--------------------------------------
	cli
	call SetGDT
;--------------------------------------------------------------



;2-Enable A20:-------------------------------------------------
	call EnableA20
;-------------------------------------------------------------------

;Get memory Size and map: (Used in kernel) ------
	sti
	KernelData BootData <>
	
	call GetMemorySize
	mov KernelData.MemorySizeBel16MB, ax
	mov KernelData.MemorySizeAb16MB, bx
	
	xor ax, ax
	mov es, ax
	mov di, 500h
	call GetMemoryMap
	mov KernelData.MemMapEntriesCount, bp
	mov KernelData.MemMapEntriesBase, di
	
	;This is the address of data we pass to kernel :D
	;In kernel we will creat pointer with value of EBX to access structure members ;-)
	mov EBX, ((offset KernelData) + 7E00h)
	
	cli
;-------------------------------------------------------------------

;3-Change CR0 (PE) bit to 1:--------------------------
	mov 	EBP, (10400h)
	smsw	dx
	OR	dx, 1h
	lmsw	dx
;-------------------------------------------------------------------



;Make far jump manually ; ) -----------------------------
	push 8h  				;Cs: selector
	push ((offset done) + 7E00h)	;we add 7e00h to get absolute address ;-)
	retf
;-----------------------------------------------------------------------




DONE:
;*********************************************************32-bit part :D :D :D*****************************************************

;mov ax, 10h
;mov ds,ax
;mov ds,ax
;
;;NOTE:: the next part is written in code machine, as the assembler has TINY model which is 16 bit so, it will assemble it incorrectly ;-)
;
;
;;mov EAX, [10000h + 3Ch]
;Byte		0B8h
;DWord	0001003Ch
;
;;mov EAX, [EAX]
;Byte		8Bh
;Byte		00h
;
;;add EAX, 40(28h)
;Byte		83h
;Byte		0C0h
;Byte		28h 
;
;;mov EBX, [EAX]
;Byte		8Bh
;Byte		18h
;
;;add EAX, 12
;Byte		83h
;Byte		0C0h
;Byte		0Ch
;
;;mov EBP, [EAX]
;Byte		8Bh
;Byte		28h
;
;;add EBP, EBX
;Byte		03h
;Byte		0EBh

;CallEBP
Word	0D5FFh
	hlt
	
main ENDP

End