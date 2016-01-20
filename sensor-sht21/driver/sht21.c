/* SHT21 Driver for ESP8266
 *
 *  Created on: Jan 20, 2016
 *      Author: piiiters
 */

#include <user_interface.h>
#include "driver/sht21.h"
#include "osapi.h"

/* Function sht21_reset
 *
 * */
bool ICACHE_FLASH_ATTR sht21_reset(void) {

	i2c_master_start();
	i2c_master_writeByte(SHT21_ADDR);

	os_delay_us(20000);

	if(i2c_master_checkAck()){

		i2c_master_writeByte(SHT21_RESET);

		os_delay_us(20000);

		if(i2c_master_checkAck()){
			i2c_master_stop();
			return TRUE;
		}
	} else {
		i2c_master_stop();
		return FALSE;
	}
	return FALSE;
}

/* Function sht21_init
 *
 * */
bool ICACHE_FLASH_ATTR sht21_init(void) {
	i2c_master_gpio_init();
	return sht21_reset();
}

/* Function sht21_read_raw_value
 *
 * */
uint16_t ICACHE_FLASH_ATTR sht21_read_raw_value(uint8_t dataType) {

    switch(dataType){
        case SHT21_TEMPERATURE:
            break;
        case SHT21_HUMIDITY:
            break;
    }
return 0;
}

/* Function sht21_get_temp
 *
 * */
uint16_t ICACHE_FLASH_ATTR sht21_get_value(void) {
    return 0;
}

