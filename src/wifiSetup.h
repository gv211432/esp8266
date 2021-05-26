// ================================= Wifi SETUP functions =============================
// ====================================================================================
// Following function contains all code for wifi setup and wifi webserver config
// ╻ ╻╻┏━╸╻   ┏━┓┏━╸╺┳╸╻ ╻┏━┓
// ┃╻┃┃┣╸ ┃   ┗━┓┣╸  ┃ ┃ ┃┣━┛
// ┗┻┛╹╹  ╹   ┗━┛┗━╸ ╹ ┗━┛╹
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸
void setWifi()
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

    // Starting serial monitor service
    // ----------------------------------------------
    Serial.begin(9600);

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