/**
  ******************************************************************************
  * @file    main.c
  * @author  MMY Application Team
  * @version $Revision: 1633 $
  * @date    $Date: 2016-02-10 16:31:14 +0100 (Wed, 10 Feb 2016) $
  * @brief   This file describe the main program.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under ST MYLIBERTY SOFTWARE LICENSE AGREEMENT (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/myliberty
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied,
  * AND SPECIFICALLY DISCLAIMING THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/** @addtogroup X_NUCLEO_NFC02A1_Applications
  * @{
  */

/** @addtogroup WriteURI_Application
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  char PakageName[80];
}sAARInfo;
sAARInfo sAAR;
/* Private define ------------------------------------------------------------*/
#define LED_Pin GPIO_PIN_5
#define LED_GPIO_Port GPIOA
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t NDEF_BUFFER1[NDEF_MAX_SIZE];
uint8_t Buffer_bin[NDEF_MAX_SIZE];
uint8_t LED2_value;
uint8_t LED_Green_value;
uint8_t LED_Blue_value;
uint8_t LED_Orange_value;

/* Global variables ----------------------------------------------------------*/
sURI_Info URI;
sURI_Info URI1;
/* I2C handler declaration */
I2C_HandleTypeDef hNFC02A1_i2c;

extern sCCFileInfo CCFileStruct;

/* Private function prototypes -----------------------------------------------*/
extern void SystemClock_Config( void );

void Enable_EnergyHarvesting( void );
void Disable_EnergyHarvesting( void );
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @retval None
  */
int main( void )
{
  /* STM32L0xx HAL library initialization:
       - Configure the Flash prefetch, Flash preread and Buffer caches
       - Systick timer is configured by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
       - Low Level Initialization
     */

  /******************************************************************************/
  /* Initialisation of Main STM32 board and X-NUCLEO-NFC02A1 board              */
  /******************************************************************************/
  /* Reset of all peripherals, Initializes the Flash interface and the systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  /* Init of the Nucleo Board led */
  BSP_LED_Init(LED2);
  //init gipo pin as output
  MX_GPIO_Init();

  /******************************************************************************/
  /* Configuration of X-NUCLEO-NFC02A1                                          */
  /******************************************************************************/
  /* Init of the Leds on X-NUCLEO-NFC02A1 board */
  NFC02A1_LED_Init( );
  NFC02A1_LED_ON( GREEN_LED );
  wait_ms( 500 );
  NFC02A1_LED_ON( BLUE_LED );
  wait_ms( 500 );
  NFC02A1_LED_ON( ORANGE_LED );
  wait_ms( 500 );
  NFC02A1_LED_OFF( GREEN_LED );
  wait_ms( 500 );
  NFC02A1_LED_OFF( BLUE_LED );
  wait_ms( 500 );
  NFC02A1_LED_OFF( ORANGE_LED );

  /* Init M24LR driver */
  while( BSP_NFCTAG_Init( ) != NFCTAG_OK );

  /* Enable Energy Harvesting */
  Enable_EnergyHarvesting( );
  //Disable_EnergyHarvesting();
  /* Check if no NDEF detected, init mem in Tag Type 5 */
  if( NfcType5_NDEFDetection( ) != NDEF_OK )
    {
      CCFileStruct.MagicNumber = NFCT5_MAGICNUMBER_E1_CCFILE;
      CCFileStruct.Version = NFCT5_VERSION_V1_0;
      CCFileStruct.MemorySize = ( M24LR_MAX_SIZE / 8 ) & 0xFF;
      CCFileStruct.TT5Tag = 0x05;
      /* Init of the Type Tag 5 component (M24LR) */
      while( NfcType5_TT5Init( ) != NFCTAG_OK );
    }
  /* Set the LED2 on to indicate Init done */
  NFC02A1_LED_ON( BLUE_LED );


  strcpy(sAAR.PakageName, "com.usagitoneko.nekof");

  /* Prepare URI NDEF message content */
  strcpy( URI.protocol,URI_ID_0x01_STRING );
  strcpy( URI.URI_Message,"google.com" );
  strcpy( URI.Information,"\0" );
  /* Write NDEF to EEPROM */
  //while( NDEF_WriteURI( &URI ) != NDEF_OK );

  //NDEF write text file
  char text_file[12] = {"goodbye!!!!"};
  //while(NDEF_WriteText(&text_file)!=NDEF_OK);
  /* Set the LED3 on to indicate Programming done */


  Buffer_bin[1] = 0x11;
  Buffer_bin[2] = 0x51;
  Buffer_bin[3] = 0x62;
  Buffer_bin[4] = 0x29;
  Buffer_bin[5] = 0x51;
  Buffer_bin[6] = 0x62;
  Buffer_bin[7] = 0x29;
  Buffer_bin[8] = 0x51;
  Buffer_bin[9] = 0x62;
  Buffer_bin[10] = 0x62;
  //HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
  while(BSP_NFCTAG_WriteData((Buffer_bin+1), (0), 1)!=NDEF_OK);
  //NDEF_AddAAR(sAAR);
  //HAL_Delay(500);
 //while(NDEF_ReadNDEF(NDEF_BUFFER1) != NDEF_OK );
   //NFC02A1_LED_OFF( BLUE_LED );

  while( 1 )
  {
	 //NDEF_ReadNDEF(NDEF_BUFFER1);
	 BSP_NFCTAG_ReadData(NDEF_BUFFER1, 0, 4);	//read all the data
	 //NFC02A1_LED_Toggle( ORANGE_LED );
	 //take the 1st bit
	 LED2_value = NDEF_BUFFER1[0]&0x01;
	 LED_Green_value = (NDEF_BUFFER1[0] &0x02)>>1;
	 LED_Blue_value = (NDEF_BUFFER1[0] &0x04)>>2;
	 LED_Orange_value = (NDEF_BUFFER1[0] &0x08)>>3;
	 if(LED2_value ==1){
		 HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	 }
	 else {
		 HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
	 }
	 if(LED_Green_value==1){
		 NFC02A1_LED_ON( GREEN_LED );
	 }
	 else{
		 NFC02A1_LED_OFF( GREEN_LED );
	 }
	 if(LED_Blue_value==1){
		 NFC02A1_LED_ON( BLUE_LED );
	 }
	 else{
		 NFC02A1_LED_OFF( BLUE_LED );
	 }
	 if(LED_Orange_value==1){
		 NFC02A1_LED_ON( ORANGE_LED );
	 }
	 else{
		 NFC02A1_LED_OFF( ORANGE_LED );
	 }
	 HAL_Delay(500);

  }
}
//

/******************************************************************************/
/* PRIVATE FUNCTION                                                           */
/******************************************************************************/

/**
  * @brief  This function activate Energy Harvesting mode
  */
void Enable_EnergyHarvesting( void )
{
  /* Initialise M24LR Board */
  if( BSP_NFCTAG_GetExtended_Drv() != NULL )
  {
    /* Enable Energy Harvesting */
    BSP_NFCTAG_GetExtended_Drv()->SetEH( );

    /* Store configuration in non Volatile Memory */
    BSP_NFCTAG_GetExtended_Drv()->Enable_EH_mode();
    BSP_NFCTAG_GetExtended_Drv()->WriteEH_Cfg( M24LR_EH_Cfg_6MA );
  }
}

void Disable_EnergyHarvesting( void )
{
  /* Initialise M24LR Board */
  if( BSP_NFCTAG_GetExtended_Drv() != NULL )
  {
    /* Enable Energy Harvesting */
    //BSP_NFCTAG_GetExtended_Drv()->SetEH( );
    BSP_NFCTAG_GetExtended_Drv()->ResetEH( );
    /* Store configuration in non Volatile Memory */
    BSP_NFCTAG_GetExtended_Drv()->Enable_EH_mode();
    //BSP_NFCTAG_GetExtended_Drv()->Disable_EH_mode();
    BSP_NFCTAG_GetExtended_Drv()->WriteEH_Cfg( M24LR_EH_Cfg_6MA );
  }
}

 void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  */
void assert_failed( uint8_t* file, uint32_t line )
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while( 1 )
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
