
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
|	*stdint.h									|
|	*C integer types stsndard header				|
|	*To ensure portability among Architectures ;-)	|
|	*last modified on 13/april/2011				|
++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



#ifndef _STDINT_H
#define _STDINT_H


		//Exact-width integer types
		typedef	signed char			int8;
		typedef	unsigned char			uint8;
		typedef	short				int16;
		typedef	unsigned short			uint16;
		typedef	int					int32;
		typedef	unsigned				uint32;
		typedef	long long				int64;
		typedef	unsigned long long		uint64;




		//Minimum-width integer types
		typedef	signed char			int_least8;
		typedef	unsigned char			uint_least8;
		typedef	short				int_least16;
		typedef	unsigned short			uint_least16;
		typedef	int					int_least32;
		typedef	unsigned				uint_least32;
		typedef	long long				int_least64;
		typedef	unsigned long long		uint_least64;




		//Not actually guaranteed to be fastest for all purposes
		typedef	char					int_fast8;
		typedef	unsigned char			uint_fast8;
		typedef	short				int_fast16;
		typedef	unsigned short			uint_fast16;
		typedef	int					int_fast32;
		typedef	unsigned  int			uint_fast32;
		typedef	long long				int_fast64;
		typedef	unsigned long long		uint_fast64;



		//Integer types capable of holding pointers
		typedef	int					intptr;
		typedef	unsigned				uintptr;

		
		//Bool (as we don't have bool in C)
		enum boolean{True =1, False=0};
		typedef enum boolean Bool;

		
		//Greatest-width integer types
		typedef	long long				intmax;
		typedef	unsigned long long		uintmax;




		///Limits of exact-width integer types
		#define	INT8_MIN				(-128) 
		#define	INT16_MIN				(-32768)
		#define	INT32_MIN				(-2147483647 - 1)
		#define	INT64_MIN				(-9223372036854775807LL - 1)



		#define	INT8_MAX				127
		#define	INT16_MAX				32767
		#define	INT32_MAX				2147483647
		#define	INT64_MAX				9223372036854775807LL


		#define	UINT8_MAX				0xff					/* 255U */
		#define	UINT16_MAX			0xffff				/* 65535U */
		#define	UINT32_MAX			0xffffffff			/* 4294967295U */
		#define	UINT64_MAX			0xffffffffffffffffULL	/* 18446744073709551615ULL */






#endif
