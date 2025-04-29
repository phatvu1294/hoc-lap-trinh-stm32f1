#include <stm32f10x.h>

int main(void)
{
  /* ___GPIO___ */

  /* Bật Clock PortC và PortA */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  /* Cấu hình PC13 */
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);

  /* Cấu hình PA0 */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  while (1)
  {
    /* Đọc bit thứ 0 của thanh ghi GPIOA_IDR */
    //if (GPIO_ReadInputData(GPIOA) & (1 << 0))
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_SET)
    {
      GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
    }
    else
    {
      GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
    }
  }
}
