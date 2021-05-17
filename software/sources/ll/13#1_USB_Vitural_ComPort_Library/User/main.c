#include "startup.h"
#include "delay.h"
#include "usbvcp.h"
#include "stdio.h"
#include "string.h"

uint32_t prevTick = 0;
char strBuffer[32];

int main(void)
{
  /* ___LIB___ */

  /* Khởi tạo startup */
  startup_init();

  /* Khởi tạo delay */
  delay_init();

  /* Khởi tạo usbvcp */
  usbvcp_init();

  /* Lặp vô hạn */
  while (1)
  {
    /* Định thời 1s */
    if (delay_getTick() - prevTick >= 1000)
    {
      prevTick = delay_getTick();

      /* Gửi dữ liệu ra usbvcp */
      sprintf(strBuffer, "Hello World!\r\n");
      usbvcp_transmit((uint8_t *)strBuffer, (uint16_t)strlen(strBuffer));
    }
  }
}

/* Hàm gọi về khi nhận được dữ liệu */
void usbvcp_receiveCallback(uint8_t *buf, uint32_t len)
{
  /* Gửi ngược lại dữ liệu ra usbvcp */
  sprintf(strBuffer, "buf=%s, len=%d\r\n", (char *)buf, len);
  usbvcp_transmit((uint8_t *)strBuffer, (uint16_t)strlen(strBuffer));

  /* Đặt lại bộ đệm */
  memset(buf, 0, len);
}
