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


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
|	*PIC.c																|
|	*Contains functions requred to interface Programmble Interrupt controller in IA-32	|
|	*last modified on 22/June/2011											|
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


#pragma region includes
#include "PIC.h"
#pragma endregion includes



#ifdef _MSC_VER
#pragma region Private members
#endif

/*
Note:: 
Without __forceinline, the whole code won't work... It seems that PIC needs the command words after each other without calling functions (A_A)
*/

 __forceinline void PIC_SendCommand(uint8 PicNO /*0 or 1*/, uint8 Command)
{

	uint16 Address;

	if (PicNO != 1 && PicNO != 0)  return;

	Address = (PicNO == 0)?  PIC_Ports_Pic0_Command : PIC_Ports_Pic1_Command;

	OutPort(Address, Command);

}


  __forceinline uint8 PIC_ReadStatus(uint8 PicNO)
{

	uint16 Address;

	if (PicNO != 1 && PicNO != 0)  return 0;

	Address = (PicNO == 0)?  PIC_Ports_Pic0_Command : PIC_Ports_Pic1_Command;

	return InPort(Address);

}




 __forceinline void PIC_WriteData(uint8 PicNO, uint8 Data)
{

	uint16 Address;

	if (PicNO != 1 && PicNO != 0)  return;

	Address = (PicNO == 0 )? PIC_Ports_Pic0_Data : PIC_Ports_Pic1_Data;

	OutPort(Address, Data);

}




 __forceinline uint8 PIC_ReadData(uint8 PicNO)
{

	uint16 Address;

	if (PicNO != 1 && PicNO != 0)  return 0;

	Address = (PicNO == 0 )? PIC_Ports_Pic0_Data : PIC_Ports_Pic1_Data;

	return InPort(Address);
	
}

#ifdef _MSC_VER
#pragma endregion Private members
#endif





/*
Note:
Reading the IMR is performed through access port 2.
Writing to the IMR (OCW1)
Sending an EOI (OCW2)
Reading the ISR and IRR (OCW3)
*/

#ifdef _MSC_VER
#pragma region Interface members
#endif

void PIC_Initialize(void)
{
/*goto commands iare used to make delay only as required by some PICs. Function calling here does not make that delay as they are inline (by __forceinline) ;)*/

	//ICW1:::::::>>>>>>>
	//Pic0:
	PIC_SendCommand(0,
		 PIC_ICW1_ICW4_Yes
		|PIC_ICW1_Initialize
		|PIC_ICW1_LTIM_EdgeTriggered
		|PIC_ICW1_SNGL_CascadedPics);
	
	goto A;

	//Pic1:
A:	PIC_SendCommand(1,
		 PIC_ICW1_ICW4_Yes
		|PIC_ICW1_Initialize
		|PIC_ICW1_LTIM_EdgeTriggered
		|PIC_ICW1_SNGL_CascadedPics);

	
	goto B;


	//ICW2::::::>>>>>
	//Pic0:
B:	PIC_WriteData(0, PIC_BaseAddress_Pic1);
	
	goto c;

	//Pic1:
c:	PIC_WriteData(1, PIC_BaseAddress_Pic2);


	goto D;


	//ICW3::::::>>>>>>>>
	//Pic0:
D:	PIC_WriteData(0, 0x04);	//0x00000100	each bit correspond to IRQ pin.
	
	goto E;

	//Pic1:
E:	PIC_WriteData(1, 0x02);	//0x00000010	write the value in ordinary binary!


	goto F;


	//ICW4::::::>>>>>>>>>
	//Pic0:
F:	PIC_WriteData(0,
		 PIC_ICW4_AEOI_ManualEOI
		|PIC_ICW4_BUF_DisBuffer
		|PIC_ICW4_uPM_80x86);

	goto G;

	//Pic1:
G:	PIC_WriteData(1,
		 PIC_ICW4_AEOI_ManualEOI
		|PIC_ICW4_BUF_DisBuffer
		|PIC_ICW4_uPM_80x86);

	goto H;


	//Disable all HW interrupts
H:	PIC_WriteData(0,0xFF);

	goto I;

I:	PIC_WriteData(1,0xFF);

	EnableIRQ(1);
	
}




void DisableIRQ(uint8 IRQNo)
{
	uint8 Data;
	uint8 PIC;

	if (IRQNo > 15) return ;
	
	(IRQNo < 8)? (PIC = 0) : (PIC=1, IRQNo -= 8) ;

	Data = PIC_ReadData(PIC);

	goto A;
A:	PIC_WriteData(PIC, GetMaskDis(IRQNo,Data));
}



void EnableIRQ(uint8 IRQNo)
{
	uint8 Data;
	uint8 PIC;

	if (IRQNo > 15) return ;
	
	(IRQNo < 8)? (PIC=0) : (PIC=1, IRQNo -= 8) ;

	Data = PIC_ReadData(PIC);

	goto A;

A:	PIC_WriteData(PIC, GetMaskEN(IRQNo,Data));
}




void EnableHWInt(void)
{
	_asm sti
}


void DisableHWInt(void)
{
	_asm cli
}

#ifdef _MSC_VER
#pragma endregion Interface members
#endif