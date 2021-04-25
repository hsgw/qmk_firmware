/* Copyright 2020 QMK
 * Copyright 2021 SMKiJ Casasagi Contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include_next <mcuconf.h>

#undef STM32_NO_INIT
#undef STM32_PVD_ENABLE
#undef STM32_PLS
#undef STM32_HSI_ENABLED
#undef STM32_HSI14_ENABLED
#undef STM32_HSI48_ENABLED
#undef STM32_LSI_ENABLED
#undef STM32_HSE_ENABLED
#undef STM32_LSE_ENABLED
#undef STM32_SW
#undef STM32_PLLSRC
#undef STM32_PREDIV_VALUE
#undef STM32_PLLMUL_VALUE
#undef STM32_HPRE
#undef STM32_PPRE
#undef STM32_ADCSW
#undef STM32_ADCPRE
#undef STM32_MCOSEL
#undef STM32_ADCPRE
#undef STM32_ADCSW
#undef STM32_USBSW
#undef STM32_CECSW
#undef STM32_I2C1SW
#undef STM32_USART1SW
#undef STM32_RTCSEL

#define STM32_NO_INIT FALSE
#define STM32_PVD_ENABLE FALSE
#define STM32_PLS STM32_PLS_LEV0
#define STM32_HSI_ENABLED TRUE
#define STM32_HSI14_ENABLED TRUE
#define STM32_HSI48_ENABLED FALSE
#define STM32_LSI_ENABLED TRUE
#define STM32_HSE_ENABLED TRUE
#define STM32_LSE_ENABLED FALSE
#define STM32_SW STM32_SW_PLL
#define STM32_PLLSRC STM32_PLLSRC_HSE
#define STM32_PREDIV_VALUE 1
#define STM32_PLLMUL_VALUE 6
#define STM32_HPRE STM32_HPRE_DIV1
#define STM32_PPRE STM32_PPRE_DIV1
#define STM32_ADCSW STM32_ADCSW_HSI14
#define STM32_ADCPRE STM32_ADCPRE_DIV4
#define STM32_MCOSEL STM32_MCOSEL_NOCLOCK
#define STM32_ADCPRE STM32_ADCPRE_DIV4
#define STM32_ADCSW STM32_ADCSW_HSI14
#define STM32_USBSW STM32_USBSW_PCLK
#define STM32_CECSW STM32_CECSW_HSI
#define STM32_I2C1SW STM32_I2C1SW_HSI
#define STM32_USART1SW STM32_USART1SW_PCLK
#define STM32_RTCSEL STM32_RTCSEL_LSI

#undef STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE

#undef STM32_I2C_USE_I2C2
#define STM32_I2C_USE_I2C2 TRUE
#undef STM32_I2C_USE_DMA
#define STM32_I2C_USE_DMA FALSE
// #define STM32_I2C_I2C2_RX_DMA_STREAM STM32_DMA_STREAM_ID(1, 5)
// #define STM32_I2C_I2C2_TX_DMA_STREAM STM32_DMA_STREAM_ID(1, 4)

#undef STM32_SPI_USE_SPI2
#define STM32_SPI_USE_SPI2 TRUE
#undef STM32_SPI_SPI2_IRQ_PRIORITY
#define STM32_SPI_SPI2_IRQ_PRIORITY 1
// #undef STM32_SPI_SPI2_RX_DMA_STREAM
// #define STM32_SPI_SPI2_RX_DMA_STREAM STM32_DMA_STREAM_ID(1, 6)
// #undef STM32_SPI_SPI2_TX_DMA_STREAM
// #define STM32_SPI_SPI2_TX_DMA_STREAM STM32_DMA_STREAM_ID(1, 7)
