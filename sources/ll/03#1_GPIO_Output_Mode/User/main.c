#include "startup.h"

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

  /* Lặp vô hạn */
  while (1)
  {
    /* Đảo trạng thái PC13 */
    LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);

    /* Tạo trễ khoảng thời gian */
    for (uint32_t i = 0; i < 2000000; i++);

//    /* Set PC13 */
//    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_13);
//
//    /* Tạo trễ khoảng thời gian */
//    for (uint32_t i = 0; i < 2000000; i++);
//
//    /* Reset PC13 */
//    LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_13);
//
//    /* Tạo trễ khoảng thời gian */
//    for (uint32_t i = 0; i < 2000000; i++);
  }
}
