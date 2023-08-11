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
|	*MemMappedIO-IA32.h												|
|	*Public header file for IO port function in IA32						|
|	*last modified on 01/july/2011									|
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <stdint.h>

#ifdef TargetMachine_IA32



#ifndef MemMappedIO_IA32_h
#define MemMappedIO_IA32_h


//Send byte data to port
void OutPortByte (uint16 PortNo, uint8 OutData);

//receive byte data from PortNo
uint8 InPortByte (uint16 PortNo);

//Send Word data to PortNo
void OutPortWord (uint16 PortNo, uint16 Data);

//Send DWord data to PortNo
void OutPortDWord (uint16 PortNo, uint32 Data);

//receive Word data from PortNos
uint16 InPortWord (uint16 PortNo);

//receive DWord data from PortNo
uint32 InPortDWord (uint16 PortNo);
#endif



#else
#ifdef _MSC_VER
#error File MemMappedIO is specified for IA32 architecture only.
#endif


#endif
