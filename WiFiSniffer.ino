#include "Arduino.h"

extern "C" {
	#include <user_interface.h>
}

#include "packet_structs.h"
#include "sniffer_manager.h"

void setup()
{
	  Serial.begin(115200);
	  delay(10);
	  prepareToScanMode();
}


void loop()
{
	delay(10);
}
