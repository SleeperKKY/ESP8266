#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_config.h"
#include "driver/pwm.h"

//Init function 
void ICACHE_FLASH_ATTR user_init()
{
    uint8_t duty=50;
    
	pwm_init( 20, &duty);
	pwm_start();
}
