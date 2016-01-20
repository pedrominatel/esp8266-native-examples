/*
 * sht21.h
 *
 *  Created on: Jan 20, 2016
 *      Author: piiiters
 */

#ifndef INCLUDE_DRIVER_SHT21_H_
#define INCLUDE_DRIVER_SHT21_H_

#include "i2c_master.h"

#define SHT21_ADDR			0x80
#define SHT21_T_REG_HOLD	0xe3
#define SHT21_H_REG_HOLD	0xe5
#define SHT21_RESET			0xfe
#define SHT21_WRITE_REG		0xe6
#define SHT21_READ_REG		0xe7

bool ICACHE_FLASH_ATTR sht21_init(void);

enum en_dataType {
	SHT21_TEMPERATURE,
	SHT21_HUMIDITY
};

#endif /* INCLUDE_DRIVER_SHT21_H_ */
