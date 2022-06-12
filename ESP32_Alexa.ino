/*
 Name:		    ESP32_Alexa.ino
 Created:	    06/06/2022
 Author:	    Paulo Fernando <pfsf07@gmail.com>
 Description: MCU(Esp32 in this case) that connects with Alexa(Amazon's home assistant), using "fauxmoESP" library. This example turnon/turnoff two LEDs and dims another LED.
 Connections:
	VCC    			 -> 	Powered by USB 
	LED Output(3V3 Logic)    -> 	GPIO 12,GPIO 14
  	LED Output(PWM) 	 ->     GPIO 15 
*/
#include <Arduino.h>
#include <WiFi.h>
//fauxmo library
#include "fauxmoESP.h"
//LED pins
#define LED_PIN_1 12
#define LED_PIN_2 14
#define LED_PIN_3 15
//WiFi credentials
#define WIFI_SSID "Your WIFI SSID"
#define WIFI_PASS "WIFI PASSWORD"
//Devices names
#define LED_1 "led um"
#define LED_2 "led dois"
#define LED_3 "led três"
//Fauxmo object
fauxmoESP fauxmo;
//WiFi function to handle connection
void wifiSetup(){
  //Station mode
  WiFi.mode(WIFI_STA);
  Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  //Connection OK!
  Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

void setup(){
  //Serial port to Debug
  Serial.begin(115200);
  Serial.println();
  //Initialize WiFi
  wifiSetup();
  //Configuration of LED_1 and LED_2
  pinMode(LED_PIN_1, OUTPUT);
  digitalWrite(LED_PIN_1, LOW);
  pinMode(LED_PIN_2, OUTPUT);
  digitalWrite(LED_PIN_2, LOW);
  //PWM config of LED_3:Channel, Frequency, Resolution
  ledcSetup(0, 5000, 8);
  //PWM output pin
  ledcAttachPin(LED_PIN_3, 0);
  //Create fauxmo TCP server with port number 80(gen3 devices),1901(default) 
  fauxmo.createServer(true); 
  fauxmo.setPort(80); 
  //Pass true/false to next function, to enable or disable the library. Disabling it will prevent the devices from being discovered and switched
  fauxmo.enable(true);
  //Add virtual devices
  fauxmo.addDevice(LED_1);
  fauxmo.addDevice(LED_2);
  fauxmo.addDevice(LED_3);
  //Callback function to handle Alexa requests. As short as possible!
  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value){
    //"state" variable to turn on/off | "value" variable to set the pwm output
    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
    //Turn on/off "led um" device
    if((strcmp(device_name, LED_1) == 0)){
        Serial.print("'led um' state: ");Serial.println(state);
        if(state){
            digitalWrite(LED_PIN_1, HIGH);
        } 
        else{
            digitalWrite(LED_PIN_1, LOW);
        }
    }
    //Turn on/off "led dois" device
    if((strcmp(device_name, LED_2) == 0)){
        Serial.print("'led dois' state: ");Serial.println(state);
        if(state){
            digitalWrite(LED_PIN_2, HIGH);
        } 
        else{
            digitalWrite(LED_PIN_2, LOW);
        }
    }
    //Dim "led três" device
    if((strcmp(device_name, LED_3) == 0)){
        Serial.print("'led três' value: ");Serial.println(value);
        ledcWrite(0, value);
    }
  });
}

void loop(){
  //Verifiy UDP async packets
  fauxmo.handle();
}
