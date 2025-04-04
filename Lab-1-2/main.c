#include "system.h"

#define START_TASK_PRIO		4
#define START_STK_SIZE    256

#define USERBUTTON_TASK_PRIO		4    //Task priority 
#define USERBUTTON_STK_SIZE 		128   //Task stack size 

#define UART_TASK_PRIO		3     //Task priority 
#define UART_STK_SIZE 		128   //Task stack size 

// LAB2_TASK2
#define LAB2_TASK2_PRIO		3     //Task priority 
#define LAB2_TASK2_SIZE 		128   //Task stack size 


TimerHandle_t xAutoTimer ;

void start_task(void *pvParameters);
TaskHandle_t StartTask_Handler;

void user_button_task(void *pvParameters);
TaskHandle_t User_Button_Handler;

void uart3_task(void *pvParameters);
TaskHandle_t UART_Handler;

void lab2_task2(void *pvParameters);
TaskHandle_t LAB2_TASK2_Handler;

void lab2_task3(void *pvParameters);
TaskHandle_t LAB2_TASK3_Handler;

//void lab2_task1(void *pvParameters);
//void lab2_task3(void *pvParameters);
//void lab2_task4(void *pvParameters);
//void lab2_task5(void *pvParameters);
TimerHandle_t uartTimer;

int main(void)
{
	systemInit();
	Buzzer = 0;
	
	// Legacy Task from Lab 1
	/*
	xTaskCreate((TaskFunction_t ) start_task,
							(const char*		) "start_task",
								(uint16_t			) START_STK_SIZE,
							(void*					) NULL,
							(UBaseType_t		) START_TASK_PRIO,
							(TaskHandle_t*	) &StartTask_Handler);
	*/					
							
// LAB 2 TASK A
	
							xTaskCreate((TaskFunction_t ) user_button_task,
							(const char*		) "user_button_task",
							(uint16_t			) 	USERBUTTON_STK_SIZE,
							(void*					) NULL,
							(UBaseType_t		) USERBUTTON_TASK_PRIO,
							(TaskHandle_t*	) &User_Button_Handler);
							
							
							
// LAB 2 TASK B

			xTaskCreate((TaskFunction_t ) lab2_task2,
							(const char*		) "led_blink_With_timer_task",
								(uint16_t			) LAB2_TASK2_SIZE,
							(void*					) NULL,
							(UBaseType_t		) LAB2_TASK2_PRIO,
							(TaskHandle_t*	) &LAB2_TASK2_Handler);

							
// LAB 2 TASK C						
// UART Task will hog up the processor?
							
						
	xTaskCreate((TaskFunction_t ) lab2_task3,
						(const char*		) "lab2_task3",
						(uint16_t			) 	UART_STK_SIZE,
						(void*					) NULL,
						(UBaseType_t		) UART_TASK_PRIO,
						(TaskHandle_t*	) &LAB2_TASK3_Handler);							
			

//	xTaskCreate((TaskFunction_t ) lab2_task1,
//							(const char*		) "play_song_task",
//								(uint16_t			) START_STK_SIZE,
//							(void*					) NULL,
//							(UBaseType_t		) START_TASK_PRIO,
//							(TaskHandle_t*	) &StartTask_Handler);
	

	
//		xTaskCreate((TaskFunction_t ) lab2_task3,
//							(const char*		) "uart_task",
//								(uint16_t			) START_STK_SIZE,
//							(void*					) NULL,
//							(UBaseType_t		) START_TASK_PRIO,
//							(TaskHandle_t*	) &StartTask_Handler);

			// lab2 task 4 non-Preemptive

			// lab2 task 5 compare prio
			// same prio
//			xTaskCreate(userB_task, "show_task", USERB_STK_SIZE, NULL, 3, NULL);
//			xTaskCreate(lab2_task2, "led_blink_With_timer_task", USERB_STK_SIZE, NULL, 3, NULL);			
//			xTaskCreate(lab2_task3, "compare_prio_task", USERB_STK_SIZE, NULL, 3, NULL);
			
			// lower/higher prio
			//xTaskCreate(userB_task, "playsong_task", USERB_STK_SIZE, NULL, 4, NULL);
			//xTaskCreate(lab2_task2, "led_blink_With_timer_task", USERB_STK_SIZE, NULL, 3, NULL);			
			//xTaskCreate(lab2_task3, "compare_prio_task", USERB_STK_SIZE, NULL, 3, NULL);

							
	vTaskStartScheduler();
							

}

// Lab1
void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();
	//xTaskCreate(led_task, "led_task", LED_STK_SIZE, NULL, LED_TASK_PRIO, NULL); // LAB 1 EXERCISE A
	//xTaskCreate(Buzzer_task, "buzzer_task", BUZZER_STK_SIZE, NULL, BUZZER_TASK_PRIO, NULL); // LAB 1 EXERCISE B
	//xTaskCreate(show_task, "show_task", SHOW_STK_SIZE, NULL, SHOW_TASK_PRIO, NULL); // LAB 1 EXERCISE C
	vTaskDelete(StartTask_Handler);
	
	taskEXIT_CRITICAL();
}

void user_button_task(void *pvParameters)
{
	taskENTER_CRITICAL();
	xTaskCreate(UserButton_task, "UserButton_task", USERBUTTON_STK_SIZE, NULL, USERBUTTON_TASK_PRIO, NULL); // LAB 2 EXERCISE A
	vTaskDelete(User_Button_Handler);
	taskEXIT_CRITICAL();
}

void uart3_task(void *pvParameters)
{
	taskENTER_CRITICAL();
	xTaskCreate(uart_task, "uart_task", UART_STK_SIZE, NULL, UART_TASK_PRIO, NULL); // LAB 2 EXERCISE C
	vTaskDelete(UART_Handler);
	taskEXIT_CRITICAL();
}


// Lab2

// User button to play the song
//void lab2_task1(void *pvParameters)
//{
//	taskENTER_CRITICAL();
//	xTaskCreate(userB_task, "show_task", USERB_STK_SIZE, NULL, USERB_TASK_PRIO, NULL);
//	vTaskDelete(StartTask_Handler);
//	
//	taskEXIT_CRITICAL();
//}

//// Timer let led blink
void lab2_task2(void *pvParameters)
{
	taskENTER_CRITICAL();
	
	xAutoTimer = xTimerCreate("timer1sec", pdMS_TO_TICKS(1000) , pdTRUE, 0, led_task1);
	if (xTimerStart(xAutoTimer, 0) == pdPASS)
	vTaskDelete(LAB2_TASK2_Handler);
	taskEXIT_CRITICAL();
}

//// uart_transfer

void lab2_task3(void *pvParameters)
{
	taskENTER_CRITICAL();
	// Lab2 task 3	
	uart3_init(115200);
	
	
	uartTimer = xTimerCreate(
		"SendUART1Sec", 			// name
		pdMS_TO_TICKS(1000),	// period
		pdTRUE,								// auto reload
		(void*) 0,						// timer ID
		uart3_send_name							// callback
	);
	xTimerStart(uartTimer, pdMS_TO_TICKS(0));
	vTaskDelete(LAB2_TASK3_Handler);
		
	taskEXIT_CRITICAL();
}
