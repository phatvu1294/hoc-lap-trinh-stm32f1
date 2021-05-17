#include "startup.h"

uint32_t __msTick = 0;
void delay_ms(uint32_t ms);
void SysTick_Handler(void);

int main(void)
{
  /* ___LIB___ */

  /* Khởi tạo startup */
  startup_init();

  /* ___SYSTICK___ */

  /* Cấu hình SysTick 1ms */
  SysTick_Config(SystemCoreClock / 1000);

  /* Cấu hình mức độ ưu tiên ngắt SysTick */
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));

  /* ___GPIO___ */

  /* Bật Clock PortC */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);

  /* Cấu hình PC13 */
  LL_GPIO_InitTypeDef LL_GPIO_InitStructure;
  LL_GPIO_InitStructure.Mode = LL_GPIO_MODE_OUTPUT;
  LL_GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_InitStructure.Pin = LL_GPIO_PIN_13;
  LL_GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_LOW;
  LL_GPIO_Init(GPIOC, &LL_GPIO_InitStructure);
  
  /* Set PC13 */
  LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_13);

  /* Lặp vô hạn */
  while (1)
  {
    /* Đảo trạng thái PC13 */
    LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);

    /* Tạo trễ khoảng thời gian */
    delay_ms(500);
  }
}

/* Hàm delay ms sử dụng SysTick */
void delay_ms(uint32_t ms)
{
  uint32_t startTick = __msTick;
  while (__msTick - startTick < ms);
}

/* Trình phục vụ ngắt SysTick */
void SysTick_Handler(void)
{
  /* Tăng biến tick */
  __msTick++;
}
