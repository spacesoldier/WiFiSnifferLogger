#ifndef SNIFFER_TOOLS_H
#define SNIFFER_TOOLS_H

#include "packet_structs.h"
#include "wifi_entities.h"
#include <os_type.h>

extern "C" {
  #include <user_interface.h>
}


#include "Arduino.h"

#define CHANNEL_HOP_INTERVAL_MS   1000
static os_timer_t channelHop_timer;

void showMetadata(SnifferPacket *snifferPacket);
void ICACHE_FLASH_ATTR sniffer_callback(uint8_t *buf, uint16_t len); // Default callback for promiscuous mode
void printDataSpan(uint16_t start, uint16_t size, uint8_t* data);
void getMAC(char *addr, uint8_t* data, uint16_t offset);
void channelHop();

void ICACHE_FLASH_ATTR promisc_cb(uint8_t *buf, uint16_t len); //Alternative callback for promiscuous mode

#endif
