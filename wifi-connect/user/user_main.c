#include "osapi.h"
#include "os_type.h"
#include <user_interface.h>
#include "driver/uart.h"

// Contains ssid and password
//#include "user_config.h"

const char wifi_ssid[32] = "<<SSID>";
const char wifi_pass[64] = "<<PASS>>";

// Data structure for the configuration of your wireless network.
// Will contain ssid and password for your network.
struct station_config stationConf;

void ICACHE_FLASH_ATTR wifiInit() {
  // Copy the ssid and the password into the data structure for later call.
  os_memcpy(&stationConf.ssid, wifi_ssid, 32);
  os_memcpy(&stationConf.password, wifi_pass, 64);

  // Set the wifi mode.  Can be STATION_MODE, SOFTAP_MODE or STATIONAP_MODE.
  // In this caswe we just want to connect as a client on the wireless network
  // so we use station  mode.
  wifi_set_opmode( STATION_MODE );

  // Set the ssid and password of the network you want to connect to.
  wifi_station_set_config(&stationConf);

  // wifi_station_connect isn't needed as when wifi_station_set_config is called as
  // the esp8266 will connect to the router automatically.
  //wifi_station_connect();
}

void user_init(void) {
  // Configure the UART0 and UART1 (TX only) to 115200
  uart_init(BIT_RATE_115200,BIT_RATE_115200);

  // Print a message that we are starting user_init on debug uart
  os_printf("\nStarting...\n");

  // Setup the wifi
  wifiInit();

  // Print a message that we have completed user_init on debug uart
  os_printf("Ready...\n");
}
