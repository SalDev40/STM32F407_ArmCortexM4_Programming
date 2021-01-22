/*
 * main.h
 *
 *  Created on: Jan 18, 2021
 */

#ifndef MAIN_H_
#define MAIN_H_

#define MAX_TASKS 5
/* stack memory calculations */
#define SIZE_TASK_STACK 1024U //1kb
#define SIZE_SCHED_STACK 1024U //1kb

#define SRAM_START 0x20000000U
#define SIZE_SRAM ((128) * (1024))
#define SRAM_END ((SRAM_START) + (SIZE_SRAM))

#define T1_STACK_START ((SRAM_END) - (0 * SIZE_TASK_STACK))
#define T2_STACK_START ((SRAM_END) - (1 * SIZE_TASK_STACK))
#define T3_STACK_START ((SRAM_END) - (2 * SIZE_TASK_STACK))
#define T4_STACK_START ((SRAM_END) - (3 * SIZE_TASK_STACK))
#define IDLE_STACK_START ((SRAM_END) - (4 * SIZE_TASK_STACK))
#define SCHED_STACK_START ((SRAM_END) - (5* SIZE_TASK_STACK))

#define TICK_HZ 1000U
#define HSI_CLOCK 16000000U
#define SYSTICK_TIM_CLK HSI_CLOCK

#define TASK_READY_STATE  0x00
#define TASK_BLOCKED_STATE  0XFF



__attribute__((naked)) void init_scheduler_stack(uint32_t schedTopOfStack);
__attribute__((naked)) void switch_sp_to_psp(void);


void init_task_stack(void);
void init_systick_timer(uint32_t tickHz);
void enable_processor_faults(void);

uint32_t get_psp_value(void);
void set_psp_value(uint32_t currentPspValue);
void update_next_task(void);
void task_delay(uint32_t tick_count);
void unblock_tasks(void);
void schedule_pend_sv(void);


void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);
void taskIdle_handler(void);

/* store address of each task_handler */
uint32_t taskHandlers[MAX_TASKS];

/* store task which is running  */
uint32_t currentTask = 1;

/* This variable gets updated from systick handler for every systick interrupt */
uint32_t gTickCount = 0;


typedef struct {
	uint32_t pspValue;
	uint32_t blockCount;
	uint8_t currentState;
	void (*taskHandler)(void);
} TCB_t;

TCB_t tcb[MAX_TASKS];

#endif /* MAIN_H_ */
