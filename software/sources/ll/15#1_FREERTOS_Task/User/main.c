#include "startup.h"
#include "usart1.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t mainTaskHandle;
TaskHandle_t secondTaskHandle;
TaskHandle_t thirdTaskHandle;

/* Nguyên mẫu hàm */
void mainTaskExecute(void *p);
void secondTaskExecute(void *p);
void thirdTaskExecute(void *p);

int main(void)
{
  /* ___LIB___ */

  /* Khởi tạo startup */
  startup_init();

  /* Khởi tạo usart1 */
  usart1_init();

  /* ___FreeRTOS___ */

  /* Thêm mutexe, ... */
  /* Thêm semaphore, ... */
  /* Bắt đầu software timer, ... */
  /* Thêm queue, ... */

  /* Tạo các task */
  xTaskCreate(mainTaskExecute, "mainTask", 128, NULL, 1, &mainTaskHandle);
  xTaskCreate(secondTaskExecute, "secondTask", 128, NULL, 2, &secondTaskHandle);
  xTaskCreate(thirdTaskExecute, "thirdTask", 128, NULL, 3, &thirdTaskHandle);

  /* Khởi chạy bộ lên lịch */
  vTaskStartScheduler();

  /* Khi bộ lên lịch hoạt động chúng ta sẽ không bao giờ đi xuống đây */
  /* Lặp vô hạn */
  while (1)
  {

  }
}

/* Hàm thực thi task chính */
void mainTaskExecute(void *p)
{
  while (1)
  {
    /* Gửi dữ liệu ra usart1 */
    usart1_putString((uint8_t *)"Hello Main Task!\r\n");
    vTaskDelay(1000);
  }
}

/* Hàm thực thi task thứ hai */
void secondTaskExecute(void *p)
{
  while (1)
  {
    /* Gửi dữ liệu ra usart1 */
    usart1_putString((uint8_t *)"Hello Second Task!\r\n");
    vTaskDelay(1000);
  }
}

/* Hàm thực thi task thứ ba */
void thirdTaskExecute(void *p)
{
  while (1)
  {
    /* Gửi dữ liệu ra usart1 */
    usart1_putString((uint8_t *)"Hello Third Task!\r\n");
    vTaskDelay(1000);
  }
}
