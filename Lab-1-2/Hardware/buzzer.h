#ifndef __BUZZER_H
#define __BUZZER_H
#include "sys.h"
#include "system.h"

#define BUZZER_TASK_PRIO		3     //Task priority 
#define BUZZER_STK_SIZE 		128   //Task stack size 


/*--------Buzzer control pin--------*/
#define Buzzer_PORT GPIOB
#define Buzzer_PIN GPIO_Pin_10
#define Buzzer PBout(10) 
/*----------------------------------*/

void Buzzer_Init(void);  
void Buzzer_task(void *pvParameters);
extern int Buzzer_Count;
#endif
