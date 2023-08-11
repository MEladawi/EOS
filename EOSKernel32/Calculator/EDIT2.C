#include <Keyboard.h>


void EOS_ClearBody (unsigned char  );
void EOS_ClearScrean (unsigned char );
void EOS_ClearHeader (unsigned char );
void EOS_ClearTrailer (unsigned char );
void EOS_PrintString (char * string, unsigned char  PrintColor, unsigned char  XCor, unsigned char  YCor);
static void IncY(void);
static void DecY(void);
unsigned int strlen ( const char* str );
void down ();
void up ();
void bgscreen();
void screen();
void m1 ();
void m2();
void m3();
void m4();
void right ();
void lift();
void esc();
void main();

/*******************************Private*****************************/ 
 
 
unsigned short  *VGA_Ram	=(unsigned short  *) 0xB8000;
unsigned char X	 =	0;	 //(0 -> 79)
unsigned char Y	 =	1;	 //(0 -> 24)
unsigned char Color	=	0;
unsigned short  * POINTER;

 
 
unsigned int strlen ( const char* str ) 
{
 
 
unsigned int len= 0;
while (str[len++]);
return len;
 
 
}
 
 
static void IncX(void)
{
if (X < 79) X++;
else IncY();
}
 
 
 
 
static void IncY(void)
{
if (Y < 23) { Y++; X=0; }
else {Y =1; X=0; EOS_ClearBody(Color);}
}
 
 
 
void static PrintChar(char Character)
{
 
 
unsigned short  Attribute = ((unsigned short ) Color) << 8;
 
 
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
 
 
//Any PRINTABLE character==> printable  characters are after ' ' in ascii ;)
default:
if (Character >= ' ') 
{
POINTER	 =	(VGA_Ram + (Y * 80 + X)); 
* POINTER	 =	(Character | Attribute);
IncX();
}
 
 
}
 
 
}
 
 
 
 
static void SetCoordinate (unsigned char  CoX, unsigned char  CoY)
{
if (CoX <= 79) X= CoX;
if (CoY <= 24) Y= CoY;
} 
/***************************End Private*****************************/ 
 
 
 
 
 
 
 
 
/****************************Interface****************************/ 
void EOS_ClearBody (unsigned char  Background)
{
unsigned int i;
for ( i=160; i<80*24; i++) VGA_Ram[i] = ( ((unsigned short )(Background)) << 8) | ' '; //23 = 25 - 2 (for banners).
SetCoordinate(0, 2);
}
void EOS_ClearScrean (unsigned char  Background)
{
unsigned int i;
for ( i=0; i<80*25; i++) VGA_Ram[i] = ( ((unsigned short )(Background)) << 8) | ' ';
SetCoordinate(0, 0);
}
void EOS_ClearHeader (unsigned char  Background)
{
unsigned int i;
for ( i=0; i<80; i++) VGA_Ram[i] = ( ((unsigned short )(Background)) << 8) | ' '; //first raw for header (from 0 to 79)
SetCoordinate(0, 0);
}
void EOS_ClearTrailer (unsigned char  Background)
{
unsigned int i;
for ( i=80*24; i<80*25; i++) VGA_Ram[i] = ( ((unsigned short )(Background)) << 8) | ' '; //Last raw for trailer
SetCoordinate(0, 24);
}
 void EOS_PrintString (char * string, unsigned char  PrintColor, unsigned char  XCor, unsigned char  YCor)
{
 
unsigned int i;
 
 
if (!string) return;
 
 
SetCoordinate(XCor, YCor);
Color = PrintColor;
for (i=0; i< ((unsigned int)(strlen(string))); i++)
PrintChar(string[i]);
 
 
}
//************************End Interface****************************/ 
 int linenum=2;
unsigned char mx	=1 ;	 
unsigned char mn	=0 ;	 
unsigned char t	 =	0;
unsigned char r	 =	0;
int note;
int con=0;
	int def;

int cur ;

//********************************the number declaration  for note VERY IMPORTANT   ******************************//
//note = 0 when activating the body
// note =  1 when activating menus bar
//note = 2n when activating the menu n
//note = 2nm when activating the member m in the menu n










//*******************************down with menu*******************************//
int yy;
void downfile (void)
{
	
if (yy==1)
{
EOS_PrintString("  N", 0x74,2,2);
EOS_PrintString("ew    ", 0x70,5,2);

EOS_PrintString("  Open   ", 0x30,2,3);
}
if(yy==2)
{
EOS_PrintString("  O", 0x74,2,3);
EOS_PrintString("pen   ", 0x70,5,3);
EOS_PrintString("  Save   ", 0x30,2,4);
}
if (yy==3)
{
EOS_PrintString("  S", 0x74,2,4);
EOS_PrintString("ave   ", 0x70,5,4);

EOS_PrintString("  Close  ", 0x30,2,5);
}
if(yy==4)
{
EOS_PrintString("  C", 0x74,2,5);
EOS_PrintString("lose  ", 0x70,5,5);
EOS_PrintString("  Exit   ", 0x30,2,6);
}
if (yy==5)
{
EOS_PrintString("  E", 0x74,2,6);
EOS_PrintString("xit   ",0x70,5,6);
EOS_PrintString("  New    ",0x30,2,2);
yy=1;
}

yy++;

}	

void upfile(void)
{
	
if (yy==1)
{
EOS_PrintString("  N", 0x74,2,2);
EOS_PrintString("ew    ", 0x70,5,2);
EOS_PrintString("  Exit   ", 0x30,2,6);
yy=5;
}
if(yy==2)
{
EOS_PrintString("  O", 0x74,2,3);
EOS_PrintString("pen   ", 0x70,5,3);
EOS_PrintString("  New    ",0x30,2,2);
}
if (yy==3)
{
EOS_PrintString("  S", 0x74,2,4);
EOS_PrintString("ave   ", 0x70,5,4);


EOS_PrintString("  Open   ", 0x30,2,3);
}
if(yy==4)
{
EOS_PrintString("  C", 0x74,2,5);
EOS_PrintString("lose  ", 0x70,5,5);
EOS_PrintString("  Save   ", 0x30,2,4);
}
if (yy==5)
{
EOS_PrintString("  E", 0x74,2,6);
EOS_PrintString("xit   ",0x70,5,6);
EOS_PrintString("  Close  ", 0x30,2,5);

}
yy--;

}

void downedit (void)
{

if (yy==1)
{
EOS_PrintString("  Cut    ctrl+x ", 0x70,7,2);

EOS_PrintString("  Copy   ctrl+c ", 0x30,7,3);
}
 if (yy==2)
{
EOS_PrintString("  Copy   ctrl+c ", 0x70,7,3);
EOS_PrintString("  Paste  ctrl+v ", 0x30,7,4);
}
if (yy==3)
{
EOS_PrintString("  Paste  ctrl+v ", 0x70,7,4);
EOS_PrintString("  Clear  del    ", 0x30,7,5);

}
if(yy==4)
{
EOS_PrintString("  Clear  del    ", 0x70,7,5);
EOS_PrintString("  Cut    ctrl+x ", 0x30,7,2);
yy=1;
}
yy++;
}
void upedit (void)
{
	
if (yy==1)
{
EOS_PrintString("  Cut    ctrl+x ", 0x70,7,2);

EOS_PrintString("  Clear  del    ", 0x30,7,5);
yy=4;
}
else if(yy==4)
{
EOS_PrintString("  Clear  del    ", 0x70,7,5);
EOS_PrintString("  Paste  ctrl+v ", 0x30,7,4);
}
if (yy==3)
{
EOS_PrintString("  Paste  ctrl+v ", 0x70,7,4);
EOS_PrintString("  Copy   ctrl+c ", 0x30,7,3);

}
if(yy==2)
{
EOS_PrintString("  Copy   ctrl+c ", 0x70,7,3);
EOS_PrintString("  Cut    ctrl+x ", 0x30,7,2);

}

yy--;
}
void downoption(void)
{
	
if (yy==1)
{
EOS_PrintString("  F", 0x74,12,2);
EOS_PrintString("onts        ", 0x70,15,2);
EOS_PrintString("  S", 0x34,12,3);
EOS_PrintString("et Language ", 0x30,15,3);
}
if (yy==2)
{
EOS_PrintString("  S", 0x74,12,3);
EOS_PrintString("et Language ", 0x70,15,3);
EOS_PrintString("  F", 0x34,12,2);
EOS_PrintString("onts        ", 0x30,15,2);
yy=1;
}
yy++;
}
void upoption(void)
{
	
if (yy==2)
{
EOS_PrintString("  S", 0x34,12,3);
EOS_PrintString("et Language ", 0x30,15,3);
EOS_PrintString("  F", 0x74,12,2);
EOS_PrintString("onts        ", 0x70,15,2);
}
if (yy==1)
{
EOS_PrintString("  F", 0x34,12,2);
EOS_PrintString("onts        ", 0x30,15,2);
EOS_PrintString("  S", 0x74,12,3);
EOS_PrintString("et Language ", 0x70,15,3);
yy=2;

}
yy--;
}

//**************************up with menu**********************************//



//*********************back ground screen**************************************//
void bgscreen(void)
{
	char far *ptr=(char *)0xb8000000;
	int x;
	int f;
EOS_PrintString(" LOTUS Editor...                                                            _ X ", 112,0,0);
EOS_PrintString("  F", 4,0,1);
EOS_PrintString("ile", 7,3,1);
EOS_PrintString(" E", 4,6,1);
EOS_PrintString("dit", 7,8,1);
EOS_PrintString(" O", 4,11,1);
EOS_PrintString("ption", 7,13,1);
EOS_PrintString(" H", 4,18,1);
EOS_PrintString("elp", 7,20,1);
EOS_PrintString("                                                        ", 7,23,1);
EOS_PrintString("                                                                       LOUTS OS ", 127,0,24);
EOS_ClearBody(23) ;
for (x=160 ;x<=3839 ; x=x+160){
	*(ptr+(x)) = ' ' ;
*(ptr+ (x+1))= 7 ;
}

for (f=318 ;f<=3839 ; f=f+160){
*(ptr+(f)) = ' ' ;
*(ptr+ (f+1))= 7 ;
}

}





//*********************screen1***********************************//

//////////////////////////////

void openscreen(void){
	
	int q ;

	note = 2121;
EOS_PrintString("                      OPEN                      ",63,16,5);
EOS_PrintString("                                                ",112,16,6);
EOS_PrintString(" WRITE THE FILE NAME:                           ",121,16,7);
EOS_PrintString("    ",112,16,8);
EOS_PrintString("-                                       ",31,20,8);
EOS_PrintString("    ",112,60,8);
EOS_PrintString("                                                ",112,16,9);
EOS_PrintString("                                                ",112,16,10);
EOS_PrintString("                                                ",112,16,11);
EOS_PrintString("                                                ",112,16,12);
EOS_PrintString("          ",112,16,13);
EOS_PrintString("  Open   ",63,26,13);
EOS_PrintString("          ",112,35,13);
EOS_PrintString(" Cancel  ",63,45,13);
EOS_PrintString("          ",112,54,13);
EOS_PrintString("                                                ",112,16,14);
EOS_PrintString("                                          LOTUS ",15,17,15);



	
for( q =6;q<=15;q++)
{
EOS_PrintString(" ",0,64,q);
}
}

////////////////////////////////
void savescreen(void)
{
	int q ;

	note = 2121;
EOS_PrintString("                      SAVE                      ",63,16,5);
EOS_PrintString("                                                ",112,16,6);
EOS_PrintString(" WRITE THE FILE NAME:                           ",121,16,7);
EOS_PrintString("    ",112,16,8);
EOS_PrintString("-                                       ",31,20,8);
EOS_PrintString("    ",112,60,8);
EOS_PrintString("                                                ",112,16,9);
EOS_PrintString("                                                ",112,16,10);
EOS_PrintString("                                                ",112,16,11);
EOS_PrintString("                                                ",112,16,12);
EOS_PrintString("          ",112,16,13);
EOS_PrintString("  SAVE   ",63,26,13);
EOS_PrintString("          ",112,35,13);
EOS_PrintString(" Cancel  ",63,45,13);
EOS_PrintString("          ",112,54,13);
EOS_PrintString("                                                ",112,16,14);
EOS_PrintString("                                          LOTUS ",15,17,15);



	
for( q =6;q<=15;q++)
{
EOS_PrintString(" ",0,64,q);
}

}



//***********************closescreen**************************//

void close(void)

{
int q;
note = 2151;
EOS_PrintString("                   SAVE FIle                    ",63,16,10);
EOS_PrintString("                                                ",116,16,11);
EOS_PrintString("        The file has not been saved yet.        ",116,16,12);
EOS_PrintString("                                                ",112,16,13);
EOS_PrintString("                 save it now ?                  ",112,16,14);
EOS_PrintString("                                                ",112,16,15);
EOS_PrintString("                                                ",112,16,16);
EOS_PrintString("     ",112,16,17);                          
EOS_PrintString("  Yes  ",63,21,17);                                
EOS_PrintString("        ",112,28,17);                              
EOS_PrintString("  No   ",63,36,17);                                    
EOS_PrintString("        ",112,43,17); 
EOS_PrintString(" Cancel ",63,51,17);
EOS_PrintString("     ",112,59,17);
EOS_PrintString("                                                ",112,16,18);
EOS_PrintString("                                          LOTUS ",15,17,19);



for( q =11;q<=18;q++){
EOS_PrintString(" ", 0,64,q);

}
}

//******************************Exit screen****************************//


void exit(void)

{
int q;
note = 2161;
EOS_PrintString("                   SAVE FIle                    ",63,16,10);
EOS_PrintString("                                                ",116,16,11);
EOS_PrintString("        The file has not been saved yet.        ",116,16,12);
EOS_PrintString("                                                ",112,16,13);
EOS_PrintString("                 save it now ?                  ",112,16,14);
EOS_PrintString("                                                ",112,16,15);
EOS_PrintString("                                                ",112,16,16);
EOS_PrintString("     ",112,16,17);                          
EOS_PrintString("  Yes  ",63,21,17);                                
EOS_PrintString("        ",112,28,17);                              
EOS_PrintString("  No   ",63,36,17);                                    
EOS_PrintString("        ",112,43,17); 
EOS_PrintString(" Cancel ",63,51,17);
EOS_PrintString("     ",112,59,17);
EOS_PrintString("                                                ",112,16,18);
EOS_PrintString("                                          LOTUS ",15,17,19);



for( q =11;q<=18;q++){
EOS_PrintString(" ", 0,64,q);

}

}
void cut (void)
{
}
void copy (void)
{
}
void paste (void)
{
}
void del (void)
{
}
void help (void)
{
int q;
note = 2161;
EOS_PrintString("                          HELP MENU                       ",63,16,10);
EOS_PrintString(" ENTER ***> Start a new line                              ",116,16,11);
EOS_PrintString(" ALT   ***> Move the cursor to the next tap stop          ",116,16,12);
EOS_PrintString(" CTRL+C ***> Copy word from position                      ",116,16,13);
EOS_PrintString(" CTRL+V ***> Paste word to another position               ",116,16,14);
EOS_PrintString(" CTRL+X ***> Move Word from position to another position  ",116,16,15);
EOS_PrintString("                                                          ",116,16,16);
}

	
	

//********************FILE menu******************************//
void m1name(void){
	note=1;
	EOS_PrintString("File", 31,2,1);
	r=2;
	
}


void m1 (void)
{        	int v ;
	 yy=1;
	note=2;
bgscreen();

mx = 6;
mn = 2;
r =2; 
t = 2;
EOS_PrintString("File", 31,2,1);
EOS_PrintString("  N", 0x34,2,2);
EOS_PrintString("ew    ", 0x30,5,2);
EOS_PrintString("  O", 116,2,3);
EOS_PrintString("pen   ", 112,5,3);
EOS_PrintString("  S", 116,2,4);
EOS_PrintString("ave   ", 112,5,4);
EOS_PrintString("  C", 116,2,5);
EOS_PrintString("lose  ", 112,5,5);
EOS_PrintString("  E", 116,2,6);
EOS_PrintString("xit   ", 112,5,6);
for( v =3;v<=6;v++){
EOS_PrintString(" ", 0,11,v);
}
EOS_PrintString("         ", 0,3,7);



}



//******************************Edit menu*********************//
void m2name(void){
EOS_PrintString("Edit", 31,7,1);
note =1;
r =7;

}

void m2(void)
{       int v ;
	yy=1;
	note = 2;
bgscreen();

mx =5;
mn = 2;
r =7; 
t = 2;
EOS_PrintString("Edit", 31,7,1);
EOS_PrintString("  Cut    ctrl+x ", 0x30,7,2);
EOS_PrintString("  Copy   ctrl+c ", 112,7,3);
EOS_PrintString("  Paste  ctrl+v ", 112,7,4);
EOS_PrintString("  Clear  del    ", 112,7,5);
for( v =3;v<=6;v++){
EOS_PrintString(" ", 0,23,v);
}
EOS_PrintString("               ",0,8,6);

}




//******************************option menu*****************//
void m3name(void){
EOS_PrintString("Option", 31,12,1);
note =1;
r=12; 

}


void m3 (void)
{       int v ;
	yy=1;
note = 2;
bgscreen();

mx=3;
mn=2;
r=12; 
t=2;
EOS_PrintString("Option", 31,12,1);
EOS_PrintString("  F", 0x34,12,2);
EOS_PrintString("onts        ", 0x30,15,2);
EOS_PrintString("  S", 116,12,3);
EOS_PrintString("et Language ", 112,15,3);
for( v =3;v<=4;v++){
EOS_PrintString(" ", 0,27,v);
}
EOS_PrintString("               ",0,13,4);

}



//*****************************help menu********************//
void m4name(void){
	EOS_PrintString("help", 31,19,1);
	note=1;
	r =19; 
	
}

void m4 (void) 
{
	yy=1;
note = 2;
bgscreen();
mx =2;
mn = 2;
r =19; 
t = 2;
EOS_PrintString("help", 31,19,1);
EOS_PrintString("  V", 0x34,19,2);
EOS_PrintString("iew Help ", 0x30,22,2);
EOS_PrintString("            ",0,20,3);


}

void down (void)
{
	if (r==2)
	{
		downfile();
		
	}
	if (r==7)
	{
downedit();
	
	}
	if (r==12)
	{
		downoption();
	}
}
void up (void)
{
	if (r==2)
	{
		upfile();
		
	}
	if (r==7)
	{
upedit();
	
	}
	if (r==12)
	{
		upoption();
	}
}
void downhelp (void)
{
	if (yy==1){
		m4();
	}
}


//*************************cursor in the body*********************//
void cursor (void)
{

	char far *ptr=(char *)0xb8000000;
	//*(ptr+cur) =""
	*(ptr+ (cur+1))= 112 ;
}




//*************************right*********************************//
void right (void) {

if (note == 2)
	{
if (r==2)
{
m2();
}
else if (r==7)
{
m3();
}
else if (r==12)
{
m4();
}
else if (r==19)
{
m1();
}
	}
	//////////////////////////
	if (note==1)
	{
if (r==2)
{
m2name();
}
else if (r==7)
{
m3name();
}
else if (r==12)
{
m4name();
}
else if (r==19)
{
m1name();
}
	}
	///////////////////////////
	if (note == 0)
	{
	cur++;
	cursor ();

	}
	//////openscreen////////
	if (note == 21210)
	{ 
		note = 21220;	
		EOS_PrintString("  Open   ",0x37,26,13);

EOS_PrintString(" Cancel  ",0x27,45,13);
	}
	else if (note == 21220)
	{
	note = 21210;
	EOS_PrintString("  Open   ",0x27,26,13);

EOS_PrintString(" Cancel  ",0x37,45,13);
	}
	////////////savescreen/////////////
	else if (note == 21310)
	{
	note = 21320;
	EOS_PrintString("  Save   ",0x37,26,13);

EOS_PrintString(" Cancel  ",0x27,45,13);
	}
	else if (note == 21320)
	{ 
	note = 21320;	
EOS_PrintString("  Save   ",0x27,26,13);

EOS_PrintString(" Cancel  ",0x37,45,13);
	}

	
	//////////////////close screen//////////
else if (note == 21530)
	{
		note = 21510;
		EOS_PrintString("  Yes  ",0x27,21,17);                                
                              
EOS_PrintString("  No   ",0x37,36,17);                                    

EOS_PrintString(" Cancel ",0x37,51,17);
}
else if (note == 21510)
	{
		note = 21520;
		EOS_PrintString("  Yes  ",0x37,21,17);                                
                              
EOS_PrintString("  No   ",0x27,36,17);                                    

EOS_PrintString(" Cancel ",0x37,51,17);

}
else if (note == 21520)
	{
		note = 21530;
		EOS_PrintString("  Yes  ",0x37,21,17);                                
                              
EOS_PrintString("  No   ",0x37,36,17);                                    

EOS_PrintString(" Cancel ",0x27,51,17);
}

///////////////exit screen/////////////
else if (note == 21630)
	{
		note = 21610;
		EOS_PrintString("  Yes  ",0x27,21,17);                                
                              
EOS_PrintString("  No   ",0x37,36,17);                                    

EOS_PrintString(" Cancel ",0x37,51,17);
}
else if (note == 21610)
	{
		note = 21620;
		EOS_PrintString("  Yes  ",0x37,21,17);                                
                              
EOS_PrintString("  No   ",0x27,36,17);                                    

EOS_PrintString(" Cancel ",0x37,51,17);

}
else if (note == 21620)
	{
		note = 21630;
		EOS_PrintString("  Yes  ",0x37,21,17);                                
                              
EOS_PrintString("  No   ",0x37,36,17);                                    

EOS_PrintString(" Cancel ",0x27,51,17);
}
}





//***********************left*************************************//
void left(void){
	if (note == 2)
	{
if (r==2)
{
m4();
}
else if (r==7)
{
m1();
}
else if (r==12)
{
m2();
}
else if (r==19)
{
m3();
}
	}
	//////////////////////////
	if (note==1)
	{
if (r==2)
{
m4name();
}
else if (r==7)
{
m1name();
}
else if (r==12)
{
m2name();
}
else if (r==19)
{
m3name();
}
	}
	///////////////////////////
	if (note == 0)
	{
	cur++;
	cursor ();

	}
	if (note == 21210)
	{ 
		note = 21220;	
		EOS_PrintString("  Open   ",0x37,26,13);

EOS_PrintString(" Cancel  ",0x27,45,13);
	}
	else if (note == 21220)
	{
	note = 21210;
	EOS_PrintString("  Open   ",0x27,26,13);

EOS_PrintString(" Cancel  ",0x37,45,13);
	}
	////////////savescreen/////////////
	else if (note == 21310)
	{
	note = 21320;
	EOS_PrintString("  Save   ",0x37,26,13);

EOS_PrintString(" Cancel  ",0x27,45,13);
	}
	else if (note == 21320)
	{ 
	note = 21320;	
EOS_PrintString("  Save   ",0x27,26,13);

EOS_PrintString(" Cancel  ",0x37,45,13);
	}

	
	//////////////////close screen//////////
else if (note == 21530)
	{
		note = 21520;
		EOS_PrintString("  Yes  ",0x37,21,17);                                
                              
EOS_PrintString("  No   ",0x27,36,17);                                    

EOS_PrintString(" Cancel ",0x37,51,17);
}
else if (note == 21510)
	{
		note = 21530;
		EOS_PrintString("  Yes  ",0x37,21,17);                                
                              
EOS_PrintString("  No   ",0x37,36,17);                                    

EOS_PrintString(" Cancel ",0x27,51,17);

}
else if (note == 21520)
	{
		note = 21510;
		EOS_PrintString("  Yes  ",0x27,21,17);                                
                              
EOS_PrintString("  No   ",0x37,36,17);                                    

EOS_PrintString(" Cancel ",0x37,51,17);
}

///////////////exit screen/////////////
else if (note == 21630)
	{
		note = 21620;
		EOS_PrintString("  Yes  ",0x37,21,17);                                
                              
EOS_PrintString("  No   ",0x37,26,17);                                    

EOS_PrintString(" Cancel ",0x37,51,17);
}
else if (note == 21610)
	{
		note = 21630;
		EOS_PrintString("  Yes  ",0x37,21,17);                                
                              
EOS_PrintString("  No   ",0x37,36,17);                                    

EOS_PrintString(" Cancel ",0x27,51,17);

}
else if (note == 21620)
	{
		note = 21610;
		EOS_PrintString("  Yes  ",0x27,21,17);                                
                              
EOS_PrintString("  No   ",0x37,36,17);                                    

EOS_PrintString(" Cancel ",0x37,51,17);
}
}


void tabopen(void)
{
	note=21210;
EOS_PrintString("  Open   ",0x27,26,13);
}
void tabsave(void)
{
	note=21310;
	EOS_PrintString("  Save   ",0x27,26,13);
}
void tabclose(void)
{
	note=21510;
	EOS_PrintString("  Yes  ",0x27,21,17);      
}
void tabexit(void)
{
	note=21610;
	EOS_PrintString("  Yes  ",0x27,21,17);      
}
void tab(void)
{
if (note==2121){
	tabopen();
}
if (note==2131){
	tabsave();
}
if (note==2151){
tabclose();
}
if (note==21610){
	tabexit();
}
}
//*****************************ESC***************************//
void esc(void)
{
	if (note == 1 )
	{
		note = 0;
bgscreen();
	}
	else if (note==21)
	{
		note = 1;
		m1name();
	}
	else if (note==22)
	{
		note = 1;
		m2name();
	}
	else if (note==23)
	{
		note = 1;
		m3name();
	}
	 else if (note==24)
	{
		note = 1;
		m4name();
	}
	else if (note ==3)
	{
		note =0;
	bgscreen();
	}
	else 
		{
			note = 0;
	bgscreen();
}
}



//*****************************alt***************************//
void altpress(void)
{
	if (note ==0)
	{
		note = 1;
       m1name();
	}
}


//**********************pressing F after alt******************//
void altf(void) 
{
	Keyboard_Status.
	m1();
}



//**********************pressing E after alt******************//
void alte(void) 
{
	m2();
}



//**********************pressing O after alt******************//
void alto(void) 
{
	m3();
}



//**********************pressing H after alt******************//
void alth(void) 
{
	m4();
}

//**************************Enter with menu************************************//
void enter (void) 
{
	 if (r==2){
			 if (yy==1) {
		bgscreen();
	}
	
	if (yy==2 ){ 
	
		
		openscreen();
	}
	
	if ( yy==3){  
	 
		savescreen();
	}
	
	if (yy==4) { 
	 
		close();
	}
	
	if (yy==5){
	 

		exit();
	}
	}
	
		 if (r==7){
	if (yy==1){ 
		cut();
	
	}
	if (yy==2 ){  
	
		 
		copy();
	}
	
	if ( yy==3){  
 
		paste();
	
	}
	if (yy==4) { 
   
		del();
	}
	}
		 if (r==19){
	if (yy==1){
	 
		help();
	}
	}
	if (note ==1)
	{


		if (r == 2)
			{
				m1();
			}

		 if (r == 7)
			{
				m2();
			}
		 if (r == 12)
			{
				m3();
			}
		if (r == 19)
			{
				m4();
			}
		}
}

/////////////copyfn////////////////////////////////////
void copyfn(void)
{

}


////////////////pastefn//////////////////////////////
void pastefn(void)
{

}


////////////////cutfn///////////////////////////////


void cutfn(void)
{

}


//*****************************MAIN**************************//
void Editor(void)
{
	enum KeyBoard_Keys MyKey;
	KeyHandler MyHandler;

	note = 0;
	bgscreen();
	

	MyKey = KeyBoard_Keys_F;
	MyHandler = &altf;
	Keyboard_UpdateHandler(MyKey, MyHandler);



}