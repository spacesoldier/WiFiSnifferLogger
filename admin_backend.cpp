/*
 * admin_backend.cpp
 *
 *  Created on: 16 θών. 2017 γ.
 *      Author: Soldat
 */

#include "admin_backend.h"

void startWebServer(){
	/*if (!MDNS.begin(hostname)) {
	    Serial.println("Error setting up MDNS responder!");
	}*/
	//MDNS.addService("http","tcp",80);
	wsBeacons.onEvent(onWsBeaconsEvent);
	wsClients.onEvent(onWsClientsEvent);

	SPIFFS.begin();

	server.serveStatic("/", SPIFFS, "/").setDefaultFile("/index.html");
	server.serveStatic("/index.html", SPIFFS, "/index.html");
	server.serveStatic("/bootstrap.min.css", SPIFFS, "/bootstrap.min.css");
	server.serveStatic("/bootstrap.min.js", SPIFFS, "/bootstrap.min.js");
	server.serveStatic("/jquery-3.2.1.min.js", SPIFFS, "/jquery-3.2.1.min.js");


	Serial.println("server configured");

	server.onNotFound([](AsyncWebServerRequest *request){
	    Serial.printf("NOT_FOUND: ");
	    if(request->method() == HTTP_GET)
	      Serial.printf("GET");
	    else if(request->method() == HTTP_POST)
	      Serial.printf("POST");
	    else if(request->method() == HTTP_DELETE)
	      Serial.printf("DELETE");
	    else if(request->method() == HTTP_PUT)
	      Serial.printf("PUT");
	    else if(request->method() == HTTP_PATCH)
	      Serial.printf("PATCH");
	    else if(request->method() == HTTP_HEAD)
	      Serial.printf("HEAD");
	    else if(request->method() == HTTP_OPTIONS)
	      Serial.printf("OPTIONS");
	    else
	      Serial.printf("UNKNOWN");
	    Serial.printf(" http://%s%s\n", request->host().c_str(), request->url().c_str());

	    if(request->contentLength()){
	      Serial.printf("_CONTENT_TYPE: %s\n", request->contentType().c_str());
	      Serial.printf("_CONTENT_LENGTH: %u\n", request->contentLength());
	    }

	    int headers = request->headers();
	    int i;
	    for(i=0;i<headers;i++){
	      AsyncWebHeader* h = request->getHeader(i);
	      Serial.printf("_HEADER[%s]: %s\n", h->name().c_str(), h->value().c_str());
	    }

	    int params = request->params();
	    for(i=0;i<params;i++){
	      AsyncWebParameter* p = request->getParam(i);
	      if(p->isFile()){
	        Serial.printf("_FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
	      } else if(p->isPost()){
	        Serial.printf("_POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
	      } else {
	        Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
	      }
	    }

	    request->send(404);
	  });
	server.begin();
}

void onWsBeaconsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){

}

void onWsClientsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){

}
