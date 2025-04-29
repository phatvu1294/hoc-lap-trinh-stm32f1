#include "startup.h"

void EXTI0_IRQHandler(void);

int main(void)
{
  /* ___LIB___ */

  /* Khởi tạo startup */
  startup_init();

  /* ___GPIO___ */

  /* Bật Clock PortA */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);

  /* Cấu hình PA0 */
  LL_GPIO_InitTypeDef LL_GPIO_InitStructure;
  LL_GPIO_InitStructure.Mode = LL_GPIO_MODE_FLOATING;
  LL_GPIO_InitStructure.Pin = LL_GPIO_PIN_0;
  LL_GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_LOW;
  LL_GPIO_Init(GPIOA, &LL_GPIO_InitStructure);

  /* Bật Clock PortC */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);

  /* Cấu hình PC13 */
  LL_GPIO_InitStructure.Mode = LL_GPIO_MODE_OUTPUT;
  LL_GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_InitStructure.Pin = LL_GPIO_PIN_13;
  LL_GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_LOW;
  LL_GPIO_Init(GPIOC, &LL_GPIO_InitStructure);

  /* Set PC13 */
  LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_13);

  /* ___AFIO___ */

  /* Bật Clock AFIO */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);

  /* Kết nối EXTI line0 với PortA */
  LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTA, LL_GPIO_AF_EXTI_LINE0);

  /* ___EXTI___ */

  /* Cấu hình EXTI line0 */
  LL_EXTI_InitTypeDef LL_EXTI_InitStructure;
  LL_EXTI_InitStructure.LineCommand = ENABLE;
  LL_EXTI_InitStructure.Line_0_31 = LL_EXTI_LINE_0;
  LL_EXTI_InitStructure.Mode = LL_EXTI_MODE_IT;
  LL_EXTI_InitStructure.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;
  LL_EXTI_Init(&LL_EXTI_InitStructure);

  /* ___NVIC__ */

  /* Đặt mức độ ưu tiên ngắt EXTI line0 */
  NVIC_SetPriority(EXTI0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));

  /* Cho phép ngắt toàn cục EXTI line0 */
  NVIC_EnableIRQ(EXTI0_IRQn);

  /* Lặp vô hạn */
  while (1)
  {

  }
}

/* Trình phục vụ ngắt EXTI line0 */
void EXTI0_IRQHandler(void)
{
  /* Nếu EXTI line0 đã được ngắt và ngắt EXTI line0 được cho phép */
  if ((LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0)) && (LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_0)))
  {
    /* Đọc trạng thái PA0 và xuất ra PC13 */
    if ((LL_GPIO_ReadInputPort(GPIOA) & GPIO_IDR_IDR0) != 0)
    {
      LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_13);
    }
    else
    {
      LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_13);
    }

    /* Xóa cờ ngắt EXTI line0 bằng phần mềm */
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);
  }
}
