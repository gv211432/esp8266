// =================================== Include Section ==============================
// ==================================================================================
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "ESPAsyncWebServer.h"
#include <ESPAsyncTCP.h>
#include <FS.h>
#include <LittleFS.h>
#include "html.h"

String ssid;
String *ptrssid = &ssid;
String ssidpw;
String *ptrssidpw = &ssidpw;
String ap;
String *ptrap = &ap;
String appw;
String *ptrappw = &appw;
String lock;
String *ptrlock;
String user;

AsyncWebServer server(80);

// =================================== Variable Section =============================
// ==================================================================================

// =================================== Function Definations =============================
// ======================================================================================

String processor(const String &var)
{
    String s = "";
    String myObj = s + "{wifi:'" + ssid + "',wifipw:'" + ssidpw + "',ap:'" + ap + "',appw:'" + appw + "',lock:'" + lock + "',user:'" + user + "'}";
    if (var == "OBJ")
        return myObj;
    return String();
}

// -----------------------------------------------
// -----------------------------------------------

// -----------------------------------------------
// -----------------------------------------------

// -----------------------------------------------
// -----------------------------------------------

void serverSetup()
{
    server.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request) {
        const char *http_username = user.c_str();
        const char *http_password = lock.c_str();
        if (!request->authenticate(http_username, http_password))
        {
            return request->requestAuthentication();
        };

        AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", index_html, processor);
        response->addHeader("Server", "ESP Async Web Server");
        request->send(response);
    });

    server.on("/changesettings", HTTP_GET, [](AsyncWebServerRequest *request) {
        const char *http_username = user.c_str();
        const char *http_password = lock.c_str();
        if (!request->authenticate(http_username, http_password))
        {
            return request->requestAuthentication();
        }

        String wifiname;
        String wifipass;
        String hotname;
        String hotpass;
        String lockpass;
        String username;

        Serial.println(request->url());

        wifiname = request->getParam("wifiname")->value();
        wifipass = request->getParam("wifipass")->value();
        hotname = request->getParam("hotname")->value();
        hotpass = request->getParam("hotpass")->value();
        lockpass = request->getParam("lockpass")->value();
        username = request->getParam("user")->value();

        request->send(200, "text/plain", "OK");

        LittleFS.begin();

        String check = "b";
        if (ssid != wifiname)
        {
            File data1 = LittleFS.open("/st", "w");
            data1.print(wifiname);
            data1.close();
            check = "a";
        }
        if (ssidpw != wifipass)
        {
            File data1 = LittleFS.open("/stp", "w");
            data1.print(wifipass);
            data1.close();
            check = "a";
        }

        if (ap != hotname)
        {
            File data1 = LittleFS.open("/ap", "w");
            data1.print(hotname);
            data1.close();
            check = "a";
        }
        if (appw != hotpass)
        {
            File data1 = LittleFS.open("/app", "w");
            data1.print(hotpass);
            data1.close();
            check = "a";
        }
        if (lock != lockpass)
        {
            File data1 = LittleFS.open("/lock", "w");
            data1.print(lockpass);
            data1.close();
            check = "a";
        }
        if (user != username)
        {
            File data1 = LittleFS.open("/user", "w");
            data1.print(username);
            data1.close();
            check = "a";
        }

        LittleFS.end();

        if (check != "b")
        {
            delay(500);
            ESP.restart();
        }
    });
    server.begin();
}

// =================================== Two main functions =============================
// ====================================================================================

void setup()
{
    LittleFS.begin();

    // -----------------------------------------------
    File data1 = LittleFS.open("/st", "r");
    String getssid;
    while (data1.available())
    {
        char a = data1.read();
        getssid.concat(a);
    }
    data1.close();
    ssid = getssid;

    // -----------------------------------------------
    File data2 = LittleFS.open("/stp", "r");
    String getssidpw;
    while (data2.available())
    {
        char a = data2.read();
        getssidpw.concat(a);
    }
    data2.close();
    ssidpw = getssidpw;

    // ----------------------------------------------

    File data3 = LittleFS.open("/ap", "r");
    String getap;
    while (data3.available())
    {
        char a = data3.read();
        getap.concat(a);
    }
    data3.close();
    ap = getap;

    // -----------------------------------------------

    File data4 = LittleFS.open("/app", "r");
    String getappw;
    while (data4.available())
    {
        char a = data4.read();
        getappw.concat(a);
    }
    data4.close();
    appw = getappw;

    // -----------------------------------------------

    File data5 = LittleFS.open("/lock", "r");
    String getlock;
    while (data5.available())
    {
        char a = data5.read();
        getlock.concat(a);
    }
    data5.close();
    lock = getlock;

    // -----------------------------------------------

    File data6 = LittleFS.open("/user", "r");
    String getuser;
    while (data6.available())
    {
        char a = data6.read();
        getuser.concat(a);
    }
    data6.close();
    user = getuser;

    LittleFS.end();

    // {wifi:'ssid', wifipw:'wifipw', ap:'ap', appw:'mypass'}
    // -----------------------------------------------

    String s = "";
    String myObj = s + "{wifi:'" + ssid + "',wifipw:'" + ssidpw + "',ap:'" + ap + "',appw:'" + appw + "',lock:'" + lock + "',user:'" + user + "'}";

    Serial.begin(9600);
    Serial.println(myObj);

    // -----------------------------------------------

    WiFi.mode(WIFI_AP_STA);
    if (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin(ssid, ssidpw);
    }
    WiFi.softAP(ap, appw);

    // -----------------------------------------------

    // -----------------------------------------------

    // -----------------------------------------------

    // -----------------------------------------------
    // -----------------------------------------------
    // -----------------------------------------------
    // -----------------------------------------------

    serverSetup();
}

void loop()
{
}