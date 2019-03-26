/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "sys.h"

#define ON  0
#define OFF 1

#define CPU_RUN_LED_PIN    GPIO_PIN_8
#define CPU_ALARM_LED_PIN  GPIO_PIN_9
#define BEEP_PIN       GPIO_PIN_6

#define CPU_RUN_LED   PDout(8)
#define CPU_ALARM_LED PDout(9)
#define BEEP          PFout(6)

#define GREEN_LED1_PIN   GPIO_PIN_6
#define GREEN_LED2_PIN   GPIO_PIN_5
#define GREEN_LED3_PIN   GPIO_PIN_4
#define GREEN_LED4_PIN   GPIO_PIN_1
#define GREEN_LED5_PIN   GPIO_PIN_0
#define GREEN_LED6_PIN   GPIO_PIN_15
#define GREEN_LED7_PIN   GPIO_PIN_14
#define GREEN_LED8_PIN   GPIO_PIN_13
#define GREEN_LED9_PIN   GPIO_PIN_12
#define GREEN_LED10_PIN  GPIO_PIN_11
#define GREEN_LED11_PIN  GPIO_PIN_10
#define GREEN_LED12_PIN  GPIO_PIN_9
#define GREEN_LED13_PIN  GPIO_PIN_7
#define GREEN_LED14_PIN  GPIO_PIN_6
#define GREEN_LED15_PIN  GPIO_PIN_5
#define GREEN_LED16_PIN  GPIO_PIN_4

#define GREEN_LED1  PIout(6)
#define GREEN_LED2  PIout(5)
#define GREEN_LED3  PIout(4)
#define GREEN_LED4  PEout(1)
#define GREEN_LED5  PEout(0)
#define GREEN_LED6  PGout(15)
#define GREEN_LED7  PGout(14)
#define GREEN_LED8  PGout(13)
#define GREEN_LED9  PGout(12)
#define GREEN_LED10 PGout(11)
#define GREEN_LED11 PGout(10)
#define GREEN_LED12 PGout(9)
#define GREEN_LED13 PDout(7)
#define GREEN_LED14 PDout(6)
#define GREEN_LED15 PDout(5)
#define GREEN_LED16 PDout(4)

#define RED_LED1_PIN   GPIO_PIN_5
#define RED_LED2_PIN   GPIO_PIN_4
#define RED_LED3_PIN   GPIO_PIN_3
#define RED_LED4_PIN   GPIO_PIN_2
#define RED_LED5_PIN   GPIO_PIN_1
#define RED_LED6_PIN   GPIO_PIN_0
#define RED_LED7_PIN   GPIO_PIN_11
#define RED_LED8_PIN   GPIO_PIN_10
#define RED_LED9_PIN   GPIO_PIN_9
#define RED_LED10_PIN  GPIO_PIN_13
#define RED_LED11_PIN  GPIO_PIN_8
#define RED_LED12_PIN  GPIO_PIN_6
#define RED_LED13_PIN  GPIO_PIN_5
#define RED_LED14_PIN  GPIO_PIN_4
#define RED_LED15_PIN  GPIO_PIN_3
#define RED_LED16_PIN  GPIO_PIN_7

#define RED_LED1  PFout(5)
#define RED_LED2  PFout(4)
#define RED_LED3  PFout(3)
#define RED_LED4  PFout(2)
#define RED_LED5  PFout(1)
#define RED_LED6  PFout(0)
#define RED_LED7  PIout(11)
#define RED_LED8  PIout(10)
#define RED_LED9  PIout(9)
#define RED_LED10 PCout(13)
#define RED_LED11 PIout(8)
#define RED_LED12 PEout(6)
#define RED_LED13 PEout(5)
#define RED_LED14 PEout(4)
#define RED_LED15 PEout(3)
#define RED_LED16 PIout(7)

#define SWITCH1_PIN   GPIO_PIN_10
#define SWITCH2_PIN   GPIO_PIN_12
#define SWITCH3_PIN   GPIO_PIN_14
#define SWITCH4_PIN   GPIO_PIN_2
#define SWITCH5_PIN   GPIO_PIN_3
#define SWITCH6_PIN   GPIO_PIN_4
#define SWITCH7_PIN   GPIO_PIN_5
#define SWITCH8_PIN   GPIO_PIN_6
#define SWITCH9_PIN   GPIO_PIN_7
#define SWITCH10_PIN  GPIO_PIN_8
#define SWITCH11_PIN  GPIO_PIN_1
#define SWITCH12_PIN  GPIO_PIN_2
#define SWITCH13_PIN  GPIO_PIN_3
#define SWITCH14_PIN  GPIO_PIN_11
#define SWITCH15_PIN  GPIO_PIN_13
#define SWITCH16_PIN  GPIO_PIN_15

#define SWITCH1  PDout(10)
#define SWITCH2  PDout(12)
#define SWITCH3  PDout(14)
#define SWITCH4  PGout(2)
#define SWITCH5  PGout(3)
#define SWITCH6  PGout(4)
#define SWITCH7  PGout(5)
#define SWITCH8  PGout(6)
#define SWITCH9  PGout(7)
#define SWITCH10 PGout(8)
#define SWITCH11 PIout(1)
#define SWITCH12 PIout(2)
#define SWITCH13 PIout(3)
#define SWITCH14 PDout(11)
#define SWITCH15 PDout(13)
#define SWITCH16 PDout(15)

/* USER CODE END Private defines */

int MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */


