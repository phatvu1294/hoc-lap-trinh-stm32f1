#include <stm32f10x.h>
//#include "..\libraries\delay.h"

void usart1_putChar(uint8_t c);
void usart1_putString(uint8_t *s);
uint8_t usart1_getChar(void);

int main(void)
{
	/* ___LIB___ */
	
	/* Khởi tạo thư viện delay */
	//delay_init();
	
  /* ___GPIO___ */

  /* Bật Clock PortA */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  /* Cấu hình PA10 (USART1 RX) */
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Cấu hình PA9 (USART1 TX) */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* ___AFIO___ */

  /* Bật clock AFIO để remap lại chân USART1, Xem tài liệu TX:PA9/PB6(remap), RX:PA10/PB7(remap) */
  /* Phải cấu hình chân GPIO về PB6 và PB7 */
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  //GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

  /* ___USART___ */

  /* Bật Clock USART1 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  /* Cấu hình USART1 */
  USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_Init(USART1, &USART_InitStructure);
  USART_Cmd(USART1, ENABLE);

  while (1)
  {
    /* Gửi chuỗi ra USART1 */
    //usart1_putString((uint8_t *)"Hello World!\r\n");
    //delay_ms(1000);

    /* Đọc được ký tự nào thì gửi ngược ra USART1 */
    /* Không nên sử dụng delay */
    usart1_putChar(usart1_getChar());
  }
}

/* Hàm gửi ký tự ra USART1 */
void usart1_putChar(uint8_t c)
{
  /* Gửi từng byte ra USART1 */
  USART_SendData(USART1, c);

  /* Chờ cho đến khi USART1 data rỗng */
  /* Cờ TXE = 1: USART1 truyền thành công và USART1 data lúc này rỗng */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/* Hàm gửi chuỗi ra USART1 */
void usart1_putString(uint8_t *s)
{
  uint8_t i = 0;

  /* Nếu không phải là ký tự null */
  while (s[i] != 0)
  {
    /* Gửi ký tự ra USART1 */
    usart1_putChar(s[i++]);
  }
}

/* Hàm nhận ký tự từ USART1 */
uint8_t usart1_getChar(void)
{
  /* Chờ cho đến khi USART1 data khác rỗng */
  /* Cờ RXNE = 1: USART1 sẵn sàng đọc dữ liệu và USART1 data lúc này khác rỗng */
  while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

  /* Trả về ký tự nhận được từ thanh ghi USART1 data */
  return USART_ReceiveData(USART1);
}
