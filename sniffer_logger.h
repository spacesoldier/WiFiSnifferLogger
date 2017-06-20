#ifndef SNIFFER_LOGGER_H
#define SNIFFER_LOGGER_H

#include <FS.h>

extern "C" {
  #include <user_interface.h>
}

#include "wifi_entities.h"



void ICACHE_FLASH_ATTR logBeacon(beaconinfo*);
void ICACHE_FLASH_ATTR logClient(clientinfo*);


#endif
