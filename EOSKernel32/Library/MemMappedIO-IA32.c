//;							          _____                   _______                   _____          
//;							         /\    \                 /::\    \                 /\    \         
//;							        /::\    \               /::::\    \               /::\    \        
//;							       /::::\    \             /::::::\    \             /::::\    \       
//;							      /::::::\    \           /::::::::\    \           /::::::\    \      
//;							     /:::/\:::\    \         /:::/~~\:::\    \         /:::/\:::\    \     
//;							    /:::/__\:::\    \       /:::/    \:::\    \       /:::/__\:::\    \    
//;							   /::::\   \:::\    \     /:::/    / \:::\    \      \:::\   \:::\    \   
//;							  /::::::\   \:::\    \   /:::/____/   \:::\____\   ___\:::\   \:::\    \  
//;							 /:::/\:::\   \:::\    \ |:::|    |     |:::|    | /\   \:::\   \:::\    \ 
//;							/:::/__\:::\   \:::\____\|:::|____|     |:::|    |/::\   \:::\   \:::\____\
//;							\:::\   \:::\   \::/    / \:::\    \   /:::/    / \:::\   \:::\   \::/    /
//;							 \:::\   \:::\   \/____/   \:::\    \ /:::/    /   \:::\   \:::\   \/____/ 
//;							  \:::\   \:::\    \        \:::\    /:::/    /     \:::\   \:::\    \     
//;							   \:::\   \:::\____\        \:::\__/:::/    /       \:::\   \:::\____\    
//;							    \:::\   \::/    /         \::::::::/    /         \:::\  /:::/    /    
//;							     \:::\   \/____/           \::::::/    /           \:::\/:::/    /     
//;							      \:::\    \                \::::/    /             \::::::/    /      
//;							       \:::\____\                \::/____/               \::::/    /       
//;							        \::/    /                 ~~                      \::/    /        
//;							         \/____/  '11 Grad project                         \/____/         
//;							                                                                           
//
//
//


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
|	*MemMappedIO-IA32.c												|
|	*Contains functions required to deal with Memory mapped I/O ports in IA-32	|
|	*last modified on 21/June/2011									|
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdint.h>


void OutPortByte (uint16 PortNo, uint8 OutData)
{

	_asm
	{
		mov 	dx, [PortNo]
		mov  al, [OutData]
		out  dx, al
	}

}


uint8 InPortByte (uint16 PortNo)
{
	uint8 Data;

	_asm
	{
		mov dx, [PortNo]
		in  al, dx
		mov byte ptr [Data], al
	}

	return Data;
}


void OutPortWord (uint16 PortNo, uint16 Data)
{
	_asm
	{
		mov dx, [PortNo]
		mov ax, [Data]
		out dx, ax
	}

}


void OutPortDWord (uint16 PortNo, uint32 Data)
{
	_asm
	{
		mov dx, [PortNo]
		mov eax, [Data]
		out dx, eax
	}

}


uint16 InPortWord (uint16 PortNo)
{
	uint16 Data;

	_asm
	{
		mov DX, [PortNo]
		in  AX, DX
		mov word ptr [Data], AX
	}

	return Data;
}


uint32 InPortDWord (uint16 PortNo)
{
	uint32 Data;

	_asm
	{
		mov DX, [PortNo]
		in  EAX, DX
		mov dword ptr [Data], EAX
	}

	return Data;
}
