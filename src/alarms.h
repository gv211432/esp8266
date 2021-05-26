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

void alarmLoop(int alarmOne[18])
{
    if (alarmOne[0] == 1 && alarmOne[1] == 1)
    {
        if (alarmOne[14] == 2)
        {
            if (alarmOne[3] == hour() && alarmOne[4] == minute())
            {
                if (alarmOne[weekday() + 6] == 1)
                {
                    pinMode(alarmOne[2], OUTPUT);
                    digitalWrite(alarmOne[2], LOW);
                    return;
                }
            }
            if (alarmOne[5] == hour() && alarmOne[6] == minute())
            {
                if (alarmOne[weekday() + 6] == 1)
                {
                    Serial.println("Executed off job");
                    pinMode(alarmOne[2], OUTPUT);
                    digitalWrite(alarmOne[2], HIGH);
                    return;
                }
            }
        }

        if (alarmOne[14] == 0)
        {

            if (alarmOne[6] == minute() && alarmOne[5] == hour() && alarmOne[15] == day() && alarmOne[16] == month() && alarmOne[17] == year())
            {
                pinMode(alarmOne[2], OUTPUT);
                digitalWrite(alarmOne[2], HIGH);
                alarmOne[1] = 0;
                return;
            }
        }

        if (alarmOne[14] == 1)
        {

            if (alarmOne[4] == minute() && alarmOne[3] == hour() && alarmOne[15] == day() && alarmOne[16] == month() && alarmOne[17] == year())
            {
                pinMode(alarmOne[2], OUTPUT);
                digitalWrite(alarmOne[2], LOW);
                alarmOne[1] = 0;
                return;
            }
        }
    }
}

void startAlarm()
{
    for (int i = 0; i <= 9; i++)
    {
        alarmLoop(alarms[i]);
    }
}

// ================================Alarmrecover functions =============================
// ====================================================================================
// Following function reads from the saved copy of alarms and put them again in their
// respective int arrays...
// for unintended poweroff it is safeguard..
// ┏━┓╻  ┏━┓┏━┓┏┳┓  ┏━┓┏━╸┏━╸┏━┓╻ ╻┏━╸┏━┓
// ┣━┫┃  ┣━┫┣┳┛┃┃┃  ┣┳┛┣╸ ┃  ┃ ┃┃┏┛┣╸ ┣┳┛
// ╹ ╹┗━╸╹ ╹╹┗╸╹ ╹  ╹┗╸┗━╸┗━╸┗━┛┗┛ ┗━╸╹┗╸
// ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸
void alarmRecover()
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
                // Sparing 256 bytes for the same in the memory for my doc array..
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
}