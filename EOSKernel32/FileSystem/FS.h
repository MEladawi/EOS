#ifndef FS_H
#define FS_H




#ifdef _MSC_VER
#pragma region Includes
#endif

#include <stdint.h>
#include <String.h>
#include <Drivers_EIDE.h>
#include <MemMappedIO-IA32.h>

#ifdef _MSC_VER
#pragma endregion Includes
#endif










#ifdef _MSC_VER
#pragma region Declarations
#endif

void FS_MemoryMap_SetFragmentBit(int32 FragmentNo);

void FS_MemoryMap_ClrFragmentBit(int32 FragmentNo);

Bool FS_MemoryMap_TestFragmentBit(int32 FragmentNo);

int32 FS_MemoryMap_GetFirstFreeFragment (void);

int32 FS_MemoryMap_GetFirstFreePattern (uint32 PatternSize_Fragment);

void FS_Setup(uint32 MemorySize_KiByte, void* MemoryMapAddress);

void FS_ClrPatternBits (void* PatternBaseAddress, uint32 PatternSize_Byte);

void FS_SetPatterBits (void* PatternBaseAddress, uint32 PatternSize_Bytes);

void* FS_AllocateMemory_Fragment (void);

void FS_DeallocateMemory_Fragment (void* FragmentAddress);

void* FS_AllocateMemory_Pattern (uint32 PatternSize);

void FS_DeallocateMemory_Pattern (void* PatternBaseAddress, uint32 PatternSize);

uint32 FS_GetMemorySize_KiBytes (void);

uint32 FS_GetMemorySize_Fragments (void);

uint32 FS_GetUsedMemorySize_Fragments (void);

uint32 FS_GetFreeMemorySize_Fragments(void);

uint32 FS_GetUsedMemorySize_KiBytes(void);

uint32 FS_GetFreeMemorySize_KiBytes(void);

#ifdef _MSC_VER
#pragma region Declarations
#endif







#ifdef _MSC_VER
#pragma region Macroes
#endif

//Size of sector in bytes...
#define FS_SectorSize_Bytes			512

//Size of memory Fragment in bytes.
#define PMM_MemFragmentSize_Bytes		4096

//Size of memory Fragment in sectors.
#define PMM_MemFragmentSize_Sectors	8

//Memory fragments per fragment (65536/4096)
#define FS_MemFragPerFrag			16

//Each fragment is represented as 1 bit.. so 1 byte represent 8 fragments.
#define FS_FragmentsPerByte			8

//no of bytes per fragment = 64 KiB
#define FS_FragmentSize_Bytes			65536

//no of sectors in each fragment
#define FS_FragmentSize_Sectors		128

//Size of bitmap of memory
#define FS_MemoryMapSize_Bytes		(FS_MemoryMaxSize_Fragments /  FS_FragmentsPerByte)

//Get the fragment certain address corresponds to. Note this formula is right without regards to remainder, as the Address "x" is zero based
//and also fragmnet no. is zero based.
#define GetFargmentOf(x)				(x / FS_FragmentSize_Bytes)

//Get the no of fragments for certain size of pattern "x"
#define GetNoOfFragments(x)			(((x-1) / FS_FragmentSize_Bytes) + 1 )


#define GetNoOfMemFragments(x)		(((x-1) / PMM_MemFragmentSize_Bytes) + 1 )



#ifdef _MSC_VER
#pragma endregion Macroes
#endif








#ifdef _MSC_VER
#pragma region Structures
#endif


struct Partition
{
	uint32 BootIndicator;
	uint32 PartitionType;
	uint32 StartLBA;
	uint32 SectorsNo;
};



struct MBR
{
	uint8 Code [448];
	struct Partition PartitionTable[4];
	uint16 Signature;
};




struct MediaInfo 
{
	char  Name [15];
	char  Extension[5];
	uint32 StartFragment;
	uint32 Length_Bytes;     //<---------We dsigned it as 64, but we need support for aulldiv function in runtime.
};




struct MetaInfo
{
	uint32 MaxSize_Sec;
	uint32 FreeFragments;
};




#ifdef _MSC_VER
#pragma region Structures
#endif









#ifdef _MSC_VER
#pragma region Global variables
#endif

static	uint32	FS_MemoryMaxSize_Sectors			=	0;

static	uint32	FS_MemoryMaxSize_Fragments		=	0;

static	uint32	FS_MemoryUsedSize_Fragments		=	0;

static	uint32*	FS_MemoryMap					=	0;

static	struct MediaInfo RootDirectory [2048]		 ;

static	struct MetaInfo StorageMetaInfo;



#ifdef _MSC_VER
#pragma endregion Global Variables
#endif


#endif