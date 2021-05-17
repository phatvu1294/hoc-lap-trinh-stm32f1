#include "stm32f1xx.h"

int main(void)
{
  /* Thêm chương trình chính tại đây */

  /* ___INIT___ */

  /* Bật Clock PWR */
  RCC->APB1ENR |= RCC_APB1ENR_PWREN; // 1: Enable

  /* Đặt nhóm mức độ ưu tiên ngắt */
  /* ((uint32_t)0x00000007) 0 bit  for pre-emption priority, 4 bits for subpriority */
  /* ((uint32_t)0x00000006) 1 bit  for pre-emption priority, 3 bits for subpriority */
  /* ((uint32_t)0x00000005) 2 bits for pre-emption priority, 2 bits for subpriority */
  /* ((uint32_t)0x00000004) 3 bits for pre-emption priority, 1 bit  for subpriority */
  /* ((uint32_t)0x00000003) 4 bits for pre-emption priority, 0 bit  for subpriority */
  NVIC_SetPriorityGrouping((uint32_t)0x00000004);

  /* ___DEBUG___ */

  /* Bật Clock AFIO để cấu hình Debug */
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

  /* Cho phép SWD-DP và cấm JTAG-DP */
  AFIO->MAPR &= ~AFIO_MAPR_SWJ_CFG; // 000: Reset State
  AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_1; // 010: JTAG-DP Disabled and SW-DP Enabled

  /* Bật Clock PortA SWJ-DP */
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // 1: Enable

  /* ___CLOCK___ */

  /* Thông số Clock được cấu hình như sau: */
  /* System Clock source            = PLL (HSE) */
  /* SYSCLK(Hz)                     = 72000000 */
  /* HCLK(Hz)                       = 72000000 */
  /* AHB Prescaler                  = 1 */
  /* APB1 Prescaler                 = 2 */
  /* APB2 Prescaler                 = 1 */
  /* HSE Frequency(Hz)              = 8000000 */
  /* PLL_MUL                        = 16 */
  /* Flash Latency(WS)              = 2 */

  /* Cho phép Prefetch Buffer */
  FLASH->ACR |= FLASH_ACR_PRFTBE;

  /* Cấu hình Latency (WS) */
  FLASH->ACR &= ~FLASH_ACR_LATENCY; // 000: Clear
  FLASH->ACR |= FLASH_ACR_LATENCY_1; // 010: 2 wait state

  /* Bật HSE */
  RCC->CR |= RCC_CR_HSEON; // 1: HSE oscillator ON

  /* Chờ cho đến khi HSE Ready */
  while ((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY); // 1: HSE oscillator ready

  /* Nguồn PLL từ HSE */
  RCC->CFGR |= RCC_CFGR_PLLSRC; // 1: HSE oscillator clock selected as PLL input clock

  /* Hệ số chia trước PLL */
  //RCC->CFGR &= ~RCC_CFGR_PLLXTPRE; // 0: HSE clock not divided
  // Hoặc sử dụng
  RCC->CFGR |= RCC_CFGR_PLLXTPRE_HSE; // 0: HSE clock not divided

  /* Hệ số nhân PLL */
  //RCC->CFGR &= ~RCC_CFGR_PLLMULL; // 000: Clear
  //RCC->CFGR |= RCC_CFGR_PLLMULL_2 | RCC_CFGR_PLLMULL_1 | RCC_CFGR_PLLMULL_0; // 0111: PLL input clock x 9
  // Hoặc sử dụng
  RCC->CFGR |= RCC_CFGR_PLLMULL9; // 9: PLL input clock x 9

  /* Bật PLL */
  RCC->CR |= RCC_CR_PLLON; // 1: PLL ON

  /* Chờ cho đến khi PLL Ready (Locked) */
  while ((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY); // 1: PLL locked

  /* Đặt hệ số chia trước AHB */
  //RCC->CFGR &= ~RCC_CFGR_HPRE; // 0000: SYSCLK not divided
  // Hoặc sử dụng
  RCC->CFGR |= RCC_CFGR_HPRE_DIV1; // 0000: SYSCLK not divided

  /* Đặt hệ số chia trước APB1 */
  //RCC->CFGR &= RCC_CFGR_PPRE1; // 0000: Clear
  //RCC->CFGR |= RCC_CFGR_PPRE1_2; // 1000: HCLK divided by 2
  // Hoặc sử dụng
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; // 1000: HCLK divided by 2

  /* Đặt hệ số chia trước APB2 */
  //RCC->CFGR &= RCC_CFGR_PPRE2; // 0000: HCLK not divided
  // Hoặc sử dụng
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV1; // 0000: HCLK not divided

  /* Đặt System Clock Switch */
  //RCC->CFGR &= RCC_CFGR_SW; // 00: Clear
  //RCC->CFGR |= RCC_CFGR_SW_1; // 10: PLL used as system clock
  // Hoặc sử dụng
  RCC->CFGR |= RCC_CFGR_SW_PLL; // 10: PLL used as system clock

  /* Chờ cho đến khi System Clock Switch sẵn sàng */
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

  /* Đặt System Clock Core */
  SystemCoreClock = 72000000;

  /* Bật Clock PortD OSC-DP */
  RCC->APB2ENR |= RCC_APB2ENR_IOPDEN; // 1: Enable

  /* Hàm lặp vô hạn */
  while (1)
  {

  }
}
