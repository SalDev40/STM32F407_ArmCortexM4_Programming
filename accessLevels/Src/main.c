/**
 ******************************************************************************
 * @file    main.c
 * @author  Auto-generated by STM32CubeIDE
 * @version V1.0
 * @brief   Default main function.
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include<stdio.h>
#include<stdint.h>

/* This function executes in THREAD MODE of the processor */
void generate_interrupt() {

	//these address can only be accessed being in priv access level
	uint32_t *pSTIR = (uint32_t*) 0xE000EF00;
	uint32_t *pISER0 = (uint32_t*) 0xE000E100;

	//wont work in unprivileged mode -> throws fault
	//enable IRQ3 interrupt
	*pISER0 |= (1 << 3);

	//generate an interrupt from software for IRQ3
	*pSTIR = (3 & 0x1FF);

}

void switchToUnprivAccess(void) {

	//change bit of control register to 1 -> unprivileged mode
	//control is a core register therefore we need to use assembly

	//read -> read control register into R0
	__asm volatile("MRS R0, CONTROL");

	//modify -> set bit to 1
	__asm volatile("ORR R0, R0, #0X01");

	//write back value to control register
	__asm volatile("MSR CONTROL, R0");

}

/* This function executes in THREAD MODE + PRIV ACCESS MODE of the processor */
int main(void) {
	printf("In thread mode : before interrupt\n");

	switchToUnprivAccess(); //will make thread mode unprivileged
	generate_interrupt(); //generate interrupt in unprivileged mode

	printf("In thread mode : after interrupt\n");

	while (1)
			;
}

/* This function(ISR) executes in HANDLER MODE of the processor */
void RTC_WKUP_IRQHandler(void) {
	printf("In handler mode : ISR\n");
}

/* Fault handler */
void HardFault_Handler(void) {

	printf("Hard fault detected\n");
	while (1)
		;

}
