// =================================== Variable Section =============================
// ==================================================================================
// ┏━┓╻  ╻     ╻ ╻┏━┓┏━┓╻┏━┓┏┓ ╻  ┏━╸┏━┓
// ┣━┫┃  ┃     ┃┏┛┣━┫┣┳┛┃┣━┫┣┻┓┃  ┣╸ ┗━┓
// ╹ ╹┗━╸┗━╸   ┗┛ ╹ ╹╹┗╸╹╹ ╹┗━┛┗━╸┗━╸┗━┛
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸

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

// All variables for alarms
// ----------------------------------------------
void startAlarm();
void alarmLoop(int alarmOne[18]);
void alarmRecover();

// ---------------------------------------------------------------------------------------------------------
// {"free":0,"enable":0,"pin":50,"onHr":25,"onMin":61,"offHr":25,"offMin":61,"sun":0,"mon":0,
// "tue":0,"wed":0,"thu":0,"fri":0,"sat":0,"oneShot":2,"day":32,"month":13,"year":0}
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸
// free,enable/disable,pinNo,onHr,onMin,offHr,offMin,sun,mon,tue,wed,thu,fri,sat,oneShot,day,month,year [18]
//  0/1      1/0,        0,   0,    0,    0,    0,    0,  1,  1,  1,  1,  1,  0,  0/1/2,  32,   13,  0  [18]
//   0        1          2    3      4     5    6     7   8   9   10  11  12  13   14     15    16   17 [18]
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸

int alarms[10][18] = {
    {0, 0, 50, 25, 61, 25, 61, 0, 0, 0, 0, 0, 0, 0, 2, 32, 13, 0},
    {0, 0, 50, 25, 61, 25, 61, 0, 0, 0, 0, 0, 0, 0, 2, 32, 13, 0},
    {0, 0, 50, 25, 61, 25, 61, 0, 0, 0, 0, 0, 0, 0, 2, 32, 13, 0},
    {0, 0, 50, 25, 61, 25, 61, 0, 0, 0, 0, 0, 0, 0, 2, 32, 13, 0},
    {0, 0, 50, 25, 61, 25, 61, 0, 0, 0, 0, 0, 0, 0, 2, 32, 13, 0},
    {0, 0, 50, 25, 61, 25, 61, 0, 0, 0, 0, 0, 0, 0, 2, 32, 13, 0},
    {0, 0, 50, 25, 61, 25, 61, 0, 0, 0, 0, 0, 0, 0, 2, 32, 13, 0},
    {0, 0, 50, 25, 61, 25, 61, 0, 0, 0, 0, 0, 0, 0, 2, 32, 13, 0},
    {0, 0, 50, 25, 61, 25, 61, 0, 0, 0, 0, 0, 0, 0, 2, 32, 13, 0},
    {0, 0, 50, 25, 61, 25, 61, 0, 0, 0, 0, 0, 0, 0, 2, 32, 13, 0}};

const int demoAlarm[18] = {0, 0, 50, 25, 61, 25, 61, 0, 0, 0, 0, 0, 0, 0, 2, 32, 13, 0};

#define LED 2 //Define blinking LED pin
#define SPIFFS LittleFS

unsigned long previouTime = 2000;
unsigned long eventTime = 30000;

// ============================ Initilizations ======================================
// ==================================================================================
// Following is server initialization
// ╻┏┓╻╻╺┳╸╻╻  ╻╺━┓┏━┓╺┳╸╻┏━┓┏┓╻┏━┓
// ┃┃┗┫┃ ┃ ┃┃  ┃┏━┛┣━┫ ┃ ┃┃ ┃┃┗┫┗━┓
// ╹╹ ╹╹ ╹ ╹┗━╸╹┗━╸╹ ╹ ╹ ╹┗━┛╹ ╹┗━┛
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Following function processes the output html going to be given to the web client.
// It replaces the templet word with specified one
// ----------------------------------------------
String processor(const String &var)
{
    String s = "";
    if (var == "OBJ")
    {
        String myObj = s + "{wifi:\"" + ssid + "\",wifipw:\"" + ssidpw + "\",ap:\"" + ap + "\",appw:\"" + appw + "\",lock:\"" + lock + "\",user:\"" + user + "\"}";
        return myObj;
    }
    if (var == "MENU")
    {
        return menu_html;
    }
    return s;
}

String sendAlarms()
{
    String thisAlarm = "{";
    for (int i = 0; i <= 9; i++)
    {
        String myAlarm = s + "\"alarm" + i + "\"" + ":" + "{\"free\":" + alarms[i][0] + ",\"enable\":" + alarms[i][1] + ",\"pin\":" + alarms[i][2] + ",\"onHr\":" + alarms[i][3] + ",\"onMin\":" + alarms[i][4] + ",\"offHr\":" + alarms[i][5] + ",\"offMin\":" + alarms[i][6] + ",\"sun\":" + alarms[i][7] + ",\"mon\":" + alarms[i][8] + ",\"tue\":" + alarms[i][9] + ",\"wed\":" + alarms[i][10] + ",\"thu\":" + alarms[i][11] + ",\"fri\":" + alarms[i][12] + ",\"sat\":" + alarms[i][13] + ",\"oneShot\":" + alarms[i][14] + ",\"day\":" + alarms[i][15] + ",\"month\":" + alarms[i][16] + ",\"year\":" + alarms[i][17] + "},";
        thisAlarm.concat(myAlarm);
    }
    String newString = thisAlarm.substring(0, thisAlarm.length() - 1);
    newString.concat("}");
    return newString;
}

String sendTime()
{
    String thisTime = s + "{ \"hr\" : \"" + hour() + "\", \"min\" : \"" + minute() + "\", \"sec\" : \"" + second() + "\", \"wDay\" : \"" + weekday() + "\", \"day\" : \"" + day() + "\", \"mon\" : \"" + month() + "\", \"yr\" : \"" + year() + "\"}";
    return thisTime;
}

void onNotFound(AsyncWebServerRequest *request)
{
    //Handle Unknown Request
    request->redirect("/");
}