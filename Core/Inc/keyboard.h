/*
 * keyboard.h
 *
 *  Created on: Aug 9, 2024
 *      Author: Michał Lasoń
 */

#ifndef INC_KEYBOARD_H_
#define INC_KEYBOARD_H_

#include <stdint.h>

#define KEYBOARD_REPORT_SIZE 32

enum LAYOUT_PAGE{
		MAIN_LAYOUT,
		SECOND_LAYOUT,
		THIRD_LAYOUT
};

void keybord_loop();

#endif /* INC_KEYBOARD_H_ */
