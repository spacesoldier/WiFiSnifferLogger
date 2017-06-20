/*
 * sniffer_manager.cpp
 *
 *  Created on: 15 θών. 2017 γ.
 *      Author: Soldat
 */
#include "sniffer_manager.h"

void checkScanDone(){
	if (scanDone()){
		stopScan();
		startAP();
	}
}

void stopScan(){
	askScan();
	os_timer_disarm(&channelHop_timer);
	os_timer_disarm(&scan_check_timer);
}

void restartScan(){
	wifi_set_promiscuous_rx_cb(promisc_cb);
	delay(1);
	wifi_promiscuous_enable(ENABLE);
	os_timer_arm(&channelHop_timer, CHANNEL_HOP_INTERVAL_MS, 1);
	os_timer_arm(&scan_check_timer, SCAN_CHECK_INTERVAL, 1);
}

void startAP(){
	Serial.println("Starting AP..");

	wifi_set_opmode(SOFTAP_MODE);
	wifi_promiscuous_enable(DISABLE);
	wifi_set_channel(ap_channel);
	WiFi.hostname(ap_hostname);
	WiFi.softAP(ap_ssid, ap_pwd, ap_channel, 0);
	WiFi.softAPConfig(local_IP, gateway, subnet);
	WiFi.begin();

	//start a timer which checks the number of clients connected
	os_timer_disarm(&check_connection_timer);
	os_timer_setfn(&check_connection_timer, (os_timer_func_t *) checkConnection, NULL);
	os_timer_arm(&check_connection_timer, CONNECT_CHECK_INTERVAL, 1);

	// Register event handlers.
	// Callback functions will be called as long as these handler objects exist.
	// Call "onStationConnected" each time a station connects
	stationConnectedHandler = WiFi.onSoftAPModeStationConnected(&onStationConnected);
	// Call "onStationDisconnected" each time a station disconnects
	stationDisconnectedHandler = WiFi.onSoftAPModeStationDisconnected(&onStationDisconnected);

	//start web server
	startWebServer();
}

void stopAP(){
	WiFi.disconnect(true);
}

void prepareToScanMode(){
	// set the WiFi chip to "promiscuous" mode aka monitor mode
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

	// setup the pausing the scan function
	os_timer_disarm(&scan_check_timer);
	os_timer_setfn(&scan_check_timer, (os_timer_func_t *) checkScanDone, NULL);
	os_timer_arm(&scan_check_timer, SCAN_CHECK_INTERVAL, 1);
}

void checkConnection(){
	if (client_connected && clients_count == 0){
		client_connected = false;
		stopAP();
		restartScan();
	}
}

void onStationConnected(const WiFiEventSoftAPModeStationConnected& evt) {
  Serial.print("Station connected: ");
  client_connected = true;
  clients_count++;
}

void onStationDisconnected(const WiFiEventSoftAPModeStationDisconnected& evt) {
  Serial.print("Station disconnected: ");
  clients_count--;
}
