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
|	*GDT.c									|
|	*For GDT table in IA32						|
|	*Public interface: Arch.h					|
|	*last modified on 09/May/2011					|
++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



#pragma region		Includes

#include "GDT.h"

#pragma endregion	Includes






#pragma region		Private

/*
Note that the global describtor table is just an array of global descriptors!!
We use static here for private members (cannot be used in other files with extern!)
*/

//Structures we use
static struct GDT_Descriptor	GDT [GDT_Size];
static struct GDT_Register	GDTR;




//This function is for loading the GDTR
static void GDT_GdtrSetup(void)
{

#ifdef _MSC_VER	//This works for visual studio only

	_asm lgdt	[GDTR]

#endif

}




static void GDT_AddDescriptor(uint8 Desc_Index/*zero based*/ , uint32 Desc_Base, uint32 Desc_Limit, uint16 Desc_Flags /*without limit field*/)
{
	
	//checking for limit of GDT
	if (Desc_Index >= GDT_Size) return;

	//zeroing	the descriptor!!
	memset((void*) &GDT[Desc_Index], 0, (size_t) sizeof(GDT[Desc_Index]));

	//setting descriptor fields
	GDT[Desc_Index].BaseLS	=	(uint16)  (Desc_Base		& 0xFFFF	);
	GDT[Desc_Index].BaseDS	=	(uint8)   ((Desc_Base >> 16)	& 0xFF	);
	GDT[Desc_Index].BaseMS	=	(uint8)   ((Desc_Base >> 24)	& 0xFF	);
	GDT[Desc_Index].LimitLS	=	(uint16)  ((Desc_Limit)		& 0xFFFF	);
	GDT[Desc_Index].Flags	=	(Desc_Flags | (uint16) GDT_Flags_Limit(Desc_Limit));
	
}

#pragma endregion	Private







#pragma region		Interface
	

void GDT_Setup(void)
//This function used to initialze system Global descriptor table!
{

	//Add the null descriptor
	GDT_AddDescriptor(0, 0, 0, 0);


	//Add the code descriptor
	GDT_AddDescriptor(1, 0, 0x000FFFFF,//the flag field is ORing of fields in header!!
		 GDT_Flags_Type_ReadWrite	//Readable Code segment
		|GDT_Flags_Type_Code		//Code segment
		|GDT_Flags_CodeORData		//Not system segment
		|GDT_Flags_Present			//Present segment
		|GDT_Flags_DB32Bit			//32bit segment
		|GDT_Flags_Granularity4GB);	//Up to 4GiB segment


	//Add the data segment
	GDT_AddDescriptor(2, 0, 0x000FFFFF,
		 GDT_Flags_Type_ReadWrite	//Writable data segment
		|GDT_Flags_CodeORData		//Not system segment
		|GDT_Flags_Present			//Present segment
		|GDT_Flags_DB32Bit			//32bit segment
		|GDT_Flags_Granularity4GB);	//Up to 4GiB segement
	

	//Setting up the GDTR
	GDTR.GDT_Base	=	(uint32) &GDT[0];
	GDTR.GDT_Limit	=	(uint16) ((sizeof(struct GDT_Descriptor) * GDT_Size) -1);


	//Loading the GDTR
	GDT_GdtrSetup();

}


#pragma endregion	Interface