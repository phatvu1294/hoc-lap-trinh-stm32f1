#include <stm32f10x.h>

int main(void)
{
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
  //GPIO_SetBits(GPIOC, GPIO_Pin_13);

  while (1)
  {
    /* Reset PC13 */
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
    //GPIO_ResetBits(GPIOC, GPIO_Pin_13);

    /* Tạo trễ */
    for (uint32_t i = 0; i < 2000000; i++);

    /* Set PC13 */
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
    //GPIO_SetBits(GPIOC, GPIO_Pin_13);

    /* Tạo trễ */
    for (uint32_t i = 0; i < 2000000; i++);
  }
}
