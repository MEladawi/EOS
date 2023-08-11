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
|	*String.h									|
|	*Contains public interface for String.c			|
|	*last modified on 07/May/2011					|
++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#ifndef	_STRING_H
#define	_STRING_H

#include <Size_t.h>

#pragma region Declarations

extern	char *strcpy(char *dest, const char *src);				//This function copy src string to dest string and returns pointer to the dest string

extern	size_t strlen ( const char* str );						//this function returns the length of string str

extern	void *memcpy(void *dest, const void *src, size_t count);	//this function copies bulk of memory at src with length count to dest and returns pointer to dest

extern	void *memset(void *dest, char val, size_t count);			//this functiion sets bulk of memory with size count bytes to certain value

extern	int strcmp (const char* str1, const char* str2);

#pragma endregion Declarations
#pragma warning (disable:4706)
#endif