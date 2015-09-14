#include <ets_sys.h>
#include <gpio.h>
#include <osapi.h>

struct station_config{
	
	uint8_t ssid[32] ;
	uint8_t password[64] ;
	uint8_t bssid_set ;
	uint8_t bssid[6] ;
	
};

void user_init(){
	
	
	//initialize wifi config values
	char ssid[32]="ESL" ;
	char pwd[64]="wjh0123456789" ;
	struct station_config wifiConf ;
	
	//set & initialize gpio
	gpio_init() ;
	
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U,FUNC_GPIO12) ;
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U,FUNC_GPIO2) ;
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U,FUNC_GPIO0) ;
	
	wifi_set_opmode(0x01) ;
	
	//set wifi config
	
	os_memcpy(wifiConf.ssid,ssid,32) ;
	os_memcpy(wifiConf.password,pwd,64) ;
	wifiConf.bssid_set=0 ;//has to be set, otherwise u have to insert mac address of ap
	
	if(wifi_station_set_config(&wifiConf))
	{
		//gpio_output_set(BIT12,0,BIT12,0) ;
		
		uint8_t wifiSts=wifi_station_get_connect_status() ;
		
		if(wifiSts==0)
			gpio_output_set(0,BIT0,BIT0,0) ;
		else if(wifiSts==2)
			gpio_output_set(0,BIT2,BIT2,0) ;
		else if(wifiSts==3)
			gpio_output_set(0,BIT12,BIT12,0) ;
	}
	
}
