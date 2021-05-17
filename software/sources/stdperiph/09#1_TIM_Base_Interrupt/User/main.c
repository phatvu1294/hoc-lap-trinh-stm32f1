#include <stm32f10x.h>

uint8_t ledState = 0;

void TIM1_UP_IRQHandler(void);

int main(void)
{
  /* ___GPIO___ */

  /* Bật Clock PortC */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  /* Cấu hình PC13 */
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Output push-pull
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_SetBits(GPIOC, GPIO_Pin_13); // Tắt LED

  /* ___TIM___ */

  /* Bật Clock TIM1 */
  RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM1EN, ENABLE);

  /* Cấu hình TIM1 */
  /* f_clock_source/f_update = f_update * Prescaler * (Counter_Period + 1) */
  /* có f_clock_source = 72MHz */
  /* Với f_update = 1Hz => 72000000 = Prescaler * (Counter_Period + 1) */
  /* ta có Counter_Period (max) = 2^16 - 1 = 65535 => Prescaler (min) = 1098 */
  /* Chọn Prescaler = 7200 => Counter_Period = 10000-1 */
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;
  TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
  TIM_Cmd(TIM1, ENABLE);

  /* Cho phép ngắt TIM1 Update */
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

  /* ___NVIC___ */

  /* Cấu hình ngắt toàn cục TIM1 Update */
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  while (1)
  {

  }
}

/* Trình phục vụ ngắt TIM1 Update */
void TIM1_UP_IRQHandler(void)
{
  /* Nếu cờ UIF = 1 và TIM_IT_Update được cho phép */
  if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
  {
    /* Đảo trạng thái LED */
    ledState = !ledState;

    /* Ghi trạng thái LED */
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, ledState ? Bit_SET : Bit_RESET );

    /* Xoá cờ UIF */
    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
  }
}
