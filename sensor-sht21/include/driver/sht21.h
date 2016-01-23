/*
 * sht21.h
 *
 *  Created on: Jan 20, 2016
 *      Author: piiiters
 */

#ifndef INCLUDE_DRIVER_SHT21_H_
#define INCLUDE_DRIVER_SHT21_H_

#include "i2c.h"

#define SHT21_ADDR_W		0x80
#define SHT21_ADDR_R		0x81
#define SHT21_T_REG_HOLD	0xE3
#define SHT21_H_REG_HOLD	0xE5
#define SHT21_T_REG_NHOLD	0xF3
#define SHT21_H_REG_NHOLD	0xF5
#define SHT21_RESET			0xFE
#define SHT21_WRITE_REG		0xE6
#define SHT21_READ_REG		0xE7

bool ICACHE_FLASH_ATTR sht21_init(void);

enum en_dataType {
	SHT21_TEMPERATURE,
	SHT21_HUMIDITY
};

#endif /* INCLUDE_DRIVER_SHT21_H_ */
