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
#include "WiFiClientSecure.h"
#include <ArduinoJson.h>
#include "ESPAsyncWebServer.h"
#include <LittleFS.h>
#include <Time.h>
#include <PubSubClient.h>
#include "ESP8266WiFiMesh.h"

#include "extraTools.h" // Extra handy tools for this project
#include "fsValidate.h" // Validating the filesystem before starting the device
#include "WifiCtrl.h"   // Wifi setup
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

// Following are all the html files..
#include "setTimeHtml.h"
#include "wifiHtml.h"        //wifi settings html file
#include "alarmHtml.h"       // alarm html file
#include "terminalName.h"    //terminal name html file
#include "home.h"            // home html file
#include "showTerminal.h"    // show terminal html file
#include "pinRelationHtml.h" // pin relation html file
#include "menuScript.h"      // menu script file
#include "readWriteHtml.h"

#include "timeAndBoot.h" //anything can be executed here before reboot
Reboot RebootDevice;
// Only the following two scrips needa reboot function..
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

    // validating the integrity of the filesystem
    // and fixing any flaw in the FS
    fileSystemData();

    // Loading the saved time if exist..
    loadPreviousRebootTime();

    // PinControl.pinShow(2);
    // This address the function which is for wifi setup
    WifiControl.setWifi();

    // Following set ups the ssl configuration just after WIFI is configured..
    // espClient.setCertStore() ;
    // espClient.allowSelfSignedCerts();

    // Setting the time for BearSSL to verifiy the expiry date of the certificate
    // time_t nowTime;
    // tmElements_t tmSet;
    // tmSet.Hour = hour();
    // tmSet.Minute = minute();
    // tmSet.Second = second();
    // tmSet.Day = day();
    // tmSet.Month = month();
    // tmSet.Year = year();
    // nowTime = makeTime(tmSet);
    // espClient.setX509Time(nowTime);
    // espClient.setFingerprint();

    // espClient.setInsecure();

    // This address the function which setup the webserver and socket
    serverSetup();

    // This address the function which reads the memory for alarm
    AlarmControl.alarmRecover();

    // Dynamically sets, all the empty variabels from the memory data
    const char *mqtt_server = MqttControl.server.c_str();
    // For Secure ssl conection
    // client.setServer(mqtt_server, 8883);
    // Insecure unencrypted connection
    client.setServer(mqtt_server, MqttControl.mqttPort());

    // client.setServer("192.168.0.1", 1883);
    client.setCallback(mqttCallback);

    // PinControl.printIt();

    // -----------------------------------------------
    // Initializing some variables for a function in LOOP section to work properly.
    // This function holds all the code with concerned variables..
    initMqttWSTransferr();
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
    // -----------------------------------------------
    // This function is called in loop, but it only executes on interval of 30s
    AlarmControl.startAlarm();

    // -----------------------------------------------
    //Repeating for triggring the related pins if boss pin is triggered in any way..
    // This function is good for hardware pins
    PinControl.pinRelationConvertor();

    // -----------------------------------------------
    // Looping the following code for pins state check!!
    // for checking the pin state and sending the  information to the connected
    // channels(Mqtt or WebSocket)
    unsigned long currentTimeForPin = millis();
    if ((currentTimeForPin - previouTimeForPin) >= eventTimeForPin)
    {
        // Variable to use as YES or NO
        // If pins state is changed or not..
        int ifChanged = 0;

        for (size_t i = 0; i < sizeMyPinStatsT; i++)
        {
            // If any pin changes their previous status then only send the message..
            // All currently active/working pin is in myPinStatsTrack array..
            // If status changes the following loop get executed and the ifChanged is changed..
            if (myPinStatsTrack[i] != digitalRead(myPinNo[i]))
            {
                ifChanged = 1;
                // myPinStatsTrack[i] = digitalRead(myPinNo[i]);
            }
        }

        // Once message is sent revert the ifChanged status
        // Send pin status change info on the connected channel..
        if (ifChanged == 1)
        {
            ifChanged = 0;

            String getOnOffStatus = PinControl.onOffStatusJson('h'); // h means half...
            // If client exist on Websocket broadcast on WS
            if (ws.count() != 0)
            {
                ws.textAll(getOnOffStatus);
            }

            // If mqtt client is connected then publish on mqtt channel
            if (client.connected())
            {
                MqttControl.publishOnMqtt("0000000000", "loop", "pinState", getOnOffStatus);
            };

            // Refreshes the values of the variables concerned with this loop..
            initMqttWSTransferr();
        }

        // For cleaning the clients on web sockets after connection is closed..
        ws.cleanupClients(4);
        previouTimeForPin = currentTimeForPin;
    }

    // -----------------------------------------------
    // If mqtt service is set to on then start connection and MQTT service
    if (MqttControl.isMqttOn())
    {
        // If wifi is connected then only there is possibility to connect
        //  to mqtt broker and web sever....
        if (WiFi.status() == WL_CONNECTED)
        {
            // Function is to be repeated to connect to the broker..
            MqttControl.mqttReconnect();
            // Function to be repeated for listning on the mqtt topic..
            client.loop();
        }
    }

    // -----------------------------------------------
    // This function will check and reboot the device if any funcition asks
    RebootDevice.DeviceWillReboot();
}