
#include <MemMappedIO-IA32.h>
#include <stdint.h>

/***************Status bits we'll use***********************/

//The KB controller have data ready to be read.
#define KB_StatusRegister_DataReady	0x01

//The KB controller is busy performing some command.
#define KB_StatusRegister_DeviceBusy	0x02
/***********************************************************/



/*************Ports****************************************/

//Keyboard data register (read)
#define KB_Ports_DataReg				0x60
//Keyboard Encoder command register (write)
#define KB_Ports_EncoderCommandReg		0x60
//Keyboard Status register (Read)
#define KB_Ports_StatusReg			0x64
//Keyboard Controller command register (Write)
#define KB_Ports_ControllerCommandReg	0x64
/**********************************************************/




/**********Keyboard encoder commands***********************/

//The LEDS of keyboard command; After sending this command you should send the data of LEDs.
#define KB_Encoder_Command_SetLeds		0xED
/**********************************************************/



/******Keyboard controller commands***********************/

#define KB_Controller_Command_SelfTest			0xAA
#define KB_Controller_Command_InterfaceTest		0xAB
#define KB_Controller_Command_DisablrKeyBoard	0xAD
#define KB_Controller_Command_EnableKeyBoard		0xAE
#define KB_Controller_Command_ReadOutPort		0xD0
#define KB_Controller_Command_WriteOutPort		0xD1
/*********************************************************/



/*********************OutPort*****************************/

#define KB_OutPort_ResetCpu				0x00
#define KB_OutPort_NormalCpuOperation		0x01

#define KB_OutPort_A20GateEnabled			0x02
#define KB_OutPort_A20GateDisabled			0x00
/*********************************************************/



/****************LED***************************************/

#define KB_LED_ScrollLock_True			0x01

#define KB_LED_Numlock_True				0x02

#define KB_LED_CapsLock_True				0x04
/**********************************************************/



struct KBStatus
{
	uint8 CapsLock;
	uint8 LShift;
	uint8 LCtrl;
	uint8 LAlt;
	uint8 RAlt;
	uint8 RCtrl;
	uint8 RShift;
	uint8 NumLock;
	uint8 ScrollLock;
} Keyboard_Status = {0, 0, 0, 0, 0, 0, 0, 0, 0};


typedef struct KBStatus KeyboardStatus;


//NoSupport for printscreen, pause,..
//I know my code is not flexible, but I have no time really.

//The keyboard keys virtual codes.
enum KeyBoard_Keys
{	
	 KeyBoard_Keys_Esc			=1			
	,KeyBoard_Keys_1					
	,KeyBoard_Keys_2						
	,KeyBoard_Keys_3						
	,KeyBoard_Keys_4						
	,KeyBoard_Keys_5						
	,KeyBoard_Keys_6						
	,KeyBoard_Keys_7						
	,KeyBoard_Keys_8						
	,KeyBoard_Keys_9						
	,KeyBoard_Keys_0						
	,KeyBoard_Keys_Minus					
	,KeyBoard_Keys_Equal					
	,KeyBoard_Keys_BackSpace				
	,KeyBoard_Keys_Tab					
	,KeyBoard_Keys_Q						
	,KeyBoard_Keys_W
	,KeyBoard_Keys_E
	,KeyBoard_Keys_R						
	,KeyBoard_Keys_T						
	,KeyBoard_Keys_Y						
	,KeyBoard_Keys_U						
	,KeyBoard_Keys_I						
	,KeyBoard_Keys_O						
	,KeyBoard_Keys_P						
	,KeyBoard_Keys_LeftBracket				
	,KeyBoard_Keys_RightBracket				
	,KeyBoard_Keys_Enter					
	,KeyBoard_Keys_LeftCtrl				
	,KeyBoard_Keys_A						
	,KeyBoard_Keys_S						
	,KeyBoard_Keys_D						
	,KeyBoard_Keys_F						
	,KeyBoard_Keys_G						
	,KeyBoard_Keys_H						
	,KeyBoard_Keys_J						
	,KeyBoard_Keys_K						
	,KeyBoard_Keys_L						
	,KeyBoard_Keys_SemiColon					
	,KeyBoard_Keys_SingleQuotation			
	,KeyBoard_Keys_Apostrophe					
	,KeyBoard_Keys_LeftShift				
	,KeyBoard_Keys_BackSlash				
	,KeyBoard_Keys_Z						
	,KeyBoard_Keys_X						
	,KeyBoard_Keys_C						
	,KeyBoard_Keys_V						
	,KeyBoard_Keys_B						
	,KeyBoard_Keys_N						
	,KeyBoard_Keys_M						
	,KeyBoard_Keys_Coma				
	,KeyBoard_Keys_Dot				
	,KeyBoard_Keys_Slash			
	,KeyBoard_Keys_RightShift				
	,KeyBoard_Keys_Keypad_Astrisk		
	,KeyBoard_Keys_LeftAlt
	,KeyBoard_Keys_SpaceBar
	,KeyBoard_Keys_CapsLock				
	,KeyBoard_Keys_F1						
	,KeyBoard_Keys_F2						
	,KeyBoard_Keys_F3						
	,KeyBoard_Keys_F4						
	,KeyBoard_Keys_F5						
	,KeyBoard_Keys_F6						
	,KeyBoard_Keys_F7						
	,KeyBoard_Keys_F8						
	,KeyBoard_Keys_F9						
	,KeyBoard_Keys_F10					
	,KeyBoard_Keys_NumLock
	,KeyBoard_Keys_ScrollLock
	,KeyBoard_Keys_Keypad_7
	,KeyBoard_Keys_Keypad_8
	,KeyBoard_Keys_Keypad_9
	,KeyBoard_Keys_Keypad_Minus
	,KeyBoard_Keys_Keypad_4
	,KeyBoard_Keys_Keypad_5
	,KeyBoard_Keys_Keypad_6
	,KeyBoard_Keys_Keypad_Plus
	,KeyBoard_Keys_Keypad_1
	,KeyBoard_Keys_Keypad_2
	,KeyBoard_Keys_Keypad_3
	,KeyBoard_Keys_Keypad_0
	,KeyBoard_Keys_Keypad_Dot
	,KeyBoard_Keys_F11			=0x57	
	,KeyBoard_Keys_F12
	,KeyBoard_Keys_Keypad_Enter
	,KeyBoard_Keys_RightCrtl
	,KeyBoard_Keys_Keypad_Slash
	,KeyBoard_Keys_RightAlt
	,KeyBoard_Keys_Home
	,KeyBoard_Keys_Up
	,KeyBoard_Keys_Down
	,KeyBoard_Keys_Right
	,KeyBoard_Keys_Left
	,KeyBoard_Keys_PageUp
	,KeyBoard_Keys_PageDown
	,KeyBoard_Keys_Insert
	,KeyBoard_Keys_Delete
	,KeyBoard_Keys_End
	,Keyboard_Keys_Menu
};

uint8 Ascii[103] =
{	
	0	,
	0x1B	,
	'1'	,
	'2'	,
	'3'	,
	'4'	,
	'5'	,
	'6'	,
	'7'	,
	'8'	,
	'9'	,
	'0'	,
	'-'	,
	'='	,
	0x08	,
	0x09	,
	'q'	,
	'w'	,
	'e'	,
	'r'	,
	't'	,
	'y'	,
	'u'	,
	'i'	,
	'o'	,
	'p'	,
	'['	,
	']'	,
	0x0A	,
	 0	,
	 'a'	,
	 's'	,
	 'd'	,
	 'f'	,
	 'g'	,
	 'h'	,
	 'j'	,
	 'k'	,
	 'l'	,
	 ';'	,
	 0x27,
	 '`'	,
	  0	,
	 0x5c,
	 'z'	,
	 'x'	,
	 'c'	,
	 'v'	,
	 'b'	,
	 'n'	,
	 'm'	,
	 ','	,
	 '.'	,
	 '/'	,
	  0	,
	 '*'	,
	  0	,
	 0x20,
	 0	,
	 0	,
	 0	,
	 0	,
	 0	,
	 0	,
	 0	,
	 0	,
	 0	,
	 0	,
	 0	,
	 0	,
	 0	,
	 '7'	,
	 '8'	,
	 '9'	,
	 '-'	,
	 '4'	,
	 '5'	,
	 '6'	,
	 '+'	,
	 '1'	,
	 '2'	,
	 '3'	,
	 '0'	,
	 '.'	,
	 0	,
	 0	,
	 0	,
	 0	,
	 0	,
	 0x0A,
	 0	,
	 0	,
	 0	,
	 0	,
	 0	,
	 0	,
	 0	,
	 0	,
	 0	,
	 0	,
	 0	,
	 0	,
	 0	
};







//Type definition for the handlers of keys pressing.
typedef void (* KeyHandler)(void);



//The Keys handlers array.. I use the the virtual key as index to its handler directly.
//127 the max number of make scan codes. I know we need only 103, but this is better getting null pointer or wild pointer calling ;)
KeyHandler * KB_Keys_Handlers;

KeyHandler DefaultKeysHandlers [127];

KeyHandler CustomKeysHandlers [127];

static uint32 LastPressed =0;




void KB_InterruptHandler(void);

void Keyboard_UpdateHandler(enum KeyBoard_Keys Key, KeyHandler Handler);
