#include "startup.h"
#include "usart1.h"
#include "delay.h"
#include "stdio.h"

#define BUFFER_SIZE 2

uint16_t adcValue[BUFFER_SIZE];
char strBuffer[32];

int main(void)
{
  /* ___LIB___ */

  /* Khởi tạo startup */
  startup_init();

  /* Khởi tạo delay */
  delay_init();

  /* Khởi tạo usart1 */
  usart1_init();

  /* ___GPIO___ */

  /* Bật Clock PortA */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);

  /* Cấu hình PA6 (ADC1 Channel6), PA7 (ADC1 Channel7) */
  LL_GPIO_InitTypeDef LL_GPIO_InitStructure;
  LL_GPIO_InitStructure.Mode = LL_GPIO_MODE_ANALOG;
  LL_GPIO_InitStructure.Pin = LL_GPIO_PIN_6 | LL_GPIO_PIN_7;
  LL_GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_LOW;
  LL_GPIO_Init(GPIOA, &LL_GPIO_InitStructure);

  /* ___DMA___ */

  /* Bật Clock DMA1 */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

  /* Cấu hình DMA1 Channel 1 (Xem channel trong bảng 78) */
  LL_DMA_InitTypeDef LL_DMA_InitStructure;
  LL_DMA_InitStructure.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
  LL_DMA_InitStructure.MemoryOrM2MDstAddress = (uint32_t)&adcValue[0];
  LL_DMA_InitStructure.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_HALFWORD;
  LL_DMA_InitStructure.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
  LL_DMA_InitStructure.Mode = LL_DMA_MODE_CIRCULAR;
  LL_DMA_InitStructure.NbData = (uint32_t)BUFFER_SIZE;
  LL_DMA_InitStructure.PeriphOrM2MSrcAddress = (uint32_t)0x40012400 + (uint32_t)0x4C; // ADC_BASE_ADDR + OFFSET của thanh ghi ADC1_DR
  LL_DMA_InitStructure.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_HALFWORD;
  LL_DMA_InitStructure.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
  LL_DMA_InitStructure.Priority = LL_DMA_PRIORITY_LOW;
  LL_DMA_Init(DMA1, LL_DMA_CHANNEL_1, &LL_DMA_InitStructure);

  /* Bật DMA1 Channel1 */
  LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);

  /* ___ADC___ */

  /* Bật Clock PortA */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);

  /* Cấu hình Clock ADC1 */
  LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSRC_PCLK2_DIV_4);

  /* Cấu hình ADC1 */
  LL_ADC_InitTypeDef LL_ADC_InitStructure;
  LL_ADC_InitStructure.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
  LL_ADC_InitStructure.SequencersScanMode = LL_ADC_SEQ_SCAN_ENABLE;
  LL_ADC_Init(ADC1, &LL_ADC_InitStructure);

  /* Cấu hình ADC1 Regular Channel */
  LL_ADC_REG_InitTypeDef LL_ADC_REG_InitStructure;
  LL_ADC_REG_InitStructure.ContinuousMode = LL_ADC_REG_CONV_CONTINUOUS;
  LL_ADC_REG_InitStructure.DMATransfer = LL_ADC_REG_DMA_TRANSFER_UNLIMITED; // Bật ADC1 DMA
  LL_ADC_REG_InitStructure.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
  LL_ADC_REG_InitStructure.SequencerLength = LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS;
  LL_ADC_REG_InitStructure.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
  LL_ADC_REG_Init(ADC1, &LL_ADC_REG_InitStructure);

  /* Cấu hình ADC1 REG Rank 1 */
  LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_6);

  /* Cấu hình ADC1 REG Rank 2 */
  LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_2, LL_ADC_CHANNEL_7);

  /* Cấu hình thời gian trích mẫu */
  LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_6, LL_ADC_SAMPLINGTIME_239CYCLES_5);
  LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_7, LL_ADC_SAMPLINGTIME_239CYCLES_5);

  /* Bật ADC1 */
  LL_ADC_Enable(ADC1);

  /* Hiệu chuẩn điện áp tham chiếu (Vref) */
  LL_ADC_StartCalibration(ADC1);

  /* Trong khi đang hiệu chuẩn */
  while (LL_ADC_IsCalibrationOnGoing(ADC1));

  /* ___MAIN___ */

  /* Bắt đầu chuyển đổi */
  LL_ADC_REG_StartConversionSWStart(ADC1); // Sử dụng với mode Continuous

  /* Lặp vô hạn */
  while (1)
  {
    /* Gửi giá trị ADC1 Channel 6 ra usart1 */
    sprintf(strBuffer, "ADC1 (CH6)=%d, ADC1 (CH7)=%d\r\n", adcValue[0], adcValue[1]);
    usart1_putString((uint8_t *)strBuffer);
    delay_ms(100);
  }
}
