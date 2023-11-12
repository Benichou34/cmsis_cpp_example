#include "cmsis_os2.h"
#include "stm32f4xx_hal.h"

/* Use RTOS tick as HAL tick. Scheduler need to be started. */

/**
 * @brief  This function configures the timer as a time base source.
 *         The time source is configured  to have 1ms time base with a dedicated
 *         Tick interrupt priority.
 * @note   This function is called  automatically at the beginning of program after
 *         reset by HAL_Init() or at any time when clock is configured, by HAL_RCC_ClockConfig().
 * @param  TickPriority: Tick interrupt priority.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_InitTick(uint32_t /*TickPriority*/)
{
	/* Check that HAL and OS have the same configured tick frequency */
	/* HAL require 1ms tick period */
	if (osKernelGetTickFreq() != 1000)
		return HAL_ERROR;

	return HAL_OK;
}

/**
 * @brief Provides a tick value in millisecond.
 * @note This function is declared as __weak to be overwritten in case of other
 *       implementations in user file.
 * @retval tick value
 */
uint32_t HAL_GetTick(void)
{
	return osKernelGetTickCount();
}

/**
 * @brief This function provides minimum delay (in milliseconds) based
 *        on variable incremented.
 * @note In the default implementation , SysTick timer is the source of time base.
 *       It is used to generate interrupts at regular time intervals where uwTick
 *       is incremented.
 * @note This function is declared as __weak to be overwritten in case of other
 *       implementations in user file.
 * @param Delay specifies the delay time length, in milliseconds.
 * @retval None
 */
void HAL_Delay(uint32_t Delay)
{
	osDelay(Delay);
}
