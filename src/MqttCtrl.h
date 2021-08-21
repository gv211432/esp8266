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

    // Returns the mqtt connection data..
    String getMqttData();

    // On no error return 0 and on error return 1
    void setMqttData(String, String, String, String);

    // This function instantly publishes on the given topic as per this project's standard json format..
    void publishOnMqtt(String, String, String, String);

    // const char *mqtt_server = "192.168.4.2";
    // char *mqtt_server[30];
    String server;

private:
    char sendOnMqtt[MSG_BUFFER_SIZE];
    unsigned long previouTimeMqtt = 5000;

    String mqttDeviceId, password, username, inTopic, outTopic, tokenId;
};

MqttCtrl::MqttCtrl()
{
    // Default buffer size of mqtt messages is 256 bytes.
    // This api increases the message limit!!
    client.setBufferSize(374);

    Serial.println("Starting the mqtt constructor");
    // Reading all the data in setup mode for performance
    // ----------------------------------------------
    LittleFS.begin();

    // Open the directory..
    Dir dir = LittleFS.openDir("/mqtt");

    // Loop through all single files in the directory..
    while (dir.next())
    {
        String fName = dir.fileName(); // names like pinData, pinName, pinRel, pinShow, ..
        if (dir.fileSize())
        {
            File f = dir.openFile("r");
            String mqttInfo; //creating temperory string ...
            // loop through all the single character in the current file..
            while (f.available())
            {
                char alp = f.read();
                mqttInfo.concat(alp);
            }
            f.close();

            //conditionally copying to varalbles..
            // -----------------------------------------------

            if (fName == "pass")
            {
                password = mqttInfo;
                continue;
            }
            if (fName == "server")
            {
                server = mqttInfo;
                continue;
            }
            if (fName == "token")
            {
                mqttDeviceId = mqttInfo;

                String tempInTopic = "/";
                String tempOutTopic = "/";

                tempInTopic.concat(mqttInfo);
                tempInTopic.concat("/inTopic");
                inTopic = tempInTopic;

                tempOutTopic.concat(mqttInfo);
                tempOutTopic.concat("/outTopic");
                outTopic = tempOutTopic;

                continue;
            }
            if (fName == "user")
            {
                username = mqttInfo;
                continue;
            }
        }
    }
    // Unmounting file system
    // ----------------------------------------------
    LittleFS.end();
}

// To publish on mqtt call this function..
void MqttCtrl::publishOnMqtt(String id, String from, String to, String data)
{
    const char *outTopic_c = outTopic.c_str();

    if (client.connected())
    {
        String toSendJsonPayload = "{\"id\":\"" + id + "\",\"from\":\"espHome/" + from + "\",\"to\":\"" + to + "\",\"data\":" + data + "}";
        strcpy(sendOnMqtt, toSendJsonPayload.c_str());
        client.publish(outTopic_c, sendOnMqtt);
    }
}

String MqttCtrl::getMqttData()
{
    String theData = "{\"server\":\"" + server + "\",\"user\":\"" + username + "\",\"pass\":\"" + password + "\",\"token\":\"" + mqttDeviceId + "\" }";
    return theData;
}

void MqttCtrl::setMqttData(String mqttServer = "void", String userName = "void", String passWord = "void", String deviceId = "void")
{
    bool isSomethingChanged = false;
    if (mqttServer != "void" && mqttServer != "")
    {
        isSomethingChanged = true;
        writeToMemory("/mqtt/server", mqttServer);
    }
    if (userName != "void" && userName != "")
    {
        isSomethingChanged = true;
        writeToMemory("/mqtt/user", userName);
    }
    if (passWord != "void" && passWord != "")
    {
        isSomethingChanged = true;
        writeToMemory("/mqtt/pass", passWord);
    }
    if (deviceId != "void" && deviceId != "")
    {
        isSomethingChanged = true;
        writeToMemory("/mqtt/token", deviceId);
    }
    if (isSomethingChanged)
    {
        // delay(500);
        // ESP.restart();
        Serial.println("Tend to reboot on mqtt config change");
    }
}

// This function must be called in loop and it will automatically execute every 30sec
void MqttCtrl::mqttReconnect()
{
    const char *mqttDeviceId_c = mqttDeviceId.c_str();
    const char *username_c = username.c_str();
    const char *password_c = password.c_str();
    const char *inTopic_c = inTopic.c_str();

    if (!client.connected())
    {
        unsigned long currentTime = millis();
        if ((currentTime - previouTimeMqtt) >= 30000)
        {
            Serial.println("Trying to connect ot mqtt");

            if (client.connect(mqttDeviceId_c, username_c, password_c))
            {
                client.subscribe(inTopic_c);
                if (client.connected())
                {
                    Serial.println("Mqtt Server connected... on topic");
                    Serial.println(inTopic_c);
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
