/**
  ******************************************************************************
  * @file    common.h 
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
#ifndef __COMMON_H
#define __COMMON_H

/* Includes ------------------------------------------------------------------*/
#include "x_nucleo_nfc02a1_nfctag.h"
#include <string.h>

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#ifndef MIN
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif

/* Exported constants --------------------------------------------------------*/
#define MAX_NDEF_MEM                 0x200
#define M24LR_MAX_SIZE               NFCTAG_4M_SIZE
#define M24LR_NDEF_MAX_SIZE          MIN(M24LR_MAX_SIZE,MAX_NDEF_MEM)
#define NFC_DEVICE_MAX_NDEFMEMORY    M24LR_NDEF_MAX_SIZE

#define RESULTOK                     0x00
#define ERRORCODE_GENERIC            1
#define ACTION_COMPLETED             0x9000

/* Exported functions ------------------------------------------------------- */


#endif /* __COMMON_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
