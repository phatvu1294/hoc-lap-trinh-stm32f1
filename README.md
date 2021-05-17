# Học Lập Trình STM32F1 Public
*Tự học lập trình STM32F1 Public bao gồm code mẫu thư viện CMSIS, StdPeriph, HAL, Low-Layer*

### Giới thiệu
Bản rút gọn public này không hỗ trợ đầy đủ source trên MDK-ARM/MDK-ARM Legacy IDE sẽ bị **hạn chế một số nội dung**
và chỉ có tệp **main.c** mang tính chất tham khảo.

Bản đầy đủ private này đầy đủ source trên MDK-ARM/MDK-ARM Legacy IDE, ngoài ra sẽ có thêm tài liệu tham khảo, tài liệu cách sử dụng.
Lưu ý: Riêng bản HAL có dùng thêm STM32CubeMX để tạo project, còn lại chỉ dùng MDK MDK-ARM V5 Legacy IDE tạo project thủ công và code.

Nội dung đầy đủ này chỉ dành cho chủ repo:
- CMSIS (MDK-ARM V5 Legacy IDE): https://github.com/phatvu1294/hoc-lap-trinh-stm32f1-cmsis
- StdPeriph (MDK-ARM V5 Legacy IDE): https://github.com/phatvu1294/hoc-lap-trinh-stm32f1-stdperiph
- HAL (STM32CubeMX + MDK-ARM V5 IDE): https://github.com/phatvu1294/hoc-lap-trinh-stm32f1-hal
- Low-Layer + FreeRTOS (MDK-ARM V5 Legacy IDE): https://github.com/phatvu1294/hoc-lap-trinh-stm32f1-ll

Các thư viện (libraries) như startup, delay, usart, spi, i2c, lcd, pcf8574lcd, ssd1306, mpu6050, dht, ds18b20, ... chỉ có trong bản đầy đủ private.

### Nội dung CMSIS
- 01#1_New_Project
- 02#1_RCC_Configuration
- 02#2_RCC_Startup_Library
- 03#1_GPIO_Output_Mode
- 03#2_GPIO_Input_Mode
- 04#1_SYSTICK_Delay
- 04#2_SYSTICK_Delay_Library
- 05#1_EXTI_External_Interrupt
- 06#1_DMA_M2M_Mode
- 06#2_DMA_M2M_Interrupt_Mode
- 07#1_NVIC_Interrupt_Priority
- 08#1_UART_Polling_Mode
- 08#2_UART_Interrupt_Mode
- 08#3_UART_Library
- 09#1_TIM_Base_Interrupt
- 09#2_TIM_Output_Compare_Toggle
- 09#3_TIM_PWM_Output
- 09#4_TIM_Input_Capture
- 09#5_TIM_PWM_Input
- 09#6_TIM_Encoder_Mode
- 10#1_ADC_Polling_Mode
- 10#2_ADC_Interrupt_Mode
- 10#3_ADC_Analog_Watchdog
- 10#4_ADC_Scan_Mode_DMA
- 10#5_ADC_Timer_Trigger_DMA
- 10#6_ADC_Injected_Channel
- 11#1_SPI_Simplex_Mode_HC595
- 11#2_SPI_Two_SPI_Interface
- 12#1_I2C_Library
- 12#2_I2C_AT24CXX_EEPROM
- 12#3_I2C_PCF8574_LCD
- 12#4_I2C_MPU6050
- libraries

### Nội dung StdPeriph
- 01#1_New_Project
- 02#1_RCC_Configuration
- 03#1_GPIO_Output_Mode
- 03#2_GPIO_Input_Mode
- 04#1_SYSTICK_Delay
- 04#2_SYSTICK_Library
- 05#1_EXTI_External_Interrupt
- 06#1_DMA_M2M_Mode
- 06#2_DMA_M2M_Mode_Interrupt
- 07#1_NVIC_Interrupt_Priority
- 08#1_UART_Polling_Mode
- 08#2_UART_Interrupt_Mode
- 08#3_UART_Library
- 09#1_TIM_Base_Interrupt
- 09#2_TIM_PWM_Output
- 09#3_TIM_Input_Capture
- 09#4_TIM_PWM_Input
- 09#5_TIM_Encoder_Mode
- 10#1_ADC_Polling_Mode
- 10#2_ADC_Interrupt_Mode
- 10#3_ADC_Analog_Watchdog
- 10#4_ADC_Scan_Mode_DMA
- 10#5_ADC_Timer_Trigger_DMA
- 10#6_ADC_Injected_Channel
- 11#1_SPI_Simplex_HC595
- 11#2_SPI_Simplex_Two_SPI
- 12#1_I2C_Master_AT24C08
- 13#1_CAN_LoopBack_TX
- 13#2_CAN_LoopBack_RX
- 13#3_CAN_LoopBack_Interrupt
- 13#4_CAN_Normal_Two_Board
- libraries

### Nội dung HAL
- 01#1_Getting_Started
- 02#1_HAL_Bai_2.1_New_Project
- 02#2_HAL_Bai_2.2_SysTick_Timer
- 03#1_RCC_Bai_3.1_System_Clocks_Configuration
- 03#2_RCC_Bai_3.2_Software_Reset
- 04#1_GPIO_Bai_4.1_Output_Configuration
- 04#2_GPIO_Bai_4.2_Input_Configuration
- 05#1_EXTI_Bai_5.1_External_Interrupt_Configuration
- 06#1_NVIC_Bai_6.1_Interrupt_Priority_Configuration
- 07#1_DMA_Bai_7.1_Memory_To_Memory_Mode
- 07#2_DMA_Bai_7.1_Memory_To_Memory_Mode_IT
- 08#1_UART_Bai_8.1_Polling_Mode
- 08#2_UART_Bai_8.1_Data_Type_Conversion
- 08#3_UART_Bai_8.2_Interrupt_Mode
- 08#4_UART_Bai_8.2_RX_FIFO_Buffer
- 08#5_UART_Bai_8.2_DMA_Mode
- 09#1_TIM_Bai_9.1_Time_Based_Interrupt
- 09#2_TIM_Bai_9.1_Encoder_Interface_Mode
- 09#3_TIM_Bai_9.2_Output_Compare_Toggle
- 09#4_TIM_Bai_9.2_PWM_Output
- 09#5_TIM_Bai_9.3_Input_Capture
- 09#6_TIM_Bai_9.3_PWM_Input
- 10#1_ADC_Bai_10.1_Polling_Mode
- 10#2_ADC_Bai_10.1_Interrupt_Mode
- 10#3_ADC_Bai_10.2_Analog_Watchdog
- 10#4_ADC_Bai_10.2_Scan_Mode
- 10#5_ADC_Bai_10.3_Timer_Trigger
- 10#6_ADC_Bai_10.3_Injected_Channel
- 11#1_SPI_Bai_11.1_74595_Shift_Register
- 12#1_I2C_Bai_12.1_AT24C08_EEPROM
- 12#2_I2C_Bai_12.1_AT24C08_EEPROM_DMA
- 12#3_I2C_Bai_12.2_Two_Boards_Communication
- 12#4_I2C_Bai_12.2_Two_Boards_Communication_Master
- 13#1_WDG_Bai_13.1_Window_Watchdog
- 13#2_WDG_Bai_13.1_Independent_Watchdog
- 14#1_PWR_Bai_14.1_Sleep_Mode
- 14#2_PWR_Bai_14.1_Stop_Mode
- 14#3_PWR_Bai_14.1_Standby_Mode

### Nội dung Low-Layer + FreeRTOS
