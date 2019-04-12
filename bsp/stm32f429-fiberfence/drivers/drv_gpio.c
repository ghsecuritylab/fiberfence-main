/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "drv_gpio.h"
#include <rtthread.h>

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/*！！！！！！！！！！！！！！！！！！！！！！
	|function     |  pin	|
	！！！！！！！！！！！！！！！！！！！！！！
	|CPU_RUN      |  PD8	|
	|CPU_ALARM    |  PD9	|
	|BEEP			    |  PF6	|
	|GREEN_LED1   |  PI6	|
	|GREEN_LED2   |  PI5	|
	|GREEN_LED3   |  PI4	|
	|GREEN_LED4   |  PE1	|
	|GREEN_LED5   |  PE0	|
	|GREEN_LED6   |  PG15	|
	|GREEN_LED7   |  PG14	|
	|GREEN_LED8   |  PG13	|
	|GREEN_LED9   |  PG12	|
	|GREEN_LED10  |  PG11	|
	|GREEN_LED11  |  PG10	|
	|GREEN_LED12  |  PG9	|
	|GREEN_LED13  |  PD7	|
	|GREEN_LED14  |  PD6	|
	|GREEN_LED15  |  PD5	|
	|GREEN_LED16  |  PD4	|
	|RED_LED1     |  PF5	|
	|RED_LED2     |  PF4	|
	|RED_LED3     |  PF3	|
	|RED_LED4     |  PF2	|
	|RED_LED5     |  PF1	|
	|RED_LED6     |  PF0	|
	|RED_LED7     |  PI11	|
	|RED_LED8     |  PI10	|
	|RED_LED9     |  PI9	|
	|RED_LED10    |  PC13	|
	|RED_LED11    |  PI8	|
	|RED_LED12    |  PE6	|
	|RED_LED13    |  PE5	|
	|RED_LED14    |  PE4	|
	|RED_LED15    |  PE3	|
	|RED_LED16    |  PI7	|
	|S1           |  PD10	|
	|S2           |  PD12	|
	|S3           |  PD14	|
	|S4           |  PG2	|
	|S5           |  PG3	|
	|S6           |  PG4	|
	|S7           |  PG5	|
	|S8           |  PG6	|
	|S9           |  PG7	|
	|S10          |  PG8	|
	|S11          |  PI1	|
	|S12          |  PI2	|
	|S13          |  PI3	|
	|S14          |  PD11	|
	|S15          |  PD13	|
	|S16          |  PD15	|

*/

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
int MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();
	
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	
	GPIO_InitStruct.Pin = RED_LED10_PIN;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = CPU_RUN_LED_PIN|CPU_ALARM_LED_PIN|GREEN_LED13_PIN|GREEN_LED14_PIN|GREEN_LED15_PIN|GREEN_LED16_PIN|SWITCH1_PIN|SWITCH2_PIN|SWITCH3_PIN|SWITCH14_PIN|SWITCH15_PIN|SWITCH16_PIN;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GREEN_LED4_PIN|GREEN_LED5_PIN|RED_LED12_PIN|RED_LED13_PIN|RED_LED14_PIN|RED_LED15_PIN;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = RED_LED1_PIN|RED_LED2_PIN|RED_LED3_PIN|RED_LED4_PIN|RED_LED5_PIN|RED_LED6_PIN;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GREEN_LED6_PIN|GREEN_LED7_PIN|GREEN_LED8_PIN|GREEN_LED9_PIN|GREEN_LED10_PIN|GREEN_LED11_PIN|GREEN_LED12_PIN|SWITCH4_PIN|SWITCH5_PIN|SWITCH6_PIN|SWITCH7_PIN|SWITCH8_PIN|SWITCH9_PIN|SWITCH10_PIN;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GREEN_LED1_PIN|GREEN_LED2_PIN|GREEN_LED3_PIN|RED_LED7_PIN|RED_LED8_PIN|RED_LED9_PIN|RED_LED11_PIN|RED_LED16_PIN|SWITCH11_PIN|SWITCH12_PIN|SWITCH13_PIN;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
	
	/*Configure GPIO pins : pin8 485 enable*/
	GPIO_InitStruct.Pin = GPIO_PIN_8;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);

  /*Configure GPIO pin : PD3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);
	

	return 0;
}
INIT_BOARD_EXPORT(MX_GPIO_Init);


