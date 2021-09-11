// ============================ Initilizations ======================================
// ==================================================================================
// Following is server initialization
// ┏━┓╻┏┓╻   ┏━╸┏━┓┏┓╻╺┳╸┏━┓┏━┓╻     ╻┏┓╻╻╺┳╸╻╻  ╻╺━┓┏━┓╺┳╸╻┏━┓┏┓╻
// ┣━┛┃┃┗┫   ┃  ┃ ┃┃┗┫ ┃ ┣┳┛┃ ┃┃     ┃┃┗┫┃ ┃ ┃┃  ┃┏━┛┣━┫ ┃ ┃┃ ┃┃┗┫
// ╹  ╹╹ ╹   ┗━╸┗━┛╹ ╹ ╹ ╹┗╸┗━┛┗━╸   ╹╹ ╹╹ ╹ ╹┗━╸╹┗━╸╹ ╹ ╹ ╹┗━┛╹ ╹
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸

// PinCtrl PinControl;

AlarmCtrl AlarmControl;

// This variable keeps the track of the pins state..
int myPinStatsTrack[10] = {};
// This variable keeps the information of the address number of the pins
int myPinNo[10] = {};
// this keeps number of the pins involved.
size_t sizeMyPinStatsT = 0;
// this keeps the count of the number of websocket clients connected..
size_t previousWsCount = 0;

// initial delay for starting the loop
unsigned long previouTimeForPin = 100;
// interval difference for consecutive check by the concerned loop on the pins
unsigned long eventTimeForPin = 500;

void initMqttWSTransferr()
{
    String getOnOffStatus = PinControl.onOffStatusJson();

    DynamicJsonDocument docOrg2(1024);
    deserializeJson(docOrg2, getOnOffStatus);
    JsonArray myShowPin = docOrg2["pinOnOff"].as<JsonArray>();

    for (size_t i = 0; i < myShowPin.size(); i++)
    {
        sizeMyPinStatsT = myShowPin.size();
        myPinNo[i] = myShowPin[i]["no"];
        myPinStatsTrack[i] = myShowPin[i]["is"];
    }
}

void onWsConnectSend()
{
    String getOnOffStatus = PinControl.onOffStatusJson();

    // DynamicJsonDocument docOrg2(512);
    // deserializeJson(docOrg2, getOnOffStatus);
    // JsonArray myShowPin = docOrg2["pinOnOff"].as<JsonArray>();

    // for (size_t i = 0; i < myShowPin.size(); i++)
    // {
    //     sizeMyPinStatsT = myShowPin.size();
    //     myPinNo[i] = myShowPin[i]["no"];
    //     myPinStatsTrack[i] = myShowPin[i]["is"];
    // }
    ws.textAll(getOnOffStatus);
};

// This function is binded with the websocket if a new client gets connected,
// or disconnected, it will trigger for once..
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        initMqttWSTransferr();
        String getOnOffStatus = PinControl.onOffStatusJson();
        ws.textAll(getOnOffStatus);

        // onWsConnectSend();
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        client->close();
    }
    else if (type == WS_EVT_DATA)
    {
    }
}
