// ┏━╸┏━┓┏━┓┏━┓┏━┓┏━┓┏━┓   ┏━┓╻ ╻╺┳╸┏━┓┏┳┓┏━┓╺┳╸╻┏━┓┏┓╻┏━┓
// ┣╸ ┗━┓┣━┛┣━┫┏━┛┣━┓┣━┓   ┣━┫┃ ┃ ┃ ┃ ┃┃┃┃┣━┫ ┃ ┃┃ ┃┃┗┫┗━┓
// ┗━╸┗━┛╹  ┗━┛┗━╸┗━┛┗━┛   ╹ ╹┗━┛ ╹ ┗━┛╹ ╹╹ ╹ ╹ ╹┗━┛╹ ╹┗━┛

// =================================== Include Section ==============================
// ==================================================================================
// ╻┏┓╻┏━╸╻  ╻ ╻╺┳┓┏━╸┏━┓
// ┃┃┗┫┃  ┃  ┃ ┃ ┃┃┣╸ ┗━┓
// ╹╹ ╹┗━╸┗━╸┗━┛╺┻┛┗━╸┗━┛
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸

// Platform import
// ----------------------------------------------
#include <Arduino.h>

// Dependencies import
// ----------------------------------------------
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "ESPAsyncWebServer.h"
#include <LittleFS.h>
#include <Time.h>
#include <PubSubClient.h>
#include "ESP8266WiFiMesh.h"

#include "timeWriter.h"
#include "WifiCtrl.h" //wifi setup
WifiCtrl WifiControl;

#include "PinCtrl.h"
PinCtrl PinControl;
#include "AlarmCtrl.h"

#include "MqttCtrl.h"
MqttCtrl MqttControl;

// Own header files import
// ----------------------------------------------
// Web dependencies for the pages..
#include "menuHtml.h"
#include "jquery.h" //jquery.js file hosted locally
#include "css.h"

//all variables and extra variable in the pinControl file
#include "variables.h"
#include "pinControl.h"

// Following are all the html..
#include "setTimeHtml.h"
#include "wifiHtml.h" //wifi settings html file
#include "alarmHtml.h"
#include "terminalName.h"
#include "home.h"
#include "showTerminal.h"
#include "pinRelationHtml.h"
#include "menuScript.h"

#include "webServer.h"    // webserver setup
#include "mqttCallback.h" //The handler function for the mqtt

// ================================= Dear SETUP functions =============================
// ====================================================================================
// Following is the setup function runs on reboot
// ┏━┓┏━╸╺┳╸╻ ╻┏━┓
// ┗━┓┣╸  ┃ ┃ ┃┣━┛
// ┗━┛┗━╸ ╹ ┗━┛╹
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸
void setup()
{
    // Starting serial monitor service
    // ----------------------------------------------
    Serial.begin(9600);

    // PinControl.pinShow(2);
    // This address the function which is for wifi setup
    WifiControl.setWifi();
    // This address the function which setup the webserver and socket
    serverSetup();
    // This address the function which reads the memory for alarm
    AlarmControl.alarmRecover();

    client.setServer(MqttControl.mqtt_server, 1883);
    client.setCallback(mqttCallback);
    // PinControl.printIt();
    // -----------------------------------------------
}

// ================================== Dear LOOP functions =============================
// ====================================================================================
// Following function run again and again
// ╻  ┏━┓┏━┓┏━┓   ╻  ┏━┓┏━┓┏━┓   ╻  ┏━┓┏━┓┏━┓
// ┃  ┃ ┃┃ ┃┣━┛   ┃  ┃ ┃┃ ┃┣━┛   ┃  ┃ ┃┃ ┃┣━┛
// ┗━╸┗━┛┗━┛╹     ┗━╸┗━┛┗━┛╹     ┗━╸┗━┛┗━┛╹
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸
void loop()
{

    unsigned long currentTime = millis();
    if ((currentTime - previouTime) >= eventTime)
    {
        AlarmControl.startAlarm();
        previouTime = currentTime;
    }

    //Repeating for triggring the related pins if boss pin is triggered in any way..
    PinControl.pinRelationConvertor();

    // Repeating the following for check if there is client on web sockets..
    unsigned long currentTimeForPin = millis();
    if ((currentTimeForPin - previouTimeForPin) >= eventTimeForPin)
    {
        if (ws.count() != 0)
        {
            int ifChanged = 0;

            for (size_t i = 0; i < sizeMyPinStatsT; i++)
            {
                // If any pin changes their previous status then only send the message..
                // All currently active/working pin is in myPinStatsTrack array..
                // If status changes the following loop get executed and the ifChanged is changed..
                if (myPinStatsTrack[i] != digitalRead(myPinNo[i]))
                {
                    ifChanged = 1;
                    myPinStatsTrack[i] = digitalRead(myPinNo[i]);
                }
            }

            // Once message is sent revert the ifChanged status
            if (ifChanged == 1)
            {
                ifChanged = 0;

                String getOnOffStatus = PinControl.onOffStatusJson('h');
                ws.textAll(getOnOffStatus);

                Serial.println(client.connected());
                MqttControl.publishOnMqtt("loop", "stateCheck", getOnOffStatus);
            }
        }

        // For cleaning the clients on web sockets after connection is closed..
        ws.cleanupClients(4);

        previouTimeForPin = currentTimeForPin;
    }

    // If wifi is connected then only there is possibility to connect to mqtt broker and web sever....
    if (WiFi.status() == WL_CONNECTED)
    {
        // Function is to be repeated to connect to the broker..
        MqttControl.mqttReconnect();
        // Function to be repeated for listning on the mqtt topic..
        client.loop();
    }
}