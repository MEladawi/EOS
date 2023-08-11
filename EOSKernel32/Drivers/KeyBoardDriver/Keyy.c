
#include "Keyboard.h"


void www_ClearBody (unsigned char  );
void www_ClearScrean (unsigned char );
void www_ClearHeader (unsigned char );
void www_ClearTrailer (unsigned char );
void www_PrintString (char * string, unsigned char  PrintColorA, unsigned char  XCor, unsigned char  YCor);
static void IncY(void);
static void DecY(void);
unsigned int strlenA ( const char* str );




/*******************************Private*****************************/


unsigned short  *	VGA_RamA	=	(unsigned short *) 0xB8000;
unsigned char XE	 =	0;	 //(0 -> 79)
unsigned char YE	 =	1;	 //(0 -> 24)
unsigned char ColorA	=	0;
unsigned short * POINTERQ;



unsigned int strlenA ( const char* str )
{


unsigned int len= 0;
while (str[len++]);
return len;


}


static void IncX(void)
{
if (XE < 79) XE++;
else IncY();
}




static void IncY(void)
{
if (YE < 23) { YE++; XE=0; }
else {YE =1; XE=0; www_ClearBody(ColorA);}
}



void static PrintChar(char Character)
{


unsigned short  Attribute = ((unsigned short ) ColorA) << 8;


switch (Character)
{


//Tab
case 0x09:
XE = (XE + 8) & ~(8 - 1);
break;


//New Line
case '\n':
IncY();
break;


//Any PRINTABLE character==> printable  characters are after ' ' in ascii ;)
default:
if (Character >= ' ')
{
POINTERQ	 =	(VGA_RamA + (YE * 80 + XE));
* POINTERQ	 =	(Character | Attribute);
IncX();
}


}


}




static void SetCoordinate (unsigned char  CoX, unsigned char  CoY)
{
if (CoX <= 79) XE= CoX;
if (CoY <= 24) YE= CoY;
}


/***************************End Private*****************************/








/****************************Interface****************************/
void www_ClearBody (unsigned char  Background)
{
unsigned int i;
for ( i=160; i<80*24; i++) VGA_RamA[i] = ( ((unsigned short )(Background)) << 8) | ' '; //23 = 25 - 2 (for banners).
SetCoordinate(0, 2);
}




void www_ClearScrean (unsigned char  Background)
{
unsigned int i;
for ( i=0; i<80*25; i++) VGA_RamA[i] = ( ((unsigned short )(Background)) << 8) | ' ';
SetCoordinate(0, 0);
}



void www_ClearHeader (unsigned char  Background)
{
unsigned int i;
for ( i=0; i<80; i++) VGA_RamA[i] = ( ((unsigned short )(Background)) << 8) | ' '; //first raw for header (from 0 to 79)
SetCoordinate(0, 0);
}



void www_ClearTrailer (unsigned char  Background)
{
unsigned int i;
for ( i=80*24; i<80*25; i++) VGA_RamA[i] = ( ((unsigned short )(Background)) << 8) | ' '; //Last raw for trailer
SetCoordinate(0, 24);
}



void www_PrintString (char * string, unsigned char  PrintColorA, unsigned char  XCor, unsigned char  YCor)
{

unsigned int i;


if (!string) return;


SetCoordinate(XCor, YCor);
ColorA = PrintColorA;
for (i=0; i< ((unsigned int)(strlenA(string))); i++)
PrintChar(string[i]);


}


/************************End Interface****************************/

unsigned char mx	=1 ;
unsigned char mn	=0 ;
unsigned char t	 =	0;
unsigned char r	 =	0;
void down () {
www_PrintString("  ",240,r,t);
t++;
if (t==mx+1 )
	t=mn;
else mx =mx;
www_PrintString("*>",112,r,t);
}


void up () {

t--;
www_PrintString("  ",112,r,t);
if (t ==mn-1 )
	t=mx;
else mx =mx;

www_PrintString("*>",112,r,t);

}

void right () {






}

void screen1(){
	int q ;
int r; for(r=5;r<=17;r++){
www_PrintString("                                            ",112,18,r);
}
www_PrintString("                                       XIOS ",7,19,18);


for( q =6;q<=17;q++){
www_PrintString(" ", 0,62,q);
}

www_PrintString(" Save as ** ", 112,18,5);

www_PrintString("   File name:", 112,18,8);

www_PrintString("                 ", 128,33,8);

www_PrintString("   Save as type: ", 112,18,10);

www_PrintString("                 ", 128,35,10);
www_PrintString(" Save ", 23,32,15);
www_PrintString("Cancel", 23,45,15);

}




void screen2(){
	int q ;
int r; for(r=5;r<=17;r++){
www_PrintString("                                            ",112,18,r);
}
www_PrintString("                                       wwwIOS ",7,19,18);


for( q =6;q<=17;q++){
www_PrintString(" ", 0,62,q);
}

www_PrintString(" Open ** ", 112,18,5);

www_PrintString("   File name:", 112,18,8);

www_PrintString("                 ", 128,33,8);

www_PrintString("   Open as type: ", 112,18,10);

www_PrintString("                 ", 128,35,10);
www_PrintString(" Open ", 23,32,15);
www_PrintString("Cancel", 23,45,15);

}

void screen3(){
	int q ;
int r; for(r=5;r<=15;r++){
www_PrintString("                                            ",112,18,r);
}
www_PrintString("                                       wwwIOS ",7,19,16);


for( q =6;q<=16;q++){
www_PrintString(" ", 0,62,q);
}

www_PrintString(" Close ** ", 112,18,5);

www_PrintString("     Do you want to save changes?", 112,18,8);


www_PrintString("  Save ", 23,22,13);

www_PrintString(" Don't save ", 23,34,13);

www_PrintString(" Cancel", 23,50,13);

}

void screen4(){
	int q ;
int r; for(r=5;r<=20;r++){
www_PrintString("                                            ",112,18,r);
}
www_PrintString("                                       XIOS ",7,19,21);


for( q =6;q<=21;q++){
www_PrintString(" ", 0,62,q);
}

www_PrintString(" Font ** ", 112,18,5);

www_PrintString("  Font:", 112,18,7);

www_PrintString("  Font style:", 112,30,7);

www_PrintString("  Size: ", 112,48,7);



www_PrintString("          ", 128,20,8);

www_PrintString("             ", 128,32,8);

www_PrintString("     ", 128,50,8);

www_PrintString("  OK  ", 23,35,18);

www_PrintString("Cancel", 23,50,18);





}












//void ctrl+f() {
//	m1();
//}
//void ctrl+f() {
	//m1();
//}
void m1 ()
{
int v ;

mx = 6;
 mn = 2;
 r =2;
 t = 2;

www_PrintString("File", 31,2,1);
www_PrintString("  N", 116,2,2);
www_PrintString("ew    ", 112,5,2);
www_PrintString("  O", 116,2,3);
www_PrintString("pen   ", 112,5,3);
www_PrintString("  S", 116,2,4);
www_PrintString("ave   ", 112,5,4);

www_PrintString("  C", 116,2,5);
www_PrintString("lose  ", 112,5,5);

www_PrintString("  E", 116,2,6);
www_PrintString("xit   ", 112,5,6);



for( v =3;v<=6;v++){
www_PrintString(" ", 0,11,v);
}
www_PrintString("         ", 0,3,7);
www_PrintString("*>",112,r,2);

}





void m2(){
	int v ;
mx =5;
 mn = 2;
 r =7;
 t = 2;

www_PrintString("Edit", 31,7,1);
www_PrintString("  Cut    ctrl+x ", 112,7,2);
www_PrintString("  Copy   ctrl+c ", 112,7,3);
www_PrintString("  Paste  ctrl+v ", 112,7,4);
www_PrintString("  Clear  del    ", 112,7,5);



for( v =3;v<=6;v++){
www_PrintString(" ", 0,23,v);
}
www_PrintString("               ",0,8,6);
www_PrintString("*>",112,r,2);

}




void m3 (){
	int v ;
	mx =3;
 mn = 2;
 r =12;
 t = 2;
	www_PrintString("Option", 31,12,1);
www_PrintString("  F", 116,12,2);
www_PrintString("onts        ", 112,15,2);
www_PrintString("  S", 116,12,3);
www_PrintString("et Language ", 112,15,3);

for( v =3;v<=4;v++){
www_PrintString(" ", 0,27,v);
}
www_PrintString("               ",0,13,4);
www_PrintString("*>",112,r,2);
}


//void ctrlF () { m1();}
//void ctrlE () {m2();}
//void ctrlO () {m3();}
//void ctrlH () {m4();}



void m4 () {

	mx =2;
 mn = 2;
 r =19;
 t = 2;
 www_PrintString("help", 31,19,1);
 www_PrintString("  V", 116,19,2);
www_PrintString("iew Help ", 112,22,2);
www_PrintString("*>",112,r,t);



www_PrintString("            ",0,20,3);
www_PrintString("*>",112,r,2);
}





void AA(void)
{
	int x;
	int f;

enum KeyBoard_Keys MyKey = KeyBoard_Keys_F;
char  *ptr=(char *)0xb8000;

KeyHandler MyHandler= (KeyHandler) &m1;

//X_ClearScrean(0x00);
www_PrintString(" XIOS Editor...                                                             _ X ", 112,0,0);

www_PrintString("  F", 4,0,1);
www_PrintString("ile", 7,3,1);
www_PrintString(" E", 4,6,1);
www_PrintString("dit", 7,8,1);
www_PrintString(" O", 4,11,1);
www_PrintString("ption", 7,13,1);
www_PrintString(" H", 4,18,1);
www_PrintString("elp", 7,20,1);
www_PrintString("                                                        ", 7,23,1);

www_PrintString("                                                          from Xero to Infinity ", 112,0,24);
www_ClearBody(23) ;

for (x=160 ;x<=3839 ; x=x+160){
	*(ptr+(x)) = ' ' ;
*(ptr+ (x+1))= 7 ;
}
*(ptr+478) =' ';
*(ptr+479) =6;



for (f=318 ;f<=3839 ; f=f+160){
*(ptr+(f)) = ' ' ;
*(ptr+ (f+1))= 7 ;
}

//screen4();
//m1();
Keyboard_UpdateHandler(MyKey, MyHandler);

}