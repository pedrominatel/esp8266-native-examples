/*
 *
 *
*/

/*
	GPIO0		GPIO0_U
	GPIO1		U0TXD_U
	GPIO2		GPIO2_U
	GPIO3		U0RXD_U
	GPIO4		GPIO4_U
	GPIO5		GPIO5_U
	GPIO6		SD_CLK_U
	GPIO7		SD_DATA0_U
	GPIO8		SD_DATA1_U
	GPIO9		SD_DATA2_U
	GPIO10		SD_DATA3_U
	GPIO11		SD_CMD_U
	GPIO12		MTDI_U
	GPIO13		MTCK_U
	GPIO14		MTMS_U
	GPIO15		MTDO_U
*/

enum GPIO {
	GPIO0,
	GPIO1,
	GPIO2,
	GPIO3,
	GPIO4,
	GPIO5,
	GPIO6,
	GPIO7,
	GPIO8,
	GPIO9,
	GPIO10,
	GPIO11,
	GPIO12,
	GPIO13,
	GPIO14,
	GPIO15
}

/* Function ezio_init
* */
void ezio_init(void){
}

/* Function ezio_set
 * */
void ezio_set(uint8_t pin, uint8_t mode){        
}

/* Function ezio_set
 * */
void ezio_set(uint8_t pin, uint8_t mode, uint8_t pullup){
}

void ezio_set_intr(uint8_t pin, uint8_t mode){
}

/* Function ezio_write
 * */
void ezio_write(uint8_t gpio, uint8_t state){
}

/* Function ezio_read
 * */
bool ezio_read(uint8_t gpio){
return TRUE;
}

/* Function ezio_disable disable the pin by setting as output
 * and disable interruption for robustness reasons
 * */
void ezio_disable(uint8_t pin){
}
