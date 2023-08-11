#ifndef _TextDisplay_H
#define _TextDisplay_H



#include <String.h>
#include <stdint.h>



void EOS_ClearBody	 (uint8 );
void EOS_ClearScrean (uint8);
void EOS_ClearHeader (uint8);
void EOS_ClearTrailer (uint8);
void EOS_PrintString (char * string, uint8 PrintColor, uint8 XCor, uint8 YCor);
void XPrintChar(char Character, uint8 Color);


#endif