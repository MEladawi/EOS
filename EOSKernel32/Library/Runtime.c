
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



//+++++++++This module is used instead of run time library of windows (that we disabled) to get suuport for floating points numbers. NO interface headers+++++++++++





//This to make sure that we are in x86 :D, as EOS may support others!! May be in next time ;)
#ifndef X86_Dependent
#define X86_Dependent
#endif




extern float __declspec(naked) _CIcos(void)
{
#ifdef X86_Dependent
   _asm fcos
#endif
};


extern float __declspec(naked) _CIsin(void) 
{
#ifdef X86_Dependent
   _asm fsin
#endif
};


extern float __declspec(naked) _CIsqrt(void)
{
#ifdef X86_Dependent
   _asm fsqrt
#endif
};


// called by MSVC++ for casting between float and int types.
extern long __declspec (naked) _ftol2_sse(void) 
{
	int a;
#ifdef X86_Dependent
 
	_asm {
		fistp [a]
		mov	ebx, a
	}
#endif
}


// To support floating point operations.
extern int _fltused = 1;
