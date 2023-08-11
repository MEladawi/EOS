


//The i8042 is usually set to translate key codes from scancode 2 to scancode 1 .



//Includes---------------------------------------------------------------------------------
#include "KB.h"
#include <Platform_Dependent.h>
#include <TextDisplay.h>
//--------------------------------------------------------------------------------------------




//Private--------------------------------------------------------------------------------------------

__forceinline uint8 KB_ReadData()
{
	while(!(InPortByte(KB_Ports_StatusReg) & KB_StatusRegister_DataReady));
	return InPortByte(KB_Ports_DataReg);
}



void DefaultKBHandler()
{ 
	//EOS_PrintString(Ascii[LastPressed] ,0x47,5,6);
	XPrintChar(Ascii[LastPressed], 0xF0);
	LastPressed=0;
}



__forceinline uint8 KB_ReadStatus()
{
	return InPortByte(KB_Ports_StatusReg);
}




__forceinline void KB_SendEncoderCommand(uint8 Command)
{
	
	while(InPortByte(KB_Ports_StatusReg) & KB_StatusRegister_DeviceBusy);
	OutPortByte(KB_Ports_EncoderCommandReg, Command);
}





__forceinline void KB_SendControllerCommand(uint8 Command)
{
	while(InPortByte(KB_Ports_StatusReg) & KB_StatusRegister_DeviceBusy);
	OutPortByte(KB_Ports_ControllerCommandReg,  Command);
}





void KB_UpdateLEDs()
{
	uint8 LED_Command = 0;

	if (Keyboard_Status.ScrollLock) LED_Command |= KB_LED_ScrollLock_True;
	if (Keyboard_Status.NumLock)    LED_Command |= KB_LED_Numlock_True;
	if (Keyboard_Status.CapsLock)   LED_Command |= KB_LED_CapsLock_True;

	KB_SendEncoderCommand (KB_Encoder_Command_SetLeds);
	KB_SendEncoderCommand (LED_Command);
}





_inline uint8 Get_Extended_KBVirtualCode(uint8 ScanCode)
{
	uint8 VirtualCode = 0;
	
	switch (ScanCode)
	{
	case 0x1C : 
		VirtualCode= 89;
		break;

	case 0x1D : 
		VirtualCode= 90;
		break;

	case 0x35 : 
		VirtualCode= 91;
		break;

	case 0x38 : 
		VirtualCode= 92;
		break;

	case 0x47 : 
		VirtualCode= 93;
		break;

	case 0x48 : 
		VirtualCode= 94;
		break;

	case 0x50 : 
		VirtualCode= 95;
		break;

	case 0x4D : 
		VirtualCode= 96;
		break;

	case 0x4B : 
		VirtualCode= 97;
		break;

	case 0x49 : 
		VirtualCode= 98;
		break;

	case 0x51 : 
		VirtualCode= 99;
		break;

	case 0x52 : 
		VirtualCode= 100;
		break;

	case 0x53 : 
		VirtualCode= 101;
		break;
	case 0x4f : 
		VirtualCode= 102;
		break;

	case 0x5d : 
		VirtualCode= 103;
		break;
	}

	return VirtualCode;
}




ISR void KBHandlerCaller(void)
{
	//Prologue of Function
	_asm pushad


	KB_InterruptHandler();
	//EOS_PrintString("Thank you ALLAH :D",0x13,5,6);

	//Epilogue of function 
	OutPortByte(0x20, 0x20);
	_asm popad
	_asm iretd
}




void KB_InterruptHandler(void)
{

	uint8		ScanCode		= KB_ReadData();
	int32		VirtualCode	= 0;
	KeyHandler	Handler		= (KeyHandler) 0;
	uint8 static	Extended		= 0;


	//extension??!
	if (ScanCode == 0xE0)
	{
		Extended = 1;
	}


	//Not extension sign 
	else
	{

		//BreakCode---------------------------------------------------------------
		if (ScanCode & 128)		
		{
			ScanCode -= 128;

			if (Extended) 
			{
				VirtualCode = Get_Extended_KBVirtualCode(ScanCode);
			}
			
			else
			{
				if (ScanCode <= 88 )
				{
					 VirtualCode = ScanCode; 
				}
			}

			LastPressed=VirtualCode;
			Extended = 0;

			switch (VirtualCode)
			{
			case (KeyBoard_Keys_RightAlt)		:	
				Keyboard_Status.RAlt	=0;
				break;

			case (KeyBoard_Keys_RightCrtl)	:	
				Keyboard_Status.RCtrl	=0;
				break;

			case (KeyBoard_Keys_RightShift)	:	
				Keyboard_Status.RShift	=0;
				break;

			case (KeyBoard_Keys_LeftAlt)		:	
				Keyboard_Status.LAlt	=0;
				break;

			case (KeyBoard_Keys_LeftCtrl)		:	
				Keyboard_Status.LCtrl	=0;
				break;

			case (KeyBoard_Keys_LeftShift)	:	
				Keyboard_Status.LShift	=0;
				break;
			}
		}
		//------------------------------------------------------------------------





		//MakeCode--------------------------------------------------------------------
		else
		{

			if (Extended) 
			{
				VirtualCode = Get_Extended_KBVirtualCode(ScanCode);
			}
			
			else
			{
				if (ScanCode <= 88 )
				{
					 VirtualCode = ScanCode; 
				}
			}

			LastPressed = VirtualCode;
			Extended = 0;

			
			if (VirtualCode) Handler = KB_Keys_Handlers[VirtualCode];
			else goto End;


			//Modifiers:
			switch (VirtualCode)
			{
			case (KeyBoard_Keys_RightAlt):	
				Keyboard_Status.RAlt	=1;
				break;

			case (KeyBoard_Keys_RightCrtl):	
				Keyboard_Status.RCtrl	=1;
				break;

			case (KeyBoard_Keys_RightShift):	
				Keyboard_Status.RShift	=1;
				break;

			case (KeyBoard_Keys_LeftAlt):	
				Keyboard_Status.LAlt	=1;
				break;

			case (KeyBoard_Keys_LeftCtrl):	
				Keyboard_Status.LCtrl	=1;
				break;

			case (KeyBoard_Keys_LeftShift):	
				Keyboard_Status.LShift	=1;
				break;

			case KeyBoard_Keys_CapsLock:
				Keyboard_Status.CapsLock = (!Keyboard_Status.CapsLock);
				KB_UpdateLEDs();
				break;

			case KeyBoard_Keys_ScrollLock:
				Keyboard_Status.ScrollLock = (!Keyboard_Status.ScrollLock);
				KB_UpdateLEDs();
				break;

			case KeyBoard_Keys_NumLock:
				Keyboard_Status.NumLock = (!Keyboard_Status.NumLock);
				KB_UpdateLEDs();
				break;

			}
End:

			if (Handler) Handler();

		}
		//-----------------------------------------------------------
	

	}

	
}

//----------------------------------------------------------------------------------------------








//Public-----------------------------------------------------------------------------------------
void KB_DisableKeyBoard(void)
{
	KB_SendControllerCommand(KB_Controller_Command_DisablrKeyBoard);
}




void KB_EnableKeyBoard(void)
{
	KB_SendControllerCommand(KB_Controller_Command_EnableKeyBoard);
}



//void TestHandler()
//{
//	EOS_PrintString("Shokran Ya RAAAAAAAAB (FromTest)",0x47,5,9);
//}




void InitializeKeyboard(void)
{
	register uint8 i;

	//enum KeyBoard_Keys Key = KeyBoard_Keys_1;

	KB_Keys_Handlers = (KeyHandler*) &DefaultKeysHandlers[0];

	for (i=0; i<127; i++) KB_Keys_Handlers[i]   = (KeyHandler) &DefaultKBHandler;
	for (i=0; i<127; i++) CustomKeysHandlers[i] = (KeyHandler) &DefaultKBHandler;

	IDT_AddHandler(PIC_IRQ_Devices_Keyboard, (uint32) &KBHandlerCaller, 0x8,
		 IDT_Flags_32Bit
		|IDT_Flags_Default
		|IDT_Flags_Present);

	

	//Keyboard_UpdateHandler(Key, (KeyHandler) &TestHandler);

}





void Keyboard_UpdateHandler(enum KeyBoard_Keys Key, KeyHandler Handler)
{
	CustomKeysHandlers[(uint32)Key] = Handler;
	KB_Keys_Handlers = &CustomKeysHandlers[0];
}




void Keyboard_RestoreDefaultHandlers()
{
	KB_Keys_Handlers = &DefaultKeysHandlers[0];
}



