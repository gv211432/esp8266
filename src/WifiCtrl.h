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
    String getWifiInfoJson();
    // Returns the perticular given variable...
    String getTheWifiElement(String);

private:
    // All variabes for wifi
    // ----------------------------------------------
    const String s = "";
    String ssid;
    // String *ptrssid = &ssid;
    String ssidpw;
    // String *ptrssidpw = &ssidpw;
    String ap;
    // String *ptrap = &ap;
    String appw;
    // String *ptrappw = &appw;
    String lock;
    // String *ptrlock;
    String user;
};

// Reads the flash memory for the credentials and bring into the ram...
void WifiCtrl::setWifi()
{
    // Reading all the data in setup mode for performance
    // ----------------------------------------------
    LittleFS.begin();

    // -----------------------------------------------
    File data1 = LittleFS.open("/wifi/st", "r");
    String getssid;
    while (data1.available())
    {
        char a = data1.read();
        getssid.concat(a);
    }
    data1.close();
    ssid = getssid;

    // -----------------------------------------------
    File data2 = LittleFS.open("/wifi/stp", "r");
    String getssidpw;
    while (data2.available())
    {
        char a = data2.read();
        getssidpw.concat(a);
    }
    data2.close();
    ssidpw = getssidpw;

    // ----------------------------------------------
    File data3 = LittleFS.open("/wifi/ap", "r");
    String getap;
    while (data3.available())
    {
        char a = data3.read();
        getap.concat(a);
    }
    data3.close();
    ap = getap;

    // -----------------------------------------------
    File data4 = LittleFS.open("/wifi/app", "r");
    String getappw;
    while (data4.available())
    {
        char a = data4.read();
        getappw.concat(a);
    }
    data4.close();
    appw = getappw;

    // -----------------------------------------------
    File data5 = LittleFS.open("/wifi/lock", "r");
    String getlock;
    while (data5.available())
    {
        char a = data5.read();
        getlock.concat(a);
    }
    data5.close();
    lock = getlock;

    // -----------------------------------------------
    File data6 = LittleFS.open("/wifi/user", "r");
    String getuser;
    while (data6.available())
    {
        char a = data6.read();
        getuser.concat(a);
    }
    data6.close();
    user = getuser;

    // Unmounting file system
    // ----------------------------------------------
    LittleFS.end();

    String myObj = s + "{wifi:'" + ssid + "',wifipw:'" + ssidpw + "',ap:'" + ap + "',appw:'" + appw + "',lock:'" + lock + "',user:'" + user + "'}";

    // Printing on the serial monitor
    // -----------------------------------------------
    Serial.println(myObj);

    // Wifi Connection settings
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
    char check = 'b';
    if (ssid != wifiname)
    {
        File data1 = LittleFS.open("/wifi/st", "w");
        data1.print(wifiname);
        data1.close();
        check = 'a';
    }
    if (ssidpw != wifipass)
    {
        File data1 = LittleFS.open("/wifi/stp", "w");
        data1.print(wifipass);
        data1.close();
        check = 'a';
    }

    if (ap != hotname)
    {
        File data1 = LittleFS.open("/wifi/ap", "w");
        data1.print(hotname);
        data1.close();
        check = 'a';
    }
    if (appw != hotpass)
    {
        File data1 = LittleFS.open("/wifi/app", "w");
        data1.print(hotpass);
        data1.close();
        check = 'a';
    }
    if (lock != lockpass)
    {
        File data1 = LittleFS.open("/wifi/lock", "w");
        data1.print(lockpass);
        data1.close();
        check = 'a';
    }
    if (user != username)
    {
        File data1 = LittleFS.open("/wifi/user", "w");
        data1.print(username);
        data1.close();
        check = 'a';
    }

    // Unmounting the filesystem to prevent form curruption
    // ----------------------------------------------
    LittleFS.end();

    // Following code reboots the esp for conges to apply
    // ----------------------------------------------
    if (check != 'b')
    {
        delay(500);
        ESP.restart();
    }
}

// Returns the json format wifi information to the caller..
String WifiCtrl::getWifiInfoJson()
{
    String myObj = s + "{wifi:\"" + ssid + "\",wifipw:\"" + ssidpw + "\",ap:\"" + ap + "\",appw:\"" + appw + "\",lock:\"" + lock + "\",user:\"" + user + "\"}";
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
    return "void";
}

#endif