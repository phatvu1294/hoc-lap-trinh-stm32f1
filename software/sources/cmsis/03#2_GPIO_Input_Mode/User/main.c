#include "stm32f1xx.h"
#include "startup.h"

int main(void)
{
  /* Thêm chương trình chính tại đây */

  /* ___LIB___ */

  /* Khởi tạo hệ thống */
  startup_init();

  /* ___GPIO___ */

  /* Bật Clock PortC */
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // 1: Enable

  /* Set PC13 */
  GPIOC->BSRR |= GPIO_BSRR_BS13;

  /* Cấu hình PC13 */
  GPIOC->CRH &= ~GPIO_CRH_MODE13; // Clear
  GPIOC->CRH |= GPIO_CRH_MODE13_1; // 10: Output mode, max speed 2 MHz
  GPIOC->CRH &= ~GPIO_CRH_CNF13; // 00: General purpose output push-pull

  /* Bật Clock PortA */
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // 1: Enable

  /* Cấu hình PA0 */
  GPIOA->CRL &= ~GPIO_CRL_MODE0; // 00: Input mode
  GPIOA->CRL &= ~GPIO_CRL_CNF0; // Clear
  GPIOA->CRL |= GPIO_CRL_CNF0_0; // 01: Floating input

  /* Hàm lặp vô hạn */
  while (1)
  {
    /* Đọc bit thứ 0 của thanh ghi GPIO IDR */
    if ((GPIOA->IDR & GPIO_IDR_IDR0) == GPIO_IDR_IDR0)
    {
      /* Set PC13 */
      GPIOC->BSRR |= GPIO_BSRR_BS13;
    }
    else
    {
      /* Reset PC13 */
      GPIOC->BSRR |= GPIO_BSRR_BR13;
    }
  }
}
