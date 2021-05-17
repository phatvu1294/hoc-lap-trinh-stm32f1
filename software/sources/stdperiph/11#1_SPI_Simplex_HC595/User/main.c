#include <stm32f10x.h>
#include "..\libraries\delay.h"

uint8_t txBuffer;
uint32_t prevMillis = 0;

int main(void)
{
  /* ___LIB___ */

  /* Khởi tạo thư viện delay */
  delay_init();

  /* ___GPIO___ */

  /* Bật Clock PortA và PortB */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

  /* Cấu hình PA7 (SPI1 MOSI) */
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Cấu hình PA5 (SPI1 CLK) */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Cấu hình PB0 (HC595 Latch) */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);

  /* ___SPI___ */

  /* Bật Clock SPI1 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

  /* Cấu hình SPI1 */
  SPI_InitTypeDef SPI_InitStructure;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; // Prescaler
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; // Clock Phase
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; // Clock Polarity LOW
  SPI_InitStructure.SPI_CRCPolynomial = 0; // 0
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; // Data size 8bit
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx; // Simplex
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; // MSB First
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master; // Mode Master
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; // NSS Signal Software
  SPI_Init(SPI1, &SPI_InitStructure);
  SPI_CalculateCRC(SPI1, DISABLE); // Disable CRC Calculation

  /* Bật SPI1 */
  SPI_Cmd(SPI1, ENABLE);

  /* ___MAIN___ */

  /* Đặt dữ liệu gửi đi */
  txBuffer = 0x00;

  while (1)
  {
    /* Gửi dữ liệu ra SPI1 */
    SPI_I2S_SendData(SPI1, txBuffer);

    /* Chờ cho đến khi SPI TX data rỗng (TXE) */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

    /* Chốt dữ liệu HC595 */
    GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);
    delay_ms(1);
    GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);

    /* Định thời 100ms tăng dữ liệu bộ đếm lên 1 */
    if (millis() - prevMillis >= 200)
    {
      prevMillis = millis();
      if (++txBuffer > 255) txBuffer = 0x00;
    }
  }
}
