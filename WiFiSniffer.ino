#include "Arduino.h"

extern "C" {
	#include <user_interface.h>
}

#include "packet_structs.h"
#include "sniffer_tools.h"

#define DISABLE 0
#define ENABLE  1

void setup()
{
	 // set the WiFi chip to "promiscuous" mode aka monitor mode
	  Serial.begin(115200);
	  delay(10);

//	  Serial.print("for clients:");
//	  Serial.print(sizeof(clients_known));
//	  Serial.println(" bytes");

	  wifi_set_opmode(STATION_MODE);
	  wifi_set_channel(1);
	  wifi_promiscuous_enable(DISABLE);
	  delay(10);
	  //wifi_set_promiscuous_rx_cb(sniffer_callback);
	  wifi_set_promiscuous_rx_cb(promisc_cb);
	  delay(10);
	  wifi_promiscuous_enable(ENABLE);

	  // setup the channel hoping callback timer
	  os_timer_disarm(&channelHop_timer);
	  os_timer_setfn(&channelHop_timer, (os_timer_func_t *) channelHop, NULL);
	  os_timer_arm(&channelHop_timer, CHANNEL_HOP_INTERVAL_MS, 1);
}


void loop()
{
	delay(10);
}
