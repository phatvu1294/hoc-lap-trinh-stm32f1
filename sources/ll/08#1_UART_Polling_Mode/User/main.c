#include "startup.h"
#include "delay.h"

void usart1_putChar(uint8_t c);
void usart1_putString(uint8_t *s);
uint8_t usart1_getChar(void);

int main(void)
{
  /* ___LIB___ */

  /* Khởi tạo startup */
  startup_init();

  /* Khởi tạo delay */
  delay_init();

  /* ___GPIO___ */

  /* Bật Clock PortA */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);

  /* Cấu hình PA10 (RX) */
  LL_GPIO_InitTypeDef LL_GPIO_InitStructure;
  LL_GPIO_InitStructure.Mode = LL_GPIO_MODE_FLOATING;
  LL_GPIO_InitStructure.Pin = LL_GPIO_PIN_10;
  LL_GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_LOW;
  LL_GPIO_Init(GPIOA, &LL_GPIO_InitStructure);

  /* Cấu hình PA9 (TX) */
  LL_GPIO_InitStructure.Mode = LL_GPIO_MODE_ALTERNATE;
  LL_GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_InitStructure.Pin = LL_GPIO_PIN_9;
  LL_GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_LOW;
  LL_GPIO_Init(GPIOA, &LL_GPIO_InitStructure);

  /* ___AFIO___ */

  /* Bật Clock AFIO để remap USART1, xem tài liệu TX:PA9/PB6(remap), RX:PA10/PB7(remap) */
  /* Phải cấu hình lại chân GPIO về PB6 và PB7 */
  //LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
  //LL_GPIO_AF_EnableRemap_USART1();

  /* ___USART___ */

  /* Bật Clock USART1 */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

  /* Cấu hình USART1 */
  LL_USART_InitTypeDef LL_USART_InitStructure;
  LL_USART_InitStructure.BaudRate = 9600;
  LL_USART_InitStructure.DataWidth = LL_USART_DATAWIDTH_8B;
  LL_USART_InitStructure.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  LL_USART_InitStructure.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_InitStructure.Parity = LL_USART_PARITY_NONE;
  LL_USART_InitStructure.StopBits = LL_USART_STOPBITS_1;
  LL_USART_InitStructure.TransferDirection = LL_USART_DIRECTION_TX_RX;
  LL_USART_Init(USART1, &LL_USART_InitStructure);

  /* Chế độ bất đồng bộ */
  LL_USART_ConfigAsyncMode(USART1);

  /* Bật USART1 */
  LL_USART_Enable(USART1);

  /* Lặp vô hạn */
  while (1)
  {
    /* Gửi chuỗi ra USART1 */
    usart1_putString((uint8_t *)"Hello World!\r\n");
    delay_ms(1000);

    /* Nhận được ký tự nào thì gửi ra USART1 */
    //usart1_putChar(usart1_getChar());
  }
}

/* Hàm gửi ký tự ra USART1 */
void usart1_putChar(uint8_t c)
{
  /* Gửi ký tự nhận được ra USART1 */
  LL_USART_TransmitData8(USART1, c);

  /* Chờ cho đến khi thanh ghi USART1 data rỗng */
  /* Cờ TXE = 1: USART1 truyền thành công và USART1 data lúc này rỗng */
  while (!LL_USART_IsActiveFlag_TXE(USART1));
}

/* Hàm gửi chuỗi ra USART1 */
void usart1_putString(uint8_t *s)
{
  uint8_t i = 0;

  /* Nếu không phải ký tự null */
  while (s[i] != 0)
  {
    /* Gửi ký tự */
    usart1_putChar(s[i++]);
  }
}

/* Hàm nhận ký tự từ USART1 */
uint8_t usart1_getChar(void)
{
  /* Chờ cho đến khi thanh ghi USART1 data khác rỗng */
  /* Cờ RXNE = 1: USART1 sẵn sàng đọc dữ liệu và USART1 data lúc này khác rỗng */
  while (!LL_USART_IsActiveFlag_RXNE(USART1));

  /* Trả về ký tự nhận được từ thanh ghi USART1 data */
  return LL_USART_ReceiveData8(USART1);
}
