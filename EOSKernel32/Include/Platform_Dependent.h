
#include <stdint.h>

extern  void IDT_AddHandler(uint16 IntHandler_Index, uint32 IntHandler_Offset //This is a pointer to IntHandler function
	, uint16 IntHandler_Selector, uint8 IntHandler_Flags);

extern __forceinline void IntPrologue(uint8 IntNo);

extern __forceinline void IntEpilogue(uint8 IntNo);

extern void INT_Fn (uint8 n);

extern void IDT_Setup(void);

#define	ISR					__declspec( naked )	



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



/********the interrupt descriptor flags************/

//The default (11 binary) bits at 9-10 
#define	IDT_Flags_Default		0x06

//The D bit at 11
#define	IDT_Flags_32Bit		0x08

//DPL bits at 13-14
#define	IDT_Flags_ApplicationDPL	0x60

//The present bit at 15
#define	IDT_Flags_Present		0x80

/********End interrupt descriptor flags************/