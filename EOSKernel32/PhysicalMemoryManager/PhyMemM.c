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



#include "PMM.h"


/*
Note: Glossary:
Fragment => 4KiB block of memory.
Pattern  => Contiguous fragments.

Note: Fragment No type:
I used fragment no as int32 not uint32, as sometimes we need to return -1 to refere error
*/



#ifdef _MSC_VER
#pragma region Private Members
#endif



//Bitmap manipulation operations----------------------------------------------------------------------------

//Note that we start counting from right.. (for that we sgift left for offset inside the 32 bit DWord.)
__forceinline void PMM_MemoryMap_SetFragmentBit(int32 FragmentNo)
{
	PMM_MemoryMap[FragmentNo / 32] |= (1 << (FragmentNo % 32));
}



void PMM_SetPatternBits (void* PatternBaseAddress, uint32 PatternSize_Bytes)   //<--------------------uint32 Make limitation of 4gb of pattern.
{

	//Get the start fragment of the PatternBaseAddress .. 
	int32 StartFragment		=	GetFargmentOf ((int32)PatternBaseAddress);
	
	//Get the no of fragments needed for that PatternSize_Bytes
	uint32 NoOfFragments	=	GetNoOfFragments (PatternSize_Bytes);

	//If size = 0 return of course !
	if(!PatternSize_Bytes) return;

	//Set the bits in Memory map corresponds to that fragments
	while (NoOfFragments > 0)
	{

		PMM_MemoryMap_SetFragmentBit(StartFragment);
		StartFragment++;
		NoOfFragments--;

		//Increase no of used fragments in memory
		PMM_MemoryUsedSize_Fragments++;
	
	}

}






__forceinline void PMM_MemoryMap_ClrFragmentBit(int32 FragmentNo)
{
	PMM_MemoryMap[FragmentNo / 32] &= (~(1 << (FragmentNo % 32)));
}



void PMM_ClrPatternBits (void* PatternBaseAddress, uint32 PatternSize_Bytes)
{

	//Get the start fragment of the PatternBaseAddress .. 
	int32 StartFragment		=	GetFargmentOf ((int32)PatternBaseAddress);
	
	//Get the no of fragments needed for that PatternSize_Bytes
	uint32 NoOfFragments	=	GetNoOfFragments (PatternSize_Bytes);

	//Clear the bits in Memory map corresponds to that fragments
	while (NoOfFragments > 0)
	{

		PMM_MemoryMap_ClrFragmentBit(StartFragment);
		StartFragment++;
		NoOfFragments--;

		//Decrease no of used fragments in memory
		PMM_MemoryUsedSize_Fragments--;
	
	}
}




__forceinline Bool PMM_MemoryMap_TestFragmentBit(int32 FragmentNo)
{ 
	if (PMM_MemoryMap[FragmentNo / 32] & (1 << (FragmentNo % 32))) return True;
	else return False; 
}

//End Bitmap manipulation operations----------------------------------------------------------------------







//Searching Operations---------------------------------------------------------------------------------------


int32 PMM_MemoryMap_GetFirstFreeFragment (void)
{

	uint32 register i= 0;
	uint32 register j= 0;

	for (i =0; i < (PMM_GetMemorySize_Fragments() / 32); i++)
	{
		//This makes us don't search everybit in map instead we search just the 32 bits that contains bit correspond to free fragment.
		if (PMM_MemoryMap[i] != 0xFFFFFFFF)
		{
			//Search the 32 bit for the free fragment !
			for (j=0; j < 32; j++)
			{
				if ( !(PMM_MemoryMap[i] & (1 << j)) ) 
					return (i * 32  /*now we have the dword of free fragment*/ + j);	
			}

		}
	}

	return -1;
}





int32 PMM_MemoryMap_GetFirstFreePattern (uint32 PatternSize_Fragments)
{

	uint32 register i=0;
	uint32 register j=0;

	if (PatternSize_Fragments == 0)
		return -1;

	if (PatternSize_Fragments == 1)
		return PMM_MemoryMap_GetFirstFreeFragment ();

	for (i =0; i < (PMM_GetMemorySize_Fragments() / 32); i++)
	{
		if (PMM_MemoryMap[i] != 0xFFFFFFFF)
		{
			for (j=0; j < 32; j++)
			{
				if (!(PMM_MemoryMap[i] & (1 << j)))
				{
					int32 register Address = i*32 + j; //First free fragment.
					uint32 register Index;
					uint32 register ContigFragments=0;

					for (Index=0; Index < PatternSize_Fragments; Index++)
					{
						if (PMM_MemoryMap_TestFragmentBit(Address+Index) == False) 
							break;
						
						ContigFragments++;
						
						if (ContigFragments == PatternSize_Fragments)
							return Address;
					}
				}	
			}
		}
	}

	return -1;

}

//End Searching Operations------------------------------------------------------------------------


#ifdef _MSC_VER
#pragma endregion Private Members
#endif









#ifdef _MSC_VER
#pragma region Public Members
#endif


uint32 PMM_GetFreeMemorySize_KiBytes(void)
{
	return (((PMM_MemoryMaxSize_Fragments - PMM_MemoryUsedSize_Fragments) * PMM_FragmentSize_Bytes) / 1024);
}



uint32 PMM_GetMemorySize_KiBytes (void)
{
	return PMM_MemoryMaxSize_KiBytes;
}




uint32 PMM_GetMemorySize_Fragments (void)
{
	return PMM_MemoryMaxSize_Fragments;
}




uint32 PMM_GetUsedMemorySize_Fragments (void)
{
	return PMM_MemoryUsedSize_Fragments;
}




uint32 PMM_GetFreeMemorySize_Fragments(void)
{
	return (PMM_MemoryMaxSize_Fragments - PMM_MemoryUsedSize_Fragments);
}





uint32 PMM_GetUsedMemorySize_KiBytes(void)
	
{
	return ((PMM_MemoryUsedSize_Fragments * PMM_FragmentSize_Bytes ) / (1024));
}



void PMM_Setup(uint32 MemorySize_KiByte, void* MemoryMapAddress)
{

	//Setting memory map pointer value
	PMM_MemoryMap				=	(uint32*) MemoryMapAddress;

	//Setting The memory size that was given from bootloader
	PMM_MemoryMaxSize_KiBytes	=	MemorySize_KiByte;

	//calculate the number of fragments (memory size in fragments instead of kibytes) in system 
	PMM_MemoryMaxSize_Fragments	=	((MemorySize_KiByte * 1024)/*Now in Bytes*/ / PMM_FragmentSize_Bytes);

	//Initialze the used memory fragment to all fragments as we initialize all memory as used
	PMM_MemoryUsedSize_Fragments	=	PMM_GetMemorySize_Fragments();

	//Here we clear all bits in mempry map
	memset ((void*) PMM_MemoryMap, 0xFF, PMM_MemoryMapSize_Bytes);

}




void* PMM_AllocateMemory_Fragment (void)
{

	int32 Fragment;

	//Check if there are free fragments in memory 
	if ( !(PMM_GetFreeMemorySize_Fragments() > 0))
		return 0;

	Fragment = PMM_MemoryMap_GetFirstFreeFragment ();

	//Set this fragment as used in the memory map
	PMM_MemoryMap_SetFragmentBit(Fragment);

	//Increase the no of memory fragments used
	PMM_MemoryUsedSize_Fragments++;

	return (void *) (Fragment * PMM_FragmentSize_Bytes);

}



void PMM_DeallocateMemory_Fragment (void* FragmentAddress)
{

	//Get the fragment no. of address "FragmentAddress"
	int32 Fragment = GetFargmentOf((int32) FragmentAddress);

	//Decrease the no of used fragments in memory 
	PMM_MemoryUsedSize_Fragments--;

	//Set fragment Bit in memory map as free fragment.
	PMM_MemoryMap_ClrFragmentBit(Fragment);

}





void* PMM_AllocateMemory_Pattern (uint32 PatternSize_Fragments)
{

	int32 Fragment;
	uint32 register i;

	//Check if there are enough free fragments in memory for that pattern
	if ( !(PMM_GetFreeMemorySize_Fragments() > PMM_GetMemorySize_Fragments()) )
		return 0;

	Fragment = PMM_MemoryMap_GetFirstFreePattern(PatternSize_Fragments);

	//Just to make sure that we have enough free contiguous fragments ..
	if (Fragment == -1) 
		return 0;

	//Set these fragments as used in the memory map
		for ( i=0; i < PatternSize_Fragments; i++)
		PMM_MemoryMap_SetFragmentBit(Fragment + i);
	
	//Increase the no of memory fragments used
	PMM_MemoryUsedSize_Fragments += PatternSize_Fragments ;

	return (void *) (Fragment * PMM_FragmentSize_Bytes);

}



void PMM_DeallocateMemory_Pattern (void* PatternBaseAddress, uint32 PatternSize_Fragments)
{
	
	uint32 i;

	//Get the fragment no of address "FragmentAddress"
	int32 Fragment = GetFargmentOf((int32) PatternBaseAddress);

	//Set fragments Bits in memory map as free fragments.
	for (i=0; i < PatternSize_Fragments; i++)
		PMM_MemoryMap_ClrFragmentBit (Fragment + i);

	//Decrease the no of used fragments in memory by pattern size => (PatternSize_Fragments)
	PMM_MemoryUsedSize_Fragments -= PatternSize_Fragments;

}




#ifdef _MSC_VER
#pragma endregion Public Members
#endif

