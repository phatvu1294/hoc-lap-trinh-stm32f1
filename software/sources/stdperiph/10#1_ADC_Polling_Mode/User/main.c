#include <stm32f10x.h>
#include <stdio.h>
#include "..\libraries\delay.h"
#include "..\libraries\usart1.h"

uint16_t adcValue = 0;
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

  /* ___ADC___ */

  /* Bật Clock ADC1 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  /* Cấu hình Clock ADC */
  RCC_ADCCLKConfig(RCC_PCLK2_Div4);

  /* Cấu hình ADC1 Channel 6 */
  ADC_InitTypeDef ADC_InitStructure;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE; // Disable scan mode
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; // Enable continous
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // Data align right
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // Sofware start trigger
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; // Mode Independent
  ADC_InitStructure.ADC_NbrOfChannel = 1; // Number channel
  ADC_Init(ADC1, &ADC_InitStructure);

  /* Cấu hình ADC1 Rank 1 */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_239Cycles5);

  /* Bật ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Hiệu chuẩn điện áp tham chiếu (Vref) */
  ADC_ResetCalibration(ADC1);
  while (ADC_GetResetCalibrationStatus(ADC1));
  ADC_StartCalibration(ADC1);
  while (ADC_GetCalibrationStatus(ADC1));

  /* ___MAIN___ */

  /* Bắt đầu chuyển đổi */
  ADC_SoftwareStartConvCmd(ADC1, ENABLE); // Sử dụng cho mode continous

  while (1)
  {
    /* Bắt đầu chuyển đổi */
    //ADC_SoftwareStartConvCmd(ADC1, DISABLE); // Sử dụng cho mode discontinous

    /* Chờ cho đến khi ADC1 chuyển đổi thành công */
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

    /* Đọc giá trị ADC1 */
    adcValue = ADC_GetConversionValue(ADC1);

    /* xoá cờ EOC */
    ADC_ClearFlag(ADC1, ADC_FLAG_EOC);

    /* Dừng chuyển đổi */
    //ADC_SoftwareStartConvCmd(ADC1, DISABLE); // Sử dụng cho mode discontinous

    /* Gửi giá trị ra usart1 */
    sprintf(strBuffer, "ADC Value=%d\r\n", adcValue);
    usart1_putString((uint8_t *)strBuffer);
    delay_ms(100);
  }
}
