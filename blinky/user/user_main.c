#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_config.h"

#define user_procTaskPrio		0
#define user_procTaskQueueLen	1

//GPIO a ser utilizada
#define GPIO					BIT5

os_event_t    user_procTaskQueue[user_procTaskQueueLen];
static void user_procTask(os_event_t *events);

//Definição do TIMER a ser utilizado
static volatile os_timer_t some_timer;

/* Função de blink
 * */
void some_timerfunc(void *arg)
{
    if (GPIO_REG_READ(GPIO_OUT_ADDRESS) & GPIO)
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
    //Configura o modo da GPIO
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5);
    //Configura a GPIO para OUTPUT e define para LOW LEVEL
    GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);

    //Desabilita o timer para a confuguração
    os_timer_disarm(&some_timer);
    //Configura o TIMER
    os_timer_setfn(&some_timer, (os_timer_func_t *)some_timerfunc, NULL);
    //Arma o timer
    os_timer_arm(&some_timer, 1000, 1);
    
    //Inicia a uma tarefa no sistema
    //system_os_task(user_procTask, user_procTaskPrio,user_procTaskQueue, user_procTaskQueueLen);
}
