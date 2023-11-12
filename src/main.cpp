#include "OS.h"
#include "Thread.h"
#include "stm32f4xx_hal.h"

#define LED_PIN       GPIO_PIN_7
#define LED_GPIO_PORT GPIOB

namespace
{
	using namespace std::chrono_literals;

	void LED_Init()
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.Pin = LED_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	}
} // namespace

int main()
{
	sys::kernel::initialize();

	HAL_Init();
	LED_Init();

	std::thread led_thread(
		[&]
		{
			while (true)
			{
				HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
				std::this_thread::sleep_for(1s);
			}
		});

	// Start scheduler
	sys::kernel::start();
}
