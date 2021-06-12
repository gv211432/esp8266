// =================================== Variable Section =============================
// ==================================================================================
// ┏━┓╻  ╻     ╻ ╻┏━┓┏━┓╻┏━┓┏┓ ╻  ┏━╸┏━┓
// ┣━┫┃  ┃     ┃┏┛┣━┫┣┳┛┃┣━┫┣┻┓┃  ┣╸ ┗━┓
// ╹ ╹┗━╸┗━╸   ┗┛ ╹ ╹╹┗╸╹╹ ╹┗━┛┗━╸┗━╸┗━┛
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸

// All variabes for wifi
// ----------------------------------------------
const String s = "";
String ssid;
// String *ptrssid = &ssid;
String ssidpw;
// String *ptrssidpw = &ssidpw;
String ap;
// String *ptrap = &ap;
String appw;
// String *ptrappw = &appw;
String lock;
// String *ptrlock;
String user;

// This must be used before making an array to pass in the function of
const int demoAlarm[18] = {0, 0, 50, 25, 61, 25, 61, 0, 0, 0, 0, 0, 0, 0, 2, 32, 13, 0};

#define LED 2 //Define blinking LED pin
#define SPIFFS LittleFS

unsigned long previouTime = 2000;
unsigned long eventTime = 30000;

// ============================ Initilizations ======================================
// ==================================================================================
// Following is server initialization
// ╻┏┓╻╻╺┳╸╻╻  ╻╺━┓┏━┓╺┳╸╻┏━┓┏┓╻┏━┓
// ┃┃┗┫┃ ┃ ┃┃  ┃┏━┛┣━┫ ┃ ┃┃ ┃┃┗┫┗━┓
// ╹╹ ╹╹ ╹ ╹┗━╸╹┗━╸╹ ╹ ╹ ╹┗━┛╹ ╹┗━┛
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Following function processes the output html going to be given to the web client.
// It replaces the templet word with specified one
// ----------------------------------------------
String processor(const String &var)
{
    String s = "";
    if (var == "OBJ")
    {
        String myObj = s + "{wifi:\"" + ssid + "\",wifipw:\"" + ssidpw + "\",ap:\"" + ap + "\",appw:\"" + appw + "\",lock:\"" + lock + "\",user:\"" + user + "\"}";
        return myObj;
    }
    if (var == "MENU")
    {
        return menu_html;
    }
    return s;
}

String sendTime()
{
    String thisTime = s + "{ \"hr\" : \"" + hour() + "\", \"min\" : \"" + minute() + "\", \"sec\" : \"" + second() + "\", \"wDay\" : \"" + weekday() + "\", \"day\" : \"" + day() + "\", \"mon\" : \"" + month() + "\", \"yr\" : \"" + year() + "\"}";
    return thisTime;
}

void onNotFound(AsyncWebServerRequest *request)
{
    //Handle Unknown Request
    request->redirect("/");
}