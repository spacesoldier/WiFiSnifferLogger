#ifndef SNIFFER_MANAGER_H
#define SNIFFER_MANAGER_H

#include "sniffer_tools.h"
#include "ESP8266WiFi.h"
#include "admin_backend.h"

#define DISABLE 0
#define ENABLE  1

#define SCAN_CHECK_INTERVAL   1000
#define AP_ACTIVE_PERIOD 15000
#define CONNECT_CHECK_INTERVAL 5000

static os_timer_t scan_check_timer;
static os_timer_t check_connection_timer;
static bool admin_connected = false;

static int ap_channel = 1;
static char ap_ssid[] = "wifi_spy";
static char ap_pwd[] = "kaboo00m";
static char ap_hostname[] = "mac-log.com";

static IPAddress local_IP(192,168,0,100);
static IPAddress gateway(192,168,1,1);
static IPAddress subnet(255,255,255,0);

static WiFiEventHandler stationConnectedHandler;
static WiFiEventHandler stationDisconnectedHandler;
static int clients_count = 0;
static bool client_connected = false;

void checkScanDone();
void checkClientDisconnected();
void stopScan();
void restartScan();
void startAP();
void stopAP();

// initially sets up the thing to scan mode
void prepareToScanMode();
void startWebServer();

void checkConnection();

void onStationConnected(const WiFiEventSoftAPModeStationConnected& evt);
void onStationDisconnected(const WiFiEventSoftAPModeStationDisconnected& evt);

#endif
