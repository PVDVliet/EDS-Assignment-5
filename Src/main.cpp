#include "main.h"

#include <stdio.h>
#include <stm32f051x8.h>

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
extern "C" void initialise_monitor_handles(void);

uint32_t i = 0;

extern "C" void EXTI0_1_IRQHandler()
{
	EXTI->PR |= EXTI_PR_PR0;

	GPIOA->ODR ^= GPIO_ODR_10;
}

extern "C" void TIM3_IRQHandler()
{
	TIM3->SR &= ~TIM_SR_TIF;
	TIM3->SR &= ~TIM_SR_CC1IF;

	i++;
}

int main(void)
{
	initialise_monitor_handles();

	//HAL_Init();

	//SystemClock_Config();
	MX_GPIO_Init();

	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODER10) | (0b01 << GPIO_MODER_MODER10_Pos);
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_10;

	GPIOC->MODER &= ~GPIO_MODER_MODER0;
	GPIOC->PUPDR = (GPIOC->PUPDR & ~GPIO_PUPDR_PUPDR0) | (0b01 << GPIO_PUPDR_PUPDR0_Pos);

	SYSCFG->EXTICR[0] = (SYSCFG->EXTICR[0] & ~SYSCFG_EXTICR1_EXTI0) | (0b0010 << SYSCFG_EXTICR1_EXTI0_Pos);

	EXTI->FTSR |= EXTI_FTSR_TR0;
	EXTI->IMR |= EXTI_IMR_MR0;

	NVIC_EnableIRQ(EXTI0_1_IRQn);

	// timer setup using TIM3 channel 1
	TIM3->CCR1 = 1000; // set compare value to 1
	TIM3->ARR = 1; // set auto reload value to 0
	TIM3->PSC = 4799; // set counter clock frequency to 1000 hertz (T = 1ms)

	TIM3->DIER |= TIM_DIER_CC1IE; // enable interrupt
	TIM3->CCMR1 |= (0b001 << TIM_CCMR1_OC1M_Pos); // set output mode to set active level

	//TIM3->CNT = 0; // reset timer counter
	TIM3->CR1 |= TIM_CR1_CEN; // enable timer

	NVIC_EnableIRQ(TIM3_IRQn);

	//TIM3->EGR |= TIM_EGR_CC1G;

	while (1)
	{
		if (i > 1000)
		{
			i = 0;
			GPIOA->ODR ^= GPIO_ODR_10;
		}

		printf("CNT: %lu\n", TIM3->CNT);
		printf("SR: %lx\n", TIM3->SR);
		printf("i: %lu\n", i);
	}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Initializes the CPU, AHB and APB busses clocks 
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
	RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
	Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks 
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
								|RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
	{
	Error_Handler();
	}
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, LD4_Pin|LD3_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : B1_Pin */
	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : LD4_Pin LD3_Pin */
	GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
