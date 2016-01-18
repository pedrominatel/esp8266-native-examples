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
#include "wifi_manager.h"

#define user_procTaskPrio        0
#define user_procTaskQueueLen    1

static char ssid[32] = "IOT";
static char pass[64] = "iotnetwork";

os_event_t    user_procTaskQueue[user_procTaskQueueLen];

static void ost_loop(os_event_t *events);
static void ost_wifi_setup(os_event_t *events);
static void ost_wifi_scan(os_event_t *events);

struct scan_config scan;

static void ICACHE_FLASH_ATTR ost_wifi_setup(os_event_t *events){
	os_printf("WiFi Setup...\n");
	uint8_t stationStatus = wifi_station_get_connect_status();
	//Handle status
	wifi_station_set_auto_connect(TRUE);
	wifi_setup(&ssid,&pass, STATION_MODE);
}

static void ICACHE_FLASH_ATTR ost_wifi_scan(os_event_t *events){
	os_printf("WiFi Scan...\n");
	os_delay_us(10000);
	wifi_promiscuous_enable(0);
	wifi_station_scan(NULL, wifiScan_cb);
}


static void ICACHE_FLASH_ATTR ost_loop(os_event_t *events){
	os_delay_us(10000);
    system_os_post(user_procTaskPrio, 0, 0 );
}

void ICACHE_FLASH_ATTR user_init(void) {

#ifdef DEBUG_SERIAL
	uart_init(BIT_RATE_115200,BIT_RATE_115200);
	system_set_os_print(TRUE);
#else
	system_set_os_print(FALSE);
#endif

	//Create task for main loop
    system_os_task(ost_loop, user_procTaskPrio,user_procTaskQueue, user_procTaskQueueLen);
    system_os_post(user_procTaskPrio, 0, 0 );
    //Create task for the WiFi setup
    system_os_task(ost_wifi_setup, 1,user_procTaskQueue, user_procTaskQueueLen);
    system_os_post(1, 0, 0 );
    //Create task for the WiFi networks scan
    system_os_task(ost_wifi_scan, 2,user_procTaskQueue, user_procTaskQueueLen);
    system_os_post(2, 0, 0 );

}
