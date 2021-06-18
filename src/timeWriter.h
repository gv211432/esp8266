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
    return 0;
}
// Returns the time in the string format..
String sendTime()
{
    const String s = "";
    String thisTime = s + "{ \"hr\" : \"" + hour() + "\", \"min\" : \"" + minute() + "\", \"sec\" : \"" + second() + "\", \"wDay\" : \"" + weekday() + "\", \"day\" : \"" + day() + "\", \"mon\" : \"" + month() + "\", \"yr\" : \"" + year() + "\"}";
    return thisTime;
}
