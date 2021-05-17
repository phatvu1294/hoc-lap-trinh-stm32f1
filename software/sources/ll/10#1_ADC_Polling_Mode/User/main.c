#include "startup.h"
#include "usart1.h"
#include "delay.h"
#include "stdio.h"

uint16_t adcValue = 0;
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

  /* Cấu hình PA6 (ADC1 Channel6) */
  LL_GPIO_InitTypeDef LL_GPIO_InitStructure;
  LL_GPIO_InitStructure.Mode = LL_GPIO_MODE_ANALOG;
  LL_GPIO_InitStructure.Pin = LL_GPIO_PIN_6;
  LL_GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_LOW;
  LL_GPIO_Init(GPIOA, &LL_GPIO_InitStructure);

  /* ___ADC___ */

  /* Bật Clock PortA */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);

  /* Cấu hình Clock ADC1 */
  LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSRC_PCLK2_DIV_4);

  /* Cấu hình ADC1 */
  LL_ADC_InitTypeDef LL_ADC_InitStructure;
  LL_ADC_InitStructure.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
  LL_ADC_InitStructure.SequencersScanMode = LL_ADC_SEQ_SCAN_DISABLE;
  LL_ADC_Init(ADC1, &LL_ADC_InitStructure);

  /* Cấu hình ADC1 Regular Channel */
  LL_ADC_REG_InitTypeDef LL_ADC_REG_InitStructure;
  LL_ADC_REG_InitStructure.ContinuousMode = LL_ADC_REG_CONV_CONTINUOUS;
  LL_ADC_REG_InitStructure.DMATransfer = LL_ADC_REG_DMA_TRANSFER_NONE;
  LL_ADC_REG_InitStructure.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
  LL_ADC_REG_InitStructure.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE;
  LL_ADC_REG_InitStructure.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
  LL_ADC_REG_Init(ADC1, &LL_ADC_REG_InitStructure);

  /* Cấu hình ADC1 REG Rank 1 */
  LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_6);

  /* Cấu hình thời gian trích mẫu */
  LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_6, LL_ADC_SAMPLINGTIME_239CYCLES_5);

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
    /* Bắt đầu chuyển đổi */
    //LL_ADC_REG_StartConversionSWStart(ADC1); // Sử dụng với mode Single

    /* Chờ cho đến khi chuyển đổi thành công */
    while (!LL_ADC_IsActiveFlag_EOS(ADC1));

    /* Đọc giá trị ADC1 */
    adcValue = LL_ADC_REG_ReadConversionData12(ADC1);

    /* Xóa cờ EOC */
    LL_ADC_ClearFlag_EOS(ADC1);

    /* Gửi giá trị ADC1 Channel 6 ra usart1 */
    sprintf(strBuffer, "ADC1 (CH6)=%d\r\n", adcValue);
    usart1_putString((uint8_t *)strBuffer);
    delay_ms(100);
  }
}
