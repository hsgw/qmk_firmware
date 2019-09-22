/* Copyright 2019 Takuya Urakawa, Dm9Recoreds.com
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

// place overrides here


#define RGBLED_NUM 5
#define DRIVER_LED_TOTAL RGBLED_NUM

#define RGBLIGHT_ANIMATIONS
#define RGB_MATRIX_KEYPRESSES

#define RGB_DI_PIN      B4                      // WS2812 DATA Pin
#define WS2812_TIM_N    3                       // TIMx
#define WS2812_TIM_CH   0                       // Channel - 1
#define WS2812_AF       1                       // DI Pin's alternate function value
#define WS2812_DMA_STREAM STM32_DMA1_STREAM1    // DMA Stream for TIMx_UP
#define WS2812_DMA_CHANNEL 3                    // DMA Channel for TIMx_UP

