/*
  BPLib.h - Library for communication with RN-42 HID Bluetooth module
  Created by Basel Al-Rudainy, 6 april 2013.
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*/
#ifndef BPLib_h
#define BPLib_h

#include "Arduino.h"

//Bluetooth Modes
#define BP_MODE_COMMAND    	"$$$"
#define BP_MODE_EXITCOMMAND  	"---\r\n"
#define BP_MODE_SPP  			"S~,0\r\n"
#define BP_MODE_HID  			"S~,6\r\n"
#define BP_MODE_AUTOCONNECT  	"SM,6\r\n"
#define BP_MODE_MANUCONNECT  	"SM,4\r\n"
#define BP_MODE_STATUS			"SO,/#\r\n"

//Bluetooth status messages
#define BP_STAT_CMD  			"CMD\r\n"
#define BP_STAT_END  			"END\r\n"
#define BP_STAT_ACK  			"AOK\r\n"
#define BP_STAT_REBOOT  		"Reboot!\r\n"
//Bluetooth GET commands
#define BP_GET_HID  			"GH\n"

//Bluetooth system commands
#define BP_REBOOT  				"R,1\r\n"
#define BP_RECONNECT  			"C\r\n"
#define BP_CHANGE_NAME			"SN,"
//Bluetooth protocol types
#define BP_SPP_SPP				"AW\r\n"
#define BP_HID_KEYBOARD  		"SH,0200\r\n"
#define BP_HID_MOUSE  			"SH,0220\r\n"
#define BP_HID_GAMEPAD  		"SH,0210\r\n"
#define BP_HID_JOYSTICK  		"SH,0240\r\n"
#define BP_HID_COMBO  			"SH,0230\r\n"

// KEYBOARD Scan Codes
#define BP_KEY_SPACE 0xCD
#define	BP_KEY_ENTER		0x28	//Enter
#define BP_KEY_RIGHT 0x4F
#define	BP_KEY_LEFT  0x50 //Left arrow
#define	BP_KEY_DOWN  0x51 //Down arrow
#define BP_KEY_UP    0x52  //Up arrow
#define	BP_KEY_ENTER 0x28	//Enter
#define	BP_KEY_ESC		0x29	//Escape
#define	BP_KEY_CAPSLOCK		0x39	//CapsLock
#define	BP_KEY_SCROLLLOCK	0x47	//ScrollLock
#define	BP_KEY_BREAK_PAUSE	0x48	//Break-pause
#define	BP_KEY_NUMLOCK		0x53	//NumLock
#define	BP_KEY_TOGGLE_IPHONE_VIRTUAL_KEYBOARD	0x65	//Toggle iPhone Virtual Keyboard
#define	BP_KEY_LEFT_CONTROL	0xE0	//Left Control
#define	BP_KEY_LEFT_SHIFT	0xE1	//Left Shift
#define	BP_KEY_LEFT_ALT		0xE2	//Left Alt
#define	BP_KEY_LEFT_GUI		0xE3	//Left GUI
#define	BP_KEY_RIGHT_CONTROL	0xE4	//Right Control
#define	BP_KEY_RIGHT_SHIFT	0xE5	//Right Shift
#define	BP_KEY_RIGHT_ALT	0xE6	//Right Alt
#define	BP_KEY_RIGHT_GUI	0xE7	//Right GUI
#define	BP_KEY_F1	0x3A	//F1
#define	BP_KEY_F2	0x3B	//F2
#define	BP_KEY_F3	0x3C	//F3
#define	BP_KEY_F4	0x3D	//F4
#define	BP_KEY_F5	0x3E	//F5
#define	BP_KEY_F6	0x3F	//F6
#define	BP_KEY_F7	0x40	//F7
#define	BP_KEY_F8	0x41	//F8
#define	BP_KEY_F9	0x42	//F9
#define	BP_KEY_F10	0x43	//F10
#define	BP_KEY_F11	0x44	//F11
#define	BP_KEY_F12	0x45	//F12

#define BP_KEY_A 0x04
#define BP_KEY_B 0x05
#define BP_KEY_C 0x06
#define BP_KEY_D 0x07
#define BP_KEY_E 0x08
#define BP_KEY_F 0x09
#define BP_KEY_G 0x0A
#define BP_KEY_H 0x0B
#define BP_KEY_I 0x0C
#define BP_KEY_J 0x0D
#define BP_KEY_K 0x0E
#define BP_KEY_L 0x0F
#define BP_KEY_M 0x10
#define BP_KEY_N 0x11
#define BP_KEY_O 0x12
#define BP_KEY_P 0x13
#define BP_KEY_Q 0x14
#define BP_KEY_R 0x15
#define BP_KEY_S 0x16
#define BP_KEY_T 0x17
#define BP_KEY_U 0x18
#define BP_KEY_V 0x19
#define BP_KEY_W 0x1A
#define BP_KEY_X 0x1B
#define BP_KEY_Y 0x1C
#define BP_KEY_Z 0x1D

#define BP_KEY_1 0x1E
#define BP_KEY_2 0x1F
#define BP_KEY_3 0x20
#define BP_KEY_4 0x21
#define BP_KEY_5 0x22
#define BP_KEY_6 0x23
#define BP_KEY_7 0x24
#define BP_KEY_8 0x25
#define BP_KEY_9 0x26
#define BP_KEY_0 0x27


#define BP_KEYPAD_1 0x59
#define BP_KEYPAD_2 0x5A
#define BP_KEYPAD_3 0x5B
#define BP_KEYPAD_4 0x5C
#define BP_KEYPAD_5 0x5D
#define BP_KEYPAD_6 0x5E
#define BP_KEYPAD_7 0x5F
#define BP_KEYPAD_8 0x60
#define BP_KEYPAD_9 0x61
#define BP_KEYPAD_0 0x62

//KEYBOARD MODEFIER CODES
#define BP_MOD_RIGHT_GUI	(1<<7)
#define BP_MOD_RIGHT_ALT	(1<<6)
#define BP_MOD_RIGHT_SHIFT	(1<<5)
#define BP_MOD_RIGHT_CTRL	(1<<4)
#define BP_MOD_LEFT_GUI		(1<<3)
#define BP_MOD_LEFT_ALT		(1<<2)
#define BP_MOD_LEFT_SHIFT	(1<<1)
#define BP_MOD_LEFT_CTRL	(1<<0)
#define BP_MOD_NOMOD		0x00

//Mouse Codes
#define BP_MOUSE_BTN_LEFT	(1<<0)
#define BP_MOUSE_BTN_RIGHT	(1<<1)
#define BP_MOUSE_BTN_MIDDLE	(1<<2)

//GAMEPAD/JOYSTICK BUTTON CODES
//ST == First button combination (BTN0 to BTN7)
#define BP_GAMEJOY_ST_BTN0	(1<<0)
#define BP_GAMEJOY_ST_BTN1	(1<<1)
#define BP_GAMEJOY_ST_BTN2	(1<<2)
#define BP_GAMEJOY_ST_BTN3	(1<<3)
#define BP_GAMEJOY_ST_BTN4	(1<<4)
#define BP_GAMEJOY_ST_BTN5	(1<<5)
#define BP_GAMEJOY_ST_BTN6	(1<<6)
#define BP_GAMEJOY_ST_BTN7	(1<<7)
#define BP_GAMEJOY_ST_NOBTN	0x00

//ND = Second button combination (BTN0 to BTN7)
#define BP_GAMEJOY_ND_BTN0	(1<<0)
#define BP_GAMEJOY_ND_BTN1	(1<<1)
#define BP_GAMEJOY_ND_BTN2	(1<<2)
#define BP_GAMEJOY_ND_BTN3	(1<<3)
#define BP_GAMEJOY_ND_BTN4	(1<<4)
#define BP_GAMEJOY_ND_BTN5	(1<<5)
#define BP_GAMEJOY_ND_BTN6	(1<<6)
#define BP_GAMEJOY_ND_BTN7	(1<<7)
#define BP_GAMEJOY_ND_NOBTN	0x00

class BPLib {

public:
  BPLib();
  byte begin(char BP_Mode[], char BP_Type[]);
  byte sendCmd(char BP_CMD[]);
  void sendByte(byte rawData);
  void sendChar(char rawData);
  void sendInt(int rawData);
  void sendFloat(float rawData);
  void sendLong(long rawData);
  void sendString(char rawData[]);
  byte readRaw();
  int available();
  void keyboardPrint(char BP_MSG[]);
  void keyboardPress(byte BP_KEY, byte BP_MOD);
  void keyboardRelease(byte BP_KEY);
  void keyboardReleaseAll();
  void mouseClick(byte BP_BUTTON);
  void mouseMove(signed int BP_X, signed int BP_Y);
  void mouseWheel(signed int BP_WHEEL);
  void mousePress(byte BP_BUTTON);
  void mouseReleaseAll();
  void gameJoyPress(byte BP_ST_BTN, byte BP_ND_BTN);
  void gameJoyMove(signed int BP_X1, signed int BP_Y1, signed int BP_X2, signed int BP_Y2);
  void gameJoyReleaseAll();
  byte connected();
  byte changeName(char BP_NAME[]);
  
private:
  byte get(char BP_STAT[], byte strlen);
  
};
#endif
