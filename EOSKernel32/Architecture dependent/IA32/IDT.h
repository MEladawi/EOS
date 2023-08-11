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


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++
|	*IDT.h									|
|	*Contains (private) definitions for IDT.C only!	|
|	*last modified on 08/May/2011					|
++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#ifndef _IDT_H
#define _IDT_H






#pragma region Includes

#include <stdint.h>
#include <String.h>
#include <TextDisplay.h>

#pragma endregion Includes







#pragma region Macroes

//This is a type definition for the function pointer of Inerrupt handler !
typedef void (* IDT_IntHandler)(void); 

//Size of IDT.
#define IDT_Size	256



/********the interrupt descriptor flags************/

//The default (11 binary) bits at 9-10 
#define	IDT_Flags_Default		0x06

//The D bit at 11
#define	IDT_Flags_32Bit		0x08

//DPL bits at 13-14
#define	IDT_Flags_ApplicationDPL	0x60

//The present bit at 15
#define	IDT_Flags_Present		0x80

/********End interrupt descriptor flags************/


#define	ISR					__declspec( naked )	
#pragma endregion Macroes







#pragma region Declarations


#ifdef _MSC_VER	
#pragma pack(1)		//To make sure that our structures are not aligned with padding !!
#endif
//This struction of interrupt descriptor in IA-32
struct IDT_Descriptor
{

	//least significat 16 bits of offset
	uint16	IDT_OffsetLS;

	//The 16 bit selector
	uint16	IDT_Selector;

	//The 8 bits always zeroes
	uint8	IDT_Reserved;

	//The 8 bits as flags
	uint8	IDT_Flags;

	//most significat 16 bits of offset 
	uint16	IDT_OffsetMS;

};




#ifdef _MSC_VER	
#pragma pack(1)		//To make sure that our structures are not aligned with padding !!
#endif
struct IDT_Register
{

	//The limit field in IDTR
	uint16	IDT_Limit;

	//The base field in IDTR
	uint32	IDT_Base;

};



#pragma endregion Declarations




#endif