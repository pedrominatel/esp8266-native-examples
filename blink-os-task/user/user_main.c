/*
The MIT License (MIT)

Copyright (c) 2015 Pedro Minatel

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "osapi.h"
#include "os_type.h"
#include <user_interface.h>
#include "driver/uart.h"
#include "user_config.h"
#include "gpio.h"

#define user_procTaskPrio        0
#define user_procTaskQueueLen    1

os_event_t    user_procTaskQueue[user_procTaskQueueLen];
uint8_t ledState = 0;

#define GPIO                    BIT5

static void ost_loop(os_event_t *events);

static void ICACHE_FLASH_ATTR ost_loop(os_event_t *events){
	GPIO_OUTPUT_SET(5,ledState);
	ledState = ~ledState;
	os_delay_us(1000000);
    system_os_post(user_procTaskPrio, 0, 0 );
}

void ICACHE_FLASH_ATTR user_init(void) {

#ifdef DEBUG_SERIAL
	uart_init(BIT_RATE_115200,BIT_RATE_115200);
	system_set_os_print(TRUE);
#else
	system_set_os_print(FALSE);
#endif

	//Inicialização do modulo de GPIO
	gpio_init();
	//Configura o modo da GPIO
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5);
	//Configura a GPIO para OUTPUT e define para LOW LEVEL
	GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);

	//Create task for main loop
    system_os_task(ost_loop, user_procTaskPrio,user_procTaskQueue, user_procTaskQueueLen);
    system_os_post(user_procTaskPrio, 0, 0 );
}
