//This function write into the time...
int timeWriter(int s, int h, int m, int d, int M, int y)
{
    //This function is independent of any arduino program, JUST #include time.h
    if (s == -1 && h == -1 && m == -1 && d == -1 && M == -1 && y == -1)
    {
        return 1;
    }
    if (s >= 0 && s < 60)
    {
        s = second();
    }
    if (h >= 0 && h < 24)
    {
        h = hour();
    }
    if (m >= 0 && m < 60)
    {
        m = minute();
    }
    if (d > 0 && d < 32)
    {
        d = day();
    }
    if (M > 0 && M < 13)
    {
        M = month();
    }
    if (y > 2020 && y < 2060)
    {
        y = year();
    }
    setTime(h, m, s, d, M, y);

    // const String c = "";
    // String nowTime = c + hour() + " : " + minute() + " : " + second() + " : " + weekday() + " -- " + day() + "/" + month() + "/" + year() + " ";
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
