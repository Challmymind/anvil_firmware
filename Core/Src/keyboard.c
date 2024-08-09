/*
 * keyboard.c
 *
 *  Created on: Aug 9, 2024
 *      Author: Michał Lasoń
 */

#include "keyboard.h"
#include "main.h"
#include "usb_device.h"
#include "usbd_hid.h"

extern USBD_HandleTypeDef hUsbDeviceFS;
uint8_t _keybord_report[KEYBOARD_REPORT_SIZE] = {0};

uint8_t _current_layout = MAIN_LAYOUT;

GPIO_TypeDef* c_ports[] = {
		COL0_GPIO_Port,
		COL1_GPIO_Port,
		COL2_GPIO_Port,
		COL3_GPIO_Port,
		COL4_GPIO_Port,
		COL5_GPIO_Port,
		COL6_GPIO_Port,
		COL7_GPIO_Port,
		COL8_GPIO_Port,
		COL9_GPIO_Port
};

GPIO_TypeDef* r_ports[] = {
		ROW0_GPIO_Port,
		ROW1_GPIO_Port,
		ROW2_GPIO_Port
};

uint16_t c_pins[] = {
		COL0_Pin,
		COL1_Pin,
		COL2_Pin,
		COL3_Pin,
		COL4_Pin,
		COL5_Pin,
		COL6_Pin,
		COL7_Pin,
		COL8_Pin,
		COL9_Pin
};

uint16_t r_pins[] = {
		ROW0_Pin,
		ROW1_Pin,
		ROW2_Pin
};

void keybord_loop(){

	int x = 0;

	while(x < 3){
		int y = 0;
		HAL_GPIO_WritePin(r_ports[x], r_pins[x], 1);
		while(y < 10){
			if(HAL_GPIO_ReadPin(c_ports[y], c_pins[y])){
					_keybord_report[2] = 7;
					USBD_HID_SendReport(&hUsbDeviceFS, _keybord_report, KEYBOARD_REPORT_SIZE);
					HAL_Delay(50);
					_keybord_report[2] = 0;
					USBD_HID_SendReport(&hUsbDeviceFS, _keybord_report, KEYBOARD_REPORT_SIZE);
			}

			y += 1;
		}
		HAL_GPIO_WritePin(r_ports[x], r_pins[x], 0);
		x += 1;
	}
}
