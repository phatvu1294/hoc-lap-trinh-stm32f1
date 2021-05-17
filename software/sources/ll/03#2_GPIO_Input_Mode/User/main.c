#include "startup.h"

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
  LL_GPIO_InitStructure.Mode = LL_GPIO_MODE_INPUT;
  LL_GPIO_InitStructure.Pin = LL_GPIO_PIN_0;
  LL_GPIO_InitStructure.Pull = LL_GPIO_PULL_UP;
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

  /* Lặp vô hạn */
  while (1)
  {
    /* Đọc trạng thái PA0 và xuất ra PC13 */
    /* Nếu PA0 được set */
    if (LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_0))
    {
      LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_13);
    }
    else
    {
      LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_13);
    }
  }
}
