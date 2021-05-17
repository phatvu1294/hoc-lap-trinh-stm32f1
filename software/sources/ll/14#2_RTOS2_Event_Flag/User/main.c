#include "startup.h"
#include "usart1.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"

/* Định nghĩa thread chính */
osThreadId_t mainThreadHandle;
const osThreadAttr_t mainThreadAttr =
{
  .name = "mainThread", // Tên của Thread
  .stack_size = 128 * 4, // Kích thước ngăn xếp của Thread
  .priority = (osPriority_t)osPriorityNormal, // Mức độ ưu tiên của Thread
};

/* Định nghĩa thread thứ hai */
osThreadId_t secondThreadHandle;
const osThreadAttr_t secondThreadAttr =
{
  .name = "secondThread",
  .stack_size = 128 * 4,
  .priority = (osPriority_t)osPriorityNormal,
};

/* Định nghĩa thread thứ ba */
osThreadId_t thirdThreadHandle;
const osThreadAttr_t thirdThreadAttr =
{
  .name = "thirdThread",
  .stack_size = 128 * 4,
  .priority = (osPriority_t)osPriorityNormal,
};

/* Định nghĩa event */
osEventFlagsId_t eventFlagHandle;

/* Nguyên mẫu hàm */
void mainThreadExecute(void *argument);
void secondThreadExecute(void *argument);
void thirdThreadExecute(void *argument);

int main(void)
{
  /* ___LIB___ */

  /* Khởi tạo startup */
  startup_init();

  /* Khởi tạo usart1 */
  usart1_init();

  /* ___FreeRTOS___ */

  /* Khởi tạo bộ lên lịch (scheduler) */
  osKernelInitialize();

  /* Thêm mutexe, ... */
  /* Thêm semaphore, ... */
  /* Bắt đầu software timer, ... */
  /* Thêm queue, ... */
  eventFlagHandle = osEventFlagsNew(NULL);

  /* Tạo các task */
  mainThreadHandle = osThreadNew(mainThreadExecute, NULL, &mainThreadAttr);
  secondThreadHandle = osThreadNew(secondThreadExecute, NULL, &secondThreadAttr);
  thirdThreadHandle = osThreadNew(thirdThreadExecute, NULL, &thirdThreadAttr);

  /* Khởi chạy bộ lên lịch */
  osKernelStart();

  /* Khi bộ lên lịch hoạt động chúng ta sẽ không bao giờ đi xuống đây */
  /* Lặp vô hạn */
  while (1)
  {

  }
}

/* Hàm thực thi thread chính */
void mainThreadExecute(void *argument)
{
  while (1)
  {
    /* Gửi dữ liệu ra usart1 */
    usart1_putString((uint8_t *)"Hello Main Thread!\r\n");
    osDelay(500);
    osEventFlagsSet(eventFlagHandle, 0x01);
    osDelay(500);
    osEventFlagsSet(eventFlagHandle, 0x02);
    osDelay(500);
  }
}

/* Hàm thực thi thread thứ hai */
void secondThreadExecute(void *argument)
{
  while (1)
  {
    /* Chờ cho đến khi nào có sự kiện từ main Thread thì thực thi */
    osEventFlagsWait(eventFlagHandle, 0x01, osFlagsWaitAny, osWaitForever);

    /* Gửi dữ liệu ra usart1 */
    usart1_putString((uint8_t *)"Hello Second Thread!\r\n");
  }
}

/* Hàm thực thi thread thứ ba */
void thirdThreadExecute(void *argument)
{
  while (1)
  {
    /* Chờ cho đến khi nào có sự kiện từ main Thread thì thực thi */
    osEventFlagsWait(eventFlagHandle, 0x02, osFlagsWaitAny, osWaitForever);

    /* Gửi dữ liệu ra usart1 */
    usart1_putString((uint8_t *)"Hello Third Thread!\r\n");
  }
}
