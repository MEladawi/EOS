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


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
|	*PIC.h											|
|	*Contains (private) definitions for PIC.C and IDT.c only!	|
|	*last modified on 04/July/2011						|
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#ifndef _PIC_H
#define _PIC_H




#ifdef _MSC_VER
#pragma region Includes
#endif

#include <stdint.h>
#include "MemoryMappedIO.h"

#ifdef _MSC_VER
#pragma endregion Indludes
#endif





#ifdef _MSC_VER
#pragma region FunctionsProtoypes
#endif

void	PIC_SendCommand(uint8 PicNO /*0 or 1*/, uint8 Command);
uint8 PIC_ReadStatus(uint8 PicNO);
void PIC_WriteData(uint8 PicNO, uint8 Data);
uint8 PIC_ReadData(uint8 PicNO);
void DisableIRQ(uint8 IRQNo);
void EnableIRQ(uint8 IRQNo);
void DisableHWInt(void);
void EnableHWInt(void);

#ifdef _MSC_VER
#pragma endregion FunctionsProtoypes
#endif






#ifdef _MSC_VER
#pragma region Macroes
#endif
/*|||||||--Some bits are not mentioned as they are either reserved or not used for x86--||||||||*/


/*Initialization Command Words------------------------------------------------------------------------------------------------------*/

/*
There are four initialization commands (ICW1-4), always generated in sequence. 
The first goes to access port 1 and the rest to port 2. 
Note that the PIC distinguishes between ICWs and OCWs both by the setting of various bits in the commands, and by which port the command is sent to.
*/

/*+++++++++++++++++++++++++++++++Definitions of ICW1+++++++++++++++++++++++++++++*/
#define PIC_ICW1_ICW4_Yes			0x1
#define PIC_ICW1_ICW4_No				0x0

#define PIC_ICW1_SNGL_OnePic			0x2
#define PIC_ICW1_SNGL_CascadedPics		0x0

#define PIC_ICW1_LTIM_LevelTriggered	0x8
#define PIC_ICW1_LTIM_EdgeTriggered	0x0

#define PIC_ICW1_Initialize			0x10
#define PIC_ICW1_DontInitialize		0x0
/*++++++++++++++++++++++++++++End of Definitions of ICW1++++++++++++++++++++++++++*/






/*+++++++++++++++++++++++++++++++Definitions of ICW2+++++++++++++++++++++++++++++*/
//Not needed
/*++++++++++++++++++++++++++++End of Definitions of ICW2++++++++++++++++++++++++++*/






/*+++++++++++++++++++++++++++++++Definitions of ICW3+++++++++++++++++++++++++++++*/
//Not needed
/*++++++++++++++++++++++++++++End of Definitions of ICW3++++++++++++++++++++++++++*/





/*+++++++++++++++++++++++++++++++Definitions of ICW4+++++++++++++++++++++++++++++*/
#define PIC_ICW4_uPM_80x86			0x1
#define PIC_ICW4_uPM_MCS				0x0

#define PIC_ICW4_AEOI_AutoEOI			0x2
#define PIC_ICW4_AEOI_ManualEOI		0x0

#define PIC_ICW4_MS_BufferMaster		0x4
#define PIC_ICW4_MS_BufferSlave		0x0

#define PIC_ICW4_BUF_EnBuffer			0x8
#define PIC_ICW4_BUF_DisBuffer		0x0
/*++++++++++++++++++++++++++++End of Definitions of ICW4++++++++++++++++++++++++++*/

/*Initialization Command Words------------------------------------------------------------------------------------------------------*/






/*OPERATION Command Words--------------------------------------------------------------------------------------------------------------*/

/*+++++++++++++++++++++++++++++++Definitions of OCW1+++++++++++++++++++++++++++++*/

/*
Not:
OCW1 is used to change the value of the IMR (interrupt mask register). 
To perform an OCW1, simply write the new value of the IMR @ port 2.
*/

/*++++++++++++++++++++++++++++End of Definitions of OCW1++++++++++++++++++++++++++*/




/*+++++++++++++++++++++++++++++++Definitions of OCW2+++++++++++++++++++++++++++++*/

/*
Note:
The OCW2 command is how an EOI (end-of-interrupt) is issued to the PIC by the CPU. 
This must be done explicitly by code in the interrupt handler; it is not automatic.
Before the handler returns, it should therefore send an OCW2 to just PIC#1 (for IRQs 0 - 7) or to both PIC#2 and PIC#1 (for IRQs 8 - 15). 
In this latter case, because of the cascade arrangement, an interrupt has effectively been generateed by both PICs.
*/

#define PIC_OCW2_Level_L0					0x0
#define PIC_OCW2_Level_L1					0x1
#define PIC_OCW2_Level_L2					0x2
#define PIC_OCW2_Level_L3					0x3
#define PIC_OCW2_Level_L4					0x4
#define PIC_OCW2_Level_L5					0x5
#define PIC_OCW2_Level_L6					0x6
#define PIC_OCW2_Level_L7					0x7

#define PIC_OCW2_Commands_RotInAutoEOIClr		0x0
#define PIC_OCW2_Commands_NonSpecEOI			0x20		//This is what we use really :D, other for completeness only!!
#define PIC_OCW2_Commands_NoOperation			0x40
#define PIC_OCW2_Commands_SpecEOI				0x60
#define PIC_OCW2_Commands_RotInAutoEOISet		0x80
#define PIC_OCW2_Commands_RotInNonSpecEOI		0x100
#define PIC_OCW2_Commands_SetPriority			0x120
#define PIC_OCW2_Commands_RotInSpecEOI			0x140
/*++++++++++++++++++++++++++++End of Definitions of OCW2++++++++++++++++++++++++++*/



/*+++++++++++++++++++++++++++++++Definitions of OCW3+++++++++++++++++++++++++++++*/

/*
An OCW3 is used to read the ISR and IRR. 
The command is issued (to access port 1), indicating which register value is required, and the read is then performed from access port 1.
*/

/*++++++++++++++++++++++++++++End of Definitions of ICW3++++++++++++++++++++++++++*/

/*Control Command Words--------------------------------------------------------------------------------------------------------------*/







/*Ports Adresses--------------------------------------------------------------------------------------------------------------*/

/*++++++++++++++++++Pic0+++++++++++++++*/
#define PIC_Ports_Pic0_Command		0x20
#define PIC_Ports_Pic0_Status			0x20
#define PIC_Ports_Pic0_Data			0x21
#define PIC_Ports_Pic0_IMR			0x21
/*++++++++++++++++++Pic0+++++++++++++++*/


/*++++++++++++++++++Pic1+++++++++++++++*/
#define PIC_Ports_Pic1_Command		0xA0
#define PIC_Ports_Pic1_Status			0xA0
#define PIC_Ports_Pic1_Data			0xA1
#define PIC_Ports_Pic1_IMR			0xA1
/*++++++++++++++++++Pic1+++++++++++++++*/

/*Ports Adresses--------------------------------------------------------------------------------------------------------------*/







/*Devices IR Lines--------------------------------------------------------------------------------------------------------------*/

/*++++++++++++++++++Pic0+++++++++++++++*/
#define PIC_IRQ_Devices_Timer			32
#define PIC_IRQ_Devices_Keyboard		33
#define PIC_IRQ_Devices_SlavePic		34
#define PIC_IRQ_Devices_SerialPort1	35
#define PIC_IRQ_Devices_SerialPort2	36
#define PIC_IRQ_Devices_Reserved1		37
#define PIC_IRQ_Devices_Diskette		38
#define PIC_IRQ_Devices_ParallelPort1	39
/*++++++++++++++++++Pic0+++++++++++++++*/


/*++++++++++++++++++Pic1+++++++++++++++*/
#define PIC_IRQ_Devices_CmosClock		40
#define PIC_IRQ_Devices_CGA			41
#define PIC_IRQ_Devices_Reserved2		42
#define PIC_IRQ_Devices_Reserved3		43
#define PIC_IRQ_Devices_Auxiliary		44
#define PIC_IRQ_Devices_FPU			45
#define PIC_IRQ_Devices_HardDisk		46
#define PIC_IRQ_Devices_Reserved4		47
/*++++++++++++++++++Pic1+++++++++++++++*/

/*Devices IR Lines--------------------------------------------------------------------------------------------------------------*/



/*Base addresses of pics--------------------------------------------------------------------------------------------------------------*/

#define PIC_BaseAddress_Pic1			32
#define PIC_BaseAddress_Pic2			40

/*Base addresses of pics--------------------------------------------------------------------------------------------------------------*/


/*Masks macroes***********************************/
#define GetMaskDis(IRQ, Data)	((0x01<<IRQ) | (Data))
#define GetMaskEN(IRQ, Data)	((~(0x01<<IRQ)) & (Data))
/**************************************************/

#ifdef _MSC_VER
#pragma endregion Macroes			
#endif

#endif