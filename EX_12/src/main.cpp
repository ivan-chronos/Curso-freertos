/* Exemplo de uso de um MUTEX para acesso
a recursos e a inversão de prioridade*/

/*inclusão da Biblioteca Arduino*/
#include <Arduino.h>

/*inclusão da Biblioteca FreeRTOS*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#define LED 2

SemaphoreHandle_t mutex;

TaskHandle_t task1Handle, task2Handle;

void vTask1(void * pvParameters);
void vTask2(void * pvParameters);

void enviaInformacao(int i)
{
  xSemaphoreTake(mutex,portMAX_DELAY);
  Serial.println("Enviando informação da Task: " + String(i));
  //delay(1000);
  xSemaphoreGive(mutex);
}

void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);

  mutex = xSemaphoreCreateMutex();

  xTaskCreate(vTask1,"Task1",configMINIMAL_STACK_SIZE + 1024,NULL,1,&task1Handle);
  xTaskCreate(vTask2,"Task2",configMINIMAL_STACK_SIZE + 1024,NULL,4,&task1Handle);
}

void loop() {
  digitalWrite(LED,HIGH);
  vTaskDelay(pdMS_TO_TICKS(1000));
  digitalWrite(LED,LOW);
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void vTask1(void * pvParameters)
{
  while(1)
  {
    enviaInformacao(1);
    vTaskDelay(10);
  }
}

void vTask2(void * pvParameters)
{
  while(1)
  {
    enviaInformacao(2);
    vTaskDelay(10);
  }
}