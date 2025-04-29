#include "startup.h"

#define BUFFER_SIZE 4

uint32_t srcBuffer[BUFFER_SIZE] = {0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0xDDDDDDDD};
uint32_t dstBuffer[BUFFER_SIZE];

uint8_t buffer_compare(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t bufferLength);

int main(void)
{
  /* ___LIB___ */

  /* Khởi tạo startup */
  startup_init();

  /* ___GPIO___ */

  /* Bật Clock PortC */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);

  /* Set PC13 */
  LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_13);

  /* Cấu hình PC13 */
  LL_GPIO_InitTypeDef LL_GPIO_InitStructure;
  LL_GPIO_InitStructure.Mode = LL_GPIO_MODE_OUTPUT;
  LL_GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_InitStructure.Pin = LL_GPIO_PIN_13;
  LL_GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_LOW;
  LL_GPIO_Init(GPIOC, &LL_GPIO_InitStructure);

  /* ___DMA___ */

  /* Bật Clock DMA */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

  /* Cấu hình DMA1 Channel 1 */
  LL_DMA_InitTypeDef LL_DMA_InitStructure;
  LL_DMA_InitStructure.Direction = LL_DMA_DIRECTION_MEMORY_TO_MEMORY;
  LL_DMA_InitStructure.MemoryOrM2MDstAddress = (uint32_t)&dstBuffer[0];
  LL_DMA_InitStructure.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_WORD;
  LL_DMA_InitStructure.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
  LL_DMA_InitStructure.Mode = LL_DMA_MODE_NORMAL;
  LL_DMA_InitStructure.NbData = (uint32_t)BUFFER_SIZE;
  LL_DMA_InitStructure.PeriphOrM2MSrcAddress = (uint32_t)&srcBuffer[0];
  LL_DMA_InitStructure.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_WORD;
  LL_DMA_InitStructure.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_INCREMENT;
  LL_DMA_InitStructure.Priority = LL_DMA_PRIORITY_LOW;
  LL_DMA_Init(DMA1, LL_DMA_CHANNEL_1, &LL_DMA_InitStructure);

  /* Bật DMA1 Channel1 */
  LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);

  /* ___MAIN___ */

  /* Chờ cho đến khi cờ TC được set, tức là tuyền thành công */
  while (!LL_DMA_IsActiveFlag_TC1(DMA1));

  /* Xóa cờ DMA1 Channel1 HT, TC, TE và GL */
  LL_DMA_ClearFlag_GI1(DMA1);

  /* Nếu Buffer nguồn (Flash) và Buffer đích (SRAM) giống nhau */
  if (buffer_compare((uint32_t *)srcBuffer, (uint32_t *)dstBuffer, BUFFER_SIZE) == 1)
  {
    /* Reset PC13 */
    LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_13);
  }
  else
  {
    /* Set PC13 */
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_13);
  }

  /* Lặp vô hạn */
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
