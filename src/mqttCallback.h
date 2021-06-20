
// ┏┳┓┏━┓╺┳╸╺┳╸┏━╸┏━┓╻  ╻  ┏┓ ┏━┓┏━╸╻┏
// ┃┃┃┃┓┃ ┃  ┃ ┃  ┣━┫┃  ┃  ┣┻┓┣━┫┃  ┣┻┓
// ╹ ╹┗┻┛ ╹  ╹ ┗━╸╹ ╹┗━╸┗━╸┗━┛╹ ╹┗━╸╹ ╹
// ----------------------------------------------
// This function handles the message on subscribed topic and generate response and result for the same
void mqttCallback(const char *topic, byte *payload, unsigned int length)
{
    const String msg = "{\"status\":\"ok\"}";

    String theRecievedData;

    // Cottecting data in the string variable one by one!!!s
    for (size_t i = 0; i < length; i++)
    {
        theRecievedData.concat((char)payload[i]);
    }
    // Printing the received data for debugging..
    Serial.println(theRecievedData);

    DynamicJsonDocument docs(2056);
    deserializeJson(docs, theRecievedData);
    JsonArray myData = docs["data"].as<JsonArray>();

    // again printing for debugging!!
    Serial.println(docs.as<String>());

    String toHandler = docs["to"];
    Serial.println(toHandler);

    // for switching the buttons..
    // ----------------------------------------------
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
                // This will be automatically done by other function listning for changes in pins states..
            }
        }
        return;
    }

    // This will set the system time...
    // ----------------------------------------------
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

            int sec = -1;
            int hr = -1;
            int min = -1;
            int myday = -1;
            int mymonth = -1;
            int myyear = -1;

            if (v["s"] == s)
            {
                sec = s;
            }
            if (v["h"] == h)
            {
                hr = h;
            }
            if (v["m"] == m)
            {
                min = m;
            }
            if (v["d"] == d)
            {
                myday = d;
            }
            if (v["M"] == m)
            {
                mymonth = M;
            }
            if (v["y"] == y)
            {
                myyear = y;
            }

            int tSetStatus = timeWriter(sec, hr, min, myday, mymonth, myyear);
            if (tSetStatus == 1)
            {
                MqttControl.publishOnMqtt("setTime", "opsStats", msg);
            }
        }
        return;
    }

    // This will return the system time on mqtt...
    // ----------------------------------------------
    if (toHandler == "getTime")
    {
        MqttControl.publishOnMqtt("getTime", "timeMan", sendTime());
        return;
    }

    if (toHandler == "strength")
    {
        for (JsonVariant v : myData)
        {
            String anyStr = v;
            int gotCheck = WifiControl.stringStrengthCheck(anyStr);
            MqttControl.publishOnMqtt("setTime", "opsStats", String(gotCheck));
            return;
        }
    }

    // This will set the parameters to the wifi settings and restart the esp..
    // ----------------------------------------------
    if (toHandler == "setWifi")
    {
        for (JsonVariant v : myData)
        {
            String wifiname = "void";
            String wifipass = "void";
            String hotname = "void";
            String hotpass = "void";
            String lockpass = "void";
            String username = "void";

            String wifinameProto = v["wName"];
            if (wifinameProto == v["wName"])
            {
                wifiname = wifinameProto;
            }
            String wifipassProto = v["wPass"];
            if (wifipassProto == v["wPass"])
            {
                wifipass = wifipassProto;
            }

            String hotnameProto = v["hName"];
            if (hotnameProto == v["hName"])
            {
                hotname = hotnameProto;
            }

            String hotpassProto = v["hPass"];
            if (hotpassProto == v["hPass"])
            {
                hotpass = hotpassProto;
            }

            String lockpassProto = v["lock"];
            if (lockpassProto == v["lock"])
            {
                lockpass = lockpassProto;
            }

            String usernameProto = v["user"];
            if (usernameProto == v["user"])
            {
                username = usernameProto;
            }

            WifiControl.updateWifiSettings(wifiname, wifipass, hotname, hotpass, lockpass, username);
        }

        MqttControl.publishOnMqtt("setWifi", "opsStats", msg);
        return;
    }

    if (toHandler == "wifiMode")
    {
        for (JsonVariant v : myData)
        {
            WifiControl.changeConnectionMode(v);
            MqttControl.publishOnMqtt("wifiMode", "opsStats", msg);
            delay(500);
            ESP.restart();
        }
        return;
    }
    // returns the wifi info to the other mqtt fellow subscriber..
    if (toHandler == "getWifi")
    {
        MqttControl.publishOnMqtt("setWifi", "opsStats", WifiControl.getWifiInfoJson());
        return;
    }

    // This will return the Json info of the alarms..
    // ----------------------------------------------
    if (toHandler == "alarmJson")
    {
        bool isExecuted = false;
        String getAlarm = AlarmControl.getAlarms();
        DynamicJsonDocument docsAlarm(4056);
        deserializeJson(docsAlarm, getAlarm);
        size_t sizeOfDoc = docsAlarm.size();

        for (size_t i = 0; i < sizeOfDoc; i++)
        {
            isExecuted = true;
            MqttControl.publishOnMqtt("alarmJson/alarm" + String(i), "opsStats", docsAlarm["alarm" + String(i)]);
        }
        if (!isExecuted)
        {
            MqttControl.publishOnMqtt("setAlarm", "opsStats", "{}");
        }
        return;
    }

    // ---------------------------------------------------------------------------------------------------------
    // {"free":0,"enable":0,"pin":50,"onHr":25,"onMin":61,"offHr":25,"offMin":61,"sun":0,"mon":0,
    // "tue":0,"wed":0,"thu":0,"fri":0,"sat":0,"oneShot":2,"day":32,"month":13,"year":0}
    // ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸
    // free,enable/disable,pinNo,onHr,onMin,offHr,offMin,sun,mon,tue,wed,thu,fri,sat,oneShot,day,month,year [18]
    //  0/1      1/0,        0,   0,    0,    0,    0,    0,  1,  1,  1,  1,  1,  0,  0/1/2,  32,   13,  0  [18]
    //   0        1          2    3      4     5    6     7   8   9   10  11  12  13   14     15    16   17 [18]
    // ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸
    if (toHandler == "setAlarm")
    {
        for (JsonVariant v : myData)
        {
            // Evaluate oneShot(0,1,2) and take decision
            // ----------------------------------------------
            int myShot = v["shot"];
            if (myShot == v["shot"])
            {
                Serial.println("this is Shot");

                //Creating new arry and copying demoAlarm into it..
                int myNewAlarm[18];
                for (int i = 0; i < 18; i++)
                {
                    myNewAlarm[i] = demoAlarm[i];
                }
                myNewAlarm[1] = v["enable"];
                myNewAlarm[2] = v["pinNo"];
                myNewAlarm[3] = v["onHr"];
                myNewAlarm[4] = v["onMin"];
                myNewAlarm[5] = v["offHr"];
                myNewAlarm[6] = v["offMin"];
                myNewAlarm[7] = v["sun"];
                myNewAlarm[8] = v["mon"];
                myNewAlarm[9] = v["tue"];
                myNewAlarm[10] = v["wed"];
                myNewAlarm[11] = v["thu"];
                myNewAlarm[12] = v["fri"];
                myNewAlarm[13] = v["sat"];
                myNewAlarm[14] = v["oneShot"];
                myNewAlarm[15] = v["day"];
                myNewAlarm[16] = v["month"];
                myNewAlarm[17] = v["year"];

                // If alarm is suppose to be updated
                int aID = -1;
                int alarmId = v["aID"];
                if (alarmId == v["aID"])
                {
                    aID = alarmId;
                }

                //Sending the generated Alarm array for checking and writing into memory
                int gotStatus = AlarmControl.alarmMemWriter(myNewAlarm, aID);

                if (gotStatus == 1)
                {
                    MqttControl.publishOnMqtt("setAlarm", "opsStats", "{\"status\":\"Failed\"}");
                    return;
                }
                MqttControl.publishOnMqtt("setAlarm", "opsStats", msg);
                return;
            }
            return;
        }
    }

    if (toHandler == "delAlarm")
    {
        bool doneStatus = false;
        for (JsonVariant v : myData)
        {
            // If del is set in the query with alarm index number (aID), it will delete the alarm[aID]
            // ----------------------------------------------
            int alarmID = v["aID"];
            int myDelete = v["del"];
            if (v["del"] == myDelete && v["aID"] == alarmID)
            {
                Serial.println("del and aID");
                int aID = alarmID;

                int status = AlarmControl.deleteAlarm(aID);
                if (status == 0)
                {
                    doneStatus = true;
                }
            }
        }
        if (doneStatus)
        {
            MqttControl.publishOnMqtt("setAlarm", "opsStats", msg);
            return;
        }
        MqttControl.publishOnMqtt("setAlarm", "opsStats", "{\"status\":\"Failed\"}");
        return;
    }

    if (toHandler == "enableAlarm")
    {
        bool doneStatus = false;

        for (JsonVariant v : myData)
        {
            // If enable is set in the query with alarm index number (aID), it will enable/disable the alarm[aID]
            // ----------------------------------------------
            int alarmId = v["aID"];
            int enable = v["enable"];
            if (v["enable"] == enable && v["aID"] == alarmId)
            {
                Serial.println("enable and aID");
                int aID = v["aID"];
                int status = AlarmControl.toggleEnableAlarm(aID);
                if (status == 0)
                {
                    doneStatus = true;
                }
            }
        }
        if (doneStatus)
        {
            MqttControl.publishOnMqtt("setAlarm", "opsStats", msg);
            return;
        }
        MqttControl.publishOnMqtt("setAlarm", "opsStats", "{\"status\":\"Failed\"}");
        return;
    }

    // This will return the pin names in the system memory...
    // ----------------------------------------------
    if (toHandler == "pinName")
    {
        bool isExecuted = false;
        String pinName = PinControl.pinName();
        DynamicJsonDocument docsPinName(4056);
        deserializeJson(docsPinName, pinName);
        JsonArray myPinNames = docsPinName["pinTheme"].as<JsonArray>();
        for (JsonVariant v : myPinNames)
        {
            isExecuted = true;
            MqttControl.publishOnMqtt("pinName", "opsStats", v);
        }
        if (!isExecuted)
        {
            MqttControl.publishOnMqtt("pinName", "opsStats", "{\"pinTheme\":[]}");
        }
        return;
    }

    // To delete the name of the given pin or terminal..
    // ----------------------------------------------
    if (toHandler == "pinNameDel")
    {
        for (JsonVariant v : myData)
        {
            int pinNo = v;
            PinControl.pinNameDel(pinNo);
        }
        MqttControl.publishOnMqtt("setAlarm", "opsStats", msg);
        return;
    }

    // This will set the name to the perticular pins..
    // ----------------------------------------------
    if (toHandler == "setPinName")
    {
        for (JsonVariant v : myData)
        {
            PinControl.pinName(v["no"], v["name"]);
        }
        MqttControl.publishOnMqtt("setPinName", "opsStats", msg);
        return;
    }

    // This will return the pin data of input pins and output pins...
    // ----------------------------------------------
    if (toHandler == "pinCount")
    {
        MqttControl.publishOnMqtt("pinCount", "opsStats", PinControl.pinData());
        return;
    }

    // This will return the boss pins in the system...
    // ----------------------------------------------
    if (toHandler == "pinBoss")
    {
        MqttControl.publishOnMqtt("pinBoss", "opsStats", PinControl.bossPin());
        return;
    }

    // This will retur the active pins in the system..
    // ----------------------------------------------
    if (toHandler == "pinActive")
    {
        MqttControl.publishOnMqtt("pinActive", "opsStats", PinControl.pinActive());
        return;
    }

    // This will set the pin relations
    // ----------------------------------------------
    if (toHandler == "pinRelSet")
    {
        for (JsonVariant v : myData)
        {
            size_t mySlaveSize = v["slave"].size();

            int mySlaveArr[5] = {};
            for (size_t i = 0; i < mySlaveSize; i++)
            {
                mySlaveArr[i] = v["slave"][i];
            }

            PinControl.pinRelation(v["boss"], v["bInUp"], v["bOn"], mySlaveArr, mySlaveSize, v["sOn"]);
        }
        MqttControl.publishOnMqtt("pinRelSet", "opsStats", msg);
        return;
    }

    // This will set return the pin relations info ...
    // ----------------------------------------------
    if (toHandler == "pinRelRead")
    {
        MqttControl.publishOnMqtt("pinRelRead", "opsStats", PinControl.pinRelation());
        return;
    }

    // This will delete the pin relation with given perticular pins..
    // ----------------------------------------------
    if (toHandler == "pinRelDel")
    {
        for (JsonVariant v : myData)
        {
            size_t pin = v;
            PinControl.pinRelationRemove(pin);
        }
        MqttControl.publishOnMqtt("pinRelDel", "opsStats", msg);
        return;
    }

    // This will handle the pin show array ..
    // ----------------------------------------------
    if (toHandler == "pinShow")
    {
        for (JsonVariant v : myData)
        {
            int pin = v["no"];
            int add = v["add"];

            if (add == 0)
            {
                if (PinControl.pinShowValidator(pin) == 1)
                {
                    PinControl.pinShowRemove(pin);
                    MqttControl.publishOnMqtt("pinShow", "opsStats", msg);
                }
            }
            if (add == 1)
            {
                if (PinControl.pinShowValidator(pin) != 1)
                {
                    PinControl.pinShow(pin);
                    MqttControl.publishOnMqtt("pinShow", "opsStats", msg);
                }
            }
        }
        MqttControl.publishOnMqtt("pinShow", "opsStats", PinControl.pinShow());
        return;
    }

    // This will returna the ip address of the clients on local
    // ----------------------------------------------
    if (toHandler == "ip")
    {
        const String s = "";
        String myJson = s + "{\"localIp\":\"" + WiFi.localIP().toString() + "\",\"apIp\":\"" + WiFi.softAPIP().toString() + "\"}";
        MqttControl.publishOnMqtt("ip", "opsStats", myJson);
        return;
    }
}
