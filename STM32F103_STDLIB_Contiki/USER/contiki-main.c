#include "stm32f10x.h"   
#include "contiki.h"
#include "stdio.h"

unsigned int idle_count = 0;  
void led_init();  


PROCESS(blink_process, "Blink"); 

AUTOSTART_PROCESSES(&blink_process); 

PROCESS_THREAD(blink_process, ev, data)  
{  
  PROCESS_BEGIN();  
  while(1)  
  {  
   static struct etimer et;  
   etimer_set(&et, CLOCK_SECOND);  
   PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));  
   //打开LED   
   GPIO_ResetBits(GPIOE,GPIO_Pin_6);  
   printf("LED ON\r\n");  
   etimer_set(&et, CLOCK_SECOND);  
   PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));  
   //关闭LED   
   GPIO_SetBits(GPIOE,GPIO_Pin_6);  
   printf("LED OFF\r\n");  
  }  
  PROCESS_END();  
}  
     
void led_init()  
{  
  GPIO_InitTypeDef GPIO_InitStructure;  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);  
  //PE6 推挽输出   
  GPIO_InitStructure.GPIO_Pin= GPIO_Pin_6;  
  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;  
  GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;  
  GPIO_Init(GPIOE,&GPIO_InitStructure);  
}  


int main()  
{  
  dbg_setup_uart();  
  led_init();      	 	
  
  printf("printf put : Contiki 2.6 port to stm32103vet6 with stdlib 3.5! \r\n"); 
  printf("\r\n");  
  
  printf("Initialising\r\n");  
  clock_init();  
  process_init();  
  process_start(&etimer_process,NULL);  
  autostart_start(autostart_processes);  
  //process_start(&blink_process,NULL);   
  printf("Processesrunning\r\n");  
  while(1) 
  {  
      do  
      {  
        
      }  
      while(process_run()> 0);  
      idle_count++;
     // printf("The value of function process_run() is %d\r\n",process_run()); 
     
    //  printf("idle_count = %d\r\n",idle_count);   
      /* Idle! */  
      /* Stop processor clock */  
      /* asm("wfi"::); */  
   }  
 
}