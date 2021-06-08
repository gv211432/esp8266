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

// #include <WiFiUdp.h>

// Own header files import
// ----------------------------------------------
#include "menuHtml.h"
#include "variables.h" //all variables and html preprocessors
#include "jquery.h"    //jquery.js file hosted locally
#include "css.h"
#include "setTimeHtml.h"
#include "wifiHtml.h" //wifi settings html file
#include "alarmHomeHtml.h"
#include "PinCtrl.h"
#include "pinControl.h"
#include "terminalName.h"
#include "home.h"
#include "showTerminal.h"
#include "pinRelationHtml.h"
#include "menuScript.h"
#include "webServer.h" // webserver setup
#include "wifiSetup.h" //wifi setup
#include "alarms.h"    //alarm setup
#include "mqtt.h"

// ================================= Dear SETUP functions =============================
// ====================================================================================
// Following is the setup function runs on reboot
// ┏━┓┏━╸╺┳╸╻ ╻┏━┓
// ┗━┓┣╸  ┃ ┃ ┃┣━┛
// ┗━┛┗━╸ ╹ ┗━┛╹
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸
void setup()
{
    // This address the function which is for wifi setup
    setWifi();
    // This address the function which setup the webserver and socket
    serverSetup();
    // This address the function which reads the memory for alarm
    alarmRecover();

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
        startAlarm();
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
                if (myPinStatsTrack[i] != digitalRead(myPinNo[i]))
                {
                    ifChanged = 1;
                    myPinStatsTrack[i] = digitalRead(myPinNo[i]);
                }
            }

            if (ifChanged == 1)
            {
                String getOnOffStatus = PinControl.onOffStatusJson();
                ws.textAll(getOnOffStatus);
                ifChanged = 0;
            }
        }

        // For cleaning the clients on web sockets after connection is closed..
        ws.cleanupClients(4);

        previouTimeForPin = currentTimeForPin;
    }
}