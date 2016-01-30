/*
 *
 *
 */

#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_config.h"
#include "driver/ezio.h"

/* Function ezio_init
 * */
void ezio_init(void) {
	gpio_init();
}

/* Function ezio_set
 * */
void ezio_set(GPIO pin, GPIO_MODE mode) {

	switch (pin) {
	case GPIO0:
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0);
		break;
	case GPIO1:
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0TXD_U, FUNC_GPIO1);
		break;
	case GPIO2:
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
		break;
	case GPIO3:
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0RXD_U, FUNC_GPIO3);
		break;
	case GPIO4:
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U, FUNC_GPIO4);
		break;
	case GPIO5:
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5);
		break;
	case GPIO6:
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_SD_CLK_U, FUNC_SDCLK);
		break;
	case GPIO7:
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_SD_DATA0_U, FUNC_SDDATA0);
		break;
	case GPIO8:
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_SD_DATA1_U, FUNC_SDDATA1);
		break;
	case GPIO9:
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_SD_DATA2_U, FUNC_SDDATA2);
		break;
	case GPIO10:
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_SD_DATA3_U, FUNC_SDDATA3);
		break;
	case GPIO11:
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_SD_CMD_U, FUNC_SDCMD);
		break;
	case GPIO12:
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12);
		break;
	case GPIO13:
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13);
		break;
	case GPIO14:
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14);
		break;
	case GPIO15:
		PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, FUNC_GPIO15);
		break;
	}

	if(mode == INPUT){
		GPIO_DIS_OUTPUT(GPIO_ID_PIN(pin));
	}
}

/* Function ezio_set_intr
 * Function to configure the pin interruption
 * */
void ezio_set_intr(GPIO pin, GPIO_MODE mode) {
	//TODO
}

/* Function ezio_write
 * */
void ezio_write(GPIO pin, GPIO_STATE state) {
	GPIO_OUTPUT_SET(GPIO_ID_PIN(pin), state);
}

/* Function ezio_read
 * */
bool ezio_read(GPIO pin) {
	return GPIO_INPUT_GET(GPIO_ID_PIN(pin));
}

/* Function ezio_disable disable the pin by setting as output
 * and disable interruption for robustness reasons
 * */
void ezio_disable(GPIO pin) {
	GPIO_OUTPUT_SET(GPIO_ID_PIN(pin), LOW);
}
