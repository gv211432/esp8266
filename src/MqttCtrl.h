#ifndef MqttCtrl_h
#define MqttCtrl_h

// ┏┳┓┏━┓╺┳╸╺┳╸┏━╸╺┳╸┏━┓╻   ╻ ╻
// ┃┃┃┃┓┃ ┃  ┃ ┃   ┃ ┣┳┛┃   ┣━┫
// ╹ ╹┗┻┛ ╹  ╹ ┗━╸ ╹ ╹┗╸┗━╸╹╹ ╹

#define MSG_BUFFER_SIZE (2056)
WiFiClient espClient;
PubSubClient client(espClient);

class MqttCtrl
{
public:
    // Constructor function for this header file..
    MqttCtrl();

    // this function try to reconnect to the broker every given time delay in the previousTimeMqtt...
    void mqttReconnect();

    // This function instantly publishes on the given topic as per this project's standard json format..
    void publishOnMqtt(String, String, String, String);

    const char *mqtt_server = "192.168.4.2";

private:
    // This has to be unique for every device...
    const char *mqttDeviceId = "myEsp8266";
    const char *inTopic = "/tokenid/inTopic";
    const char *outTopic = "/tokenid/outTopic";
    // Anything to be plubshied on mqtt has to be copied in the sendOnMqtt variable before publishing...
    char sendOnMqtt[MSG_BUFFER_SIZE];
    unsigned long previouTimeMqtt = 5000;
};

MqttCtrl::MqttCtrl() {}

// To publish on mqtt call this function..
void MqttCtrl::publishOnMqtt(String id, String from, String to, String data)
{
    if (client.connected())
    {
        String toSendJsonPayload = "{\"id\":\"" + id + "\",\"from\":\"espHome/" + from + "\",\"to\":\"" + to + "\",\"data\":" + data + "}";
        strcpy(sendOnMqtt, toSendJsonPayload.c_str());
        client.publish(outTopic, sendOnMqtt);
    }
}

// This function must be called in loop and it will automatically execute every 30sec
void MqttCtrl::mqttReconnect()
{
    if (!client.connected())
    {
        unsigned long currentTime = millis();
        if ((currentTime - previouTimeMqtt) >= 30000)
        {
            Serial.println("Trying to connect ot mqtt");

            if (client.connect(mqttDeviceId, "gaurav", "92244@Great"))
            {
                client.subscribe(inTopic);
                if (client.connected())
                {
                    Serial.println("Mqtt Server connected...");
                }
                else
                {
                    Serial.println("Mqtt connection failed!!");
                }
            }
            else
            {
                Serial.println("Unable to connect. Unknown Problem!!!");
            }
            previouTimeMqtt = currentTime;
        }
    }
}

#endif
