// ╺┳╸╻┏┳┓┏━╸╻ ╻┏━┓╻╺┳╸┏━╸┏━┓
//  ┃ ┃┃┃┃┣╸ ┃╻┃┣┳┛┃ ┃ ┣╸ ┣┳┛
//  ╹ ╹╹ ╹┗━╸┗┻┛╹┗╸╹ ╹ ┗━╸╹┗╸

//This function write into the time...
//This function is independent of any arduino program, JUST #include time.h
// This function supports the selective or fractional time updates..
int timeWriter(int s = -1, int h = -1, int m = -1, int d = -1, int M = -1, int y = -1)
{
    // Serial.printf("hr: %d  min: %d sec: %d day:%d  month: %d year: %d", h, m, s, d, M, y);

    // If this function is called with out any argument please stop and return exit code 1
    if (s == -1 && h == -1 && m == -1 && d == -1 && M == -1 && y == -1)
    {
        return 1;
    }

    // If some of the arguments is not given then check for their default value and
    // ignore them by adding their current value
    // -------------------------------------------------------
    if (h >= 24 || h < 0)
    {
        h = hour();
    }
    if (m >= 60 || m < 0)
    {
        m = minute();
    }
    if (s >= 60 || s < 0)
    {
        s = second();
    }
    if (d > 32 || d < 0)
    {
        d = day();
    }
    if (M > 12 || M < 0)
    {
        M = month();
    }
    if (y > 2070 || y < 2021)
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
    String thisTime = s + "{\"hr\":\"" + hour() + "\",\"min\":\"" + minute() + "\",\"sec\":\"" + second() + "\",\"wDay\":\"" + weekday() + "\",\"day\":\"" + day() + "\",\"mon\":\"" + month() + "\",\"yr\":\"" + year() + "\"}";
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

// Give proper absolute path including "/" => Example "/myfile/path"
// If file not exist or no parameter given it returns ""
// File with name as "null" will not be read..
String readTheMemory(String filePath = "null")
{
    if (filePath == "null")
    {
        return "";
    }
    else
    {

        LittleFS.begin();
        if (LittleFS.exists(filePath))
        {
            File f = LittleFS.open(filePath, "r");
            String wifiInfo; //creating temperory string ...
            // loop through all the single character in the current file..
            while (f.available())
            {
                char alp = f.read();
                wifiInfo.concat(alp);
            }
            f.close();
            LittleFS.end();

            return wifiInfo;
        }
        else
        {
            return "";
        }
    }
}

// Returns the strongness of the string
// 0 = ultra strong, 1 = very strong, 2 = moderate, 3 = Low, 4 = Pass Failed
// ALways use comparision operators like (<=) or (>=) to compare the result..
int stringStrengthCheck(String &input)
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

// It cuts the given string from given position of string to the given position..
String cuttingString(String payload, size_t from = 0, size_t to = 0)
{
    String forReturn = "";
    size_t till = from + to;
    for (size_t i = from; i < till; i++)
    {
        forReturn.concat(payload[i]);
    }
    return forReturn;
}