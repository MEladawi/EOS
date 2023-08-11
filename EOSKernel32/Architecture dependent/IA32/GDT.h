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
|	*GDT.h									|
|	*Contains (private) definitions for GDT.C only!	|
|	*last modified on 07/May/2011					|
++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#ifndef _GDT_H
#define _GDT_H


#pragma region		Includes

#include <stdint.h>
#include <String.h>

#pragma endregion	Includes




#pragma region		Macroes


//Define max entries (decriptors) in GDT table. 
#define GDT_Size					3	//This what we uses till now; null, code & data segments.



/***********************Definitions for flags***************************/

//=>>Type field:
//For accessed bit in descriptor						(bit: 8)
#define GDT_Flags_Type_Accessed		0x1

//For Readable(code) or writable(data) bit in descriptor	(bit: 9)
#define GDT_Flags_Type_ReadWrite		0x2

//For Expand-down or conforming bit in descriptor			(bit: 10)
#define GDT_Flags_Type_ExpandConform	0x4

//For Type of segment(code or data?) bit in descriptor		(bit: 11)
#define GDT_Flags_Type_Code			0x8



//For System or (code or data)- S bit in descriptor		(bit: 12)
#define GDT_Flags_CodeORData			0x10 //(16)

//For DPL bits in descriptor							(bits: 13-14)
#define GDT_Flags_ApplicationDPL		0x60

//For Present bit in descriptor						(bit: 15)
#define GDT_Flags_Present			0x80

//For limit(16-19) field in descriptor					(bits: 16-19)
//This macro take the whole limit and parse it to get bit 16->19 only to use in describtor.
#define GDT_Flags_Limit(x)			((x>>8) & 0x0f00)

//For D/B bit in descriptor							(bit: 22)
#define GDT_Flags_DB32Bit			0x4000

//For Granularity bit in descriptor				(bit: 23)
#define GDT_Flags_Granularity4GB		0x8000

/************************End of flags' definition**************************/

#pragma endregion	Macroes





#pragma region		Declarations





#ifdef _MSC_VER	
#pragma pack(1)		//To make sure that our structures are not aligned with padding !!
#endif

//This is the structure of Global descriptor in IA32
struct GDT_Descriptor
{

	uint16	LimitLS;	//Note: LS =least sinificant, the rest of Limit is included in Flags field
	
	uint16	BaseLS;
	
	uint8	BaseDS;	//DS= middle significat :D
	
	uint16	Flags;
	
	uint8	BaseMS;	//MS=Most significat

};








#ifdef _MSC_VER	
#pragma pack(1)		//To make sure that our structures are not aligned with padding !!
#endif


//This is the structure of Global descriptor table register GDTR in IA32
struct GDT_Register
{

	uint16	GDT_Limit;

	uint32	GDT_Base;

};



#pragma endregion	Declaration


#endif