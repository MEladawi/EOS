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

;Variables
Sector    Byte     ?
Head      Byte     ?
Cylinder  Byte     ?




InitializeDrive PROC 
pusha
Begin:
	xor bx, bx
	xor dl, dl
	xor ah, ah
	int 13h
jc Begin
popa
	RET
InitializeDrive ENDP



CnvrtAd PROC
pusha

;This covert LBA address to CHS address.
;Input: LBA value given in AX register.
;o/p are : cylinder, head and Sector variables : in main module.	   
	

	;Symbolic constants !
	SectorPerTrack = 18
	NoHeads = 2
	BytesPerSector = 512
	
	;Sector = (LBA mod SectorsPerTrack)+1
	;Cylinder = (LBA/SectorsPerTrack)/NumHeads
	;Head = (LBA/SectorsPerTrack) mod NumHeads
	
	
	;**LBA/Sectors Per Track:
	;Quotient(Ax) : NumberOfTrack    Remainder(Dx) + 1 : Sector
	xor dx, dx
	xor bx,bx
	mov Bx, SectorPerTrack
	Div Bx
	inc dl
	mov Sector, dl
	
	
	;**Number Of Tracks(Ax)/Number Of Heads:
	;Quotient(Al) : Cylinder  ,   Remainder(Ah) : Head
	XOR Dx, Dx
	mov Bx, NoHeads
	Div Bx
	mov Cylinder, al
	mov Head, dl
	
	
popa
	RET
CnvrtAd ENDP



Load PROC

;receives Ax as start sector, Cx as no of sectors and Bx as address of loaded data

	CALL InitializeDrive

LoadBegin:
	
	mov di, 0Ah  ;Dx is loop to try to load a sector 10 times.
	
	; for wait dots :D
	mov si, offset WaitMsg
	call print
		
	SectorTrial:
		push ax
		push dx
		push cx
				
		;Convert address
		call CnvrtAd

		; Interrupt 13h to read sector
		mov ah, 2
		mov al, 1
		mov ch, cylinder
		mov cl, sector
		mov dh, head
		mov dl, 0
		int 13h
		
		jnc  NextSec ;if carry there is error so we retry, else load next sector
		
		dec Di  ;Decrement loop of error trials
		jz failure ;Di=0
		
		pop cx 
		pop dx
		pop ax
			
	jmp SectorTrial
	
NextSec:
	pop cx
	pop dx
	pop ax
	add bx, BytesPerSector   ;next memory location for next sector
	inc Ax	   ;Next sector LBA
	dec Cx ;Decrease counter of no of sectors
jnz LoadBegin



	mov si, offset DoneMsg
	call print
	
	jmp finish
	

	
Failure:
          mov si, offset FailMsg
          call    Print
          mov si, offset RebootMsg
          call print
          
          ;Reboot   :(   after user press key
          mov ah, 0
          int  16h    ; wait key press
          int  19h    ; Reboot computer	
	

finish:
	RET
	
Load ENDP



