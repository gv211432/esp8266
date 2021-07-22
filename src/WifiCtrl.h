// ================================= Wifi SETUP functions =============================
// ====================================================================================
// Following function contains all code for wifi setup and wifi webserver config
// ╻ ╻╻┏━╸╻   ┏━┓┏━╸╺┳╸╻ ╻┏━┓
// ┃╻┃┃┣╸ ┃   ┗━┓┣╸  ┃ ┃ ┃┣━┛
// ┗┻┛╹╹  ╹   ┗━┛┗━╸ ╹ ┗━┛╹
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸

#ifndef WifiCtrl_h
#define WifiCtrl_h

class WifiCtrl
{
public:
    void setWifi();
    void updateWifiSettings(String, String, String, String, String, String);
    // Returns the information of wifi in json format..
    String getWifiInfo();
    String getWifiInfoJson();
    // Returns the perticular given variable...
    String getTheWifiElement(String);
    int stringStrengthCheck(String &);
    void changeConnectionMode(String);
    int getWifiMode();

private:
    // All variabes for wifi
    // ----------------------------------------------
    const String s = "";
    String ssid;
    String ssidpw;
    String ap;
    String appw;
    String lock;
    String user;
    String __mode = "0"; // TODO mide it, its going to be chaneged..
};

// Returns the strongness of the string
// 0 = ultra strong, 1 = very strong, 2 = moderate, 3 = Low, 4 = Pass Failed
int WifiCtrl::stringStrengthCheck(String &input)
{
    size_t inputSize = input.length();
    if (inputSize < 6)
    {
        return 4;
    }

    // If size is considerabel then proceed
    bool isLower = false;
    bool isUpper = false;
    bool isDigit = false;
    bool isSpecial = false;

    for (size_t i = 0; i < inputSize; i++)
    {
        if (islower(input[i]))
        {
            isLower = true;
        }
        if (isupper(input[i]))
        {
            isUpper = true;
        }
        if (isdigit(input[i]))
        {
            isDigit = true;
        }
        if (input[i] ==
                '@' ||
            input[i] ==
                '#' ||
            input[i] ==
                '&' ||
            input[i] ==
                '%' ||
            input[i] ==
                '$' ||
            input[i] ==
                '!')
        {
            isSpecial = true;
        }
        if (input[i] == ' ')
        {
            return 4;
        }
    }
    if (isLower && isUpper && isDigit && isSpecial)
    {
        if (inputSize > 14)
        {
            // Ok for Access Point password and user password
            return 0;
        }
        if (inputSize > 9)
        {
            // Ok for Access Point password and user password
            return 1;
        }
        return 2;
    }
    if ((isLower && isSpecial) || (isUpper && isSpecial) || (isLower && isUpper))
    {
        if (inputSize > 16)
        {
            // Ok for Access Point password and user password
            return 2;
        }
        // Ok for the wifi name and user name
        return 3;
    }
    return 4;
}

// Reads the flash memory for the credentials and bring into the ram...
void WifiCtrl::setWifi()
{
    // Reading all the data in setup mode for performance
    // ----------------------------------------------
    LittleFS.begin();

    // Open the directory..
    Dir dir = LittleFS.openDir("/wifi");

    // Loop through all single files in the directory..
    while (dir.next())
    {
        String fName = dir.fileName(); // names like pinData, pinName, pinRel, pinShow, ..
        if (dir.fileSize())
        {
            File f = dir.openFile("r");
            String wifiInfo; //creating temperory string ...
            // loop through all the single character in the current file..
            while (f.available())
            {
                char alp = f.read();
                wifiInfo.concat(alp);
            }
            f.close();

            //conditionally copying to varalbles..
            // -----------------------------------------------
            if (fName == "ap")
            {
                ap = wifiInfo;
                continue;
            }
            if (fName == "app")
            {
                appw = wifiInfo;
                continue;
            }
            if (fName == "st")
            {
                ssid = wifiInfo;
                continue;
            }
            if (fName == "stp")
            {
                ssidpw = wifiInfo;
                continue;
            }
            if (fName == "lock")
            {
                lock = wifiInfo;
                continue;
            }
            if (fName == "user")
            {
                user = wifiInfo;
                continue;
            }
            if (fName == "mode")
            {
                // __mode = wifiInfo;
                // __mode = wifiInfo;
                continue;
            }
        }
    }

    // Unmounting file system
    // ----------------------------------------------
    LittleFS.end();

    String myObj = s + "{wifi:'" + ssid + "',wifipw:'" + ssidpw + "',ap:'" + ap + "',appw:'" + appw + "',lock:'" + lock + "',user:'" + user + "'}";

    // Printing on the serial monitor
    // -----------------------------------------------
    Serial.println(myObj);

    // Wifi Connection settings
    // -----------------------------------------------
    if (__mode.toInt() == 1)
    {
        // Start only the (STATION MODE) connect others wifi...
        WiFi.mode(WIFI_STA);
        if (WiFi.status() != WL_CONNECTED)
        {
            WiFi.begin(ssid, ssidpw);
        }
        return;
    }
    if (__mode.toInt() == 0)
    {
        // Start only the access point (THE HOTSPOT)
        WiFi.mode(WIFI_AP);
        WiFi.softAP(ap, appw);
        return;
    }

    // If no mode is defined start the both one!!
    // -----------------------------------------------
    WiFi.mode(WIFI_AP_STA);
    if (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin(ssid, ssidpw);
    }
    WiFi.softAP(ap, appw);
}

void WifiCtrl::updateWifiSettings(String wifiname, String wifipass, String hotname, String hotpass, String lockpass, String username)
{
    // Mounting file system to open desired files to check
    // ----------------------------------------------
    LittleFS.begin();

    // Cross Checking the settings before writing them
    // ----------------------------------------------
    bool check = false;
    if (ssid != wifiname && wifiname != "void" && wifiname != 0 && wifiname != " ")
    {
        writeToMemory("/wifi/st", wifiname);
        check = true;
    }
    if (ssidpw != wifipass && wifipass != "void" && wifipass != 0 && wifipass != " ")
    {
        writeToMemory("/wifi/stp", wifipass);
        check = true;
    }

    if (ap != hotname)
    {
        int gotCheck = stringStrengthCheck(hotname);
        if (gotCheck <= 3)
        {
            writeToMemory("/wifi/ap", hotname);
            check = true;
        }
    }
    if (appw != hotpass)
    {
        int gotCheck = stringStrengthCheck(hotpass);
        if (gotCheck <= 1)
        {
            writeToMemory("/wifi/app", hotpass);
            check = true;
        }
    }
    if (lock != lockpass)
    {
        int gotCheck = stringStrengthCheck(lockpass);
        if (gotCheck <= 1)
        {
            writeToMemory("/wifi/lock", lockpass);
            lock = lockpass;
        }
    }
    if (user != username)
    {
        int gotCheck = stringStrengthCheck(username);
        if (gotCheck <= 2)
        {
            writeToMemory("/wifi/user", username);
            user = username;
        }
    }

    // Unmounting the filesystem to prevent form curruption
    // ----------------------------------------------
    LittleFS.end();

    // Following code reboots the esp for conges to apply
    // ----------------------------------------------
    if (check)
    {
        delay(500);
        ESP.restart();
    }
}

// Returns the javascript object format wifi information to the caller..
String WifiCtrl::getWifiInfo()
{
    String myObj = s + "{wifi:\"" + ssid + "\",wifipw:\"" + ssidpw + "\",ap:\"" + ap + "\",appw:\"" + appw + "\",lock:\"" + lock + "\",user:\"" + user + "\"}";
    return myObj;
}
// Returns the json format wifi information to the caller..
String WifiCtrl::getWifiInfoJson()
{
    String myObj = s + "{\"wifi\":\"" + ssid + "\",\"wifipw\":\"" + ssidpw + "\",\"ap\":\"" + ap + "\",\"appw\":\"" + appw + "\",\"lock\":\"" + lock + "\",\"user\":\"" + user + "\"}";
    return myObj;
}

// Returns the given wifi settings element...
String WifiCtrl::getTheWifiElement(String asked = "void")
{
    if (asked == "ssid")
    {
        return ssid;
    }
    if (asked == "ssidpw")
    {
        return ssidpw;
    }
    if (asked == "ap")
    {
        return ap;
    }
    if (asked == "appw")
    {
        return appw;
    }
    if (asked == "user")
    {
        return user;
    }
    if (asked == "lock")
    {
        return lock;
    }
    if (asked == "mode")
    {
        return __mode;
    }
    return "void";
}

void WifiCtrl::changeConnectionMode(String mode = "void")
{
    if (mode != "void")
    {
        if (mode == "1" || mode == "2" || mode == "0")
        {
            writeToMemory("/wifi/mode", mode);
        }
    }
};

int WifiCtrl::getWifiMode()
{
    return __mode.toInt();
}

#endif