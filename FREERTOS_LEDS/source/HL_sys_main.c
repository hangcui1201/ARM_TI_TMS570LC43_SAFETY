/* Include FreeRTOS scheduler files */
#include "FreeRTOS.h"
#include "os_task.h"

/* Include gio header file - types, definitions and function declarations for system driver */
#include "HL_gio.h"

/* Define Task Handles */
xTaskHandle xTask1Handle;
xTaskHandle xTask2Handle;

/* Task1 */
void vTask1(void *pvParameters) {
   for(;;) {
       gioSetBit(gioPORTB, 6, gioGetBit(gioPORTB, 6) ^ 1);
       vTaskDelay(100);
   }
}

/* Task2 */
void vTask2(void *pvParameters) {
   for(;;) {
       gioSetBit(gioPORTB, 7, gioGetBit(gioPORTB, 7) ^ 1);
       vTaskDelay(200);
   }
}

int main(void)
{
   gioInit();

   /* Create Task 1 */
   if (xTaskCreate(vTask1,"Task1", configMINIMAL_STACK_SIZE, NULL, 1, &xTask1Handle) != pdTRUE)
   {
       /* Task could not be created */
       while(1);
   }

   /* Create Task 2 */
   if (xTaskCreate(vTask2,"Task2", configMINIMAL_STACK_SIZE, NULL, 1, &xTask2Handle) != pdTRUE)
   {
       /* Task could not be created */
       while(1);
   }

   /* Start Scheduler */
   vTaskStartScheduler();

   /* Run forever */
   while(1);

   return 0;
}
