#include "stm32f1xx.h"
#include "startup.h"

void TIM3_IRQHandler(void);

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

  /* ___TIM___ */

  /* Bật Clock TIM3 */
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // 1: Enable;

  /* Cấu hình TIM3 Time Base */
  /* f_clock_source/f_update = Prescaler * (Counter_Period + 1) */
  /* có f_clock_source = 72MHz */
  /* Với f_update = 1Hz => 72000000 = Prescaler * (Counter_Period + 1) */
  /* ta có Counter_Period (max) = 2^16 - 1 = 65535 => Prescaler (min) = 1099 */
  /* Chọn Prescaler = 7200 => Counter_Period = 10000-1 */
  TIM3->CR1 &= ~TIM_CR1_CKD; // 00: tDTS=tCK_INT
  TIM3->CR1 &= ~TIM_CR1_CMS; // 00: Edge-aligned mode. The counter counts up or down depending on the direction bit DIR
  TIM3->CR1 &= ~TIM_CR1_DIR; // 0: Counter used as upcounter
  TIM3->CR1 &= ~TIM_CR1_ARPE; // 0: TIMx_ARR register is not buffered
  TIM3->ARR = 10000 - 1; // Auto-reload value (Counter Period)
  TIM3->PSC = 7200 - 1; // Prescaler value
  TIM3->RCR = 0 & 0x00FF; // Repetition counter value
  TIM3->EGR |= TIM_EGR_UG; // 1: Reinitialize the counter and generates an update of the registers

  /* Cho phép ngắt TIM3 Update */
  TIM3->DIER |= TIM_DIER_UIE; // 1: Update interrupt enabled

  /* Bật TIM3 */
  TIM3->CR1 |= TIM_CR1_CEN; // 1: Counter enabled

  /* ___NVIC___ */

  /* Cấu hình mức độ ưu tiên ngắt TIM3 */
  NVIC_SetPriority(TIM3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));

  /* Cho phép ngắt toàn cục TIM3 */
  NVIC_EnableIRQ(TIM3_IRQn);

  /* Hàm lặp vô hạn */
  while (1)
  {

  }
}

/* Trình phục vụ ngắt TIM3 */
void TIM3_IRQHandler(void)
{
  /* Nếu cờ UIF được set và ngắt TIM1 Update được cho phép */
  if (((TIM3->SR & TIM_SR_UIF) == TIM_SR_UIF) && ((TIM3->DIER & TIM_DIER_UIE) == TIM_DIER_UIE))
  {
    /* Đảo trạng thái PC13 */
    GPIOC->ODR ^= GPIO_ODR_ODR13;

    /* Xóa cờ UIF */
    TIM3->SR &= ~TIM_SR_UIF;
  }
}
