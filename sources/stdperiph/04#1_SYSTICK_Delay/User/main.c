#include <stm32f10x.h>

uint32_t msTick = 0;
uint32_t prevTick = 0;

void SysTick_Handler(void);
void delay_ms(uint32_t ms);

int main(void)
{
  /* ___SYSTICK___ */

  /* SysTick 1ms */
  SysTick_Config(SystemCoreClock / 1000);

  /* Cấu hình mức độ ưu tiên ngắt SysTick */
  NVIC_SetPriority(SysTick_IRQn, 0);
	
  /* ___GPIO___ */

  /* Bật Clock PortC */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  /* Cấu hình PC13 */
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* Set PC13 */
  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);

  while (1)
  {
    /* Chớp tắt LED delay blocking */
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
    delay_ms(100);
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
    delay_ms(100);

    /* Chớp tắt LED delay non-blocking */
    //static uint8_t ledState;
    //if (msTick - prevTick >= 100)
    //{
    //  prevTick = msTick;
    //  ledState = !ledState;
    //  GPIO_WriteBit(GPIOC, GPIO_Pin_13, ledState ? Bit_SET : Bit_RESET);
    //}
  }
}

/* Trình phục vụ ngắt SysTick */
void SysTick_Handler(void)
{
  /* Tăng biến tick */
  msTick++;
}

/* Hàm tạo trễ ms (delay blocking) */
void delay_ms(uint32_t ms)
{
  uint32_t startTick = msTick;
  while (msTick - startTick < ms);
}
