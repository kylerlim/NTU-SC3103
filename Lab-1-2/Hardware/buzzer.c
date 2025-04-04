#include "buzzer.h"
#include "system.h"

int Buzzer_Count = 5000;

//Buzzer initialization
void Buzzer_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);    //Enable APB Clock
	
  GPIO_InitStructure.GPIO_Pin =  Buzzer_PIN;                  //Buzzer Pin
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;            //Push pull output
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //50MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(Buzzer_PORT, &GPIO_InitStructure);                    //Initialize Buzzer GPIO
	GPIO_SetBits(Buzzer_PORT,Buzzer_PIN);
}

void Buzzer_task(void *pvParameters)
{
    while(1)
    {
      Buzzer=~Buzzer;        //0 on, 1 off 
      vTaskDelay(Buzzer_Count); //Delay 
    }
}  
