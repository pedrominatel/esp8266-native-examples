
typedef enum e_GPIO_STATE {
	LOW,
	HIGH
} GPIO_STATE;

typedef enum e_GPIO_MODE {
	OUTPUT,
	INPUT
} GPIO_MODE;

typedef enum e_GPIO {
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
} GPIO;

void ezio_set(GPIO pin, GPIO_MODE mode);
void ezio_set_intr(GPIO pin, GPIO_MODE mode);
void ezio_write(GPIO pin, GPIO_STATE state);
bool ezio_read(GPIO pin);
void ezio_disable(GPIO pin);
