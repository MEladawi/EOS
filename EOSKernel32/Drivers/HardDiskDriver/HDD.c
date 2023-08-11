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
|	*HDD.C									|
|	*This module deals with EIDE(ATA|PATA) HDDs		|
|	*last modified on 14/July/2011				|
++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


#include "HDD.h"
#include <TextDisplay.h>



/*Private###########################################################################################*/

uint8	HDD_Test_IDEPrimaryChannel (void)
{
	uint8 TestByte;

	OutPortByte(HDD_Ports_Prim_SectorCount, 0x20);
	TestByte = InPortByte(HDD_Ports_Prim_SectorCount);

	if (TestByte == 0x20) return HDD_Channels_Prim;
	
	return 0;
}





uint8	HDD_Test_IDESecondaryChannel (void)
{
	uint8 TestByte;

	OutPortByte(HDD_Ports_Sec_SectorCount, 0x20);
	TestByte = InPortByte(HDD_Ports_Sec_SectorCount);

	if (TestByte == 0x20) return HDD_Channels_Sec;
	
	return 0;
}





uint8	HDD_Test_IDEPrimDevices(void)
{
	uint8 TestByte;
	register uint8 i;

	OutPortByte(HDD_Ports_Prim_DriveLBA4, 
		 HDD_DriveLBA4_Constant
		|HDD_DriveLBA4_Driver_Master
		|HDD_DriveLBA4_LBA);
	
	for(i=0; i<6; i++)
		TestByte =InPortByte(HDD_Ports_Prim_StatusRegister);
	
	TestByte = InPortByte(HDD_Ports_Prim_StatusRegister);

	if (TestByte & HDD_Status_Ready) return HDD_Devices_Prim_Master;



	OutPortByte(HDD_Ports_Prim_DriveLBA4,
		 HDD_DriveLBA4_Constant
		|HDD_DriveLBA4_Driver_Slave
		|HDD_DriveLBA4_LBA);

	for(i=0; i<6; i++)
		TestByte =InPortByte(HDD_Ports_Prim_StatusRegister);

	TestByte = InPortByte(HDD_Ports_Prim_StatusRegister);

	if (TestByte & HDD_Status_Ready) return HDD_Devices_Prim_Slave;


	return 0;
}




uint8	HDD_Test_IDESecDevices(void)
{
	uint8 TestByte;
	register uint8 i;


	OutPortByte(HDD_Ports_Sec_DriveLBA4,
		 HDD_DriveLBA4_Constant
		|HDD_DriveLBA4_Driver_Master
		|HDD_DriveLBA4_LBA);

	for(i=0; i<6; i++)
		TestByte =InPortByte(HDD_Ports_Sec_StatusRegister);
	
	TestByte = InPortByte(HDD_Ports_Sec_StatusRegister);

	if (TestByte & HDD_Status_Ready) return HDD_Devices_Sec_Master;



	OutPortByte(HDD_Ports_Sec_DriveLBA4,
		 HDD_DriveLBA4_Constant
		|HDD_DriveLBA4_Driver_Slave
		|HDD_DriveLBA4_LBA);

	for(i=0; i<6; i++)
		TestByte =InPortByte(HDD_Ports_Sec_StatusRegister);
	
	TestByte = InPortByte(HDD_Ports_Sec_StatusRegister);

	if (TestByte & HDD_Status_Ready) return HDD_Devices_Sec_Slave;


	return 0;
}



void	HDD_SelectDrive(void)
{
	uint8 TestByte = 0;
	uint8 TestDevice = 0;

	TestByte = HDD_Test_IDEPrimaryChannel();
	
	if(TestByte == HDD_Channels_Prim)
	{
		TestDevice = HDD_Test_IDEPrimDevices();
		if (TestDevice != 0)
		{
			ConnectedHDD.DeviceConnected	= 1;
			ConnectedHDD.DataRegisterPort = HDD_Ports_Prim_DataRegister;
			ConnectedHDD.DeviceLBA4Port	= HDD_Ports_Prim_DriveLBA4;
			ConnectedHDD.LBA1Port		= HDD_Ports_Prim_LBA1;
			ConnectedHDD.LBA2Port		= HDD_Ports_Prim_LBA2;
			ConnectedHDD.LBA3Port		= HDD_Ports_Prim_LBA3;
			ConnectedHDD.SectorCountPort	= HDD_Ports_Prim_SectorCount;
			ConnectedHDD.StatusCommandPort= HDD_Ports_Prim_CommandRegister;
			return;
		}
	}



	TestByte = HDD_Test_IDESecondaryChannel();

	if(TestByte == HDD_Channels_Sec)
	{
		TestDevice = HDD_Test_IDESecDevices();
		if (TestDevice != 0) 
		{
			ConnectedHDD.DeviceConnected	= 1;
			ConnectedHDD.DataRegisterPort = HDD_Ports_Sec_DataRegister;
			ConnectedHDD.DeviceLBA4Port	= HDD_Ports_Sec_DriveLBA4;
			ConnectedHDD.LBA1Port		= HDD_Ports_Sec_LBA1;
			ConnectedHDD.LBA2Port		= HDD_Ports_Sec_LBA2;
			ConnectedHDD.LBA3Port		= HDD_Ports_Sec_LBA3;
			ConnectedHDD.SectorCountPort	= HDD_Ports_Sec_SectorCount;
			ConnectedHDD.StatusCommandPort= HDD_Ports_Sec_CommandRegister;
			return;
		}
	}
	
}



uint32 GetHDDSize(void)
{
	uint32 j;
	uint32 MAXLBA;
	uint16 ReadBuffer[256];
	uint32 i;


	for (j=0; j<6; j++) InPortByte (ConnectedHDD.StatusCommandPort);

	//Make sure device ready to take command!
	while (InPortByte(ConnectedHDD.StatusCommandPort) & HDD_Status_Busy);

	//Send Identify command
	OutPortByte (ConnectedHDD.StatusCommandPort, HDD_Command_IdentifyDevice);
		while (																
			   (InPortByte(ConnectedHDD.StatusCommandPort) & (HDD_Status_Busy))			
			 |!(InPortByte(ConnectedHDD.StatusCommandPort) & (HDD_Status_DataRequest))		
			 );

	//Repeat the next for all data WORDs((sector(512) /2) * count of sectors)		<-----------|	
	for (i=0; i< 1; i++)														//|
	{																		//|
																			//|
		//Wait to read the data (Status we wrote above) for every sector only.			//|
		while (																//|
			   (InPortByte(ConnectedHDD.StatusCommandPort) & (HDD_Status_Busy))			//|
			 |!(InPortByte(ConnectedHDD.StatusCommandPort) & (HDD_Status_DataRequest))		//|
			 );																//|
																			//|------> This is what we call POLLING ;)
		for (j=0; j < HDD_SectorSize_Words; j++)									//|
		{																	//|
																			//|
		//Read a word to buffer													//|
		ReadBuffer[j]=InPortWord(ConnectedHDD.DataRegisterPort);						//|
		}																	//|
																			//|
	//Repeat																	//|
	}																//<---------|	


	MAXLBA  = (uint32)ReadBuffer[60];
	MAXLBA |= (((uint32)ReadBuffer[61]) << 16);

	return MAXLBA ;

}




/*Private###############################################################################################*/




/*
>>>>>>>Note:Important notes in algorithms design<<<<<<<<<<

When to R/W data buffer?
-If the IDE not busy and data buffer request is set. (HDD_Status_NotBusy and HDD_Status_DataRequest.)
When to send coomand?
-If the IDE is not busy nor data buffer request set. (HDD_Status_NotBusy and HDD_Status_NoDataRequest.)
When we know we have IDE device?
-If (after selecting it and wait 400 nano seconds) its reday signal is set.
When we know that we have IDE channel?
-If we write any value to any read/write registers and then read it and fount it same value we pust.


When we need to wait?
-Before sending command. (to get status above.)
-before reading/writing data. (until we get status above.)
-After selecting device: wemust wait 400 nano seconds before checking the status.(This is done by reading the status register 5 times before checking its value.)
*/






/*Public#################################################################################################*/

void		HDD_ReadSectors (uint32 LBA, uint32 SectorsCount, uint16* ReadBuffer)
{
	uint32 register i;
	uint32 register j;
	uint32 register BufferIndex = 0;

	if (!ConnectedHDD.DeviceConnected) return;

	
	//Set Sector Count
	OutPortByte (ConnectedHDD.SectorCountPort, (uint8)SectorsCount);

	
	//Set LBA address 1
	OutPortByte (ConnectedHDD.LBA1Port,  (uint8)(LBA	& 0x000000FF));

	
	//Set LBA address 2
	OutPortByte (ConnectedHDD.LBA2Port,  (uint8)((LBA	& 0x0000FF00) >> 8));

	
	//Set LBA address 3
	OutPortByte (ConnectedHDD.LBA3Port,  (uint8)((LBA	& 0x00FF0000) >> 16));


	//Set LBA address 4 (device already selected in selecting device, this decrease time of reading and writing very much!)
	OutPortByte (ConnectedHDD.DeviceLBA4Port, (((InPortByte(ConnectedHDD.DeviceLBA4Port)) & 0xF0)|HDD_GetLeast4LBA(LBA)) );

	
	for (i=0; i<5; i++){InPortByte(ConnectedHDD.StatusCommandPort);}


	//Make sure device ready to take command!
	while (InPortByte(ConnectedHDD.StatusCommandPort) & HDD_Status_Busy);

	
	//Send read command
	OutPortByte (ConnectedHDD.StatusCommandPort, HDD_Command_Read_Basic);

		while (																
			   (InPortByte(ConnectedHDD.StatusCommandPort) & (HDD_Status_Busy))			
			 |!(InPortByte(ConnectedHDD.StatusCommandPort) & (HDD_Status_DataRequest))		
			 );

	//Repeat the next for all data WORDs((sector(512) /2) * count of sectors)		<-----------|	
	for (i=0; i< SectorsCount; i++)												//|
	{																		//|
																			//|
		//Wait to read the data (Status we wrote above) for every sector only.			//|
		while (																//|
			   (InPortByte(ConnectedHDD.StatusCommandPort) & (HDD_Status_Busy))			//|
			 |!(InPortByte(ConnectedHDD.StatusCommandPort) & (HDD_Status_DataRequest))		//|
			 );																//|
																			//|------> This is what we call POLLING ;)
		for (j=0; j < HDD_SectorSize_Words; j++, BufferIndex++)						//|
		{																	//|
																			//|
		//Read a word to buffer													//|
		ReadBuffer[BufferIndex]=InPortWord(ConnectedHDD.DataRegisterPort);				//|
		}																	//|
																			//|
	//Repeat																	//|
	}																//<---------|	

}







void		HDD_WriteSectors (uint32 LBA, uint32 SectorsCount, uint16* WriteBuffer)
{
	uint32 register i;
	uint32 register j;
	uint32 register BufferIndex = 0;

	if (!ConnectedHDD.DeviceConnected) return;

	
	//Set Sector Count
	OutPortByte (ConnectedHDD.SectorCountPort, (uint8)SectorsCount);

	
	//Set LBA address 1
	OutPortByte (ConnectedHDD.LBA1Port,  (uint8)(LBA	& 0x000000FF));

	
	//Set LBA address 2
	OutPortByte (ConnectedHDD.LBA2Port,  (uint8)((LBA	& 0x0000FF00) >> 8));

	
	//Set LBA address 3
	OutPortByte (ConnectedHDD.LBA3Port,  (uint8)((LBA	& 0x00FF0000) >> 16));


	//Set LBA address 4 (device already selected in selecting device, this decrease time of reading and writing very much!)
	OutPortByte (ConnectedHDD.DeviceLBA4Port, (((InPortByte(ConnectedHDD.DeviceLBA4Port)) & 0xF0)|HDD_GetLeast4LBA(LBA)) );

	
	for (i=0; i<5; i++){InPortByte(ConnectedHDD.StatusCommandPort);}


	//Make sure device ready to take command!
	while (InPortByte(ConnectedHDD.StatusCommandPort) & HDD_Status_Busy);

	
	//Send Write command
	OutPortByte (ConnectedHDD.StatusCommandPort, HDD_Command_Write_Basic);

		while (																
			   (InPortByte(ConnectedHDD.StatusCommandPort) & (HDD_Status_Busy))			
			 |!(InPortByte(ConnectedHDD.StatusCommandPort) & (HDD_Status_DataRequest))		
			 );

	//Repeat the next for all data WORDs((sector(512) /2) * count of sectors)		<-----------|	
	for (i=0; i < SectorsCount; i++)												//|
	{																		//|
																			//|
		//Wait to Write the data (Status we wrote above) for every sector only.			//|
		while (																//|
			   (InPortByte(ConnectedHDD.StatusCommandPort) & (HDD_Status_Busy))			//|------> Also we POLL here.
			 |!(InPortByte(ConnectedHDD.StatusCommandPort) & (HDD_Status_DataRequest))		//|
			 );																//|
																			//|
		for (j=0; j < HDD_SectorSize_Words; j++, BufferIndex++)						//|
		{																	//|
																			//|
		//Write a word from buffer												//|
		OutPortWord (ConnectedHDD.DataRegisterPort, WriteBuffer[BufferIndex]);			//|
		}																	//|
																			//|
	//Repeat																	//|
	}																//<---------|	

}



void InitializeHDD(void)
{	
	HDD_SelectDrive();
	MaxLBA = GetHDDSize();
}

/*Public###################################################################################################*/






