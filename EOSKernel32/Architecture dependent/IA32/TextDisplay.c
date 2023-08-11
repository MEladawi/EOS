


#include <TextDisplay.h>


/*******************************Private*****************************/ 
#define Backcolor 0xF0

uint16 *	VGA_Ram	=	(uint16 *) 0xB8000;
uint8	X		=	1;		//(0 -> 79)
uint8	Y		=	1;		//(0 -> 24)
uint8	Color	=	0xF0;		
static void IncY(void);
static void DecY(void);

static void IncX(void)
{
	if (X < 79) X++;
	else IncY();
}




static void IncY(void)
{
	if (Y < 23) { Y++; X=1; }
	else {Y =1; X=1; EOS_ClearBody(Color);}
}

static void CIncY(void)
{
	if (Y < 23) { Y++; X=1; }
	else {Y =1; X=1; EOS_ClearBody(0xF0);}
}


static void CIncX(void)
{
	if (X < 79) X++;
	else CIncY();
}


void static PrintChar(char Character)
{

	uint16 Attribute = ((uint16) Color) << 8;

	switch (Character) 
	{

	//Tab
	case 0x09:
		X = (X + 8) & ~(8 - 1);
		break;

	//New Line
	case '\n':
		IncY();
		break;

	//Any PRINTABLE character; printable  characters are after ' ' in ascii ;)
	default:
		if (Character >= ' ') 
		{
			uint16 * POINTER	=	VGA_Ram + (Y * 80 + X); 
			* POINTER			=	Character | Attribute;
			IncX();
		}

	}

}



static void SetCoordinate (uint8 CoX, uint8 CoY)
{
	if (CoX <= 79) X= CoX;
	if (CoY <= 24) Y= CoY;
}




/***************************End Private*****************************/ 







/****************************Interface****************************/ 
void EOS_ClearBody (void)
{
	uint32 i;
	for ( i=80; i<80*24; i++) VGA_Ram[i] = ( ((uint16)(Backcolor)) << 8) | ' '; //24 = 25 - 1 (for banner).
	SetCoordinate(1, 1);
}



void EOS_ClearScrean (uint8 Background)
{
	uint32 i;
	for ( i=0; i<80*25; i++) VGA_Ram[i] = ( ((uint16)(Background)) << 8) | ' ';
	SetCoordinate(0, 0);
}


void EOS_ClearHeader (uint8 Background)
{
	uint32 i;
	for ( i=0; i<80; i++) VGA_Ram[i] = ( ((uint16)(Background)) << 8) | ' ';		//first raw for header (from 0 to 79)
	SetCoordinate(0, 0);
}


void EOS_ClearTrailer (uint8 Background)
{
	uint32 i;
	for ( i=80*24; i<80*25; i++) VGA_Ram[i] = ( ((uint16)(Background)) << 8) | ' '; //Last raw for trailer
	SetCoordinate(0, 24);
}


void EOS_PrintString (char * string, uint8 PrintColor, uint8 XCor, uint8 YCor)
{
	
	uint32 i;

	if (!string) return;

	SetCoordinate(XCor, YCor);
	Color = PrintColor;
	for (i=0; i< ((uint32)(strlen(string))); i++)
		PrintChar(string[i]);
	
	
}


void XPrintChar(char Character, uint8 Color)
{

	uint16 Attribute = ((uint16) Color) << 8;

	switch (Character) 
	{

	//Tab
	case 0x09:
		X = (X + 8) & ~(8 - 1);
		break;

	case 0x08:
		if (X>15) {X--; PrintChar(' '); X--; }
		break;

	//New Line
	case 0x0A:
		CIncY();
		EOS_PrintString("Invalid command!", 0xF4, X, Y);
		CIncY();
		EOS_PrintString("XiOS Terminal#", Color, X, Y);
		break;

	//Any PRINTABLE character; printable  characters are after ' ' in ascii ;)
	default:
		if (Character >= 0x20) 
		{
			uint16 * POINTER	=	VGA_Ram + (Y * 80 + X); 
			* POINTER			=	Character | Attribute;
			CIncX();
		}

	}

}



/************************End Interface****************************/ 