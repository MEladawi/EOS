



#include "FS.h"
#include <TextDisplay.h>


/*
Note: Glossary:
Fragment => 64KiB block of memory.
Pattern  => Contiguous fragments.

Note: Fragment No type:
I used fragment no as int32 not uint32, as sometimes we need to return -1 to refere error
*/



#ifdef _MSC_VER
#pragma region Private Members
#endif



//Bitmap manipulation operations----------------------------------------------------------------------------

//Note that we start counting from right.. (for that we sgift left for offset inside the 32 bit DWord.)
__forceinline void FS_MemoryMap_SetFragmentBit(int32 FragmentNo)
{
	FS_MemoryMap[FragmentNo / 32] |= (1 << (FragmentNo % 32));
}




__forceinline void FS_MemoryMap_ClrFragmentBit(int32 FragmentNo)
{
	FS_MemoryMap[FragmentNo / 32] &= (~(1 << (FragmentNo % 32)));
}



__forceinline Bool FS_MemoryMap_TestFragmentBit(int32 FragmentNo)
{ 
	if (FS_MemoryMap[FragmentNo / 32] & (1 << (FragmentNo % 32))) return True;
	else return False; 
}

//End Bitmap manipulation operations----------------------------------------------------------------------







//Searching Operations---------------------------------------------------------------------------------------


int32 FS_MemoryMap_GetFirstFreeFragment (void)
{

	uint32 register i= 0;
	uint32 register j= 0;

	for (i =0; i < (FS_GetMemorySize_Fragments() / 32); i++)
	{
		//This makes us don't search everybit in map instead we search just the 32 bits that contains bit correspond to free fragment.
		if (FS_MemoryMap[i] != 0xFFFFFFFF)
		{
			//Search the 32 bit for the free fragment !
			for (j=0; j < 32; j++)
			{
				if ( !(FS_MemoryMap[i] & (1 << j)) ) 
					return (i * 32  /*now we have the dword of free fragment*/ + j);	
			}

		}
	}

	return -1;
}





int32 FS_MemoryMap_GetFirstFreePattern (uint32 PatternSize_Fragments)
{

	uint32 register i=0;
	uint32 register j=0;

	if (PatternSize_Fragments == 0)
		return -1;

	if (PatternSize_Fragments == 1)
		return FS_MemoryMap_GetFirstFreeFragment ();

	for (i =0; i < (FS_GetMemorySize_Fragments() / 32); i++)
	{
		if (FS_MemoryMap[i] != 0xFFFFFFFF)
		{
			for (j=0; j < 32; j++)
			{
				if (!(FS_MemoryMap[i] & (1 << j)))
				{
					int32 register Address = i*32 + j; //First free fragment.
					uint32 register Index;
					uint32 register ContigFragments=0;

					for (Index=0; Index < PatternSize_Fragments; Index++)
					{
						if (FS_MemoryMap_TestFragmentBit(Address+Index) == False) 
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


uint32 FS_GetFreeMemorySize_KiBytes(void)
{
	return (((FS_MemoryMaxSize_Fragments - FS_MemoryUsedSize_Fragments) * FS_FragmentSize_Bytes) / 1024);
}



uint32 FS_GetMemorySize_KiBytes (void)
{
	return (FS_MemoryMaxSize_Sectors * 512) / 1024;
}




uint32 FS_GetMemorySize_Fragments (void)
{
	return FS_MemoryMaxSize_Fragments;
}




uint32 FS_GetUsedMemorySize_Fragments (void)
{
	return FS_MemoryUsedSize_Fragments;
}




uint32 FS_GetFreeMemorySize_Fragments(void)
{
	return (FS_MemoryMaxSize_Fragments - FS_MemoryUsedSize_Fragments);
}





uint32 FS_GetUsedMemorySize_KiBytes(void)
	
{
	return ((FS_MemoryUsedSize_Fragments * FS_FragmentSize_Bytes ) / (1024));
}



void FS_Setup(uint32 MemorySize_Sectors, void* MemoryMapAddress)
{

	//Setting memory map pointer value
	FS_MemoryMap				=	(uint32*) MemoryMapAddress;

	//Setting The memory size that was given from bootloader
	FS_MemoryMaxSize_Sectors		=	MemorySize_Sectors;

	//calculate the number of fragments (memory size in fragments instead of kibytes) in system 
	FS_MemoryMaxSize_Fragments	=	((MemorySize_Sectors * 512)/*Now in Bytes*/ / FS_FragmentSize_Bytes);

	//Initialze the used memory fragment to all fragments as we initialize all memory as used
	FS_MemoryUsedSize_Fragments	=	FS_GetMemorySize_Fragments();

	//Here we clear all bits in mempry map
	memset ((void*) FS_MemoryMap, 0xFF, FS_MemoryMapSize_Bytes);

}




void* FS_AllocateMemory_Fragment (void)
{

	int32 Fragment;

	//Check if there are free fragments in memory 
	if ( !(FS_GetFreeMemorySize_Fragments() > 0))
		return 0;

	Fragment = FS_MemoryMap_GetFirstFreeFragment ();

	//Set this fragment as used in the memory map
	FS_MemoryMap_SetFragmentBit(Fragment);

	//Increase the no of memory fragments used
	FS_MemoryUsedSize_Fragments++;

	return (void *) (Fragment * FS_FragmentSize_Bytes);

}



void FS_DeallocateMemory_Fragment (void* FragmentAddress)
{

	//Get the fragment no. of address "FragmentAddress"
	int32 Fragment = GetFargmentOf((int32) FragmentAddress);

	//Decrease the no of used fragments in memory 
	FS_MemoryUsedSize_Fragments--;

	//Set fragment Bit in memory map as free fragment.
	FS_MemoryMap_ClrFragmentBit(Fragment);

}





void* FS_AllocateMemory_Pattern (uint32 PatternSize_Fragments)
{

	int32 Fragment;
	uint32 register i;

	//Check if there are enough free fragments in memory for that pattern
	if ( !(FS_GetFreeMemorySize_Fragments() > FS_GetMemorySize_Fragments()) )
		return 0;

	Fragment = FS_MemoryMap_GetFirstFreePattern(PatternSize_Fragments);

	//Just to make sure that we have enough free contiguous fragments ..
	if (Fragment == -1) 
		return 0;

	//Set these fragments as used in the memory map
		for ( i=0; i < PatternSize_Fragments; i++)
		FS_MemoryMap_SetFragmentBit(Fragment + i);
	
	//Increase the no of memory fragments used
	FS_MemoryUsedSize_Fragments += PatternSize_Fragments ;

	return (void *) (Fragment * FS_FragmentSize_Bytes);

}





void FS_DeallocateMemory_Pattern (void* PatternBaseAddress, uint32 PatternSize_Fragments)
{
	
	uint32 i;

	//Get the fragment no of address "FragmentAddress"
	int32 Fragment = GetFargmentOf((int32) PatternBaseAddress);

	//Set fragments Bits in memory map as free fragments.
	for (i=0; i < PatternSize_Fragments; i++)
		FS_MemoryMap_ClrFragmentBit (Fragment + i);

	//Decrease the no of used fragments in memory by pattern size => (PatternSize_Fragments)
	FS_MemoryUsedSize_Fragments -= PatternSize_Fragments;

}




void ReadMemFragment(uint32 StartMemFragment, uint16 * Buffer)
{
	uint32 StartLBA = StartMemFragment * PMM_MemFragmentSize_Sectors;
	HDD_ReadSectors(StartLBA, PMM_MemFragmentSize_Sectors, Buffer);
}




void WriteFragment(uint32 StartFragment, uint16 * Buffer)
{
	uint32 StartLBA = StartFragment * FS_FragmentSize_Sectors  ;
	HDD_WriteSectors (StartLBA, FS_FragmentSize_Sectors, Buffer);
}




void AddFileToRootDir(char * FileName, char * FileExtension, uint32 StartFragment, uint32 FileLegnth_Bytes)
{
	uint32 register i;
	uint32 register j;


	for (i=0; i<2048; i++)
	{
		
		if(RootDirectory[i].Name[0] == 0)
		{
			for (j=0; j<strlen(FileName) && j<14; j++) 
				RootDirectory[i].Name[j] = FileName[j];
			RootDirectory[i].Name[14]= 0;
			
			for (j=0; j<strlen(FileExtension) && j<4; j++) 
				RootDirectory[i].Extension[j] = FileExtension[j];
			RootDirectory[i].Extension[5]= 0;

			RootDirectory[i].Length_Bytes = FileLegnth_Bytes;
			
			RootDirectory[i].StartFragment= StartFragment;
			

			break;
		}

	}
}






int32 FindFile(char * FileName, char * FileExtension)
{
	uint32 register i;

	if ((strlen(FileName) > 14) || (strlen(FileExtension) > 4)) 
		return -1;
	
	for (i=0; i<2048; i++)
	{
		if (strcmp(FileName, RootDirectory[i].Name) == 0) 
		{
				return i;
		}
	}

	return -1;
}





uint32 LoadFile(char* FileName, char* FileExtension, uint16* Buffer)
{
	int32 FileIndex;
	uint32 FileLength_MemFragments = 0;
	uint32 register i;
	uint32 register MemFrag;

	FileIndex = FindFile (FileName, FileExtension);
	
	if (FileIndex < 0)
		return; 

	FileLength_MemFragments = GetNoOfMemFragments(RootDirectory[FileIndex].Length_Bytes);

	//Map start as fragment to start as memory fragment.
	MemFrag = RootDirectory[FileIndex].StartFragment * FS_MemFragPerFrag;

	for (i=0; i<FileLength_MemFragments; i++, MemFrag++)
		ReadMemFragment(MemFrag, (uint16 *)((uint32)Buffer + (i*PMM_MemFragmentSize_Bytes/2)));

	return  RootDirectory[FileIndex].Length_Bytes;

}



void WriteFile (char* FileName, char* FileExtension, uint16* Buffer, uint32 FileLength_Bytes)
{
	uint32 StartFragment = 0; //>>>>Fro search algorithm
	uint32 register FragmentsNo;
	uint32 register i;

	FragmentsNo = GetNoOfFragments(FileLength_Bytes);

	for (i=0; i<FragmentsNo; i++) 
		WriteFragment(StartFragment+i, (uint16 *)((uint32)Buffer + (i*FS_FragmentSize_Bytes)));

	AddFileToRootDir(FileName, FileExtension, StartFragment, FileLength_Bytes);
	
}





void TryFS(void)
{
	uint32 register i;
	uint16 * gg = (uint16 *) 0x100000 ;
	uint16 * gg2= (uint16 *) 0x200000;

	for (i=0; i<2048; i++)
		RootDirectory[i].Name[0]= 0;

	for (i=0; i<90000; i++)
		gg[i] = 'A';


	WriteFile("Deeeeeedo", "EXe", gg, 90000);


	//LoadFile("Deeeeeedo", "EXe", gg2);

}







#ifdef _MSC_VER
#pragma endregion Public Members
#endif