#include "startup.h"

void TIM3_IRQHandler(void);

int main(void)
{
  /* ___LIB___ */

  /* Khởi tạo startup */
  startup_init();

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

  /* ___TIM___ */

  /* Bật Clock TIM3 */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

  /* Cấu hình TIM3 Time Base */
  /* f_clock_source/f_update = Prescaler * (Counter_Period + 1) */
  /* có f_clock_source = 72MHz */
  /* Với f_update = 1Hz => 72000000 = Prescaler * (Counter_Period + 1) */
  /* ta có Counter_Period (max) = 2^16 - 1 = 65535 => Prescaler (min) = 1099 */
  /* Chọn Prescaler = 7200 => Counter_Period = 10000-1 */
  LL_TIM_InitTypeDef LL_TIM_InitStructure;
  LL_TIM_InitStructure.Autoreload = 10000 - 1;
  LL_TIM_InitStructure.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  LL_TIM_InitStructure.CounterMode = LL_TIM_COUNTERMODE_UP;
  LL_TIM_InitStructure.Prescaler = 7200 - 1;
  LL_TIM_InitStructure.RepetitionCounter = 0;
  LL_TIM_Init(TIM3, &LL_TIM_InitStructure);

  /* Cho phép ngắt TIM3 Update */
  LL_TIM_EnableIT_UPDATE(TIM3);

  /* Bật TIM3 */
  LL_TIM_EnableCounter(TIM3);

  /* ___NVIC___ */

  /* Cấu hình mức độ ưu tiên ngắt TIM3 */
  NVIC_SetPriority(TIM3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));

  /* Cho phép ngắt toàn cục TIM3 */
  NVIC_EnableIRQ(TIM3_IRQn);

  /* Lặp vô hạn */
  while (1)
  {

  }
}

/* Trình phục vụ ngắt TIM3 */
void TIM3_IRQHandler(void)
{
  /* Nếu cờ UIF được set và ngắt TIM1 Update được cho phép */
  if ((LL_TIM_IsActiveFlag_UPDATE(TIM3)) && (LL_TIM_IsEnabledIT_UPDATE(TIM3)))
  {
    /* Đảo trạng thái PC13 */
    LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);

    /* Xóa cờ UIF */
    LL_TIM_ClearFlag_UPDATE(TIM3);
  }
}
