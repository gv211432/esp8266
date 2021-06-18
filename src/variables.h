// =================================== Variable Section =============================
// ==================================================================================
// ┏━┓╻  ╻     ╻ ╻┏━┓┏━┓╻┏━┓┏┓ ╻  ┏━╸┏━┓
// ┣━┫┃  ┃     ┃┏┛┣━┫┣┳┛┃┣━┫┣┻┓┃  ┣╸ ┗━┓
// ╹ ╹┗━╸┗━╸   ┗┛ ╹ ╹╹┗╸╹╹ ╹┗━┛┗━╸┗━╸┗━┛
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸

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
        String myObj = WifiControl.getWifiInfoJson();
        return myObj;
    }
    if (var == "MENU")
    {
        return menu_html;
    }
    return s;
}

void onNotFound(AsyncWebServerRequest *request)
{
    //Handle Unknown Request
    request->redirect("/");
}

void mqttCallback(const char *topic, byte *payload, unsigned int length)
{

    String theRecievedData;
    for (size_t i = 0; i < length; i++)
    {
        theRecievedData.concat((char)payload[i]);
    }
    Serial.println(theRecievedData);

    DynamicJsonDocument docs(1024);
    deserializeJson(docs, theRecievedData);
    JsonArray myData = docs["data"].as<JsonArray>();
    Serial.println(docs.as<String>());

    String toHandler = docs["to"];
    Serial.println(toHandler);
    if (toHandler == "btnSwitch")
    {
        for (JsonVariant v : myData)
        {
            int pin = v["no"];
            int to = v["is"];

            Serial.println(pin);
            Serial1.println(to);
            if (PinControl.pinShowValidator(pin) == 1)
            {
                PinControl.toggleThePin(pin, to);
                // No need to send the result or response
                // This will be automatically done by othe function listning for changes in pins states..
            }
        }
        return;
    }

    if (toHandler == "setTime")
    {
        for (JsonVariant v : myData)
        {
            int s = v["s"];
            int h = v["h"];
            int m = v["m"];
            int d = v["d"];
            int M = v["M"];
            int y = v["y"];
            int tSetStatus = timeWriter(s, h, m, d, M, y);

            if (tSetStatus == 1)
            {
                String msg = "{\"status\":\"ok\"}";
                MqttControl.publishOnMqtt("setTime", "opsStats", msg);
            }
        }
        return;
    }

    if (toHandler == "getTime")
    {
        MqttControl.publishOnMqtt("getTime", "timeMan", sendTime());
    }
    if (toHandler == "wifiSet")
    {
    }
    if (toHandler == "setTime")
    {
    }
    if (toHandler == "setTime")
    {
    }
    if (toHandler == "setTime")
    {
    }
    if (toHandler == "setTime")
    {
    }
    if (toHandler == "setTime")
    {
    }
}
