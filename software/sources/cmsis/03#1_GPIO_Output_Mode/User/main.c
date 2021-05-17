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
  //GPIOC->ODR |= GPIO_ODR_ODR13;
  //Hoặc sử dụng
  GPIOC->BSRR |= GPIO_BSRR_BS13;

  /* Cấu hình PC13 */
  GPIOC->CRH &= ~GPIO_CRH_MODE13; // Clear
  GPIOC->CRH |= GPIO_CRH_MODE13_1; // 10: Output mode, max speed 2 MHz
  GPIOC->CRH &= ~GPIO_CRH_CNF13; // 00: General purpose output push-pull

  /* Hàm lặp vô hạn */
  while (1)
  {
    /* Reset PC13 */
    //GPIOC->ODR &= ~GPIO_ODR_ODR13;
    //Hoặc sử dụng
    //GPIOC->BSRR |= GPIO_BSRR_BR13;
    //Hoặc sử dụng
    GPIOC->BRR |= GPIO_BRR_BR13;
    for (uint32_t i = 0; i < 1000000; i++) { }

    /* Reset PC13 */
    /* Set PC13 */
    //GPIOC->ODR |= GPIO_ODR_ODR13;
    //Hoặc sử dụng
    GPIOC->BSRR |= GPIO_BSRR_BS13;
    for (uint32_t i = 0; i < 1000000; i++) { }
  }
}
