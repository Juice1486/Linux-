/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "string.h"

char myBuffer[] = "I have gotten your message: "; //用户提示信息
char Enter[] = "\r\n"; //回车换行
char getBuffer[100]; //用户自定义的缓冲区
char value;
char str1[] = "gostm32";
char str2[] = "stopstm32";
char c;//指令 0:停止  1:开始
char message[]="hello Windows\n";//输出信息
char tips[]="CommandError\n";//提示1
char tips1[]="Start.....\n";//提示2
char tips2[]="Stop......\n";//提示3
int flag=0;//标志 0:停止发送 1.开始发送
int countofGetBuffer=0;
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**ep
  * @brief  The application entry point.
  * @retval int
  */
  #define COUNTOF(a) (sizeof(a)/sizeof(*(a)))
	  //jkl
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  
  HAL_UART_Receive_IT(&huart1, (uint8_t *)&value, 1);
  //HAL_UART_Receive_IT(&huart1, (uint8_t *)&c, 10);


  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if(flag==1){
			//发送信息
			HAL_UART_Transmit(&huart1, (uint8_t *)&message,COUNTOF(message),0xFFFF); 
			//延时
			HAL_Delay(1000);
		}else if(flag==0){
			HAL_Delay(1000);
		}
  }
}
 
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart1){
	HAL_UART_IRQHandler(huart1);
	getBuffer[countofGetBuffer++]=value;
	if(strcmp(getBuffer,str1)==0){
		flag = 1;
		HAL_UART_Transmit(huart1, (uint8_t *)&tips1, COUNTOF(tips1),0xFFFF);
		countofGetBuffer = 0;
		memset(getBuffer,0,COUNTOF(getBuffer));
	}else if(strcmp(getBuffer,str2)==0){
	    flag = 0;
		HAL_UART_Transmit(huart1, (uint8_t *)&tips2, COUNTOF(tips2),0xFFFF); 
		countofGetBuffer = 0;
		memset(getBuffer,0,COUNTOF(getBuffer));
	}
	HAL_UART_Receive_IT(huart1, (uint8_t *)&value,1);
}

void USART1_IRQHandler(void)
{
	 HAL_UART_IRQHandler(&huart1); //该函数会清空中断标志，取消中断使能，并间接调用回调函数
     HAL_UART_Receive_IT(&huart1, (uint8_t *)getBuffer,10);  //添加的一行代码
}
/*void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	
	 //当输入的指令为0时,发送提示并改变flag
	if(c=='s'){
		flag=0;
		HAL_UART_Transmit(&huart1, (uint8_t *)&tips2, COUNTOF(tips2),0xFFFF); 
	}
	//当输入的指令为1时,发送提示并改变flag
	else if(c=='t'){
		flag=1;
		HAL_UART_Transmit(&huart1, (uint8_t *)&tips1, COUNTOF(tips1),0xFFFF); 
	}
	
	//当输入不存在指令时,发送提示并改变flag
	else {
		//flag=1;
		//HAL_UART_Transmit(&huart1, (uint8_t *)&tips, COUNTOF(tips),0xFFFF); 
	}

	//重新设置中断
		HAL_UART_Receive_IT(&huart1, (uint8_t *)&c, 1);  
}*/


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void){
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
