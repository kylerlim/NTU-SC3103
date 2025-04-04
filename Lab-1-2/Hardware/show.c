#include "show.h"
#include "stdio.h"

void count_up_timer(void)
{  
	 int h = 0, m = 0, s = 0;
	 uint8_t time[20];
	 OLED_Display_On();
	
		while (1) {
			
			sprintf((char*)time, "%02d:%02d:%02d", h, m, s);
			vTaskDelay(1000);
			
		OLED_ShowString(40,40, time);
	 OLED_Refresh_Gram(); //refresh the OLED RAM
			
			s ++;
			
			if (s==60) {
				s=0;
				m ++;
			}
			
			if (m==60){
				m=0;
				h++;
			}
			
		}
	  		
	}


void show_task(void *pvParameters)
{
   u32 lastWakeTime = getSysTickCnt();
   while(1)
    {	

			vTaskDelayUntil(&lastWakeTime, F2T(RATE_50_HZ));

			oled_show(); 
			count_up_timer();
    }
}  

void oled_show(void)
{  
     //To DO
	 
	 
	 //call some function in oled to display something

	 u32 i;
	 uint8_t s[] = "Kyle Lim";
	 OLED_Display_On();
	 OLED_ShowString(20,0, s);
	 OLED_Refresh_Gram(); //refresh the OLED RAM
}
