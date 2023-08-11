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
|	*IDT.h									|
|	*Contains code for IDT table in IA-32			|
|	*last modified on 09/May/2011					|
++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



#pragma region Includes

#include "IDT.h"
#include "PIC.h"

#pragma endregion   Includes



#pragma region Private



//Structures we will use
static struct IDT_Descriptor		IDT [IDT_Size];
static struct IDT_Register		IDTR;





//This function loads the IDTR register
static void IDT_IdtrSetup(void)
{

#ifdef _MSC_VER

	_asm lidt [IDTR]

#endif

}





void IDT_AddHandler(uint16 IntHandler_Index, uint32 IntHandler_Offset //This is a pointer to IntHandler function
	, uint16 IntHandler_Selector, uint8 IntHandler_Flags)
{
	
	//check that Handling function pointer is not NULL (i.e. =0) nor index is above max value of interrupts
	if ((IntHandler_Index >= (uint16)IDT_Size) || (!IntHandler_Offset)) return;


	//Zeroing the interrupt descriptor first
	memset((void*) &IDT[IntHandler_Index], 0, (size_t) sizeof(IDT[IntHandler_Index]));


	//Assigning values to our interrupt descriptor
	IDT[IntHandler_Index].IDT_Reserved		=	0x0;
	IDT[IntHandler_Index].IDT_Selector		=	IntHandler_Selector;
	IDT[IntHandler_Index].IDT_Flags		=	IntHandler_Flags;
	IDT[IntHandler_Index].IDT_OffsetLS		=	(uint16)(IntHandler_Offset & 0xFFFF);		
	IDT[IntHandler_Index].IDT_OffsetMS		=	(uint16)((IntHandler_Offset >> 16) & 0xFFFF);
	return;

}






ISR void IDT_DefaultHandler(void)
{
	_asm pushad

	EOS_PrintString(" Alhamdo Le ALLAH ............................... :D :D :D ",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}





ISR void ZeroException(void)
{
	_asm pushad

	EOS_PrintString(" Divide by zero Exception ",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}

ISR void Debug(void)
{
	_asm pushad

	EOS_PrintString(" Debug Exception ",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}


ISR void NMI(void)
{
	_asm pushad

	EOS_PrintString(" NMI Exception",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}




ISR void BreakPoint(void)
{
	_asm pushad

	EOS_PrintString(" Break Point Exception",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}





ISR void OverFlow(void)
{
	_asm pushad

	EOS_PrintString(" OverFlow Exception",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}


ISR void Bound(void)
{
	_asm pushad

	EOS_PrintString(" Bound Exception",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}


ISR void InvalidOpcode(void)
{
	_asm pushad

	EOS_PrintString(" Invalid OPCode Exception",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}


ISR void MathCo(void)
{
	_asm pushad

	EOS_PrintString(" Math co processor does  not exist Exception",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}



ISR void DoubleFault(void)
{
	_asm add esp, 4
	_asm pushad

	EOS_PrintString(" Double Fault Exception",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}



ISR void CoprocessorOverrun(void)
{
	_asm pushad

	EOS_PrintString(" Coprocessor overrun Exception",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}


ISR void InvalidTSS(void)
{
	_asm add esp, 4
	_asm pushad

	EOS_PrintString(" Invalid TSS Exception",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}



ISR void SegmentNotPresent(void)
{
	_asm add esp, 4
	_asm pushad

	EOS_PrintString(" SegmentNotPresent Exception",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}




ISR void StackSegmentFault(void)
{
	_asm add esp, 4
	_asm pushad

	EOS_PrintString(" Stack segment fault Exception",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}


ISR void GeneralProtection(void)
{
	_asm add esp, 4
	_asm pushad

	EOS_PrintString(" General Protection Exception",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}



ISR void PageFault(void)
{
	_asm add esp, 4
	_asm pushad

	EOS_PrintString(" Page fault Exception",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}


ISR void FloatError(void)
{
	_asm pushad

	EOS_PrintString(" Float point error Exception",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}



ISR void Allignment(void)
{
	_asm add esp, 4
	_asm pushad

	EOS_PrintString(" Allignment check Exception",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}


ISR void MachineCheck(void)
{
	_asm pushad

	EOS_PrintString(" Machine check Exception",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}


ISR void SIMD(void)
{
	_asm pushad

	EOS_PrintString(" SIMD Exception",0x46, 0x2, 4);	
	
	_asm popad
	_asm iretd
}

#pragma endregion Private









#pragma region interface



void INT_Fn (uint8 n)
/*
This is our interrupt calling function. We change the 0 value by parameter n 
as the int assembly instruction can take just immediate values!! not registers or memory locations
*/
{

#ifdef _MSC_VER

	_asm
	{
		mov al, [n]
		mov byte ptr [INTR +1], al	//op code of INT = 1 byte then 1 byte for imm operand
		jmp INTR
	INTR:
		INT 0
	}
	
#endif

}





void IDT_Setup(void)
//This function used to initialize interrupt table of system !!
{
	
	uint16 i;

		
	//Add default handler for all our 256 handling routines
	for (i =0; i<(uint16)IDT_Size; i++) 
		IDT_AddHandler(i, (uint32) &IDT_DefaultHandler, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);


	IDT_AddHandler(0, (uint32) &ZeroException, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);

	IDT_AddHandler(1, (uint32) &Debug, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);

	IDT_AddHandler(2, (uint32) &NMI, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);

	IDT_AddHandler(3, (uint32) &BreakPoint, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);

	IDT_AddHandler(4, (uint32) &OverFlow, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);

	IDT_AddHandler(5, (uint32) &Bound, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);

	IDT_AddHandler(6, (uint32) &InvalidOpcode, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);

	IDT_AddHandler(7, (uint32) &MathCo, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);

	IDT_AddHandler(8, (uint32) &DoubleFault, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);

	IDT_AddHandler(9, (uint32) &CoprocessorOverrun, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);

	IDT_AddHandler(10, (uint32) &InvalidTSS, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);

	IDT_AddHandler(11, (uint32) &SegmentNotPresent, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);

	IDT_AddHandler(12, (uint32) &StackSegmentFault, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);

	IDT_AddHandler(13, (uint32) &GeneralProtection, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);

	IDT_AddHandler(14, (uint32) &PageFault, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);

	IDT_AddHandler(16, (uint32) &FloatError, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);

	IDT_AddHandler(17, (uint32) &Allignment, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);

	IDT_AddHandler(18, (uint32) &MachineCheck, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);

	IDT_AddHandler(19, (uint32) &SIMD, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);


	//Setting values of IDTR
	IDTR.IDT_Base	=	(uint32) &IDT[0];
	IDTR.IDT_Limit =	(uint16) (((sizeof(struct IDT_Descriptor)) * ((uint16)IDT_Size)) -1); 
	//Limit of idt in bytes. we minus 1 as the first byte is base eitself->last byte = base + limit ;)





	//Loading the IDTR
	IDT_IdtrSetup();

}



#pragma endregion interface