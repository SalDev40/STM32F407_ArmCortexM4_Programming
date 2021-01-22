/*
 * led.c
 *
 *  Created on: Jan 22, 2021
 */

#include<stdint.h>
#include "led.h"

void delay(uint32_t count) {
	for (uint32_t i = 0; i < count; i++)
		;
}

void led_init_all(void) {
	uint32_t volatile *const ppRcc = (uint32_t*) 0x40023830;
	uint32_t volatile *const ppGpioOutModeReg = (uint32_t*) 0x40020C00;

	*ppRcc = (1 << 3);

	*ppGpioOutModeReg &= ~(1 << 24);
	*ppGpioOutModeReg &= ~(1 << 25);
	*ppGpioOutModeReg &= ~(1 << 26);
	*ppGpioOutModeReg &= ~(1 << 27);
	*ppGpioOutModeReg &= ~(1 << 28);
	*ppGpioOutModeReg &= ~(1 << 29);
	*ppGpioOutModeReg &= ~(1 << 30);
	*ppGpioOutModeReg &= ~(1 << 31);


	*ppGpioOutModeReg |= (1 << 24); //LED_GREEN
	*ppGpioOutModeReg |= (1 << 26); //LED_ORANGE
	*ppGpioOutModeReg |= (1 << 28); //LED_RED
	*ppGpioOutModeReg |= (1 << 30); //LED_BLUE

	led_off(LED_GREEN);
	led_off(LED_BLUE);
	led_off(LED_ORANGE);
	led_off(LED_RED);
}
void led_on(uint8_t led_no) {

	uint32_t volatile *const ppGpioOutDataReg = (uint32_t*) 0x40020C14;
	*ppGpioOutDataReg = (1 << led_no);
}

void led_off(uint8_t led_no) {
	uint32_t volatile *const ppGpioOutDataReg = (uint32_t*) 0x40020C14;
	*ppGpioOutDataReg &= ~(1 << led_no);
}

