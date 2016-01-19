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
#include "gpio.h"
#include "os_type.h"
#include "user_config.h"
 
#define user_procTaskPrio        0
#define user_procTaskQueueLen    1
 
//GPIO a ser utilizada
#define GPIO                    BIT5
 
os_event_t    user_procTaskQueue[user_procTaskQueueLen];
static void user_procTask(os_event_t *events);
 
//Definição do TIMER a ser utilizado
static volatile os_timer_t some_timer;
 
/* Função de blink
* */
void some_timerfunc(void *arg)
{
if (GPIO_REG_READ(GPIO_OUT_ADDRESS) &amp; GPIO)
{
//GPIO LOW
GPIO_OUTPUT_SET(5,0);
}
else
{
//GPIO HIGH
GPIO_OUTPUT_SET(5,1);
}
}
 
//Do nothing function
static void ICACHE_FLASH_ATTR
user_procTask(os_event_t *events)
{
os_delay_us(10);
}
 
//Init function
void ICACHE_FLASH_ATTR
user_init()
{
//Inicialização do modulo de GPIO
gpio_init();
//Configura o modo da GPIO
PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5);
//Configura a GPIO para OUTPUT e define para LOW LEVEL
GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);
 
//Desabilita o timer para a confuguração
os_timer_disarm(&amp;some_timer);
//Configura o TIMER
os_timer_setfn(&amp;some_timer, (os_timer_func_t *)some_timerfunc, NULL);
//Arma o timer
os_timer_arm(&amp;some_timer, 1000, 1);
 
//Inicia a uma tarefa no sistema
system_os_task(user_procTask, user_procTaskPrio,user_procTaskQueue, user_procTaskQueueLen);
}
