/**
  ******************************************************************************
  * @file    main.h 
  * @author  MMY Application Team
  * @version $Revision: 1436 $
  * @date    $Date: 2015-11-26 17:26:33 +0100 (Thu, 26 Nov 2015) $
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MMY-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"
#include "tagtype5_wrapper.h"
#include "lib_NDEF_URI.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#define PushButton_Pin GPIO_PIN_13
#define PushButton_GPIO_Port GPIOC
#ifndef __MBED__
	#define wait_ms( time ) HAL_Delay(time)
#endif


/********************  Bit definition for NFC communication register  ********************/
#define ANDROID_PRESENT_POS	(0U)
#define ANDROID_PRESENT_MSK	(1U << ANDROID_PRESENT_POS)
#define ANDROID_PRESENT		ANDROID_PRESENT_MSK

#define ANDROID_WRCPLT_POS	(1U)
#define ANDROID_WRCPLT_MSK	(1U << ANDROID_WRCPLT_POS)
#define ANDROID_WRCPLT		ANDROID_WRCPLT_MSK

/********************  Byte Location for data storage  ********************/
#define SSID_8_BUFFER_POS	1
#define PW_8_BUFFER_POS		9
/* External variables --------------------------------------------------------*/
extern NFCTAG_ExtDrvTypeDef *Nfctag_ExtDrv;

/* Exported functions ------------------------------------------------------- */


#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
