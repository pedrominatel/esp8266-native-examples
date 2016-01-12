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

#include "wifi_manager.h"

struct station_config stationConf;
struct bss_info *bss;

/*Function wifiInit
 *
 * */
void ICACHE_FLASH_ATTR wifi_inti(void) {
	//TODO wifi intialization
}

void ICACHE_FLASH_ATTR wifiScan_cb(void *arg, STATUS status) {
    switch (status ) {
    case OK:
      os_printf("Status OK\n");
      bss = arg;
      bss = STAILQ_NEXT(bss, next);    // ignor first

      while (bss != NULL) {
          os_printf("ssid: %s\n", bss->ssid);
          bss = STAILQ_NEXT(bss, next);
      }

      break;
   case FAIL:
       os_printf("Status FAIL\n");
         break;
   case PENDING:
       os_printf("Status PENDING\n");
         break;
   case BUSY:
       os_printf("Status BUSY\n");
         break;
   case CANCEL:
       os_printf("Status CANCEL\n");
         break;
   default:
       os_printf("Status UNKNOWN\n");
         break;
    }
}

/*Function wifi_setup
 *
 * */
void ICACHE_FLASH_ATTR wifi_setup(char* ssid, char* password, uint8_t mode) {

	struct station_config stationConf;
	wifi_set_opmode(mode);
	os_memcpy(&stationConf.ssid, ssid, 32);
	os_memcpy(&stationConf.password, password, 64);
	wifi_station_set_config(&stationConf);
}
