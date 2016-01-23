/* SHT21 Driver for ESP8266
 *
 *  Created on: Jan 20, 2016
 *      Author: piiiters
 */

#include <user_interface.h>
#include "driver/sht21.h"
#include "osapi.h"

/* Function sht21_writeCommand
 *
 * */
bool ICACHE_FLASH_ATTR sht21_writeCommand(uint8_t addr,  uint8_t cmd) {

	i2c_start();
	i2c_writeByte(addr);

	if(i2c_check_ack()){
		i2c_writeByte(cmd);
		if(i2c_check_ack()){
			i2c_stop();
			return TRUE;
		}
	} else {
		i2c_stop();
		return FALSE;
	}
	return FALSE;
}

/* Function sht21_readCommand
 * TODO: Finish it!
 * */
uint32_t ICACHE_FLASH_ATTR sht21_readCommand(uint8_t addr) {
	while (!i2c_check_ack()) {
		i2c_start();
		i2c_writeByte(addr);
		if (!i2c_check_ack)
			i2c_stop();
	}
	return 0;
}

/* Function sht21_reset
 *
 * */
bool ICACHE_FLASH_ATTR sht21_reset(void) {
	return sht21_writeCommand(SHT21_ADDR_W, SHT21_RESET);
}

/* Function sht21_init
 *
 * */
bool ICACHE_FLASH_ATTR sht21_init(void) {
	i2c_init();
	return sht21_reset();
}

/* Function sht21_read_raw_value
 *
 * */
uint16_t ICACHE_FLASH_ATTR sht21_read_raw(uint8_t reg) {

	if(!sht21_writeCommand(SHT21_ADDR_W, reg))
		return 999;

	os_delay_us(20);

	sht21_readCommand(SHT21_ADDR_R);

	uint8_t msb = i2c_readByte();
	i2c_send_ack(1);
	uint8_t lsb = i2c_readByte();

	i2c_send_ack(0);
	i2c_stop();

	uint16_t rawH = msb << 8 | lsb;
	rawH = rawH & 0xFFFC;

	return rawH;
}

/* Function sht21_read_raw_value
 *
 * */
uint16_t ICACHE_FLASH_ATTR sht21_read_raw_value(uint8_t dataType) {

	uint16_t raw_data = 0;

    switch(dataType){
        case SHT21_TEMPERATURE:
        	raw_data = sht21_read_raw(SHT21_T_REG_NHOLD);
            break;
        case SHT21_HUMIDITY:
        	raw_data = sht21_read_raw(SHT21_H_REG_NHOLD);
            break;
    }
return raw_data;
}

/* Function sht21_get_temperature
 *
 * */
int16_t ICACHE_FLASH_ATTR sht21_get_temperature(void) {

	float tValue = sht21_read_raw_value(SHT21_TEMPERATURE);

	tValue *= 175.72;
	tValue /= 0xFFFF;
	tValue -= 46.85;

	return (int16_t) (tValue * 10);
}

/* Function sht21_get_humidity
 *
 * */
int16_t ICACHE_FLASH_ATTR sht21_get_humdity(void) {

	float hValue = sht21_read_raw_value(SHT21_HUMIDITY);

	hValue *= 125.0;
	hValue /= 0xFFFF;
	hValue -= 6.0;

    return (int16_t) (hValue * 10);
}

