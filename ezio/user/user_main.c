#include "ets_sys.h"
#include "osapi.h"
#include "driver/ezio.h"
#include "os_type.h"
#include "user_config.h"

#define user_procTaskPrio        0
#define user_procTaskQueueLen    1

os_event_t    user_procTaskQueue[user_procTaskQueueLen];
static void t_read_pushbtn(os_event_t *events);

uint8_t blk_state = 0;

static volatile os_timer_t some_timer;

void ICACHE_FLASH_ATTR some_timerfunc(void *arg)
{
    ezio_write(GPIO4, blk_state);
    blk_state = ~blk_state;
}

//Função NOP (NO OPERATION)
static void ICACHE_FLASH_ATTR t_read_pushbtn(os_event_t *events)
{

    if(!ezio_read(GPIO12)){
    	ezio_write(GPIO5, HIGH);
    } else {
    	ezio_write(GPIO5, LOW);
    }

	os_delay_us(100);
	system_os_post(user_procTaskPrio, 0, 0 );
}

//Init function
void ICACHE_FLASH_ATTR user_init()
{
    //GPIO driver initialization
    ezio_init();
    ezio_set(GPIO4, OUTPUT);
    ezio_set(GPIO5, OUTPUT);
    ezio_set(GPIO12, INPUT);

    //Disarm timer
    os_timer_disarm(&some_timer);

    //Setup timer
    os_timer_setfn(&some_timer, (os_timer_func_t *)some_timerfunc, NULL);

    //Arm the timer
    //&some_timer is the pointer
    //1000 is the fire time in ms
    //0 for once and 1 for repeating
    os_timer_arm(&some_timer, 1000, 1);

    //Start os task
    system_os_task(t_read_pushbtn, user_procTaskPrio,user_procTaskQueue, user_procTaskQueueLen);
    system_os_post(user_procTaskPrio, 0, 0 );
}
