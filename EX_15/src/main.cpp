/* Exemplo para demonstrar o uso de taks Notification de uma ISR para uma task */

/*inclusão da Biblioteca Arduino*/
#include <Arduino.h>

/*inclusão da Biblioteca FreeRTOS*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED 2
#define BT 12

TaskHandle_t xTaskTrataBTHandle;

void vTaskTrataBT(void *pvParameters);

void callBackBT(void)
{
  vTaskNotifyGiveFromISR(xTaskTrataBTHandle,NULL);
}

void setup()
{
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  pinMode(BT,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BT),callBackBT,FALLING);

  xTaskCreate(vTaskTrataBT,"TASK BT",configMINIMAL_STACK_SIZE,NULL,1,&xTaskTrataBTHandle);
}

void loop()
{
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void vTaskTrataBT(void *pvParameters)
{
  uint32_t quantidade = 0;
  while(1)
  {
    quantidade = ulTaskNotifyTake(pdFALSE,portMAX_DELAY);

    Serial.println("Tratando ISR botao: " + String(quantidade));
    digitalWrite(LED,!digitalRead(LED));
    delay(2000);
  }
}