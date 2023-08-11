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





 
GetMemoryMap PROC
;	Get memory map by interrupts. This info will be passed to KERNEL as we need it for memory management.
;	Input:  es:di -> destination buffer for entries, usually es=0 ;-)
;	OUT:   bp    -> entries count

	pushad
	xor	ebx, ebx
	xor	bp, bp						; number of entries stored here
	mov	edx, 'PAMS'						; 'SMAP'
	mov	eax, 0E820h
	mov	ecx, 24						; memory map entry struct is 24 bytes
	int	15h							; get first entry
	jc	Error	
	cmp	eax, 'PAMS'						; bios returns SMAP in eax
	jne	Error
	test	ebx, ebx						; if ebx=0 then list is one entry long; bail out
	je	Error
	jmp	Start

NextEntry:
	mov	edx, 'PAMS'						; some bios's trash this register
	mov	ecx, 24						; entry is 24 bytes
	mov	eax, 0E820h
	int	15h							; get next entry

Start:
	jcxz	SkipEntry						; if actual returned bytes is 0, skip entry

NoNext:
	mov	ecx, ES: [Di + 8]					; get length (low dword)
	test	ecx, ecx						; if length is 0 skip it
	jne	short CorrectEntry
	mov	ecx, ES: [Di + 12]					; get length (upper dword)
	jecxz	SkipEntry						; if length is 0 skip it

CorrectEntry:
	inc	bp							; increment entry count
	add	di, 24							; point di to next entry in buffer

SkipEntry:
	cmp	ebx, 0							; if ebx return is 0, list is done
	jne	NextEntry						; get next entry
	jmp	done

Error:
	stc

Done:
	popad
	RET
	
GetMemoryMap ENDP