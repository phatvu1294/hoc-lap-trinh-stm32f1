#include "stm32f1xx.h"
#include "startup.h"

void EXTI0_IRQHandler(void);

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

  /* ___AFIO___ */

  /* Bật Clock AFIO */
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; // 1: Enable

  /* Kết nối EXTI line0 với PortA */
  /* AFIO->EXTICR[0]: EXTI line3 -> EXTI line0 */
  /* AFIO->EXTICR[1]: EXTI line7 -> EXTI line4 */
  /* AFIO->EXTICR[2]: EXTI line11 -> EXTI line8 */
  /* AFIO->EXTICR[3]: EXTI line15 -> EXTI line12 */
  //AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI0 // 0000: PA[x] pin
  // Hoặc sử dụng
  AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PA; // 0000: PA[x] pin

  /* ___EXTI___ */

  /* Cấu hình EXTI line0 */
  EXTI->IMR |= EXTI_IMR_MR0; // 1: Interrupt request from Line x is not masked
  EXTI->EMR &= ~EXTI_EMR_MR0; // 0: Event request from Line x is masked
  EXTI->RTSR |= EXTI_RTSR_TR0; // 1: Rising trigger enabled (for Event and Interrupt) for input line
  EXTI->FTSR |= EXTI_FTSR_FT0; // 1: Falling trigger enabled (for Event and Interrupt) for input line.

  /* ___NVIC___ */

  /* Đặt mức độ ưu tiên ngắt */
  NVIC_SetPriority(EXTI0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));

  /* Cho phép ngắt toàn cục EXTI line0 */
  NVIC_EnableIRQ(EXTI0_IRQn);

  /* Hàm lặp vô hạn */
  while (1)
  {

  }
}

/* Trình phục vụ ngắt EXTI line0 */
void EXTI0_IRQHandler(void)
{
  /* Nếu EXTI line0 đã được ngắt và ngắt EXTI line0 được cho phép */
  if (((EXTI->PR & EXTI_PR_PIF0) == EXTI_PR_PIF0) && ((EXTI->IMR & EXTI_IMR_MR0) == EXTI_IMR_MR0))
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

    /* Xóa cờ ngắt EXTI line0 bằng phần mềm */
    EXTI->PR |= EXTI_PR_PIF0;
  }
}
