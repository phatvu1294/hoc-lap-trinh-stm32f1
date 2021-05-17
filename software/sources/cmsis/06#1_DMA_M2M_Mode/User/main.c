#include "stm32f1xx.h"
#include "startup.h"

#define BUFFER_SIZE 4

uint32_t srcBuffer[BUFFER_SIZE] = {0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0xDDDDDDDD};
uint32_t dstBuffer[BUFFER_SIZE];

uint8_t buffer_compare(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t bufferLength);

int main(void)
{
  /* Thêm chương trình chính tại đây */

  /* ___LIB___ */

  /* Khởi tạo hệ thống */
  startup_init();

  /* ___GPIO___ */

  /* Bật Clock PortC */
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // 1: Enable

  /* Set PC13 */
  GPIOC->BSRR |= GPIO_BSRR_BS13;

  /* Cấu hình PC13 */
  GPIOC->CRH &= ~GPIO_CRH_MODE13; // Clear
  GPIOC->CRH |= GPIO_CRH_MODE13_1; // 10: Output mode, max speed 2 MHz
  GPIOC->CRH &= ~GPIO_CRH_CNF13; // 00: General purpose output push-pull

  /* ___DMA___ */

  /* Bật Clock DMA */
  RCC->AHBENR |= RCC_AHBENR_DMA1EN; // 1: Enable

  /* Cấu hình DMA1 Channel1 */
  DMA1_Channel1->CCR &= ~DMA_CCR_DIR; // 0: Read from peripheral
  DMA1_Channel1->CCR |= DMA_CCR_MEM2MEM; // 1: Memory to memory mode enabled
  DMA1_Channel1->CCR &= ~DMA_CCR_PL; // 00: Low priority
  DMA1_Channel1->CCR &= ~DMA_CCR_MSIZE; // Clear
  DMA1_Channel1->CCR |= DMA_CCR_MSIZE_1; //10: Memory size 32-bits
  DMA1_Channel1->CCR &= ~DMA_CCR_PSIZE; // Clear
  DMA1_Channel1->CCR |= DMA_CCR_PSIZE_1; //10: Periph size 32-bits
  DMA1_Channel1->CCR |= DMA_CCR_MINC; // 1: Memory increment mode enabled
  DMA1_Channel1->CCR |= DMA_CCR_PINC; // 1: Peripheral increment mode enabled
  DMA1_Channel1->CCR &= ~DMA_CCR_CIRC; // 0: Circular mode disabled
  DMA1_Channel1->CNDTR = (uint32_t)BUFFER_SIZE; // Buffer size
  DMA1_Channel1->CPAR = (uint32_t)&srcBuffer[0]; // &srcBuffer[0] <=> srcBuffer, periph address
  DMA1_Channel1->CMAR = (uint32_t)&dstBuffer[0]; // &dstBuffer[0] <=> dstBuffer, memory address

  /* Bật DMA1 Channel1 */
  DMA1_Channel1->CCR |= DMA_CCR_EN; // 1: Channel enabled

  /* ___MAIN___ */

  /* Chờ cho đến khi cờ TC được set, tức là truyền thành công */
  while ((DMA1->ISR & DMA_ISR_TCIF1) != DMA_ISR_TCIF1) { } // 1: A transfer complete (TC) event occurred on channel x

  /* Xoá cờ DMA1 Channel1 HT, TC, TE và GL */
  DMA1->IFCR |= DMA_IFCR_CGIF1; // 1: Clears the GIF, TEIF, HTIF and TCIF flags in the DMA_ISR register

  /* Nếu Buffer nguồn (Flash) và Buffer đích (SRAM) giống nhau */
  if (buffer_compare((uint32_t *)srcBuffer, (uint32_t *)dstBuffer, BUFFER_SIZE) == 1)
  {
    /* Reset PC13 */
    GPIOC->BSRR |= GPIO_BSRR_BR13;
  }
  else
  {
    /* Set PC13 */
    GPIOC->BSRR |= GPIO_BSRR_BS13;
  }

  /* Hàm lặp vô hạn */
  while (1)
  {

  }
}

/* Hàm so sánh hai Buffer */
uint8_t buffer_compare(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t bufferLength)
{
  while (bufferLength--)
  {
    if (*pBuffer != *pBuffer1)
    {
      return 0;
    }
    pBuffer++;
    pBuffer1++;
  }

  return 1;
}
