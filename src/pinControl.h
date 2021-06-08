// ============================ Initilizations ======================================
// ==================================================================================
// Following is server initialization
// ┏━┓╻┏┓╻   ┏━╸┏━┓┏┓╻╺┳╸┏━┓┏━┓╻     ╻┏┓╻╻╺┳╸╻╻  ╻╺━┓┏━┓╺┳╸╻┏━┓┏┓╻
// ┣━┛┃┃┗┫   ┃  ┃ ┃┃┗┫ ┃ ┣┳┛┃ ┃┃     ┃┃┗┫┃ ┃ ┃┃  ┃┏━┛┣━┫ ┃ ┃┃ ┃┃┗┫
// ╹  ╹╹ ╹   ┗━╸┗━┛╹ ╹ ╹ ╹┗╸┗━┛┗━╸   ╹╹ ╹╹ ╹ ╹┗━╸╹┗━╸╹ ╹ ╹ ╹┗━┛╹ ╹
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸

PinCtrl PinControl;

int myPinStatsTrack[10] = {};
int myPinNo[10] = {};
size_t sizeMyPinStatsT = 0;
size_t previousWsCount = 0;

unsigned long previouTimeForPin = 100;
unsigned long eventTimeForPin = 500;

void onWsConnectSend()
{
    String getOnOffStatus = PinControl.onOffStatusJson();

    DynamicJsonDocument docOrg2(512);
    deserializeJson(docOrg2, getOnOffStatus);
    JsonArray myShowPin = docOrg2["pinOnOff"].as<JsonArray>();

    for (size_t i = 0; i < myShowPin.size(); i++)
    {

        sizeMyPinStatsT = myShowPin.size();
        myPinNo[i] = myShowPin[i]["no"];
        myPinStatsTrack[i] = myShowPin[i]["is"];
    }
    ws.textAll(getOnOffStatus);
};

// This function is binded with the websocket if client is connected, it will trigger..
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        onWsConnectSend();
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        client->close();
    }
    else if (type == WS_EVT_DATA)
    {
    }
}
