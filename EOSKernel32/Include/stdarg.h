

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
|	*stdarg.h									|
|	*used in var parameter nomber					|
|	*last modified on 13/april/2011				|
|	*Ex:										|
|											|
|		long func(char a, double b, int c, ...)		|
|		{									|
|		}									|
++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



#ifndef	_STDARG_H
#define	_STDARG_H

	
	//The type va_list shall be defined for variables used to traverse the list.
	typedef unsigned char* va_list;
 


	//width of stack is 32-bit => int.
	#define	STACKITEM				int


	//round up width of objects pushed on stack. The expression before the & ensures that we get 0 for objects of size 0.
	#define	VA_SIZE(TYPE)			((sizeof(TYPE) + sizeof(STACKITEM) - 1)& ~(sizeof(STACKITEM) - 1))


	// &(LASTARG) points to the LEFTMOST argument of the function call (before the ...)
	#define	va_start(AP, LASTARG)	(AP=((va_list)&(LASTARG) + VA_SIZE(LASTARG)))


	// nothing for va_end
	#define va_end(AP)


	#define va_arg(AP, TYPE)			(AP += VA_SIZE(TYPE), *((TYPE *)(AP - VA_SIZE(TYPE))))



#endif

