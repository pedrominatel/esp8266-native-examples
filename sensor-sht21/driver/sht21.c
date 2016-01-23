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
int16_t ICACHE_FLASH_ATTR sht21_read_raw_t(void) {

	if(!sht21_writeCommand(SHT21_ADDR_W, SHT21_T_REG_NHOLD))
		return 999;

	os_delay_us(20);

	uint8_t ack = 0;

	while (!ack) {
		i2c_start();
		i2c_writeByte(SHT21_ADDR_R);
		ack = i2c_check_ack();
		if (!ack)
			i2c_stop();
	}

	uint8_t msb = i2c_readByte();
	i2c_send_ack(1);
	uint8_t lsb = i2c_readByte();
	i2c_send_ack(0);
	i2c_stop();


	uint16_t _rv = msb << 8;
	_rv += lsb;
	_rv &= ~0x0003;

	float rv = _rv;

	rv *= 175.72;
	rv /= 65536;
	rv -= 46.85;

	return (int16_t) (rv * 10);
}

/* Function sht21_read_raw_value
 *
 * */
int16_t ICACHE_FLASH_ATTR sht21_read_raw_h(void) {

	if(!sht21_writeCommand(SHT21_ADDR_W, SHT21_H_REG_NHOLD))
		return 999;

	os_delay_us(20);

	uint8_t ack = 0;
	while (!ack) {
		i2c_start();
		i2c_writeByte(SHT21_ADDR_R);
		ack = i2c_check_ack();
		if (!ack)
			i2c_stop();
	}

	uint8_t msb = i2c_readByte();
	i2c_send_ack(1);
	uint8_t lsb = i2c_readByte();
	i2c_send_ack(0);
	i2c_stop();


	uint16_t _rv = msb << 8;
	_rv += lsb;
	_rv &= ~0x0003;

	float rv = _rv;

    rv *= 125.0;
    rv /= 65536;
    rv -= 6.0;

	return (int16_t) (rv * 10);
}

/* Function sht21_read_raw_value
 *
 * */
int16_t ICACHE_FLASH_ATTR sht21_read_raw_value(uint8_t dataType) {

	int16_t raw_data = 0;

    switch(dataType){
        case SHT21_TEMPERATURE:
        	raw_data = sht21_read_raw_t();
            break;
        case SHT21_HUMIDITY:
        	raw_data = sht21_read_raw_h();
            break;
    }
return raw_data;
}

/* Function sht21_get_temp
 *
 * */
uint16_t ICACHE_FLASH_ATTR sht21_get_value(void) {
    return 0;
}

