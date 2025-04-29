# Học lập trình STM32F1
*Tự học lập trình STM32F1 bao gồm code mẫu CMSIS, StdPeriph, HAL, Low-Layer, FreeRTOS*

### Giới thiệu
Bản rút gọn public này không hỗ trợ đầy đủ source trên MDK-ARM/MDK-ARM Legacy IDE sẽ bị **hạn chế một số nội dung**
và chỉ có tệp **main.c** mang tính chất tham khảo.

Bản đầy đủ private hỗ trợ source trên MDK-ARM/MDK-ARM Legacy IDE, ngoài ra sẽ có thêm tài liệu tham khảo, tài liệu cách sử dụng.

Việc học tập với HAL cực kỳ đơn giản, do đó nên học HAL đầu tiên (tham khảo lộ trình: HAL -> Stdperiph -> CMSIS -> LL -> FreeRTOS).

**Nội dung dành cho cộng đồng:**
- CMSIS (MDK-ARM V5 Legacy IDE): https://github.com/phatvu1294/hoc-lap-trinh-stm32f1-cmsis

Nội dung đầy đủ này chỉ dành cho chủ repo:
- StdPeriph (MDK-ARM V5 Legacy IDE): https://github.com/phatvu1294/hoc-lap-trinh-stm32f1-stdperiph
- HAL (STM32CubeMX + MDK-ARM V5 IDE): https://github.com/phatvu1294/hoc-lap-trinh-stm32f1-hal
- Low-Layer (MDK-ARM V5 Legacy IDE): https://github.com/phatvu1294/hoc-lap-trinh-stm32f1-ll

Phần mềm, công cụ, tài liệu cần thiết:
- MDK-ARM V5 IDE: https://www.keil.com/download/product/
- MDK-ARM V5 Legacy IDE: https://www2.keil.com/mdk5/legacy
- STM32CubeMX: https://www.st.com/en/development-tools/stm32cubemx.html
- STM32CubeProg: https://www.st.com/en/development-tools/stm32cubeprog.html
- STM32 ST-Link Utility: https://www.st.com/en/development-tools/stsw-link004.html
- ST-Link Driver: https://www.st.com/en/development-tools/stsw-link009.html
- STM32 Virtual ComPort Driver: https://www.st.com/en/development-tools/stsw-stm32102.html
- STM32StdPeriph: https://www.st.com/en/embedded-software/stm32-standard-peripheral-libraries.html
- STM32CubeF1: https://www.st.com/en/embedded-software/stm32cubef1.html
- STM32F1 Reference Manual (RM0008): https://www.st.com/resource/en/reference_manual/cd00171190-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf (tham khảo các ngoại vi tích hợp trên STM32)
- STM32F1 ARM Cortex-M3 Programming Manual (PM0056): https://www.st.com/resource/en/programming_manual/cd00228163-stm32f10xxx-20xxx-21xxx-l1xxxx-cortex-m3-programming-manual-stmicroelectronics.pdf (tham khảo các thành phần liên quan đến lõi Cortex-M3)
- STM32F103C8T6 Datasheet: https://www.st.com/resource/en/datasheet/stm32f103c8.pdf
- FreeRTOS V10.0 Reference Manual: https://www.freertos.org/fr-content-src/uploads/2018/07/FreeRTOS_Reference_Manual_V10.0.0.pdf
- CMSIS-RTOS2 V2: https://www.keil.com/pack/doc/CMSIS/RTOS2/html/group__CMSIS__RTOS.html
- Hecules/RealTerm: Debug dữ liệu từ USART
- HID Termial: Truyền nhận gói dữ liệu từ USB Custom HID
- HID Descriptor: Dùng để tạo Desciption USB Device
- ...

### Nội dung CMSIS (Bây giờ đã public)

Liên kết đầy đủ đến source: https://github.com/phatvu1294/hoc-lap-trinh-stm32f1-cmsis

Các tài liệu về Timer: https://github.com/phatvu1294/hoc-lap-trinh-stm32f1-cmsis/tree/main/documents

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

### Nội dung StdPeriph (Public 1 phần cũ)
- ~~01#1_New_Project~~
- ~~02#1_RCC_Configuration~~
- 03#1_GPIO_Output_Mode
- 03#2_GPIO_Input_Mode
- 04#1_SYSTICK_Delay
- ~~04#2_SYSTICK_Library~~
- 05#1_EXTI_External_Interrupt
- 06#1_DMA_M2M_Mode
- ~~06#2_DMA_M2M_Mode_Interrupt~~
- ~~07#1_NVIC_Interrupt_Priority~~
- 08#1_UART_Polling_Mode
- ~~08#2_UART_Interrupt_Mode~~
- ~~08#3_UART_Library~~
- 09#1_TIM_Base_Interrupt
- ~~09#2_TIM_PWM_Output~~
- ~~09#3_TIM_Input_Capture~~
- ~~09#4_TIM_PWM_Input~~
- ~~09#5_TIM_Encoder_Mode~~
- 10#1_ADC_Polling_Mode
- ~~10#2_ADC_Interrupt_Mode~~
- ~~10#3_ADC_Analog_Watchdog~~
- 10#4_ADC_Scan_Mode_DMA
- ~~10#5_ADC_Timer_Trigger_DMA~~
- ~~10#6_ADC_Injected_Channel~~
- 11#1_SPI_Simplex_HC595
- ~~11#2_SPI_Simplex_Two_SPI~~
- ~~12#1_I2C_Master_AT24C08~~
- ~~13#1_CAN_LoopBack_TX~~
- ~~13#2_CAN_LoopBack_RX~~
- ~~13#3_CAN_LoopBack_Interrupt~~
- ~~13#4_CAN_Normal_Two_Board~~
- ~~libraries~~

### Nội dung HAL (Public 1 phần cũ)
- ~~01#1_Getting_Started~~
- ~~02#1_HAL_Bai_2.1_New_Project~~
- 02#2_HAL_Bai_2.2_SysTick_Timer
- 03#1_RCC_Bai_3.1_System_Clocks_Configuration
- ~~03#2_RCC_Bai_3.2_Software_Reset~~
- 04#1_GPIO_Bai_4.1_Output_Configuration
- 04#2_GPIO_Bai_4.2_Input_Configuration
- 05#1_EXTI_Bai_5.1_External_Interrupt_Configuration
- ~~06#1_NVIC_Bai_6.1_Interrupt_Priority_Configuration~~
- 07#1_DMA_Bai_7.1_Memory_To_Memory_Mode
- ~~07#2_DMA_Bai_7.1_Memory_To_Memory_Mode_IT~~
- 08#1_UART_Bai_8.1_Polling_Mode
- ~~08#2_UART_Bai_8.1_Data_Type_Conversion~~
- ~~08#3_UART_Bai_8.2_Interrupt_Mode~~
- ~~08#4_UART_Bai_8.2_RX_FIFO_Buffer~~
- ~~08#5_UART_Bai_8.2_DMA_Mode~~
- 09#1_TIM_Bai_9.1_Time_Based_Interrupt
- ~~09#2_TIM_Bai_9.1_Encoder_Interface_Mode~~
- ~~09#3_TIM_Bai_9.2_Output_Compare_Toggle~~
- ~~09#4_TIM_Bai_9.2_PWM_Output~~
- ~~09#5_TIM_Bai_9.3_Input_Capture~~
- ~~09#6_TIM_Bai_9.3_PWM_Input~~
- 10#1_ADC_Bai_10.1_Polling_Mode
- ~~10#2_ADC_Bai_10.1_Interrupt_Mode~~
- ~~10#3_ADC_Bai_10.2_Analog_Watchdog~~
- 10#4_ADC_Bai_10.2_Scan_Mode
- ~~10#5_ADC_Bai_10.3_Timer_Trigger~~
- ~~10#6_ADC_Bai_10.3_Injected_Channel~~
- 11#1_SPI_Bai_11.1_74595_Shift_Register
- 12#1_I2C_Bai_12.1_AT24C08_EEPROM
- ~~12#2_I2C_Bai_12.1_AT24C08_EEPROM_DMA~~
- ~~12#3_I2C_Bai_12.2_Two_Boards_Communication~~
- ~~12#4_I2C_Bai_12.2_Two_Boards_Communication_Master~~
- ~~13#1_WDG_Bai_13.1_Window_Watchdog~~
- ~~13#2_WDG_Bai_13.1_Independent_Watchdog~~
- ~~14#1_PWR_Bai_14.1_Sleep_Mode~~
- ~~14#2_PWR_Bai_14.1_Stop_Mode~~
- ~~14#3_PWR_Bai_14.1_Standby_Mode~~

### Nội dung Low-Layer (Public 1 phần cũ)
- ~~01#1_New_Project~~
- ~~02#1_RCC_Configuration~~
- ~~02#2_RCC_Startup_Library~~
- 03#1_GPIO_Output_Mode
- 03#2_GPIO_Input_Mode
- 04#1_SYSTICK_Delay
- ~~04#2_SYSTICK_Delay_Library~~
- 05#1_EXTI_External_Interrupt
- 06#1_DMA_M2M_Mode
- ~~06#2_DMA_M2M_Interrupt_Mode~~
- ~~07#1_NVIC_Interrupt_Priority~~
- 08#1_UART_Polling_Mode
- ~~08#2_UART_Interrupt_Mode~~
- ~~08#3_UART_Library~~
- 09#1_TIM_Base_Interrupt
- ~~09#2_TIM_Output_Compare_Toggle~~
- ~~09#3_TIM_PWM_Output~~
- ~~09#4_TIM_Input_Capture~~
- ~~09#5_TIM_PWM_Input~~
- ~~09#6_TIM_Encoder_Mode~~
- 10#1_ADC_Polling_Mode
- ~~10#2_ADC_Interrupt_Mode~~
- ~~10#3_ADC_Analog_Watchdog~~
- 10#4_ADC_Scan_Mode_DMA
- ~~10#5_ADC_Timer_Trigger_DMA~~
- ~~10#6_ADC_Injected_Channel~~
- ~~11#1_SPI_Simplex_Mode_HC595~~
- ~~11#2_SPI_Two_SPI_Interface~~
- ~~12#1_I2C_Master_Library~~
- ~~12#2_I2C_AT24CXX_EERPOM_Library~~
- ~~12#3_I2C_PCF8574_LCD_Library~~
- ~~12#4_I2C_SSD1306_OLED_Library~~
- 13#1_USB_Vitural_ComPort_Library
- ~~13#2_USB_Winform_VCP_Terminal~~
- ~~13#3_USB_Custom_HID_Library~~
- ~~13#4_USB_HID_Mouse~~
- ~~13#5_USB_HID_Keyboard~~
- ~~13#6_USB_AUDIO_Streaming~~
- 14#1_RTOS2_Thread
- 14#2_RTOS2_Event_Flag
- ~~14#3_RTOS2_Message_Queue~~
- ~~14#4_RTOS2_Mutex~~
- ~~14#5_RTOS2_Binary_Semaphore~~
- ~~14#6_RTOS2_Counting_Semaphore~~
- ~~14#7_RTOS2_Software_Timer~~
- 15#1_FREERTOS_Task
- 15#2_FREERTOS_Task_Notification
- ~~15#3_FREERTOS_Queue~~
- ~~15#4_FREERTOS_Mutex~~
- ~~15#5_FREERTOS_Software_Timer~~
- ~~drivers~~
- ~~libraries~~
