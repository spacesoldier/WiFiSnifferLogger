#ifndef WIFI_ENTITIES_H
#define WIFI_ENTITIES_H

#include "packet_structs.h"

#define ETH_MAC_LEN 6
#define MAX_APS_TRACKED 200
#define MAX_CLIENTS_TRACKED 500

struct beaconinfo
{
  uint8_t bssid[ETH_MAC_LEN];
  uint8_t ssid[33];
  int ssid_len;
  int channel;
  int err;
  signed rssi;
  uint8_t capa[2];
};

struct clientinfo
{
  uint8_t bssid[ETH_MAC_LEN];
  uint8_t station[ETH_MAC_LEN];
  uint8_t ap[ETH_MAC_LEN];
  int channel;
  int err;
  signed rssi;
  uint16_t seq_n;
};

extern clientinfo clients_known[MAX_CLIENTS_TRACKED];

// methods for working with cliens and beacons representations:

int register_beacon(beaconinfo beacon);
int register_client(clientinfo ci);
void print_beacon(beaconinfo beacon);
void print_client(clientinfo ci);



clientinfo parse_data(uint8_t *frame, uint16_t framelen, signed rssi, unsigned channel);
beaconinfo parse_beacon(uint8_t *frame, uint16_t framelen, signed rssi);


#endif
