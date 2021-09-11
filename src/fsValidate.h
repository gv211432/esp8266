// If any path doesnot exist, then default values will be written over there
void fileSystemData()
{
    // File system must be mounted before calling the validatePath function...
    LittleFS.begin();

    validatePath("/alarm/alarm1");
    validatePath("/mqtt/ison", "1");
    validatePath("/mqtt/pass", "esphome");
    validatePath("/mqtt/port", "1883");
    validatePath("/mqtt/server", "15.206.246.196");
    validatePath("/mqtt/token", "tokenid");
    validatePath("/mqtt/user", "gaurav");
    validatePath("/time/time");

    DynamicJsonDocument docs(1024);
    JsonArray arr = docs["pinActive"].to<JsonArray>();
    String json = docs.as<String>();
    // Serial.println(json);
    validatePath("/pins/pinActive", json);

    // Clearing the previous data and writing new..
    docs.clear();
    arr = docs["allInPin"].to<JsonArray>();
    arr[0] = 4;
    arr[1] = 5;
    arr[2] = 12;
    arr[3] = 13;
    arr[4] = 14;

    arr = docs["allOutPin"].to<JsonArray>();
    arr[0] = 2;
    arr[1] = 4;
    arr[2] = 5;
    arr[3] = 12;
    arr[4] = 13;
    arr[5] = 14;

    json = docs.as<String>();
    // Serial.println(json);
    validatePath("/pins/pinData", json);

    // Clearing the previous data and writing new..
    docs.clear();
    arr = docs["pinTheme"].to<JsonArray>();
    json = docs.as<String>();
    // Serial.println(json);
    validatePath("/pins/pinName", json);

    // Clearing the previous data and writing new..
    docs.clear();
    arr = docs["pinRel"].to<JsonArray>();
    json = docs.as<String>();
    // Serial.println(json);
    validatePath("/pins/pinRel", json);

    // Clearing the previous data and writing new..
    docs.clear();
    arr = docs["pinShow"].to<JsonArray>();
    json = docs.as<String>();
    // Serial.println(json);
    validatePath("/pins/pinShow", json);

    // Clearing the previous data and writing new..
    docs.clear();
    arr = docs["pinStatKeep"].to<JsonArray>();
    json = docs.as<String>();
    // Serial.println(json);
    validatePath("/pins/pinStateKeep", json);

    // Clearing the previous data and writing new..
    docs.clear();
    docs["h"] = 12;
    docs["m"] = 0;
    docs["s"] = 0;
    docs["d"] = 1;
    docs["M"] = 9;
    docs["y"] = 2021;
    validatePath("/time/time", docs.as<String>());

    // Clearing the previous data and writing new..
    docs.clear();

    // Validating the wifi credentials..
    validatePath("/wifi/ap", "espHome");
    validatePath("/wifi/appw", "espHome");
    validatePath("/wifi/device", "espHome");
    validatePath("/wifi/lock", "espHome");
    validatePath("/wifi/mode", "2");
    validatePath("/wifi/st", "espHome");
    validatePath("/wifi/stp", "espHome");
    validatePath("/wifi/user", "espHome");

    // Unmounting file system
    LittleFS.end();
}