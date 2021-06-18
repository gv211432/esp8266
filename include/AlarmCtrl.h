#ifndef AlarmCtrl_h
#define AlarmCtrl_h

// ================================AlarmLOOP functions ================================
// ====================================================================================
// Following function repetes all the alarms arrays..
// ┏━┓╻  ┏━┓┏━┓┏┳┓  ╻  ┏━┓┏━┓┏━┓
// ┣━┫┃  ┣━┫┣┳┛┃┃┃  ┃  ┃ ┃┃ ┃┣━┛
// ╹ ╹┗━╸╹ ╹╹┗╸╹ ╹  ┗━╸┗━┛┗━┛╹
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸

// ---------------------------------------------------------------------------------------------------------
// {"free":0,"enable":0,"pin":50,"onHr":25,"onMin":61,"offHr":25,"offMin":61,"sun":0,"mon":0,
// "tue":0,"wed":0,"thu":0,"fri":0,"sat":0,"oneShot":2,"day":32,"month":13,"year":0}
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸
// free,enable/disable,pinNo,onHr,onMin,offHr,offMin,sun,mon,tue,wed,thu,fri,sat,oneShot,day,month,year [18]
//  0/1      1/0,        0,   0,    0,    0,    0,    0,  1,  1,  1,  1,  1,  0,  0/1/2,  32,   13,  0  [18]
//   0        1          2    3      4     5    6     7   8   9   10  11  12  13   14     15    16   17 [18]
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸

class AlarmCtrl
{
public:
    // Constructor for this class..
    // Get called automatically when class is included in other file
    AlarmCtrl();

    // This must be used for recovery form reset and reboot ..
    void alarmRecover();

    // This must be called in loop for starting the alarm functionality...
    void startAlarm();

    // Returns the json string of the status of the alarms..
    String getAlarms();

    // Write into the working array of alarms the given array ..
    int alarmMemWriter(int[18], int);

    // Deletes the alarm for given alarm ID..
    int deleteAlarm(int);

    //If enable is not same as the previous one, update..
    int toggleEnableAlarm(int);

private:
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

    void alarmLoop(int[18]);
    const String s = "";
};

// ====================================================================================
// ┏━┓╻  ╻     ┏━╸╻ ╻┏┓╻┏━╸╺┳╸╻┏━┓┏┓╻   ╺┳┓┏━╸┏━╸╻┏┓╻╻╺┳╸╻┏━┓┏┓╻┏━┓
// ┣━┫┃  ┃     ┣╸ ┃ ┃┃┗┫┃   ┃ ┃┃ ┃┃┗┫    ┃┃┣╸ ┣╸ ┃┃┗┫┃ ┃ ┃┃ ┃┃┗┫┗━┓
// ╹ ╹┗━╸┗━╸   ╹  ┗━┛╹ ╹┗━╸ ╹ ╹┗━┛╹ ╹   ╺┻┛┗━╸╹  ╹╹ ╹╹ ╹ ╹┗━┛╹ ╹┗━┛
//  ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸

AlarmCtrl::AlarmCtrl() {}

void AlarmCtrl::alarmRecover()
{
    // Mount the fiel system..
    if (LittleFS.begin())
    {
        // Open the directory..
        Dir dir = LittleFS.openDir("/alarms");

        // Loop through all single files in the directory..
        while (dir.next())
        {
            String fName = dir.fileName(); // Alarms name are like => alarm0, alarm1, alarm2 ..
            char aNo = fName[5];           //will return number at this place = 0,1,2,3,4,5,6,7,8,9
            int aNoInt = int(aNo) - 48;    //ascii 0 => 48 so.. 48-48=0
            if (dir.fileSize())
            {
                File f = dir.openFile("r");
                String alarmJson;
                // loop through all the single character in the current file..
                while (f.available())
                {
                    char alp = f.read();
                    alarmJson.concat(alp);
                }
                f.close();

                // Creating json object of json text file..
                // Sparing 512 bytes for the same in the memory for my doc array..
                DynamicJsonDocument doc(512);
                // Assigning the same in doc array..
                // Values can be read using keys in the json file..
                deserializeJson(doc, alarmJson);

                // if alarm is not free (means occupied = 1)
                if (int(doc["free"]) == 1)
                {
                    alarms[aNoInt][0] = 1;
                    alarms[aNoInt][1] = int(doc["enable"]);
                    alarms[aNoInt][2] = int(doc["pin"]);
                    alarms[aNoInt][3] = int(doc["onHr"]);
                    alarms[aNoInt][4] = int(doc["onMin"]);
                    alarms[aNoInt][5] = int(doc["offHr"]);
                    alarms[aNoInt][6] = int(doc["offMin"]);
                    alarms[aNoInt][7] = int(doc["sun"]);
                    alarms[aNoInt][8] = int(doc["mon"]);
                    alarms[aNoInt][9] = int(doc["tue"]);
                    alarms[aNoInt][10] = int(doc["wed"]);
                    alarms[aNoInt][11] = int(doc["thu"]);
                    alarms[aNoInt][12] = int(doc["fri"]);
                    alarms[aNoInt][13] = int(doc["sat"]);
                    alarms[aNoInt][14] = int(doc["oneShot"]);
                    alarms[aNoInt][15] = int(doc["day"]);
                    alarms[aNoInt][16] = int(doc["month"]);
                    alarms[aNoInt][17] = int(doc["year"]);
                }
            }
        }
    }
    //Unmounting the file system..
    LittleFS.end();
}

void AlarmCtrl::startAlarm()
{
    for (int i = 0; i <= 9; i++)
    {
        alarmLoop(alarms[i]);
    }
}

String AlarmCtrl::getAlarms()
{
    String thisAlarm = "{";
    for (int i = 0; i <= 9; i++)
    {
        if (alarms[i][0] == 0)
        {
            continue;
        }
        String myAlarm = s + "\"alarm" + i + "\"" + ":" + "{\"free\":" + alarms[i][0] + ",\"enable\":" + alarms[i][1] + ",\"pin\":" + alarms[i][2] + ",\"onHr\":" + alarms[i][3] + ",\"onMin\":" + alarms[i][4] + ",\"offHr\":" + alarms[i][5] + ",\"offMin\":" + alarms[i][6] + ",\"sun\":" + alarms[i][7] + ",\"mon\":" + alarms[i][8] + ",\"tue\":" + alarms[i][9] + ",\"wed\":" + alarms[i][10] + ",\"thu\":" + alarms[i][11] + ",\"fri\":" + alarms[i][12] + ",\"sat\":" + alarms[i][13] + ",\"oneShot\":" + alarms[i][14] + ",\"day\":" + alarms[i][15] + ",\"month\":" + alarms[i][16] + ",\"year\":" + alarms[i][17] + "},";
        thisAlarm.concat(myAlarm);
    }
    String newString = thisAlarm.substring(0, thisAlarm.length() - 1);
    newString.concat("}");
    return newString;
}

void AlarmCtrl::alarmLoop(int alarmOne[18])
{
    if (alarmOne[0] == 1 && alarmOne[1] == 1)
    {
        // Switch on and off alarm in loop..
        if (alarmOne[14] == 2)
        {
            if (alarmOne[3] == hour() && alarmOne[4] == minute())
            {
                if (alarmOne[weekday() + 6] == 1)
                {
                    // pinMode(alarmOne[2], OUTPUT);
                    // digitalWrite(alarmOne[2], LOW);
                    PinControl.toggleThePin(alarmOne[2], 0);
                    return;
                }
            }
            if (alarmOne[5] == hour() && alarmOne[6] == minute())
            {
                if (alarmOne[weekday() + 6] == 1)
                {
                    // pinMode(alarmOne[2], OUTPUT);
                    // digitalWrite(alarmOne[2], HIGH);
                    PinControl.toggleThePin(alarmOne[2], 1);

                    return;
                }
            }
        }
        // Switch off alarm for once
        if (alarmOne[14] == 0)
        {

            if (alarmOne[6] == minute() && alarmOne[5] == hour() && alarmOne[15] == day() && alarmOne[16] == month() && alarmOne[17] == year())
            {
                // pinMode(alarmOne[2], OUTPUT);
                // digitalWrite(alarmOne[2], HIGH);
                PinControl.toggleThePin(alarmOne[2], 1);

                alarmOne[1] = 0;
                return;
            }
        }

        // Switch alarm for once
        if (alarmOne[14] == 1)
        {
            if (alarmOne[4] == minute() && alarmOne[3] == hour() && alarmOne[15] == day() && alarmOne[16] == month() && alarmOne[17] == year())
            {
                // pinMode(alarmOne[2], OUTPUT);
                // digitalWrite(alarmOne[2], LOW);
                PinControl.toggleThePin(alarmOne[2], 0);

                alarmOne[1] = 0;
                return;
            }
        }

        // Only switch off alarm in loop until stopted..
        if (alarmOne[14] == 3)
        {
            if (alarmOne[5] == hour() && alarmOne[6] == minute())
            {
                if (alarmOne[weekday() + 6] == 1)
                {
                    // pinMode(alarmOne[2], OUTPUT);
                    // digitalWrite(alarmOne[2], LOW);
                    PinControl.toggleThePin(alarmOne[2], 1);
                    return;
                }
            }
        }

        // Only switch ON alarm in loop until stopted..
        if (alarmOne[14] == 4)
        {

            if (alarmOne[3] == hour() && alarmOne[4] == minute())
            {
                if (alarmOne[weekday() + 6] == 1)
                {
                    // pinMode(alarmOne[2], OUTPUT);
                    // digitalWrite(alarmOne[2], LOW);
                    PinControl.toggleThePin(alarmOne[2], 0);
                    return;
                }
            }
        }
    }
}

// Function for writting into memory..
int AlarmCtrl::alarmMemWriter(int myIndexer[18], int aID = -1)
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
    if (myIndexer[1] > 2)
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
    if (myIndexer[14] < 0 || myIndexer[14] > 4)
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

    // Creating a prototype index for upcoming  Sub Routin...
    int i = 0;

    // If alarmId is given then
    if (aID != -1)
    {
        i = aID;
        goto alarmWriterSubRoutin;
    }

    // If alarmId is not give loop through the alarms and find the one and update..
    for (int myI = 0; myI < 10; myI++)
    {
        if (alarms[myI][0] == 0) //if alarms[i][1]=0 means its free to use..
        {
            i = myI;
            goto alarmWriterSubRoutin;
        }
    }

alarmWriterSubRoutin:
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
    return 0;
}

int AlarmCtrl::deleteAlarm(int alarmID = -1)
{
    if (alarmID > -1 && alarmID < 10)
    {
        if (alarms[alarmID][0] == 1)
        {
            alarms[alarmID][0] = 0;

            String myAlarm = s + "{\"free\":" + 0 + ",\"enable\":" + 0 + ",\"pin\":" + 50 + ",\"onHr\":" + 25 + ",\"onMin\":" + 61 + ",\"offHr\":" + 25 + ",\"offMin\":" + 61 + ",\"sun\":" + 0 + ",\"mon\":" + 0 + ",\"tue\":" + 0 + ",\"wed\":" + 0 + ",\"thu\":" + 0 + ",\"fri\":" + 0 + ",\"sat\":" + 0 + ",\"oneShot\":" + 2 + ",\"day\":" + 32 + ",\"month\":" + 13 + ",\"year\":" + 0 + "}";

            if (LittleFS.begin())
            {
                File wAlarm = LittleFS.open("/alarms/alarm" + String(alarmID), "w");
                wAlarm.print(myAlarm);
                wAlarm.close();
                LittleFS.end();
            }
        }
        return 0;
    }
    return 1;
}

int AlarmCtrl::toggleEnableAlarm(int aID = -1)
{
    if (aID > -1 && aID < 10)
    {
        //Check alarms[aId] free status
        if (alarms[aID][0] == 1)
        {
            if (alarms[aID][1] == 1)
            {
                alarms[aID][1] = 0;
                String myAlarm = s + "{\"free\":" + 1 + ",\"enable\":" + 0 + ",\"pin\":" + alarms[aID][2] + ",\"onHr\":" + alarms[aID][3] + ",\"onMin\":" + alarms[aID][4] + ",\"offHr\":" + alarms[aID][5] + ",\"offMin\":" + alarms[aID][6] + ",\"sun\":" + alarms[aID][7] + ",\"mon\":" + alarms[aID][8] + ",\"tue\":" + alarms[aID][9] + ",\"wed\":" + alarms[aID][10] + ",\"thu\":" + alarms[aID][11] + ",\"fri\":" + alarms[aID][12] + ",\"sat\":" + alarms[aID][13] + ",\"oneShot\":" + alarms[aID][14] + ",\"day\":" + alarms[aID][15] + ",\"month\":" + alarms[aID][16] + ",\"year\":" + alarms[aID][17] + "}";
                if (LittleFS.begin())
                {
                    File wAlarm = LittleFS.open("/alarms/alarm" + String(aID), "w");
                    wAlarm.print(myAlarm);
                    wAlarm.close();
                    LittleFS.end();
                }
                return 0;
            }

            if (alarms[aID][1] == 0)
            {
                alarms[aID][1] = 1;

                String myAlarm = s + "{\"free\":" + 1 + ",\"enable\":" + 1 + ",\"pin\":" + alarms[aID][2] + ",\"onHr\":" + alarms[aID][3] + ",\"onMin\":" + alarms[aID][4] + ",\"offHr\":" + alarms[aID][5] + ",\"offMin\":" + alarms[aID][6] + ",\"sun\":" + alarms[aID][7] + ",\"mon\":" + alarms[aID][8] + ",\"tue\":" + alarms[aID][9] + ",\"wed\":" + alarms[aID][10] + ",\"thu\":" + alarms[aID][11] + ",\"fri\":" + alarms[aID][12] + ",\"sat\":" + alarms[aID][13] + ",\"oneShot\":" + alarms[aID][14] + ",\"day\":" + alarms[aID][15] + ",\"month\":" + alarms[aID][16] + ",\"year\":" + alarms[aID][17] + "}";
                if (LittleFS.begin())
                {
                    File wAlarm = LittleFS.open("/alarms/alarm" + String(aID), "w");
                    wAlarm.print(myAlarm);
                    wAlarm.close();
                    LittleFS.end();
                }
                return 0;
            }
        }
    }
    return 1;
}

#endif
