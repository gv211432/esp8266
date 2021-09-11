// This function will load the previously saved time before reboot..
void loadPreviousRebootTime()
{
    String timeJson = readTheMemory("/time/time");
    DynamicJsonDocument docs(1024);
    DeserializationError err = deserializeJson(docs, timeJson);
    if (err)
    {
        Serial.println(err.c_str());
        return;
    }

    int h = docs["h"].as<int>();
    int m = docs["m"].as<int>();
    int s = docs["s"].as<int>();
    int d = docs["d"].as<int>();
    int M = docs["M"].as<int>();
    int y = docs["y"].as<int>();

    Serial.printf("hr: %d  min: %d sec: %d day:%d  month: %d year: %d", h, m, s, d, M, y);

    // Setting the previous boot time..
    setTime(h, m, s, d, M, y);
}

class Reboot
{
public:
    // This function will start reboot process..
    void RebootDevice()
    {
        prvTime = millis();
        toReboot = true;
    }

    // If any thing supposed to be fixed must be fixed in here before reboot..
    void DeviceWillReboot(unsigned long eveTime = 2000)
    {
        // It reboot is true get in the block..
        if (toReboot)
        {
            // writing the millis in the temp variable to
            // execute after condition is met
            unsigned long curTime = millis();
            if ((curTime - prvTime) >= eveTime)
            {
                // Creating a Object
                DynamicJsonDocument docs(1024);
                docs["h"] = hour();
                docs["m"] = minute();
                docs["s"] = second() + 2;
                docs["d"] = day();
                docs["M"] = month();
                docs["y"] = year();
                // Writing the JSON info to the memory for recovery in next boot
                writeToMemory("/time/time", docs.as<String>());
                Serial.println(docs.as<String>());
                // If mqtt client connected disconnect before reboot
                if (client.connected())
                {
                    client.disconnect();
                }
                // Actually restarting..
                delay(500);
                ESP.restart();
            }
        }
    }

private:
    bool toReboot = false;
    unsigned long prvTime = 0;
};
