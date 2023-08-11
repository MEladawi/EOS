

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



//The Handler of keys pressing.
typedef void (* KeyHandler)(void);


//To update the action of pressing key.
void Keyboard_UpdateHandler(enum KeyBoard_Keys Key, KeyHandler Handler);


//Restore all default hanlders of pressing keys. 
void Keyboard_RestoreDefaultHandlers();

//Disable the keyboard input.
void KB_DisableKeyBoard(void);

//Enable Keyboard input
void KB_EnableKeyBoard(void);

extern struct KBStatus
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
} Keyboard_Status;