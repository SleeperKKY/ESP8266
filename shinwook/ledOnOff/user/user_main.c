#include "ets_sys.h"//header file that contains constants
#include "mem.h"//header file that contains memory related api
#include "osapi.h"//header file including os api
#include "espconn.h"//header file for tcp layer api
#include "gpio.h"//header file that contains gpio api

void ICACHE_FLASH_ATTR onServerDisconnect(void *arg){
	
	//blink gpio2 for indicating disconnection
	gpio_output_set(BIT2,0,BIT2,0) ;
	os_delay_us(1000000) ;
	gpio_output_set(0,BIT2,BIT2,0) ;
}

void ICACHE_FLASH_ATTR onReceiveTCPMessage(void *arg, char *pdata, unsigned short len)
{
	
	//blink gpio4 for indicating something received
	gpio_output_set(BIT4,0,BIT4,0) ;
	os_delay_us(50000) ;
	gpio_output_set(0,BIT4,BIT4,0) ;
	
}

void ICACHE_FLASH_ATTR onServerConnect(void *arg)
{
	//convert arg to incoming espconn struct, which is client
	struct espconn *pespconn=(struct espconn*)arg ;
	//create receive, disconnect callback function for each client
	espconn_regist_recvcb(pespconn,onReceiveTCPMessage) ;
	espconn_regist_disconcb(pespconn,onServerDisconnect) ;
	
	//blink gpio0 1 sec for indicating connection
	gpio_output_set(BIT0,0,BIT0,0) ;
	os_delay_us(1000000) ;
	gpio_output_set(0,BIT0,BIT0,0) ;
	
}

void ICACHE_FLASH_ATTR user_init(){
	
	//select gpio2 pin function
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U,FUNC_GPIO0) ;
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U,FUNC_GPIO2) ;
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U,FUNC_GPIO4) ;
	
	//create espconn struct and set
	struct espconn *pLedOnOff=(struct espconn*)os_malloc((sizeof(struct espconn))) ;
	ets_memset(pLedOnOff,0,sizeof(struct espconn)) ;
	
	//initialize espconn
	espconn_create(pLedOnOff) ;
	pLedOnOff->type=ESPCONN_TCP ;
	pLedOnOff->state=ESPCONN_NONE ;
	
	//make it a tcp connection
	pLedOnOff->proto.tcp=(esp_tcp*)os_malloc(sizeof(esp_tcp)) ;
	pLedOnOff->proto.tcp->local_port=2323 ;
	
	//register successful connection callback
	espconn_regist_connectcb(pLedOnOff,onServerConnect) ;
	
	//start listening
	espconn_accept(pLedOnOff) ;
	
	//set regist time
	espconn_regist_time(pLedOnOff,15,0) ;
	
}
