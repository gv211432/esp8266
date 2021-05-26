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
#include "variables.h" //all variables and html preprocessors
#include "jquery.h"    //jquery.js file hosted locally
#include "css.h"
#include "setTimeHtml.h"
#include "wifiHtml.h" //wifi settings html file
#include "alarmHomeHtml.h"
#include "webServ.h"   // webserver setup
#include "wifiSetup.h" //wifi setup
#include "alarms.h"    //alarm setup

// ================================= Dear SETUP functions =============================
// ====================================================================================
// Following is the setup function runs on reboot
// ┏━┓┏━╸╺┳╸╻ ╻┏━┓
// ┗━┓┣╸  ┃ ┃ ┃┣━┛
// ┗━┛┗━╸ ╹ ┗━┛╹
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸
void setup()
{
    setWifi();
    serverSetup();
    String nowTime = s + hour() + " : " + minute() + " : " + second() + " : " + weekday() + " -- " + day() + "/" + month() + "/" + year() + " ";
    Serial.println(nowTime);
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
}