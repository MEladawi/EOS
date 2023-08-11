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
|	*String.c									|
|	*Contains some string common functions			|
|	*last modified on 07/May/2011					|
++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



//As we use assignment in conditional statement we will disable its warning!!
#pragma warning (disable:4706)

#include <String.h>




//This function copy src string to dest string and returns pointer to the dest string
char *strcpy(char *dest, const char *src)
{

   char *save = dest;		//we did not return dest as its value will change in next statement.
   while(*dest++ = *src++);
   return save;

}




//this function returns the length of string str
size_t strlen ( const char* str ) 
{

	size_t len= 0;
	while (str[len++]);
	return len;

}




//this function copies bulk of memory at src with length count to dest and returns pointer to dest
void *memcpy(void *dest, const void *src, size_t count)
{
   
	const char *SrcP = (const char *)src;
    char *DestP = (char *)dest;
    for (; count != 0; count--) *DestP++ = *SrcP++;
    return dest;

}




//this functiion sets bulk of memory with size count bytes to certain value
void *memset(void *dest, char val, size_t count)
{

	unsigned char *temp = (unsigned char *)dest;
	for ( ; count != 0; count--, temp[count] = val);
	return dest;

}




int strcmp (const char* str1, const char* str2) {

	int res=0;

	while (!(res = *(unsigned char*)str1 - *(unsigned char*)str2) && *str2)
		++str1, ++str2;

	if (res < 0)
		res = -1;

	if (res > 0)
		res = 1;

	return res;
}