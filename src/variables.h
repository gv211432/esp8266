// =================================== Variable Section =============================
// ==================================================================================
// ┏━┓╻  ╻     ╻ ╻┏━┓┏━┓╻┏━┓┏┓ ╻  ┏━╸┏━┓
// ┣━┫┃  ┃     ┃┏┛┣━┫┣┳┛┃┣━┫┣┻┓┃  ┣╸ ┗━┓
// ╹ ╹┗━╸┗━╸   ┗┛ ╹ ╹╹┗╸╹╹ ╹┗━┛┗━╸┗━╸┗━┛
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸

// This must be used before making an array to pass in the function of
const int demoAlarm[18] = {0, 0, 50, 25, 61, 25, 61, 0, 0, 0, 0, 0, 0, 0, 2, 32, 13, 0};

#define LED 2 //Define blinking LED pin

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
    String myObj = "";
    if (var == "WIFIOBJ")
    {
        myObj = WifiControl.getWifiInfoJson();
    }
    else if (var == "MQTTOBJ")
    {
        myObj = MqttControl.getMqttData();
    }
    else if (var == "MENU")
    {
        myObj = menu_html;
    }
    return myObj;
}

// Function to be executed when no web path is found..
void onNotFound(AsyncWebServerRequest *request)
{
    // Handle Unknown Request
    // Redirect to the home page..
    request->redirect("/");
}