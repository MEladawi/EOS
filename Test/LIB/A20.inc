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








;The 8042 controller contains the following registers:
;
;A one-byte input buffer - contains byte read from keyboard; read-only
;A one-byte output buffer - contains byte to-be-written to keyboard; write-only
;A one-byte status register - 8 status flags; read-only
;A one-byte control register - 7 control flags; read/write 



;8043 Keyboard Controller Status Register is at 64h port address
;Bit 0:
	;Output Buffer Full-A 0 indicates that the keyboard
	;controller's output buffer has no data. A 1 indicates that
	;the controller has placed data into its output buffer but
	;the system has not yet read the data. When the system
	;reads the output buffer (1/0 address hex 60), this bit will
	;return to a 0. (With instruction IN)
;Bit 1:
	;Input Buffer Full-A 0 indicates that the keyboard
	;controller's input buffer (1/0 address hex 60 or 64) is
	;empty. A 1 indicates that data has been written into the
	;buffer but the controller has not read the data. When the
	;controller reads the input buffer, this bit will return to 0.(With instruction OUT)

WaitKB_IP PROC USES Ax

Begin_WaitKB_IP:
	in al, 64h
	Test al, 2h
jnz Begin_WaitKB_IP

	RET
WaitKB_IP ENDP

WaitKB_OP PROC USES Ax
Begin_WaitKB_OP:
	in al, 64h
	Test al, 1h
jz Begin_WaitKB_OP
	RET
WaitKB_OP ENDP



;**Controller command used in next proc::
;D0h:
	;Read Output Port-This command causes the controller
	;to read its output port and place the data in its output
	;buffer. This command should be issued only if the output
	;buffer is empty.
;D1h:
	;Write Output Port-The next byte of data written to I/0
	;address hex 60 is placed in the controller's output port.

;ADh:
	;Disable Keyboard Feature-This command sets bit 4 of
	;the controller's command byte. This disables the
	;keyboard interface by driving the clock line low. Data
	;will not be sent or received.

;AEh:
	;Enable Keyboard Interface-This command clears bit 4
	;of the command byte, which releases the keyboard
	;interface.
EnableA20 PROC
pusha
	;Diable keyboard
	call WaitKB_IP ;wait I/P buffer
	mov al, 0ADh
	OUT 64h, al


Start_EnableA20:
	;This cause the o/p port to be written to output bufer, then wait it to finish
	call WaitKB_IP
	mov al, 0D0h
	out 64h, al
	
	
	;Read the o/p port data that exists in o/p buffer 
	call WaitKB_op
	IN al, 60h
	mov bl, al
	
	
	;Send Data we want to put in o/p port later to I/P buffer
	call WaitKB_IP
	mov al, 0D1h
	OUT 64h, al
	
	
	;Set second bit ; of A20
	call WaitKB_IP
	mov al, bl
	OR al, 2h
	OUT 60h, al
	

	;make sure that A20 bit is set
	call WaitKB_IP
	mov al, 0D0h
	out 64h, al
	call WaitKB_OP
	IN al, 60h
	Test al, 2
JZ Start_EnableA20

	;Enable keyboard
	call WaitKB_IP
	mov al, 0AEh
	OUT 64h, al
	call WaitKB_IP
	
popa
	RET
EnableA20 ENDP

