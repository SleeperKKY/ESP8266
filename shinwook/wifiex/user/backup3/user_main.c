#include "osapi.h"
#include "at_custom.h"
#include "user_interface.h"

void user_init(void)
{
    at_init();
   
   at_port_print("AT+RST");
   at_port_print("\r");
   at_port_print("\n");
   
  os_delay(5000);
   at_port_print("AT+CWMODE=3");
   at_port_print("\r");
   at_port_print("\n");
  os_delay(500);
   at_port_print("AT+CIPMUX=1");
  at_port_print("\r");
   at_port_print("\n");
  os_delay(500);
   at_port_print("AT+CWSAP=\"ESL2\",\"2323\",11,0");
   at_port_print("\r");
   at_port_print("\n");
  os_delay(500);
   at_port_print("AT+CIPSERVER=1,2323");
   at_port_print("\r");
   at_port_print("\n");
  os_delay(500);
   at_port_print("AT+CIFSR");
   at_port_print("\r");
   at_port_print("\n");
  os_delay(500);
}
