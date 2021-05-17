#include "stm32f1xx.h"
#include "startup.h"

uint32_t __msTick = 0;
void delay_ms(uint32_t ms);
void SysTick_Handler(void);

int main(void)
{
  /* Thêm chương trình chính tại đây */

  /* ___LIB___ */

  /* Khởi tạo hệ thống */
  startup_init();

  /* ___SYSTICK___ */

  /* Cấu hình Systick 1ms */
  SysTick_Config(SystemCoreClock / 1000);

  /* Cấu hình mức độ ưu tiên ngắt SysTick */
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));

  /* ___GPIO___ */

  /* Bật Clock PortC */
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // 1: Enable

  /* Set PC13 */
  GPIOC->BSRR |= GPIO_BSRR_BS13;

  /* Cấu hình PC13 */
  GPIOC->CRH &= ~GPIO_CRH_MODE13; // Clear
  GPIOC->CRH |= GPIO_CRH_MODE13_1; // 10: Output mode, max speed 2 MHz
  GPIOC->CRH &= ~GPIO_CRH_CNF13; // 00: General purpose output push-pull

  /* Hàm lặp vô hạn */
  while (1)
  {
    /* Reset PC13 */
    GPIOC->BSRR |= GPIO_BSRR_BR13;
    delay_ms(500);

    /* Set PC13 */
    GPIOC->BSRR |= GPIO_BSRR_BS13;
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
