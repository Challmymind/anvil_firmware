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


uint_fast8_t LAYOUTS[2][3][10] =
{

		{
				{0x14, 0x1a, 0x08, 0x15, 0x17, 0x1c, 0x18, 0x0c, 0x12, 0x13},
				{0x04, 0x16, 0x07, 0x09, 0x0a, 0x0b, 0x0d, 0x0e, 0x0f, 0x00},
				{0x1d, 0x1b, 0x06, 0x19, 0x2c, 0x05, 0x11, 0x10, 0x00, 0x28}
		},
		{
				{0x29, 0x00, 0x14, 0x1a, 0x08, 0x15, 0x00, 0x00, 0x00, 0x00},
				{0x00, 0x00, 0x04, 0x16, 0x07, 0x09, 0x0a, 0x00, 0x00, 0x00},
				{0x00, 0x00, 0x00, 0x00, 0x2c, 0x2c, 0x00, 0x00, 0x00, 0x28}
		}

};

uint_fast8_t STATUS[3][10] = {
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}
};
uint_fast8_t report_offset = 2;
uint_fast8_t current_layout = MAIN_LAYOUT;
uint8_t keybord_report[KEYBOARD_REPORT_SIZE] = {0};

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

	while(1){

		uint_fast8_t x = 0;

		while(x < 3){
			uint_fast8_t y = 0;
			HAL_GPIO_WritePin(r_ports[x], r_pins[x], 1);
			while(y < 10){
				if(HAL_GPIO_ReadPin(c_ports[y], c_pins[y])){
					if(!STATUS[x][y]){
						//					_keybord_report[2+_key_count] = LAYOUT_1[x][y];
						//					_key_count += 1;
						//					_STATUS[x][y] = _key_count;

						STATUS[x][y] = report_offset;
						report_offset++;

						//					keybord_report[2] = LAYOUTS[current_layout][x][y];
						//					key_count += 1;
						//					STATUS[x][y] = key_count;
					}

				}
				else {
					if(STATUS[x][y]){
						//					_keybord_report[2+_STATUS[x][y]-1] = 0;
						//					uint8_t size = _key_count - _STATUS[x][y];
						//					memmove(_keybord_report+(2+_STATUS[x][y]-1),_keybord_report+(2+_STATUS[x][y]),size);
						//					_STATUS[x][y] = 0;
						//					_key_count -= 1;
						//
						//					if(STATUS[x][y] == key_count) keybord_report[2] = 0;
						//					STATUS[x][y] = 0;
						//					key_count -= 1;



						uint_fast8_t m = 0;
						while(m < 3){
							uint_fast8_t n = 0;
							while(n < 10){
								if(STATUS[m][n] > STATUS[x][y]) STATUS[m][n]--;
								n++;
							}
							m++;
						}
						STATUS[x][y] = 0;
						report_offset--;
					}
				}

				y++;
			}
			HAL_GPIO_WritePin(r_ports[x], r_pins[x], 0);
			x++;
		}

		uint_fast8_t m = 0;
		memset(keybord_report,0,sizeof(keybord_report));
		switch (current_layout){
		case MAIN_LAYOUT:
			if(STATUS[1][0] || STATUS[0][1]){
				if(STATUS[1][0] < STATUS[0][1]){
					current_layout = GAME_LAYOUT;
					break;
				}
			}
		case GAME_LAYOUT:
			if(STATUS[2][0]){
				current_layout=MAIN_LAYOUT;
			}
			break;
		}
		while(m < 3){
			uint_fast8_t n = 0;
			while(n < 10){
				if(STATUS[m][n])
					keybord_report[STATUS[m][n]] = LAYOUTS[current_layout][2-m][9-n];

				n++;
			}
			m++;
		}
		if(current_layout == GAME_LAYOUT && (STATUS[1][9]&&STATUS[1][8])) keybord_report[0] = 2;
		USBD_HID_SendReport(&hUsbDeviceFS, keybord_report, KEYBOARD_REPORT_SIZE);
		HAL_Delay(10);

//	}
	}
}

