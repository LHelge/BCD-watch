/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define WAKEUP_Pin GPIO_PIN_13
#define WAKEUP_GPIO_Port GPIOC
#define LED_M_02_Pin GPIO_PIN_0
#define LED_M_02_GPIO_Port GPIOH
#define LED_M_03_Pin GPIO_PIN_1
#define LED_M_03_GPIO_Port GPIOH
#define LED_M_12_Pin GPIO_PIN_0
#define LED_M_12_GPIO_Port GPIOA
#define LED_M_13_Pin GPIO_PIN_1
#define LED_M_13_GPIO_Port GPIOA
#define LED_S_0_DIM_Pin GPIO_PIN_2
#define LED_S_0_DIM_GPIO_Port GPIOA
#define LED_S_1_DIM_Pin GPIO_PIN_3
#define LED_S_1_DIM_GPIO_Port GPIOA
#define LED_S_13_Pin GPIO_PIN_4
#define LED_S_13_GPIO_Port GPIOA
#define LED_S_03_Pin GPIO_PIN_5
#define LED_S_03_GPIO_Port GPIOA
#define LED_S_12_Pin GPIO_PIN_6
#define LED_S_12_GPIO_Port GPIOA
#define LED_S_02_Pin GPIO_PIN_7
#define LED_S_02_GPIO_Port GPIOA
#define LED_S_11_Pin GPIO_PIN_0
#define LED_S_11_GPIO_Port GPIOB
#define LED_S_01_Pin GPIO_PIN_1
#define LED_S_01_GPIO_Port GPIOB
#define LED_S_10_Pin GPIO_PIN_2
#define LED_S_10_GPIO_Port GPIOB
#define LED_S_00_Pin GPIO_PIN_10
#define LED_S_00_GPIO_Port GPIOB
#define LED_M_11_Pin GPIO_PIN_11
#define LED_M_11_GPIO_Port GPIOB
#define LED_M_10_Pin GPIO_PIN_12
#define LED_M_10_GPIO_Port GPIOB
#define LED_M_0_DIM_Pin GPIO_PIN_13
#define LED_M_0_DIM_GPIO_Port GPIOB
#define LED_M_1_DIM_Pin GPIO_PIN_14
#define LED_M_1_DIM_GPIO_Port GPIOB
#define LED_M_01_Pin GPIO_PIN_15
#define LED_M_01_GPIO_Port GPIOB
#define LED_M_00_Pin GPIO_PIN_8
#define LED_M_00_GPIO_Port GPIOA
#define ACC_SCL_Pin GPIO_PIN_9
#define ACC_SCL_GPIO_Port GPIOA
#define ACC_SDA_Pin GPIO_PIN_10
#define ACC_SDA_GPIO_Port GPIOA
#define LED_H_01_Pin GPIO_PIN_11
#define LED_H_01_GPIO_Port GPIOA
#define LED_H_00_Pin GPIO_PIN_12
#define LED_H_00_GPIO_Port GPIOA
#define LED_H_0_DIM_Pin GPIO_PIN_15
#define LED_H_0_DIM_GPIO_Port GPIOA
#define LED_H_1_DIM_Pin GPIO_PIN_3
#define LED_H_1_DIM_GPIO_Port GPIOB
#define LED_H_10_Pin GPIO_PIN_4
#define LED_H_10_GPIO_Port GPIOB
#define LED_H_11_Pin GPIO_PIN_5
#define LED_H_11_GPIO_Port GPIOB
#define DBG_TX_Pin GPIO_PIN_6
#define DBG_TX_GPIO_Port GPIOB
#define DBG_RX_Pin GPIO_PIN_7
#define DBG_RX_GPIO_Port GPIOB
#define LED_H_02_Pin GPIO_PIN_8
#define LED_H_02_GPIO_Port GPIOB
#define LED_H_03_Pin GPIO_PIN_9
#define LED_H_03_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
