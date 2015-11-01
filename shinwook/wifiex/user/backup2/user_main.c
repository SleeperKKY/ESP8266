#include "ets_sys.h"
#include "gpio.h"
#include "osapi.h"
#include "at_custom.h"
#include "ip_addr.h"
#include "user_interface.h"

void user_init(){
	
	struct softap_config config;
	struct ip_info info ;
	char *myssid="NotHello" ;
	char *mypwd="12345678" ;
	
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U,FUNC_GPIO2) ;
	
	wifi_set_opmode(STATIONAP_MODE) ;
	
   //wifi_softap_get_config(&config); // Get config first.
   
   os_memset(config.ssid, 0, 32);
   os_memset(config.password, 0, 64);
   os_memcpy(config.ssid, "NotHello", 8);
   os_memcpy(config.password, "12345678", 8);
   config.ssid_len=0 ;
   config.authmode = AUTH_WPA_WPA2_PSK;
   config.max_connection = 4; // how many stations can connect to ESP8266 softAP at most.
   config.beacon_interval=100 ;

   wifi_softap_set_config(&config) ;// Set ESP8266 softap config . 
   
	gpio_output_set(BIT2,0,BIT2,0) ;
	   
	   
	//wifi_get_ip_info(SOFTAP_IF,&info) ;
	  /*
	IP4_ADDR(&info.ip,203,250,123,245) ;
	IP4_ADDR(&info.gw,203,250,123,1) ;
	IP4_ADDR(&info.netmask,255,255,255,0) ;
	  
	if(wifi_set_ip_info(SOFTAP_IF,&info))
	{
			gpio_output_set(0,BIT2,BIT2,0) ;
	}
	*/
	
   
}
