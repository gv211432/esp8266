
// ┏┳┓┏━┓╺┳╸╺┳╸┏━╸┏━┓╻  ╻  ┏┓ ┏━┓┏━╸╻┏
// ┃┃┃┃┓┃ ┃  ┃ ┃  ┣━┫┃  ┃  ┣┻┓┣━┫┃  ┣┻┓
// ╹ ╹┗┻┛ ╹  ╹ ┗━╸╹ ╹┗━╸┗━╸┗━┛╹ ╹┗━╸╹ ╹
// ----------------------------------------------
// This function handles the message on subscribed topic and generate response and result for the same
void mqttCallback(const char *topic, byte *payload, unsigned int length)
{
    const String msg = "{\"status\":\"ok\"}";

    // Signature of the received data is :
    // {"id":_any_random_number, "from":"_from_the_source_handler", "toHandler", "data":[{"key":"pair"},{"name":"payload"}....]}
    String theRecievedData;

    // Cottecting data in the string variable one by one!!!s
    for (size_t i = 0; i < length; i++)
    {
        theRecievedData.concat((char)payload[i]);
    }
    // Printing the received data for debugging..
    Serial.println(theRecievedData);

    DynamicJsonDocument docs(2056);
    DeserializationError err = deserializeJson(docs, theRecievedData);
    // If error found in the deserialize
    // DeserializationError::Ok
    // DeserializationError::EmptyInput
    // DeserializationError::IncompleteInput
    // DeserializationError::InvalidInput
    // DeserializationError::NoMemory
    // DeserializationError::NotSupported ⚠️ removed
    // DeserializationError::TooDeep
    // TODO Not tested if dose not work remove it
    if (err)
    {
        String e = err.c_str();
        MqttControl.publishOnMqtt("0000000001", "err", "err", "{\"err\":\"" + e + "\"}");
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(e);
        return;
    }
    // On Success it gets data in JSON Array
    JsonArray myData = docs["data"].as<JsonArray>();

    // again printing for debugging!!
    // Serial.println(docs.as<String>());

    String toHandler = docs["to"];
    String mqttCmdId = docs["id"];
    // Serial.println(toHandler);

    bool isAllState = false;

    // ----------------------------------------------
    if (toHandler == "allState")
    {
        isAllState = true;
    }

    // Signature: {""}
    // ----------------------------------------------
    if (toHandler == "pinState" || isAllState)
    {
        String getOnOffStatus = PinControl.onOffStatusJson(); // h means half...
        // Serial.println(getOnOffStatus);

        DynamicJsonDocument docsOther(3056);
        deserializeJson(docsOther, getOnOffStatus);
        JsonArray myDataOther = docsOther["pinOnOff"].as<JsonArray>();
        size_t myDataOtherSize = myDataOther.size();

        if (myDataOtherSize == 0)
        {
            MqttControl.publishOnMqtt(mqttCmdId, "pinState", "pinState", "{}");
        }

        // If pin status size is less or equal to 4 send it directly it will not crash the system...
        if (myDataOtherSize <= 4)
        {
            MqttControl.publishOnMqtt(mqttCmdId, "pinState", "pinState", getOnOffStatus);
        }

        // If size is greater than 4 then we can not send it directly the whole string(beyond size limit)
        // Send it in bunch of four it will not crash the system..
        // Followig code does the same..
        if (myDataOtherSize > 4)
        {
            DynamicJsonDocument docs2(2056);
            JsonArray myData2 = docs2["pinOnOff"].to<JsonArray>();

            for (size_t i = 0; i < myDataOtherSize; i++)
            {
                myData2[(i % 4)] = myDataOther[i];

                if (((i + 1) % 4) == 0)
                {
                    MqttControl.publishOnMqtt(mqttCmdId, "pinState", "pinState", docs2.as<String>());
                    myData2.remove(0);
                    myData2.remove(1);
                    myData2.remove(2);
                    myData2.remove(3);
                }
            }

            if ((myDataOtherSize % 4) != 0)
            {
                // size_t newIteratorSize = ((myDataOtherSize % 4));
                size_t newIteratorNum = (myDataOtherSize - (myDataOtherSize % 4));
                // printf("Printing the no : %d, and % d\n", newIteratorSize, newIteratorNum);

                for (size_t i = newIteratorNum; i < myDataOtherSize; i++)
                {
                    myData2[(i % 4)] = myDataOther[i];

                    // Because the very next iteration of the i will stop hence adding 1 to i in IF condition
                    if (myDataOtherSize == (i + 1))
                    {
                        MqttControl.publishOnMqtt(mqttCmdId, "pinState", "pinState", docs2.as<String>());
                        break;
                    }
                }
            }
        }
        if (!isAllState)
        {
            return;
        }
    }

    // for switching the buttons..
    // ----------------------------------------------
    if (toHandler == "btnSwitch")
    {
        for (JsonVariant v : myData)
        {
            int pin = v["no"];
            int to = v["is"];

            // Serial.println(pin);
            // Serial1.println(to);
            if (PinControl.pinShowValidator(pin) == 1)
            {
                PinControl.toggleThePin(pin, to);
                // String getOnOffStatus = PinControl.onOffStatusJson('h'); // h means half...
                // MqttControl.publishOnMqtt(mqttCmdId, "btnSwitch", "btnSwitch", getOnOffStatus);

                // No need to send the result or response
                // This will be automatically done by other function listening for changes in pins states..
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

            // This conditional checking will not let the undefined or empty or null values to
            // occupy the variables...
            // If any value is missing it will just ignore them and update the time with the
            // availabel values with is good for selective/fractional time update :)
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

            // Values with -1 will be ignored by the time update handler function.. named(timeWriter)
            int tSetStatus = timeWriter(sec, hr, min, myday, mymonth, myyear);
            if (tSetStatus == 0)
            {
                MqttControl.publishOnMqtt(mqttCmdId, "setTime", "setTime", sendTime());
            }
        }
        return;
    }

    // This will return the system time on mqtt...
    // ----------------------------------------------
    if (toHandler == "getTime" || isAllState)
    {
        String timeData = "{\"time\":[" + sendTime() + "]}";
        MqttControl.publishOnMqtt(mqttCmdId, "getTime", "getTime", timeData);
        if (!isAllState)
        {
            return;
        }
    }

    if (toHandler == "strength")
    {
        for (JsonVariant v : myData)
        {
            String anyStr = v;
            int gotCheck = stringStrengthCheck(anyStr);
            MqttControl.publishOnMqtt(mqttCmdId, "mq", "strength", String(gotCheck));
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

        MqttControl.publishOnMqtt(mqttCmdId, "setWifi", "setWifi", WifiControl.getWifiInfoJson());
        return;
    }

    // Changes the wifimode to given one in standard format
    // ----------------------------------------------
    if (toHandler == "wifiMode")
    {
        for (JsonVariant v : myData)
        {
            int to = v["to"];
            WifiControl.changeConnectionMode(to);
            MqttControl.publishOnMqtt(mqttCmdId, "wifiMode", "wifiMode", msg);
            // delay(500);
            // ESP.restart();
            // pls use reboot api to reboot after confirmation..
        }
        return;
    }
    // returns the wifi info to the other mqtt fellow subscriber..
    // ----------------------------------------------
    if (toHandler == "getWifi" || isAllState)
    {
        String wifiData = "{\"wifi\":[" + WifiControl.getWifiInfoJson() + "]}";
        MqttControl.publishOnMqtt(mqttCmdId, "getWifi", "getWifi", wifiData);
        if (!isAllState)
        {
            return;
        }
    }

    // data payload expected is : [{ "ask": "ssid" }, { "ask": "mode" },...]
    // The following handler will publish the required info of wifi settings..
    // ----------------------------------------------
    if (toHandler == "getWifiElement")
    {
        for (JsonVariant v : myData)
        {
            String element = v["ask"];
            String toSend = "{\"" + element + "\":\"" + WifiControl.getTheWifiElement(element) + "\"}";
            MqttControl.publishOnMqtt(mqttCmdId, "getWifi", "getWifi", toSend);
        }
    }

    // This will return the Json info of the alarms..
    // ----------------------------------------------
    if (toHandler == "alarmJson" || isAllState)
    {
        String getAlarm = AlarmControl.getAlarms();
        DynamicJsonDocument docsAlarm(3056);
        deserializeJson(docsAlarm, getAlarm);
        size_t sizeOfDoc = docsAlarm.size();

        for (size_t i = 0; i < sizeOfDoc; i++)
        {
            String alarmData = "{\"aID\":" + String(i) + ",\"alarm\":[" + docsAlarm["alarm" + String(i)].as<String>() + "]}";
            MqttControl.publishOnMqtt(mqttCmdId, "alarm", "alarmJson", alarmData);
            Serial.println(alarmData);
        }
        if (sizeOfDoc == 0)
        {
            MqttControl.publishOnMqtt(mqttCmdId, "alarm", "alarmJson", "{\"alarm\":\"[]\"}");
        }
        if (!isAllState)
        {
            return;
        }
    }

    if (toHandler == "aID" || isAllState)
    {
        MqttControl.publishOnMqtt(mqttCmdId, "aID", "aID", AlarmControl.activeAlarmId());

        if (!isAllState)
        {
            return;
        }
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
            int myShot = v["oneShot"];
            if (myShot == v["oneShot"])
            {
                Serial.println("this is Shot");

                //Creating new arry and copying demoAlarm into it..
                // demoAlarm is exported by AlarmCtrl.h
                // It is a standard signature/format for alarm arrays..
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
                    MqttControl.publishOnMqtt(mqttCmdId, "setAlarm", "setAlarm", "{\"status\":\"Failed\"}");
                    return;
                }
                MqttControl.publishOnMqtt(mqttCmdId, "setAlarm", "setAlarm", msg);
                return;
            }
            return;
        }
    }

    // Deletes the alarm of given alarm ID
    // ----------------------------------------------
    if (toHandler == "delAlarm")
    {
        bool doneStatus = false;
        for (JsonVariant v : myData)
        {
            // If del is set in the query with alarm index number (aID),
            //  it will delete the alarm[aID]
            // ----------------------------------------------
            int alarmID = v["aID"];
            int myDelete = v["del"];
            if (v["del"] == myDelete && v["aID"] == alarmID)
            {
                Serial.println("del and aID");
                // int aID = alarmID;

                int status = AlarmControl.deleteAlarm(alarmID);
                if (status == 0)
                {
                    doneStatus = true;
                }
            }
        }
        if (doneStatus)
        {
            MqttControl.publishOnMqtt(mqttCmdId, "setAlarm", "delAlarm", msg);
            return;
        }
        MqttControl.publishOnMqtt(mqttCmdId, "setAlarm", "delAlarm", "{\"status\":\"Failed\"}");
        return;
    }

    // this will enable or disable the alarm of given aId
    // ----------------------------------------------
    if (toHandler == "enableAlarm")
    {
        bool doneStatus = false;

        for (JsonVariant v : myData)
        {
            // If enable is set in the query with alarm index number (aID),
            // it will enable/disable the alarm[aID]
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
            MqttControl.publishOnMqtt(mqttCmdId, "setAlarm", "enableAlarm", msg);
            return;
        }
        MqttControl.publishOnMqtt(mqttCmdId, "setAlarm", "enableAlarm", "{\"status\":\"Failed\"}");
        return;
    }

    // This will return the pin names in the system memory...
    // ----------------------------------------------
    if (toHandler == "pinName" || isAllState)
    {
        String pinName = PinControl.pinName();
        DynamicJsonDocument docsOther(3056);
        deserializeJson(docsOther, pinName);

        JsonArray myDataOther = docsOther["pinTheme"].as<JsonArray>();
        size_t myDataOtherSize = myDataOther.size();

        // if (myDataOtherSize == 0)
        // {
        //     MqttControl.publishOnMqtt(mqttCmdId, "pinName", "pinName", "{\"pinTheme\":[]}");
        // }
        // If pin status size is less or equal to 4 send it directly it will not crash the system...
        if (myDataOtherSize <= 4 && myDataOtherSize > 0)
        {
            MqttControl.publishOnMqtt(mqttCmdId, "pinName", "pinName", pinName);
        }

        // If size is greater than 4 then we can not send it directly the whole string(beyond size limit)
        // Send it in bunch of four it will not crash the system..
        // Followig code does the same..
        if (myDataOtherSize > 4)
        {
            DynamicJsonDocument docs2(2056);
            JsonArray myData2 = docs2["pinTheme"].to<JsonArray>();

            for (size_t i = 0; i < myDataOtherSize; i++)
            {
                myData2[(i % 4)] = myDataOther[i];

                if (((i + 1) % 4) == 0)
                {
                    MqttControl.publishOnMqtt(mqttCmdId, "pinName", "pinName", docs2.as<String>());
                    myData2.remove(0);
                    myData2.remove(1);
                    myData2.remove(2);
                    myData2.remove(3);
                }
            }

            if ((myDataOtherSize % 4) != 0)
            {
                // size_t newIteratorSize = ((myDataOtherSize % 4));
                size_t newIteratorNum = (myDataOtherSize - (myDataOtherSize % 4));
                // printf("Printing the no : %d, and % d\n", newIteratorSize, newIteratorNum);

                for (size_t i = newIteratorNum; i < myDataOtherSize; i++)
                {
                    myData2[(i % 4)] = myDataOther[i];

                    // Because the very next iteration of the i will stop hence adding 1 to i in IF condition
                    if (myDataOtherSize == (i + 1))
                    {
                        MqttControl.publishOnMqtt(mqttCmdId, "pinName", "pinName", docs2.as<String>());
                        break;
                    }
                }
            }
        }
        if (!isAllState)
        {
            return;
        }
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
        MqttControl.publishOnMqtt(mqttCmdId, "setAlarm", "pinNameDel", msg);
        return;
    }

    // This will set the name to the perticular pins..
    // ----------------------------------------------
    if (toHandler == "setPinName")
    {
        for (JsonVariant v : myData)
        {
            int no = v["no"];
            if (no == v["no"])
            {

                PinControl.pinName(v["no"], v["name"]);
            }
        }
        MqttControl.publishOnMqtt(mqttCmdId, "setPinName", "setPinName", msg);
        return;
    }

    // This will return the pin data of input pins and output pins...
    // ----------------------------------------------
    if (toHandler == "pinCount" || isAllState)
    {
        MqttControl.publishOnMqtt(mqttCmdId, "pinCount", "pinCount", PinControl.pinData());
        if (!isAllState)
        {
            return;
        }
    }

    // This will return the boss pins in the system...
    // ----------------------------------------------
    if (toHandler == "pinBoss" || isAllState)
    {
        MqttControl.publishOnMqtt(mqttCmdId, "pinBoss", "pinBoss", PinControl.bossPin());
        if (!isAllState)
        {
            return;
        }
    }

    // This will retur the active pins in the system..
    // ----------------------------------------------
    if (toHandler == "pinActive" || isAllState)
    {
        MqttControl.publishOnMqtt(mqttCmdId, "pinActive", "pinActive", PinControl.pinActive());
        if (!isAllState)
        {
            return;
        }
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
        MqttControl.publishOnMqtt(mqttCmdId, "pinRelSet", "pinRelSet", msg);
        return;
    }

    // This will set return the pin relations info ...
    // ----------------------------------------------
    if (toHandler == "pinRelRead" || isAllState)
    {
        // MqttControl.publishOnMqtt(mqttCmdId, "pinRelRead", "pinRelRead", PinControl.pinRelation());

        String pinRelRead = PinControl.pinRelation();
        DynamicJsonDocument docsOther(3056);
        deserializeJson(docsOther, pinRelRead);

        JsonArray myDataOther = docsOther["pinRel"].as<JsonArray>();
        size_t myDataOtherSize = myDataOther.size();

        // if (myDataOtherSize == 0)
        // {
        //     MqttControl.publishOnMqtt(mqttCmdId, "pinRelRead", "pinRelRead", "{}");
        // }
        // If pin status size is less or equal to 4 send it directly it will not crash the system...
        if (myDataOtherSize <= 3)
        {
            MqttControl.publishOnMqtt(mqttCmdId, "pinRelRead", "pinRelRead", pinRelRead);
        }

        // If size is greater than 4 then we can not send it directly the whole string(beyond size limit)
        // Send it in bunch of four it will not crash the system..
        // Followig code does the same..
        if (myDataOtherSize > 3)
        {
            DynamicJsonDocument docs2(2056);
            JsonArray myData2 = docs2["pinRel"].to<JsonArray>();

            for (size_t i = 0; i < myDataOtherSize; i++)
            {
                myData2[(i % 3)] = myDataOther[i];

                if (((i + 1) % 3) == 0)
                {
                    MqttControl.publishOnMqtt(mqttCmdId, "pinRelRead", "pinRelRead", docs2.as<String>());
                    myData2.remove(0);
                    myData2.remove(1);
                    myData2.remove(2);
                }
            }

            if ((myDataOtherSize % 3) != 0)
            {
                // size_t newIteratorSize = ((myDataOtherSize % 3));
                size_t newIteratorNum = (myDataOtherSize - (myDataOtherSize % 3));
                // printf("Printing the no : %d, and % d\n", newIteratorSize, newIteratorNum);

                for (size_t i = newIteratorNum; i < myDataOtherSize; i++)
                {
                    myData2[(i % 3)] = myDataOther[i];

                    // Because the very next iteration of the i will stop hence adding 1 to i in IF condition
                    if (myDataOtherSize == (i + 1))
                    {
                        MqttControl.publishOnMqtt(mqttCmdId, "pinRelRead", "pinRelRead", docs2.as<String>());
                        break;
                    }
                }
            }
        }

        if (!isAllState)
        {
            return;
        }
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
        MqttControl.publishOnMqtt(mqttCmdId, "pinRelDel", "pinRelDel", msg);
        return;
    }

    // This will handle the pin show array ..
    // ----------------------------------------------
    if (toHandler == "pinShow" || isAllState)
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
                    MqttControl.publishOnMqtt(mqttCmdId, "pinShow", "pinShow", msg);
                }
            }
            if (add == 1)
            {
                if (PinControl.pinShowValidator(pin) != 1)
                {
                    PinControl.pinShow(pin);
                    MqttControl.publishOnMqtt(mqttCmdId, "pinShow", "pinShow", msg);
                }
            }
        }
        MqttControl.publishOnMqtt(mqttCmdId, "pinShow", "pinShow", PinControl.pinShow());
        if (!isAllState)
        {
            return;
        }
    }

    // This will returna the ip address of the clients on local
    // ----------------------------------------------
    if (toHandler == "ip" || isAllState)
    {
        String wifiIp = "";
        String apIp = "";
        const String s = "";
        if (WiFi.status() == WL_CONNECTED)
        {
            wifiIp = WiFi.localIP().toString();
        }
        if (WifiControl.getWifiMode() == 0 || WifiControl.getWifiMode() == 2)
        {
            apIp = WiFi.softAPIP().toString();
        }
        String myJson = s + "{\"ip\":[{\"localIp\":\"" + wifiIp + "\",\"apIp\":\"" + apIp + "\"}]}";
        MqttControl.publishOnMqtt(mqttCmdId, "ip", "ip", myJson);
        if (!isAllState)
        {
            return;
        }
    }

    // Scans the available wifi network in the vicinity
    // ----------------------------------------------
    if (toHandler == "scanWifi")
    {
        // TODO Contains error..
        // byte numSsid[] = WiFi.scanNetworks();
        // String mySsid = "" + String((char *)numSsid);
        // Serial.print("Number of available WiFi networks discovered:");
        // Serial.println(numSsid);
        // MqttControl.publishOnMqtt(mqttCmdId, "ip", "scanWifi", mySsid);
        // if (!isAllState)
        // {
        //     return;
        // }
    }

    // Publishes the the mqtt data on the outTopic
    // ----------------------------------------------
    if (toHandler == "getMqtt")
    {
        String mqttData = "{\"mqtt\":[" + MqttControl.getMqttData() + "]}";
        MqttControl.publishOnMqtt(mqttCmdId, "getMqtt", "getMqtt", mqttData);
    }

    // This sets the new mqtt configs after validation and supports fractional updates...
    // ----------------------------------------------
    if (toHandler == "setMqtt")
    {
        String user = "void";
        String pass = "void";
        String server = "void";
        String device = "void";

        for (JsonVariant v : myData)
        {
            String username = v["user"];
            String password = v["pass"];
            String serverIP = v["server"];
            String deviceID = v["token"];

            if (stringStrengthCheck(username) <= 2)
            {
                user = username;
            }
            if (stringStrengthCheck(password) <= 2)
            {
                pass = password;
            }
            if (stringStrengthCheck(serverIP) <= 4)
            {
                server = serverIP;
            }
            if (stringStrengthCheck(deviceID) <= 2)
            {
                device = deviceID;
            }
            MqttControl.setMqttData(server, user, pass, device);
            break;
        }
        if (!isAllState)
        {
            return;
        }
    }

    // This reads the given path and publish data on the outTopic
    // Mqtt works well wen length is 145 or less, more length might crash or no response..
    // ----------------------------------------------
    if (toHandler == "readPath")
    {
        for (JsonVariant v : myData)
        {
            String path = v["path"];
            String theData = readTheMemory(path);
            size_t length = theData.length();
            // Serial.println("Length of the data....");

            if (length > 170)
            {
                size_t index = 170;
                while (index < length)
                {
                    // Cutting the string to acceptable length to transfer on mqtt protocol...
                    String toSend = "{\"" + path + "\":\"" + cuttingString(theData, index - 170, 170) + "\"}";
                    MqttControl.publishOnMqtt(mqttCmdId, "readPath", "readPath", toSend);
                    // Serial.println(theData.substring(index, 170));
                    // Serial.println(cuttingString(theData, index - 170, 170));
                    // Serial.println(index);
                    index += 170;
                };

                if (length % 170 != 0)
                {
                    String toSend = "{\"" + path + "\":\"" + cuttingString(theData, index - 170, 170 + length - index) + "\"}";
                    MqttControl.publishOnMqtt(mqttCmdId, "readPath", "readPath", toSend);
                    // Serial.println("Final printing....");
                    // Serial.println(theData.substring(index - 170, length));
                    // Serial.println(cuttingString(theData, index - 170, 170 + length - index));
                    // Serial.println(index - 170);
                    // Serial.println(length);
                }
            }
            else
            {
                String toSend = "{\"" + path + "\":\"" + theData + "\"}";
                // Serial.println(toSend.length());
                MqttControl.publishOnMqtt(mqttCmdId, "readPath", "readPath", toSend);
            }
            return;
            //TODO there is data length limit of mqtt to publish please fix that..
        }
    }

    // This writes the given data to the given path..
    // ----------------------------------------------
    if (toHandler == "writePath")
    {
        for (JsonVariant v : myData)
        {
            String path = v["path"];
            String payload = v["data"];
            writeToMemory(path, payload);
            return;
            //TODO there is data length limit of mqtt to receive please fix that..
        }
        MqttControl.publishOnMqtt(mqttCmdId, "writePath", "writePath", msg);
    }

    // this handler resets this device instantly!!
    // ----------------------------------------------
    if (toHandler == "reboot")
    {
        // delay(1000);
        // ESP.restart();
        RebootDevice.RebootDevice();
    }
}
