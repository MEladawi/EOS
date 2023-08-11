


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
|	*ctype.h									|
|	*general operations on characters				|	
|	*To facilitate working with characters only		|
|	*last modified on 13/april/2011				|
++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


#ifndef	_CTYPE_H
#define	_CTYPE_H

	// In Case of using VC get disable conversion warnings
	#ifdef _MSC_VER
	#pragma warning (disable:4244)
	#endif



	extern char _ctype[];



	/*++++ Constants ++++*/

	#define	CT_UP	0x01		/* upper case */
	#define	CT_LOW	0x02		/* lower case */
	#define	CT_DIG	0x04		/* digit */
	#define	CT_CTL	0x08		/* control */
	#define	CT_PUN	0x10		/* punctuation */
	#define	CT_WHT	0x20		/* white space (space/cr/lf/tab) */
	#define	CT_HEX	0x40		/* hex digit */
	#define	CT_SP	0x80		/* hard space (0x20) */





	/*++++ Basic macros ++++*/

	//-------------------------------------------------------------------
	//"Tests"	=>In the form int isfunc(int)<=
	//Return a nonzero number for true and zero for false.
	//-------------------------------------------------------------------
	//isalnum		test for alphanumeric character
	//isalpha		test for alphabetic character
	//isblank		test for blank character (new in C99)
	//iscntrl		test for control character
	//isdigit		test for digit. Not locale-specific.
	//isgraph		test for graphic character, excluding the space character.
	//islower		test for lowercase character
	//isprint		test for printable character, including the space character.
	//ispunct		test for punctuation character
	//isspace		test for any whitespace character
	//isupper		test for uppercase character
	//isxdigit	test for hexadecimal digit. Not locale-specific.
	//
	//-------------------------------------------------------------------
	//"Character conversion"	  =>in the form int tofunc(int)<=
	//Return the converted character unless it is not alphabetic.
	//--------------------------------------------------------------------
	//tolower		convert character to lowercase
	//toupper		convert character to uppercase
	//
	//isascii		test that the parameter is between 0 and 127
	//toascii		converts a character to ASCII

	#define	isalnum(c)	((_ctype + 1)[(unsigned)(c)] & (CT_UP | CT_LOW | CT_DIG))
	#define	isalpha(c)	((_ctype + 1)[(unsigned)(c)] & (CT_UP | CT_LOW))
	#define	iscntrl(c)	((_ctype + 1)[(unsigned)(c)] & (CT_CTL))
	#define	isdigit(c)	((_ctype + 1)[(unsigned)(c)] & (CT_DIG))
	#define	isgraph(c)	((_ctype + 1)[(unsigned)(c)] & (CT_PUN | CT_UP | CT_LOW | CT_DIG))
	#define	islower(c)	((_ctype + 1)[(unsigned)(c)] & (CT_LOW))
	#define	isprint(c)	((_ctype + 1)[(unsigned)(c)] & (CT_PUN | CT_UP | CT_LOW | CT_DIG | CT_SP))
	#define	ispunct(c)	((_ctype + 1)[(unsigned)(c)] & (CT_PUN))
	#define	isspace(c)	((_ctype + 1)[(unsigned)(c)] & (CT_WHT))
	#define	isupper(c)	((_ctype + 1)[(unsigned)(c)] & (CT_UP))
	#define	isxdigit(c)	((_ctype + 1)[(unsigned)(c)] & (CT_DIG | CT_HEX))
	
	#define	isascii(c)	((unsigned)(c) <= 0x7F)
	#define	toascii(c)	((unsigned)(c) & 0x7F)
	
	#define	tolower(c)	(isupper(c) ? c + 'a' - 'A' : c)
	#define	toupper(c)	(islower(c) ? c + 'A' - 'a' : c)



#endif
