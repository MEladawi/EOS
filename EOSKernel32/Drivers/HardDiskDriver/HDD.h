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
|	*HDD.h									|
|	*Private for HDD.C only						|
|	*last modified on 1/July/2011					|
++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifndef HDD_H
#define HDD_H



#ifdef _MSC_VER
#pragma region Includes
#endif

#include <stdint.h>
#include <MemMappedIO-IA32.h>

#ifdef _MSC_VER
#pragma endregion Includes
#endif




#ifdef _MSC_VER
#pragma region Declarations
#endif

uint8	HDD_Test_IDEPrimaryChannel		(void);

uint8	HDD_Test_IDESecondaryChannel		(void);

uint8	HDD_Test_IDEPrimDevices			(void);

uint8	HDD_Test_IDESecDevices			(void);

void 	HDD_SelectDrive				(void);

void		HDD_ReadSectors				(uint32 LBA, uint32 SectorsCount, uint16* ReadBuffer);

void		HDD_WriteSectors				(uint32 LBA, uint32 SectorsCount, uint16* WriteBuffer);

uint32	MaxLBA;

#ifdef _MSC_VER
#pragma endregion Declarations
#endif






#ifdef _MSC_VER
#pragma region Macroes
#endif

#ifdef TargetMachine_IA32	//These ports addresses are specific for IA32 only.


/*
The Primary IDE channel Devices----------------------------------------------
*/

#define	HDD_Ports_Prim_DataRegister		0x1F0	//	16bit	W/R

#define	HDD_Ports_Prim_ErrorRegister		0x1F1	//	8bit		R
#define	HDD_Ports_Prim_Precompensation	0x1F1	//	8bit		W

#define	HDD_Ports_Prim_SectorCount		0x1F2	//	8bit		W/R

#define	HDD_Ports_Prim_LBA1				0x1F3	//	8bit		W/R	**Least significant of LBA address

#define	HDD_Ports_Prim_LBA2				0x1F4	//	8bit		W/R

#define	HDD_Ports_Prim_LBA3				0x1F5	//	8bit		W/R

#define	HDD_Ports_Prim_DriveLBA4			0x1F6	//	8bit		W/R

#define	HDD_Ports_Prim_StatusRegister		0x1F7	//	8bit		R
#define	HDD_Ports_Prim_CommandRegister	0x1F7	//	8bit		W

#define	HDD_Ports_Prim_AltStatusRegister	0x3F6	//	8bit		R
#define	HDD_Ports_Prim_DigitalOutRegister	0x3F6	//	8bit		W

#define	HDD_Ports_Prim_DriveAddress		0x3F7	//	8bit		W/R

//-----------------------------------------------------------------------------





/*
The secondary IDE channel Devices--------------------------------------------------------
*/

#define	HDD_Ports_Sec_DataRegister		0x170	//	16bit	W/R

#define	HDD_Ports_Sec_ErrorRegister		0x171	//	8bit		R
#define	HDD_Ports_Sec_Precompensation		0x171	//	8bit		W

#define	HDD_Ports_Sec_SectorCount		0x172	//	8bit		W/R

#define	HDD_Ports_Sec_LBA1				0x173	//	8bit		W/R	**Least significant part of LBA address

#define	HDD_Ports_Sec_LBA2				0x174	//	8bit		W/R

#define	HDD_Ports_Sec_LBA3				0x175	//	8bit		W/R

#define	HDD_Ports_Sec_DriveLBA4			0x176	//	8bit		W/R

#define	HDD_Ports_Sec_StatusRegister		0x177	//	8bit		R
#define	HDD_Ports_Sec_CommandRegister		0x177	//	8bit		W

#define	HDD_Ports_Sec_AltStatusRegister	0x376	//	8bit		R
#define	HDD_Ports_Sec_DigitalOutRegister	0x376	//	8bit		W

#define	HDD_Ports_Sec_DriveAddress		0x377	//	8bit		W/R

//----------------------------------------------------------------------------------
#endif




/*Definitions for DriveLBA4------------------------------------*/

//The Constant part in drive head value. Should always be used
#define	HDD_DriveLBA4_Constant		0xA0

//Use LBA addressing scheme
#define	HDD_DriveLBA4_LBA			0x40
//Use CHS addressing scheme
#define	HDD_DriveLBA4_CHS			0x0

//Use master drive of the channel
#define	HDD_DriveLBA4_Driver_Master	0x0
//Use slave drive of the channel
#define	HDD_DriveLBA4_Driver_Slave	0x10

//Macro to get MS 4 bits of LBA address.
#define	HDD_GetLeast4LBA(x)			((x >> 24) & 0x0F)

//-----------------------------------------------------------------






/*Definitions for status register----------------------------*/

//The driver is busy
#define	HDD_Status_Busy			0x80
//Driver is not busy
#define	HDD_Status_NotBusy			0x00

//The driver is Ready
#define	HDD_Status_Ready			0x40
//The driver is NOT ready
#define	HDD_Status_NotReady			0x00

//Drive encountered write fault
#define	HDD_Status_DeviceFault		0x20

//Seek operation is complete
#define	HDD_Status_SeekComplete		0x10
//Seek operation is in progress
#define	HDD_Status_SeekInProgress	0x00

//The data buffer of HDD is ready to write/read
#define	HDD_Status_DataRequest		0x08
//The data buffer of HDD is NOT ready to write/read
#define	HDD_Status_NoDataRequest		0x00

//Error occurred in last command operation
#define	HDD_Status_Error			0x01
//No error occuring now
#define	HDD_Status_NoError			0x00
//------------------------------------------------------------






/*Definitions for controlling-----------------------------------------*/

//Needs drive only
#define	HDD_Command_Calibrate		0x10		


/*
Needs:
-Sectors count
-Drive
-LBA
*/
#define	HDD_Command_Read_Basic		0x20
#define	HDD_Command_Read_WithECC		0x02
#define	HDD_Command_Read_AutoRep		0x01


/*
Needs:
-Sectors count
-Drive
-LBA
*/
#define	HDD_Command_Write_Basic		0x30
#define	HDD_Command_Write_WithECC	0x02
#define	HDD_Command_Write_AutoRep	0x01


/*
Flush the cache
*/
#define	HDD_Command_Write_FlushCache	0xE7


/*
Identify the device
*/
#define	HDD_Command_IdentifyDevice	0xEC

//--------------------------------------------------------------------



//General----------------------------------------------------------------------

//Sector Size in words
#define	HDD_SectorSize_Words		256	//sector is 512 and word in 2 -> 512/2 :D


/*The next numbers are not descriptive, just used for comparisons*/

//Primary IDE channel
#define	HDD_Channels_Prim			0x10

//Secondary IDE channel
#define	HDD_Channels_Sec			0x20

//Primary channel master device
#define	HDD_Devices_Prim_Master		0x11

//primary channel slave device
#define	HDD_Devices_Prim_Slave		0x12

//Secondary channel master device
#define	HDD_Devices_Sec_Master		0x21

//Secondary channel slave device
#define	HDD_Devices_Sec_Slave		0x22


//-----------------------------------------------------------------------------




//------------------------------------------------------------------------------

//This is the data we use in reading and writing as we don't know which device is connected.
struct AbstractHDD
{
	uint8  DeviceConnected;//?
	uint16 DataRegisterPort;
	uint16 SectorCountPort;
	uint16 LBA1Port;
	uint16 LBA2Port;
	uint16 LBA3Port;
	uint16 DeviceLBA4Port;
	uint16 StatusCommandPort;
}ConnectedHDD = {0, 0, 0, 0, 0, 0, 0, 0};
//------------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma endregion Macroes
#endif

#endif