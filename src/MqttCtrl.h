#ifndef MqttCtrl_h
#define MqttCtrl_h

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
    void publishOnMqtt(String, String, String);

    const char *mqtt_server = "192.168.28.229";

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

void MqttCtrl::publishOnMqtt(String from, String to, String data)
{
    if (client.connected())
    {
        String toSendJsonPayload = "{\"from\":\"espHome/" + from + "\",\"to\":\"" + to + "\",\"data\":" + data + "}";
        strcpy(sendOnMqtt, toSendJsonPayload.c_str());
        client.publish(outTopic, sendOnMqtt);
    }
}

void MqttCtrl::mqttReconnect()
{
    if (!client.connected())
    {
        unsigned long currentTime = millis();
        if ((currentTime - previouTimeMqtt) >= 30000)
        {
            if (client.connect(mqttDeviceId, "gaurav", "92244@Great"))
            {
                client.subscribe(inTopic);
            }
            previouTimeMqtt = currentTime;
        }
    }
}

#endif
