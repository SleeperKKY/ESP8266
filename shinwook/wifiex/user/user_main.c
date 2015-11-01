#include "ets_sys.h"
#include "gpio.h"
#include "osapi.h"
#include "at_custom.h"
#include "ip_addr.h"
#include "user_interface.h"

void ICACHE_FLASH_ATTR user_init(){
	
	//struct softap_config config;
	struct softap_config config ;
	struct ip_info info ;
	char *myssid="ESP2" ;
	char *mypwd="1234567890" ;
	
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U,FUNC_GPIO2) ;
	
	wifi_set_opmode(STATIONAP_MODE) ;
	
   wifi_softap_get_config(&config); // Get config first.
   
   //os_memset(config.ssid,0,32) ;
   //os_memset(config.password,0,32) ;
   os_memcpy(config.ssid, myssid, 4);
   os_memcpy(config.password, mypwd, 10);
   config.ssid_len=4 ;
   config.authmode = AUTH_WPA_WPA2_PSK;
   config.channel=1 ;
   config.max_connection = 10; // how many stations can connect to ESP8266 softAP at most.
   config.beacon_interval=100 ;
   config.ssid_hidden=0 ;

   wifi_softap_set_config(&config) ;// Set ESP8266 softap config . 
   
	gpio_output_set(BIT2,0,BIT2,0) ;
	   
	   
	//wifi_get_ip_info(SOFTAP_IF,&info) ;
	  
	IP4_ADDR(&info.ip,192,168,4,1) ;	
	IP4_ADDR(&info.gw,192,168,4,1) ;
	IP4_ADDR(&info.netmask,255,255,255,0) ;
	  
	if(wifi_set_ip_info(1,&info))
	{
			gpio_output_set(0,BIT2,BIT2,0) ;
	}
	
	
   
}
