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



#include <TextDisplay.h>
#include <Drivers_EIDE.h>

extern	void GDT_Setup(void);
extern	void IDT_Setup(void);
void		main(void);
extern	void PIC_Initialize(void);
extern	void InitializeKeyboard(void);
extern	void TryFS(void);
/*
This PROC is for initializing environment of 32-bit kernel start main() PROC
*/
void Kernel_Entry(void)
{
	//This part is architecture dependent.
	#ifdef TargetMachine_IA32
		_asm 
		{
			cli						
			mov ax, 10h				// offset 0x10 in gdt for data selector(As sat up in boot loader.)
			mov ds, ax
			mov es, ax
			mov fs, ax
			mov gs, ax
			mov ss, ax				// Set up 32-bit kernel stack
			mov esp, 0x90000
			push ebp
		}
	#endif

	
	main();
}




void main(void)
{
	//uint8 aa;


	GDT_Setup();
	IDT_Setup();
	PIC_Initialize();
	InitializeKeyboard();
	

	EOS_ClearScrean (0xF0);
	EOS_ClearHeader (0x40);
	EOS_ClearTrailer(0x00);

	EOS_PrintString(" Lotus Operating System",								0x4f,	0,		0);
	EOS_PrintString(" Ready",											0x0F,	0x0,		24);
	EOS_PrintString(" Lotus Terminal#",									0xF0,	0,		1);
	_asm sti


	InitializeHDD();
	TryFS();

	for(;;);


#ifdef TargetMachine_IA32
	_asm
	{
		hlt
	}
#endif
	

}