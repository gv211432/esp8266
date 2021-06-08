
// =================================== Server setup =================================
// ==================================================================================
// Following is the setup fonction for web server to start service
// ┏━┓┏━╸┏━┓╻ ╻┏━╸┏━┓   ┏━┓┏━╸╺┳╸╻ ╻┏━┓
// ┗━┓┣╸ ┣┳┛┃┏┛┣╸ ┣┳┛   ┗━┓┣╸  ┃ ┃ ┃┣━┛
// ┗━┛┗━╸╹┗╸┗┛ ┗━╸╹┗╸   ┗━┛┗━╸ ╹ ┗━┛╹
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸

// Function for writting into memory..
int alarmMemWriter(int myIndexer[18], int aID = -1)
{
    // ---------------------------------------------------------------------------------------------------------
    // {"free":0,"enable":0,"pin":50,"onHr":25,"onMin":61,"offHr":25,"offMin":61,"sun":0,"mon":0,
    // "tue":0,"wed":0,"thu":0,"fri":0,"sat":0,"oneShot":2,"day":32,"month":13,"year":0}
    // ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸
    // free,enable/disable,pinNo,onHr,onMin,offHr,offMin,sun,mon,tue,wed,thu,fri,sat,oneShot,day,month,year [18]
    //  0/1      1/0,        0,   0,    0,    0,    0,    0,  1,  1,  1,  1,  1,  0,  0/1/2,  32,   13,  0  [18]
    //   0        1          2    3      4     5    6     7   8   9   10  11  12  13   14     15    16   17 [18]
    // ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸

    if (myIndexer[0] < 0 || myIndexer[0] > 1)
    {
        myIndexer[0] = 1;
    }
    if (myIndexer[2] > 2)
    {
        return 1;
    }
    if (myIndexer[3] >= 24 && myIndexer[3] < 0)
    {
        myIndexer[3] = 25;
    }
    if (myIndexer[4] >= 60 && myIndexer[4] < 0)
    {
        myIndexer[4] = 0;
    }
    if (myIndexer[5] >= 24 && myIndexer[5] < 0)
    {
        myIndexer[5] = 25;
    }
    if (myIndexer[6] >= 60 && myIndexer[6] < 0)
    {
        myIndexer[6] = 0;
    }
    if (myIndexer[7] < 0 || myIndexer[7] > 1)
    {
        myIndexer[7] = 0;
    }
    if (myIndexer[8] < 0 || myIndexer[8] > 1)
    {
        myIndexer[8] = 0;
    }
    if (myIndexer[9] < 0 || myIndexer[9] > 1)
    {
        myIndexer[9] = 0;
    }
    if (myIndexer[10] < 0 || myIndexer[10] > 1)
    {
        myIndexer[10] = 0;
    }
    if (myIndexer[11] < 0 || myIndexer[11] > 1)
    {
        myIndexer[11] = 0;
    }
    if (myIndexer[12] < 0 || myIndexer[12] > 1)
    {
        myIndexer[12] = 0;
    }
    if (myIndexer[13] < 0 || myIndexer[13] > 1)
    {
        myIndexer[13] = 0;
    }
    if (myIndexer[14] < 0 || myIndexer[14] > 2)
    {
        myIndexer[14] = 2;
    }
    if (myIndexer[15] > 31 || myIndexer[15] < 1)
    {
        myIndexer[15] = day();
    }
    if (myIndexer[16] > 12 || myIndexer[16] < 1)
    {
        myIndexer[16] = month();
    }
    if (myIndexer[17] < year() || myIndexer[17] > 2060)
    {
        myIndexer[17] = year();
    }

    for (int i = 0; i <= 10; i++)
    {
        if (alarms[i][0] == 0) //if alarms[i][1]=0 means its free to use..
        {

            if (aID != -1)
            {
                i = aID;
            }

            if (i == 10)
            {
                //Shold only allow to 0-9 not more...
                return 1;
            }

            alarms[i][0] = 1;
            alarms[i][1] = myIndexer[1];
            alarms[i][2] = myIndexer[2];
            alarms[i][3] = myIndexer[3];
            alarms[i][4] = myIndexer[4];
            alarms[i][5] = myIndexer[5];
            alarms[i][6] = myIndexer[6];
            alarms[i][7] = myIndexer[7];
            alarms[i][8] = myIndexer[8];
            alarms[i][9] = myIndexer[9];
            alarms[i][10] = myIndexer[10];
            alarms[i][11] = myIndexer[11];
            alarms[i][12] = myIndexer[12];
            alarms[i][13] = myIndexer[13];
            alarms[i][14] = myIndexer[14];
            alarms[i][15] = myIndexer[15];
            alarms[i][16] = myIndexer[16];
            alarms[i][17] = myIndexer[17];

            String myAlarm = s + "{\"free\":" + 1 + ",\"enable\":" + alarms[i][1] + ",\"pin\":" + alarms[i][2] + ",\"onHr\":" + alarms[i][3] + ",\"onMin\":" + alarms[i][4] + ",\"offHr\":" + alarms[i][5] + ",\"offMin\":" + alarms[i][6] + ",\"sun\":" + alarms[i][7] + ",\"mon\":" + alarms[i][8] + ",\"tue\":" + alarms[i][9] + ",\"wed\":" + alarms[i][10] + ",\"thu\":" + alarms[i][11] + ",\"fri\":" + alarms[i][12] + ",\"sat\":" + alarms[i][13] + ",\"oneShot\":" + alarms[i][14] + ",\"day\":" + alarms[i][15] + ",\"month\":" + alarms[i][16] + ",\"year\":" + alarms[i][17] + "}";

            if (LittleFS.begin())
            {
                File wAlarm = LittleFS.open("/alarms/alarm" + String(i), "w");
                wAlarm.print(myAlarm);
                wAlarm.close();
                LittleFS.end();
                return 0;
            }
        }
    }
    return 0;
}

//This function write into the time...
int timeWriter(int s, int h, int m, int d, int M, int y)
{
    //This function is independent of any arduino program, JUST #include time.h
    if (s == -1 && h == -1 && m == -1 && d == -1 && M == -1 && y == -1)
    {
        return 1;
    }
    if (s == -1)
    {
        s = second();
    }
    if (h == -1)
    {
        h = hour();
    }
    if (m == -1)
    {
        m = minute();
    }
    if (d == -1)
    {
        d = day();
    }
    if (M == -1)
    {
        M = month();
    }
    if (y == -1)
    {
        y = year();
    }
    setTime(h, m, s, d, M, y);

    const String c = "";
    String nowTime = c + hour() + " : " + minute() + " : " + second() + " : " + weekday() + " -- " + day() + "/" + month() + "/" + year() + " ";
    Serial.println(nowTime);
    return 0;
}

void serverSetup()
{

    // Home of this server
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/html", home, processor); });

    //style css hosting
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/css", css); });

    // Listening on the path settings for wifi configuratios
    // ----------------------------------------------
    server.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  const char *http_username = user.c_str();
                  const char *http_password = lock.c_str();
                  if (!request->authenticate(http_username, http_password))
                  {
                      return request->requestAuthentication();
                  };

                  AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", index_html, processor);
                  response->addHeader("Server", "ESP Async Web Server");
                  request->send(response);
              });

    // Lisnening for any change on time..
    // ----------------------------------------------
    server.on("/settime", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  if (request->getParam("h") &&
                      request->getParam("m") &&
                      request->getParam("d") &&
                      request->getParam("M") &&
                      request->getParam("y") &&
                      request->getParam("s"))
                  {

                      int s = (request->getParam("s")->value()).toInt();
                      int h = (request->getParam("h")->value()).toInt();
                      int m = (request->getParam("m")->value()).toInt();
                      int d = (request->getParam("d")->value()).toInt();
                      int M = (request->getParam("M")->value()).toInt();
                      int y = (request->getParam("y")->value()).toInt();

                      int tSetStatus = timeWriter(s, h, m, d, M, y);

                      if (tSetStatus == 1)
                      {
                          request->send(200, "text/plain", "Not in proper format!!");
                          return;
                      }
                      request->send(200, "text/plain", "ok");
                      return;
                  }
                  request->send(200, "text/plain", "Not in proper format!!");
              });

    // API for giving the systems current time
    server.on("/gettime", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  AsyncWebServerResponse *response = request->beginResponse(200, "text/json", sendTime().c_str());
                  response->addHeader("Access-Control-Allow-Origin", "*");
                  response->addHeader("Server", "Vishwakarma home automation");
                  request->send(response);
              });

    // for alarm editing
    // ----------------------------------------------
    server.on("/alarm", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/html", alarmHome_html, processor); });

    server.on("/alarmjson", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  AsyncWebServerResponse *response = request->beginResponse(200, "text/json", sendAlarms().c_str());
                  response->addHeader("Access-Control-Allow-Origin", "*");
                  response->addHeader("Server", "Vishwakarma home automation");
                  request->send(response);
              });

    //Jquery hosting..
    server.on("/jquery.js", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  if (request->getParam("menu"))
                  {
                      request->send_P(200, "application/javascript", menuScript);
                      return;
                  }
                  request->send_P(200, "application/javascript", jquery);
              });

    // Listening for any alarm set up on this path..
    // ----------------------------------------------
    server.on("/setalarm", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  // Evaluate oneShot(0,1,2) and take decision
                  // ----------------------------------------------
                  if (request->getParam("shot"))
                  {
                      //Creating new arry and copying demoAlarm into it..
                      int myNewAlarm[18];
                      for (int i = 0; i < 18; i++)
                      {
                          myNewAlarm[i] = demoAlarm[i];
                      }

                      char a = 'b';

                      // ---------------------------------------------------------------------------------------------------------
                      // {"free":0,"enable":0,"pin":50,"onHr":25,"onMin":61,"offHr":25,"offMin":61,"sun":0,"mon":0,
                      // "tue":0,"wed":0,"thu":0,"fri":0,"sat":0,"oneShot":2,"day":32,"month":13,"year":0}
                      // ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸
                      // free,enable/disable,pinNo,onHr,onMin,offHr,offMin,sun,mon,tue,wed,thu,fri,sat,oneShot,day,month,year [18]
                      //  0/1      1/0,        0,   0,    0,    0,    0,    0,  1,  1,  1,  1,  1,  0,  0/1/2,  32,   13,  0  [18]
                      //   0        1          2    3      4     5    6     7   8   9   10  11  12  13   14     15    16   17 [18]
                      // ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸

                      request->getParam("enable") ? myNewAlarm[1] = (request->getParam("enable")->value()).toInt() : a = 'a';
                      request->getParam("pin") ? myNewAlarm[2] = (request->getParam("pin")->value()).toInt() : a = 'b';
                      request->getParam("onHr") ? myNewAlarm[3] = (request->getParam("onHr")->value()).toInt() : a = 'a';
                      request->getParam("onMin") ? myNewAlarm[4] = (request->getParam("onMin")->value()).toInt() : a = 'a';
                      request->getParam("offHr") ? myNewAlarm[5] = (request->getParam("offHr")->value()).toInt() : a = 'a';
                      request->getParam("offMin") ? myNewAlarm[6] = (request->getParam("offMin")->value()).toInt() : a = 'a';
                      request->getParam("sun") ? myNewAlarm[7] = (request->getParam("sun")->value()).toInt() : a = 'a';
                      request->getParam("mon") ? myNewAlarm[8] = (request->getParam("mon")->value()).toInt() : a = 'a';
                      request->getParam("tue") ? myNewAlarm[9] = (request->getParam("tue")->value()).toInt() : a = 'a';
                      request->getParam("wed") ? myNewAlarm[10] = (request->getParam("wed")->value()).toInt() : a = 'a';
                      request->getParam("thu") ? myNewAlarm[11] = (request->getParam("thu")->value()).toInt() : a = 'a';
                      request->getParam("fri") ? myNewAlarm[12] = (request->getParam("fri")->value()).toInt() : a = 'a';
                      request->getParam("sat") ? myNewAlarm[13] = (request->getParam("sat")->value()).toInt() : a = 'a';
                      request->getParam("shot") ? myNewAlarm[14] = (request->getParam("shot")->value()).toInt() : a = 'a';
                      request->getParam("day") ? myNewAlarm[15] = (request->getParam("day")->value()).toInt() : a = 'a';
                      request->getParam("month") ? myNewAlarm[16] = (request->getParam("month")->value()).toInt() : a = 'a';
                      request->getParam("year") ? myNewAlarm[17] = (request->getParam("year")->value()).toInt() : a = 'a';

                      int aID = -1;
                      if (request->getParam("aID"))
                      {
                          aID = (request->getParam("aID")->value()).toInt();
                      }

                      //Sending the generated Alarm array for checking and writing into memory
                      int gotStatus = alarmMemWriter(myNewAlarm, aID);

                      if (gotStatus == 1)
                      {
                          request->send(200, "text/plain", "Failed");
                          return;
                      }
                      request->send(200, "text/plain", "Done");
                      return;
                  }

                  // If del is set in the query with alarm index number (aID), it will delete the alarm[aID]
                  // ----------------------------------------------
                  if (request->getParam("del") && request->getParam("aID"))
                  {
                      int aID = (request->getParam("aID")->value()).toInt();

                      if (alarms[aID][0] == 1)
                      {
                          alarms[aID][0] = 0;

                          String myAlarm = s + "{\"free\":" + 0 + ",\"enable\":" + 0 + ",\"pin\":" + 50 + ",\"onHr\":" + 25 + ",\"onMin\":" + 61 + ",\"offHr\":" + 25 + ",\"offMin\":" + 61 + ",\"sun\":" + 0 + ",\"mon\":" + 0 + ",\"tue\":" + 0 + ",\"wed\":" + 0 + ",\"thu\":" + 0 + ",\"fri\":" + 0 + ",\"sat\":" + 0 + ",\"oneShot\":" + 2 + ",\"day\":" + 32 + ",\"month\":" + 13 + ",\"year\":" + 0 + "}";

                          if (LittleFS.begin())
                          {
                              File wAlarm = LittleFS.open("/alarms/alarm" + String(aID), "w");
                              wAlarm.print(myAlarm);
                              wAlarm.close();
                              LittleFS.end();
                          }

                          request->send(200, "text/plain", "deleted");
                          return;
                      }
                      request->send(200, "text/plain", "invalid");
                      return;
                  }

                  // If enable is set in the query with alarm index number (aID), it will enable/disable the alarm[aID]
                  // ----------------------------------------------
                  if (request->getParam("enable") && request->getParam("aID"))
                  {
                      int aID = (request->getParam("aID")->value()).toInt();
                      int ena = (request->getParam("enable")->value()).toInt();

                      // check enable parameter....
                      if (ena != 0)
                      {
                          if (ena != 1)
                          {
                              request->send(200, "text/plain", "invalid");
                              return;
                          }
                      }

                      //Check alarms[aId] free status
                      if (alarms[aID][0] == 1)
                      {
                          //If enable is not same as the previous one, update..
                          if (alarms[aID][1] != ena)
                          {
                              alarms[aID][1] = ena;
                              String myAlarm = s + "{\"free\":" + 1 + ",\"enable\":" + ena + ",\"pin\":" + alarms[aID][2] + ",\"onHr\":" + alarms[aID][3] + ",\"onMin\":" + alarms[aID][4] + ",\"offHr\":" + alarms[aID][5] + ",\"offMin\":" + alarms[aID][6] + ",\"sun\":" + alarms[aID][7] + ",\"mon\":" + alarms[aID][8] + ",\"tue\":" + alarms[aID][9] + ",\"wed\":" + alarms[aID][10] + ",\"thu\":" + alarms[aID][11] + ",\"fri\":" + alarms[aID][12] + ",\"sat\":" + alarms[aID][13] + ",\"oneShot\":" + alarms[aID][14] + ",\"day\":" + alarms[aID][15] + ",\"month\":" + alarms[aID][16] + ",\"year\":" + alarms[aID][17] + "}";
                              if (LittleFS.begin())
                              {
                                  File wAlarm = LittleFS.open("/alarms/alarm" + String(aID), "w");
                                  wAlarm.print(myAlarm);
                                  wAlarm.close();
                                  LittleFS.end();
                              }
                              request->send(200, "text/plain", "toggled");
                              return;
                          }
                      }
                      request->send(200, "text/plain", "invalid");
                      return;
                  }
              });

    // Listenigng on the path for changed settings to implement the same
    // ----------------------------------------------
    server.on("/changesettings", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  const char *http_username = user.c_str();
                  const char *http_password = lock.c_str();
                  if (!request->authenticate(http_username, http_password))
                  {
                      return request->requestAuthentication();
                  }

                  if (request->getParam("wifiname") &&
                      request->getParam("wifipass") &&
                      request->getParam("hotname") &&
                      request->getParam("hotpass") &&
                      request->getParam("lockpass") &&
                      request->getParam("user"))
                  {
                      String wifiname = request->getParam("wifiname")->value();
                      String wifipass = request->getParam("wifipass")->value();
                      String hotname = request->getParam("hotname")->value();
                      String hotpass = request->getParam("hotpass")->value();
                      String lockpass = request->getParam("lockpass")->value();
                      String username = request->getParam("user")->value();

                      request->send(200, "text/plain", "OK");

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
                  else
                  {
                      request->send(200, "text/plain", "Not in proper format!!");
                  }
              });

    server.on("/time", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/html", give_time, processor); });

    server.on("/pinName", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  AsyncWebServerResponse *response = request->beginResponse(200, "text/json", PinControl.pinName().c_str());
                  response->addHeader("Access-Control-Allow-Origin", "*");
                  response->addHeader("Server", "Vishwakarma home automation");
                  request->send(response);
              });

    server.on("/setPinName", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  //   Expecting for json string in headers with title setName.. as our input data form user..
                  if (request->getHeader("setName"))
                  {
                      String gotResJson = request->getHeader("setName")->value();
                      DynamicJsonDocument docOrg2(1024);
                      deserializeJson(docOrg2, gotResJson);
                      JsonArray myShowPin = docOrg2["pinTheme"].as<JsonArray>();

                      for (JsonVariant v : myShowPin)
                      {
                          PinControl.pinName(v["no"], v["name"]);
                      }

                      //   Sending "ok" as every thing is fine. It will hopefully reload users page..
                      request->send(200, "text/plain", "ok");
                      return;
                  }
                  request->send(200, "text/plain", "Not in proper format!!");
              });

    server.on("/terminalName", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/html", terminalName, processor); });

    server.on("/pinCount", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  AsyncWebServerResponse *response = request->beginResponse(200, "text/json", PinControl.pinData().c_str());
                  response->addHeader("Access-Control-Allow-Origin", "*");
                  response->addHeader("Server", "Vishwakarma home automation");
                  request->send(response);
              });

    server.on("/pinBoss", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  AsyncWebServerResponse *response = request->beginResponse(200, "text/json", PinControl.bossPin().c_str());
                  response->addHeader("Access-Control-Allow-Origin", "*");
                  response->addHeader("Server", "Vishwakarma home automation");
                  request->send(response);
              });

    // Returns the active pin present in the system..
    server.on("/pinActive", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  AsyncWebServerResponse *response = request->beginResponse(200, "text/json", PinControl.pinActive().c_str());
                  response->addHeader("Access-Control-Allow-Origin", "*");
                  response->addHeader("Server", "Vishwakarma home automation");
                  request->send(response);
              });

    // Handles the pin relation accordingly on this path..
    server.on("/pinRelation", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  if (request->getParam("read"))
                  {
                      AsyncWebServerResponse *response = request->beginResponse(200, "text/json", PinControl.pinRelation().c_str());
                      response->addHeader("Access-Control-Allow-Origin", "*");
                      response->addHeader("Server", "Vishwakarma home automation");
                      request->send(response);
                      return;
                  }
                  //   If recieved the parameter is get request..
                  if (request->getParam("pin"))
                  {
                      int pin = (request->getParam("pin")->value()).toInt();
                      PinControl.pinRelationRemove(pin);
                      request->send(200, "text/plain", "ok");
                      return;
                  }
                  //   Expecting for json string in headers with title setName.. as our input data form user..
                  if (request->getHeader("pinRel"))
                  {
                      String pinRelation = request->getHeader("pinRel")->value();
                      Serial.println(pinRelation);
                      DynamicJsonDocument pinRel(512);
                      deserializeJson(pinRel, pinRelation);
                      //   JsonObject pinRel = pinRel["pinRel"].as<JsonObject>();

                      size_t mySlaveSize = pinRel["slave"].size();

                      int mySlaveArr[5] = {};
                      for (size_t i = 0; i < mySlaveSize; i++)
                      {
                          mySlaveArr[i] = pinRel["slave"][i];
                      }

                      PinControl.pinRelation(pinRel["boss"], pinRel["bInUp"], pinRel["bOn"], mySlaveArr, mySlaveSize, pinRel["sOn"]);
                      request->send(200, "text/plain", "ok");
                      return;
                  }

                  request->send_P(200, "text/html", pin_relation, processor);
              });

    // Handles the swithing of the appliances on this path..
    server.on("/switch", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  //   Expecting for json string in headers with title setName.. as our input data form user..
                  if (request->getParam("pin") && request->getParam("to"))
                  {
                      int pin = (request->getParam("pin")->value()).toInt();
                      int to = (request->getParam("to")->value()).toInt();

                      if (PinControl.pinShowValidator(pin) == 1)
                      {
                          PinControl.toggleThePin(pin, to);
                      }

                      //   Sending "ok" as every thing is fine. It will hopefully reload users page..
                      request->send(200, "text/plain", "ok");
                      return;
                  }
                  request->send(200, "text/plain", "Not in proper format!!");
              });

    server.on("/pinShow", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  //   Expecting for json string in headers with title setName.. as our input data form user..
                  if (request->getParam("pin") && request->getParam("add"))
                  {
                      int pin = (request->getParam("pin")->value()).toInt();
                      int add = (request->getParam("add")->value()).toInt();

                      if (add == 0)
                      {
                          if (PinControl.pinShowValidator(pin) == 1)
                          {
                              PinControl.pinShowRemove(pin);
                              request->send(200, "text/plain", "ok");
                              return;
                          }
                      }
                      if (add == 1)
                      {
                          if (PinControl.pinShowValidator(pin) != 1)
                          {
                              PinControl.pinShow(pin);
                              request->send(200, "text/plain", "ok");
                              return;
                          }
                      }
                  }
                  request->send(200, "text/plain", "Not in proper format!!");
              });

    server.on("/ip", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  String myJson = s + "{\"localIp\":\"" + WiFi.localIP().toString() + "\",\"apIp\":\"" + WiFi.softAPIP().toString() + "\"}";
                  AsyncWebServerResponse *response = request->beginResponse(200, "text/json", myJson);
                  response->addHeader("Access-Control-Allow-Origin", "*");
                  response->addHeader("Server", "Vishwakarma home automation");
                  request->send(response);
              });

    server.on("/showTerminal", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/html", showTerminal, processor); });

    server.onNotFound(onNotFound);

    //  Web socket registration in the server function..
    ws.onEvent(onEvent);
    server.addHandler(&ws);

    // Starting the service of the EspAsyncLibrary
    // ----------------------------------------------
    server.begin();
}