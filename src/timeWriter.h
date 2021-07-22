//This function write into the time...
int timeWriter(int s = -1, int h = -1, int m = -1, int d = -1, int M = -1, int y = -1)
{
    // Serial.printf("hr: %d  min: %d sec: %d day:%d  month: %d year: %d", h, m, s, d, M, y);

    //This function is independent of any arduino program, JUST #include time.h
    if (s == -1 && h == -1 && m == -1 && d == -1 && M == -1 && y == -1)
    {
        return 1;
    }
    if (s >= 60 && s < 0)
    {
        s = second();
    }
    if (h >= 24 && h < 0)
    {
        h = hour();
    }
    if (m >= 60 && m < 0)
    {
        m = minute();
    }
    if (d > 32 && d < 0)
    {
        d = day();
    }
    if (M > 12 && M < 0)
    {
        M = month();
    }
    if (y > 2070 && y < 2021)
    {
        y = year();
    }
    setTime(h, m, s, d, M, y);

    // Serial.printf("hr: %d  min: %d sec: %d day:%d  month: %d year: %d", h, m, s, d, M, y);

    // const String c = "";
    // String nowTime = c + hour() + " : " + minute() + " : " + second() + " : " + weekday() + " -- " + day() + "/" + month() + "/" + year() + " ";
    // Serial.println(nowTime);
    return 0;
}
// Returns the time in the json string format..
String sendTime()
{
    const String s = "";
    String thisTime = s + "{ \"hr\" : \"" + hour() + "\", \"min\" : \"" + minute() + "\", \"sec\" : \"" + second() + "\", \"wDay\" : \"" + weekday() + "\", \"day\" : \"" + day() + "\", \"mon\" : \"" + month() + "\", \"yr\" : \"" + year() + "\"}";
    return thisTime;
}

// Caters the writing request to given path with payload in String format..
// ----------------------------------------------
void writeToMemory(String path, String payload)
{
    LittleFS.begin();
    File myF = LittleFS.open(path, "w");
    myF.print(payload);
    myF.close();
    LittleFS.end();
}
