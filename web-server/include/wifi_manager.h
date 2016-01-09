/*
 * wifi_manager.h
 *
 *  Created on: Jan 9, 2016
 *      Author: piiiters
 */

#ifndef INCLUDE_WIFI_MANAGER_H_
#define INCLUDE_WIFI_MANAGER_H_

#include "osapi.h"
#include "os_type.h"
#include <user_interface.h>

void ICACHE_FLASH_ATTR wifi_inti(void);
void ICACHE_FLASH_ATTR wifi_setup(char* ssid, char* password, uint8_t mode);

#endif /* INCLUDE_WIFI_MANAGER_H_ */
