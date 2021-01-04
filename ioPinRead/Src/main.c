/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stdio.h>

int main(void) {

	//get register addresses in the peripherals (Base + Offset)
	uint32_t *const pRccGPIOAD = (uint32_t*) 0x40023830;
	uint32_t *const pGPIODOut = (uint32_t*) 0x40020C14;
	uint32_t *const pGPIODMode = (uint32_t*) 0x40020C00;

	uint32_t *const pGPIOAIn = (uint32_t*) 0x40020010;
	uint32_t *const pGPIOAMode = (uint32_t*) 0x40020000;

	//Turn on RCC clock for GPIOD and GPIOA
	//shift the bits in the Register Corresponding to

	//RCC AHB1 peripheral clock register (RCC_AHB1ENR)
	*pRccGPIOAD |= (1 << 0); //GPIOA, first bit turn to high
	*pRccGPIOAD |= (1 << 3); //GPIOD, third but turn to high

	//configure PD12 pin as output (GPIOD MODE REGISTER)
	*pGPIODMode &= (3 << 24); //clear 24/25th bits to in mode register
	*pGPIODMode |= (1 << 24); //turn 24th bit to high for general purpose  mode

	//configure PA0 as input  (GPIOA MODE REGISTER)
	*pGPIOAMode &= ~(3 << 0); //clear first two bits to 0

	//read pin status of PA0 (GPIOA INPUT DATA REGISTER)
	//will read 32 bits of data, but we only need 0th bit so
	//we will mask out rest of bits
	while (1) {
		uint8_t pinStatus = (uint8_t) (*pGPIOAIn & 0x1);

		//if PA0 input data first bit is 1, then turn on  LED
		if (pinStatus) {
			*pGPIODOut |= (1 << 12);

		} else {
			//turn off Led
			*pGPIODOut &= ~(1 << 12);
		}

	}
}
