/*
 * admin_backend.h
 *
 *  Created on: 16 θών. 2017 γ.
 *      Author: Soldat
 */

#ifndef ADMIN_BACKEND_H_
#define ADMIN_BACKEND_H_

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <Hash.h>
#include "server/ESPAsyncTCP.h"
#include "server/ESPAsyncWebServer.h"

static AsyncWebServer server(80);
static AsyncWebSocket wsBeacons("/ws/beacons");
static AsyncWebSocket wsClients("/ws/clients");

//static char hostname[12] = "wifisniffer";

void startWebServer();
void onWsBeaconsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len);
void onWsClientsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len);


#endif /* ADMIN_BACKEND_H_ */
