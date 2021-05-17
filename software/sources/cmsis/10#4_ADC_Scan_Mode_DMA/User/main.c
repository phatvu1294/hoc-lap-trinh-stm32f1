#include "stm32f1xx.h"
#include "startup.h"
#include "usart1.h"
#include "delay.h"
#include <stdio.h>

#define BUFFER_SIZE 2

uint16_t adcValue[BUFFER_SIZE];
char strBuffer[32];

int main(void)
{
  /* Thêm chương trình chính tại đây */

  /* ___LIB___ */

  /* Khởi tạo hệ thống */
  startup_init();

  /* Khởi tạo delay */
  delay_init();

  /* Khởi tạo usart1 */
  usart1_init();

  /* ___GPIO___ */

  /* Bật Clock PortA */
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // 1: Enable

  /* Cấu hình PA6 (ADC1 Channel6), PA7 (ADC1 Channel7) */
  GPIOA->CRL &= ~GPIO_CRL_MODE6 & ~GPIO_CRL_MODE7; // 00: Input mode
  GPIOA->CRL &= ~GPIO_CRL_CNF6 & ~GPIO_CRL_CNF7; // 00: Analog mode

  /* ___DMA___ */

  /* Bật Clock DMA1 */
  RCC->AHBENR |= RCC_AHBENR_DMA1EN; // 1: Enable

  /* Cấu hình DMA1 Channel 1 (Xem channel trong bảng 78) */
  DMA1_Channel1->CCR &= ~DMA_CCR_DIR; // 0: Read from peripheral
  DMA1_Channel1->CCR &= ~DMA_CCR_MEM2MEM; // 0: Memory to memory mode disabled
  DMA1_Channel1->CCR &= ~DMA_CCR_PL; // 00: Low priority
  DMA1_Channel1->CCR &= ~DMA_CCR_MSIZE; // Clear
  DMA1_Channel1->CCR |= DMA_CCR_MSIZE_0; //01: Memory size 16-bits
  DMA1_Channel1->CCR &= ~DMA_CCR_PSIZE; // Clear
  DMA1_Channel1->CCR |= DMA_CCR_PSIZE_0; //01: Periph size 16-bits
  DMA1_Channel1->CCR |= DMA_CCR_MINC; // 1: Memory increment mode enabled
  DMA1_Channel1->CCR &= ~DMA_CCR_PINC; // 0: Peripheral increment mode disabled
  DMA1_Channel1->CCR |= DMA_CCR_CIRC; // 1: Circular mode enabled
  DMA1_Channel1->CNDTR = (uint32_t)BUFFER_SIZE; // Buffer size
  DMA1_Channel1->CPAR = (uint32_t)0x40012400 + (uint32_t)0x4C; // periph address, (ADC_BASE_ADDR + OFFSET của thanh ghi ADC1_DR)
  DMA1_Channel1->CMAR = (uint32_t)&adcValue[0]; // memory address

  /* Bật DMA1 Channel1 */
  DMA1_Channel1->CCR |= DMA_CCR_EN; // 1: Channel enabled

  /* ___ADC___ */

  /* Bật Clock ADC1 */
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // 1: Enable

  /* Cấu hình Clock ADC1 */
  RCC->CFGR &= ~RCC_CFGR_ADCPRE; // Clear
  RCC->CFGR |= RCC_CFGR_ADCPRE_0; // 01: PCLK2 divided by 4

  /* Cấu hình ADC1 */
  ADC1->CR1 &= ~ADC_CR1_DUALMOD; // 0000: Independent mode
  ADC1->CR1 |= ADC_CR1_SCAN; // 1: Scan mode enabled
  ADC1->CR2 |= ADC_CR2_CONT; // 1: Continuous conversion mode
  ADC1->CR2 &= ~ADC_CR2_ALIGN; // 0: Right Alignment
  ADC1->CR2 |= ADC_CR2_EXTSEL; // 111: SWSTART (Software Trigger)
  //ADC1->SQR1 &= ~ADC_SQR1_L; // Clear
  //ADC1->SQR1 |= ADC_SQR1_L_0; // 0001: 2 conversion (Regular channel sequence length)
  // Hoặc sử dụng
  uint32_t adcLength = 2;
  ADC1->SQR1 |= ((adcLength - 1) << 20); // 0001: 2 conversion (Regular channel sequence length)

  /* Cấu hình ADC1 Rank 1 */
  uint32_t adcChannel = 6;
  uint32_t adcRank = 1;
  ADC1->SQR3 |= (adcChannel << (5 * (adcRank - 1))); // Rank = 1th conversion in regular sequence
  ADC1->SMPR2 |= ADC_SMPR2_SMP6; // 111: 239.5 cycles

  /* Cấu hình ADC1 Rank 2 */
  adcChannel = 7;
  adcRank = 2;
  ADC1->SQR3 |= (adcChannel << (5 * (adcRank - 1))); // Rank = 2th conversion in regular sequence
  ADC1->SMPR2 |= ADC_SMPR2_SMP7; // 111: 239.5 cycles

  /* Bật ADC1 DMA */
  ADC1->CR2 |= ADC_CR2_DMA; // 1: DMA mode enabled

  /* Bật ADC1 */
  /* If this bit holds a value of zero and a 1 is written to it then it wakes up the ADC from Power Down state */
  /* Conversion starts when this bit holds a value of 1 and a 1 is written to it. The application should allow a delay of "tSTAB" between power up and start of conversion */
  ADC1->CR2 |= ADC_CR2_ADON; // hold_0->write_1: Wakes up the ADC from Power Down state
  __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); // tSTAB
  ADC1->CR2 |= ADC_CR2_ADON; // hold_1->write_1: Conversion starts

  /* Hiệu chuẩn điện áp tham chiếu (Vref) */
  ADC1->CR2 |= ADC_CR2_RSTCAL; // 1: Initialize calibration register
  while ((ADC1->CR2 & ADC_CR2_RSTCAL) == ADC_CR2_RSTCAL); // This bit is set by software and cleared by hardware. It is cleared after the calibration registersare initialized
  ADC1->CR2 |= ADC_CR2_CAL; // 1: Enable calibration
  while ((ADC1->CR2 & ADC_CR2_CAL) == ADC_CR2_CAL); // This bit is set by software to start the calibration. It is reset by hardware after calibration is complete

  /* ___MAIN___ */

  /* Bắt đầu chuyển đổi */
  ADC1->CR2 |= ADC_CR2_SWSTART; // Sử dụng với mode Continuous

  /* Hàm lặp vô hạn */
  while (1)
  {
    /* Gửi giá trị ADC1 Channel 6 ra usart1 */
    sprintf(strBuffer, "ADC1 (CH6)=%d, ADC1 (CH7)=%d\r\n", adcValue[0], adcValue[1]);
    usart1_putString((uint8_t *)strBuffer);
    delay_ms(100);
  }
}
