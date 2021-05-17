#include <stm32f10x.h>
#include <stdio.h>
#include "..\libraries\delay.h"
#include "..\libraries\usart1.h"

uint16_t adcValue[2];
char strBuffer[32];

int main(void)
{
  /* ___LIB___ */

  /* Khởi tạo thư viện delay */
  delay_init();

  /* Khởi tạo thư viện usart1 */
  usart1_init();

  /* ___GPIO___ */

  /* Bật Clock PortA */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  /* Cấu hình PA6 (ADC1 Channel 6) */
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Cấu hình PA7 (ADC1 Channel 7) */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* ___DMA___ */

  /* Bật Clock DMA1 */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  /* Cấu hình DMA Channel 1 (Xem chanel trong bảng 78) */
  DMA_InitTypeDef DMA_InitStructure;
  DMA_InitStructure.DMA_BufferSize = 2;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; // Đọc từ Periph
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; // Disable Memmory to memory (or Periph <-> Memory)
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; // Enable Circular Mode
  DMA_InitStructure.DMA_Priority = DMA_Priority_High; // Mức độ ưu tiên cao
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&adcValue[0]; // Địa chỉ của memory
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; // Độ rộng của memory data
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; // Enable Memory Increment mode
  DMA_InitStructure.DMA_PeripheralBaseAddr = 0x4001244C; // Địa chỉ của periph
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // Độ rộng của periph data
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // Disable Periph Increment mode
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);

  /* Bật DMA1 Channel 1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);

  /* ____ADC___ */

  /* Bật Clock ADC1 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  /* Cấu hình Clock ADC */
  RCC_ADCCLKConfig(RCC_PCLK2_Div4);

  /* Cấu hình ADC1 Channel 6 và Channel 7 */
  ADC_InitTypeDef ADC_InitStructure;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE; // Enable scan mode
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; // Enable continous
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // Data align right
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // Sofware start trigger
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; // Mode Independent
  ADC_InitStructure.ADC_NbrOfChannel = 2; // Number channel
  ADC_Init(ADC1, &ADC_InitStructure);

  /* Cấu hình ADC1 Rank 1 */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_239Cycles5);

  /* Cấu hình ADC1 Rank 2 */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 2, ADC_SampleTime_239Cycles5);

  /* Cho phép ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);

  /* Bật ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Hiệu chuẩn điện áp tham chiếu (Vref) */
  ADC_ResetCalibration(ADC1);
  while (ADC_GetResetCalibrationStatus(ADC1));
  ADC_StartCalibration(ADC1);
  while (ADC_GetCalibrationStatus(ADC1));

  /* ___MAIN___ */

  /* Cho phép chuyển đổi */
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);

  while (1)
  {
    /* Gửi giá trị ra usart1 */
    sprintf(strBuffer, "ADC CH6 Value=%d, ADC CH7 Value=%d\r\n", adcValue[0], adcValue[1]);
    usart1_putString((uint8_t *)strBuffer);
    delay_ms(100);
  }
}
