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

#ifndef PMM_H
#define PMM_H




#ifdef _MSC_VER
#pragma region Includes
#endif

#include <stdint.h>
#include <String.h>

#ifdef _MSC_VER
#pragma endregion Includes
#endif





#ifdef _MSC_VER
#pragma region Declarations
#endif

void PMM_MemoryMap_SetFragmentBit(int32 FragmentNo);

void PMM_MemoryMap_ClrFragmentBit(int32 FragmentNo);

Bool PMM_MemoryMap_TestFragmentBit(int32 FragmentNo);

int32 PMM_MemoryMap_GetFirstFreeFragment (void);

int32 PMM_MemoryMap_GetFirstFreePattern (uint32 PatternSize_Fragment);

void PMM_Setup(uint32 MemorySize_KiByte, void* MemoryMapAddress);

void PMM_ClrPatternBits (void* PatternBaseAddress, uint32 PatternSize_Byte);

void PMM_SetPatterBits (void* PatternBaseAddress, uint32 PatternSize_Bytes);

void* PMM_AllocateMemory_Fragment (void);

void PMM_DeallocateMemory_Fragment (void* FragmentAddress);

void* PMM_AllocateMemory_Pattern (uint32 PatternSize);

void PMM_DeallocateMemory_Pattern (void* PatternBaseAddress, uint32 PatternSize);

uint32 PMM_GetMemorySize_KiBytes (void);

uint32 PMM_GetMemorySize_Fragments (void);

uint32 PMM_GetUsedMemorySize_Fragments (void);

uint32 PMM_GetFreeMemorySize_Fragments(void);

uint32 PMM_GetUsedMemorySize_KiBytes(void);

uint32 PMM_GetFreeMemorySize_KiBytes(void);

#ifdef _MSC_VER
#pragma region Declarations
#endif







#ifdef _MSC_VER
#pragma region Macroes
#endif

//Each fragment is represented as 1 bit.. so 1 byte represent 8 fragments.
#define PMM_FragmentsPerByte			8

//no of bytes per fragment = 4 KiB
#define PMM_FragmentSize_Bytes		4096

//Size of bitmap of memory
#define PMM_MemoryMapSize_Bytes		(PMM_MemoryMaxSize_Fragments /  PMM_FragmentsPerByte)

//Get the fragment certain address corresponds to. Note this formula is right without regards to remainder, as the Address "x" is zero based
//and also fragmnet no. is zero based.
#define GetFargmentOf(x)				(x / PMM_FragmentSize_Bytes)

//Get the no of fragments for certain size of pattern "x"
#define GetNoOfFragments(x)			(((x-1) / PMM_FragmentSize_Bytes) +1 )

#ifdef _MSC_VER
#pragma endregion Macroes
#endif






#ifdef _MSC_VER
#pragma region Global variables
#endif

static	uint32	PMM_MemoryMaxSize_KiBytes		=	0;

static	uint32	PMM_MemoryMaxSize_Fragments		=	0;

static	uint32	PMM_MemoryUsedSize_Fragments		=	0;

static	uint32*	PMM_MemoryMap					=	0;

#ifdef _MSC_VER
#pragma endregion Global Variables
#endif


#endif