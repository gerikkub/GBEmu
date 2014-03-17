#ifndef __JOYPAD_H__
#define __JOYPAD_H__

#define BUTTON_SELECT_DIRECTION	1
#define BUTTON_SELECT_BUTTON	0

extern int buttonMatrix;
extern int currentButtonSelect;

void initJoypad();
void joypadUpdate();

#endif