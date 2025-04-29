#include <stm32f10x.h>

int main(void)
{
  /* ___GPIO___ */

  /* Bật Clock PortC và PortB */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  /* Cấu hình PC13 */
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* Cấu hình PB0 */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* ___AFIO___ */

  /* Bật Clock AFIO để kết nối EXTI line0 với chân PB0 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);

  /* ___EXTI___ */

  /* Cấu hình ngắt EXTI line0 */
  EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* ___NVIC___ */

  /* Cho phét ngắt EXTI line0 toàn cục */
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  while (1)
  {

  }
}

/* Trình phục vụ ngắt EXTI line0 */
void EXTI0_IRQHandler(void)
{
  /* Nếu cờ EXTI_line0 = 1 và ngắt EXTI_line0 được cho phép */
  if (EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    /* Đọc bit thứ 0 của thanh ghi GPIOB_IDR */
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == Bit_SET)
    {
      GPIO_SetBits(GPIOC, GPIO_Pin_13);
    }
    else
    {
      GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    }

    /* Xoá cờ ngắt EXTI_line0 */
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}
