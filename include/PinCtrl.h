#ifndef PinCtrl_h
#define PinCtrl_h

// ====================================================================================
// Following is the Class for pin control..
// ┏━╸╻  ┏━┓┏━┓┏━┓   ┏━┓╻┏┓╻┏━╸╺┳╸┏━┓╻
// ┃  ┃  ┣━┫┗━┓┗━┓   ┣━┛┃┃┗┫┃   ┃ ┣┳┛┃
// ┗━╸┗━╸╹ ╹┗━┛┗━┛   ╹  ╹╹ ╹┗━╸ ╹ ╹┗╸┗━╸
// / ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸

class PinCtrl
{
public:
    PinCtrl();

    void printIt();

    //[first:pinType]->0:Input OR 1->Output, [second:pinNumber]
    String pinData(int, int, char);

    //[First:pinNumber], [second:pin Usage]->0:Input Or 1:Output Or 2: Both, [third:name for pin]
    String pinName(int, String);
    String pinNameDel(int);

    //[first:bossPin], [second:bossOnState]->0:Low or 1:High, [third:array of slaves]->pin Numbers,
    //  [fourth:turn Slave to State]->0:Low Or 1:High
    String pinRelation(int, int, int, int[], size_t, int);

    // Removes the relation of given boss pin with any other pins..
    //If no pin maches return 1;
    int pinRelationRemove(int);

    //Shows the pins in the webpage or mqtt for toggling..
    //If no param it returns the Json string of pinShow pins, if param given, it add it to string list..
    String pinShow(int);

    // return 1 if pin matches to the pinShow pin lists..
    int pinShowValidator(int);

    //Removes the given pin form the pinShow list..
    //If no pin maches return 1;
    int pinShowRemove(int);

    //Trackes the all active pins in it.. Any pin in use has to be present in it..
    //If no param it returns the Json string of active pins, if param given, it add it to string list..
    String pinActive(int);

    // return 1 if pin matches to the active pin lists..
    int pinActiveValidator(int);

    //Removes the given pin form the active list..
    //If no pin maches return 1;
    int pinActiveRemove(int);

    //Keeps the state of the changing pins
    //[first: PinNumber] [second: PinState]->0:Low 1:High
    String pinStatKeep(int, int);
    String pinStatKeepRemove(int);

    //toggles the given pin after validating the active and pin type must be OUTPUT friendly..
    int toggleThePin(int, int);

    // returns 0 means Low Or 1 means High..
    int getPinPowerStatus(int);

    //This must be called in loop for toggling of linked pins to its boss pin..
    void pinRelationConvertor();

    // This function gives the on and off status of the only changed pin if given argument is 'h'
    // Over loading this function for full pin numbers..
    String onOffStatusJson(char);

    // This function trackes the boss pins
    String bossPin();

private:
    // ----------------------------------------------
    String __pinData;
    String __pinName;
    String __pinRel;
    String __pinShow;
    String __pinStatKeep;
    String __pinActive;

    // ----------------------------------------------
    int pinReLboss[10] = {};
    int pinReLbInUp[10] = {};
    int pinReLbOn[10] = {};
    int pinReLsOn[10] = {};
    //Not used in project.. may be used in future or eliminated.. but occurs at some places
    // int pinReLcOunter[10] = {};
    int pinReLcHecker[10] = {};
    int pinReLslave[10][6] = {};
    size_t __sizeOfPinRel;
    void writingToStruct();

    // ----------------------------------------------
    int __pinActiveArr[30] = {};
    size_t __sizePinActiveArr;
    void writeToPinActiveArr();

    // ----------------------------------------------
    int __pinShowArr[20] = {};
    size_t __sizePinShowArr;
    void writeToPinShowArr();

    // Contains the information of pin power High or Low
    // ----------------------------------------------
    int __pinPowerMatrix[30] = {};
    int __pinPowerMatrixHistory[30] = {};
    void pinPowerOnStart();
    // Keeps __pinPowerMatrix upto date....
    void pinPowerTracker();

    int __pinOnOffHour[30] = {};
    int __pinOnOffMin[30] = {};
};

// ====================================================================================
// ┏━┓╻  ╻     ┏━╸╻ ╻┏┓╻┏━╸╺┳╸╻┏━┓┏┓╻   ╺┳┓┏━╸┏━╸╻┏┓╻╻╺┳╸╻┏━┓┏┓╻┏━┓
// ┣━┫┃  ┃     ┣╸ ┃ ┃┃┗┫┃   ┃ ┃┃ ┃┃┗┫    ┃┃┣╸ ┣╸ ┃┃┗┫┃ ┃ ┃┃ ┃┃┗┫┗━┓
// ╹ ╹┗━╸┗━╸   ╹  ┗━┛╹ ╹┗━╸ ╹ ╹┗━┛╹ ╹   ╺┻┛┗━╸╹  ╹╹ ╹╹ ╹ ╹┗━┛╹ ╹┗━┛
//  ╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸╺━╸

//Validates the given int variable as 0 or 1 and error for other values..
// ----------------------------------------------
String zeroOneValidator(int article)
{
    if (article != 0)
    {
        if (article != 1)
        {
            return "Error";
        }
    }
    return "Ok";
}

String PinCtrl::bossPin()
{
    DynamicJsonDocument docOrg(2048);
    deserializeJson(docOrg, __pinRel);
    JsonArray myArray = docOrg["pinRel"].as<JsonArray>();

    DynamicJsonDocument docOrg2(256);
    JsonArray myArray2 = docOrg2["bosspin"].to<JsonArray>();

    for (JsonVariant v : myArray)
    {
        myArray2.add(v["boss"]);
    }

    String toReturn = docOrg2.as<String>();
    return toReturn;
}

// Writes -1 to very single place of __pinPowerMatrix..
// ----------------------------------------------
void PinCtrl::pinPowerTracker()
{

    Serial.println("Pin power is initiated....");
    for (size_t i = 0; i < 30; i++)
    {
        __pinPowerMatrix[i] = -1;
        __pinPowerMatrixHistory[i] = -1;
    }

    for (size_t i = 0; i < __sizePinActiveArr; i++)
    {
        __pinPowerMatrix[__pinActiveArr[i]] = digitalRead(__pinActiveArr[i]);
        __pinPowerMatrixHistory[__pinActiveArr[i]] = digitalRead(__pinActiveArr[i]);
    }

    for (size_t i = 0; i < __sizePinShowArr; i++)
    {
        __pinPowerMatrix[__pinShowArr[i]] = digitalRead(__pinShowArr[i]);
        __pinPowerMatrixHistory[__pinShowArr[i]] = digitalRead(__pinShowArr[i]);
    }

    // String myString = "";
    // for (size_t i = 0; i < 30; i++)
    // {
    //     String data = " " + String(__pinPowerMatrix[i]);
    //     myString.concat(data);
    // }

    DynamicJsonDocument docOrg(512);
    deserializeJson(docOrg, __pinStatKeep);
    JsonArray myArray = docOrg["pinStatKeep"].as<JsonArray>();

    for (JsonVariant v : myArray)
    {
        int pinNo = v["no"];
        __pinPowerMatrix[pinNo] = v["is"];
        __pinPowerMatrixHistory[pinNo] = v["is"];
        pinMode(pinNo, OUTPUT);
        digitalWrite(pinNo, v["is"]);
    }

    // Serial.println(myString);
}

// Returns the status of the pin..
int PinCtrl::getPinPowerStatus(int pinNo = -1)
{
    if (pinNo != -1)
    {
        return __pinPowerMatrix[pinNo];
    }
    return -1;
}

// ----------------------------------------------
void PinCtrl::printIt()
{
    Serial.println("");
    Serial.println("");
    Serial.println(__pinActive);
    Serial.println(__pinData);
    Serial.println(__pinName);
    Serial.println(__pinRel);
    Serial.println(__pinShow);
    Serial.println(__pinStatKeep);
}

// A pin number can exist in both the lists Input and Output because this function measures
// the best pin for input or output..
// ----------------------------------------------
String PinCtrl::pinData(int pinType = -1, int pinNum = -1, char toPerform = 'z')
{
    if (toPerform == 'w')
    {
        //pinType 0 = Input 1= Output..
        if (pinType != -1 && pinNum != -1)
        {
            //Validating if pinType is only 0 OR 1..
            zeroOneValidator(pinType);

            DynamicJsonDocument docOrg(512);
            deserializeJson(docOrg, __pinData);
            String newPinData;

            if (pinType == 0)
            {
                JsonArray allInPinArr = docOrg["allInPin"].as<JsonArray>();
                allInPinArr[allInPinArr.size()] = pinNum;
                newPinData = docOrg.as<String>();
            }
            else if (pinType == 1)
            {
                JsonArray allOutPinArr = docOrg["allOutPin"].as<JsonArray>();
                allOutPinArr[allOutPinArr.size()] = pinNum;
                newPinData = docOrg.as<String>();
            }

            writeToMemory("/pins/pinData", newPinData);

            __pinData = newPinData;
            return newPinData;
        }
    }
    else if (toPerform == 'r')
    {
        //pinType 0 = Input 1= Output..
        if (pinType != -1 && pinNum != -1)
        {
            DynamicJsonDocument docOrg(512);
            deserializeJson(docOrg, __pinData);
            String newPinData;

            //Validating if pinType is only 0 OR 1..
            if (pinType == 0)
            {
                JsonArray allInPinArr = docOrg["allInPin"].as<JsonArray>();
                for (size_t i = 0; i < allInPinArr.size(); i++)
                {
                    if (allInPinArr[i] == pinNum)
                    {
                        return "Ok";
                    }
                }
            }
            else if (pinType == 1)
            {
                JsonArray allOutPinArr = docOrg["allOutPin"].as<JsonArray>();

                for (size_t i = 0; i < allOutPinArr.size(); i++)
                {
                    if (allOutPinArr[i] == pinNum)
                    {
                        return "Ok";
                    }
                }
            }
            return "Error";
        }
    }

    return __pinData;
}

// Sets the pin name for the given pin..
String PinCtrl::pinName(int pinNo = -1, String name = "__blank__")
{
    if (pinNo != -1 && name != "__blank__")
    {
        DynamicJsonDocument docOrg(2048);
        deserializeJson(docOrg, __pinName);
        JsonArray myPinName = docOrg["pinTheme"].as<JsonArray>();
        bool existOrNot = false;
        for (JsonVariant v : myPinName)
        {
            if (v["no"] == pinNo)
            {
                existOrNot = true;
                v["name"] = name;
                break;
            }
        }

        if (myPinName.size() == 0 || existOrNot == false)
        {
            int myPinSize = myPinName.size();
            myPinName[myPinSize]["no"] = pinNo;
            myPinName[myPinSize]["name"] = name;
        }

        String newPinName = docOrg.as<String>();

        writeToMemory("/pins/pinName", newPinName);

        __pinName = newPinName;
    }
    return __pinName;
}

String PinCtrl::pinNameDel(int pinNo = -1)
{
    if (pinNo != -1)
    {
        DynamicJsonDocument docOrg(2048);
        deserializeJson(docOrg, __pinName);
        JsonArray myPinName = docOrg["pinTheme"].as<JsonArray>();
        size_t myPinSize = myPinName.size();
        for (size_t i = 0; i < myPinSize; i++)
        {
            if (myPinName[i]["no"] == pinNo)
            {
                myPinName.remove(i);
                break;
            }
        }
        String newPinName = docOrg.as<String>();
        writeToMemory("/pins/pinName", newPinName);
        __pinName = newPinName;
        // TODO Please complete as you get time..
    }
    return __pinName;
}

// This function writes throughly the string pinRel Json in this struct for easy usage
// for pin state toggling..
// ----------------------------------------------
void PinCtrl::writingToStruct()
{
    //Successfully tested.. Please don't alter
    Serial.println("Writing to struct initiated..");
    DynamicJsonDocument docOrg(2048);
    deserializeJson(docOrg, __pinRel);
    JsonArray myArray = docOrg["pinRel"].as<JsonArray>();

    __sizeOfPinRel = myArray.size();

    for (size_t i = 0; i < __sizeOfPinRel; i++)
    {

        if (myArray[i]["slave"].size() < 6)
        {
            for (size_t j = 0; j < myArray[i]["slave"].size(); j++)
            {
                pinReLslave[i][j] = myArray[i]["slave"][j];
                pinMode(myArray[i]["slave"][j], OUTPUT);
                digitalWrite(myArray[i]["slave"][j], HIGH);
                Serial.println("Declaring output pins");
                Serial.println(pinReLslave[i][j]);
            }

            if (myArray[i]["slave"].size() < 5)
            {
                // We have 5 palces to store slaves pin no, if all palces is not occupied fill it by -1
                for (size_t j = myArray[i]["slave"].size(); j <= 5; j++)
                {
                    pinReLslave[i][j] = -1;
                }
            }
        }
        pinReLboss[i] = myArray[i]["boss"];
        pinReLbInUp[i] = myArray[i]["bInUp"];
        pinReLbOn[i] = myArray[i]["bOn"];
        pinReLsOn[i] = myArray[i]["sOn"];
        pinReLcHecker[i] = 1;

        if (myArray[i]["bInUp"] == 0)
        {
            Serial.println("Declaring Input pins  :  ");
            Serial.println(pinReLboss[i]);

            pinMode(myArray[i]["boss"], INPUT);
        }
        else if (myArray[i]["bInUp"] == 1)
        {
            Serial.println("Declaring Inpull__up pins  :  ");
            Serial.println(pinReLboss[i]);

            pinMode(myArray[i]["boss"], INPUT_PULLUP);
        }
    }
}

String PinCtrl::pinRelation(int boss = -1, int bInUp = -1, int bOn = -1, int slave[] = {}, size_t sizeOfSlave = 0, int sOn = -1)
{
    if (boss != -1 && bInUp != -1 && bOn != -1 && sizeOfSlave != 0 && sOn != -1)
    {

        zeroOneValidator(bOn);
        zeroOneValidator(sOn);
        size_t slaveSize = sizeOfSlave;

        Serial.println("Size of slave is : ");
        Serial.println(slaveSize);

        // 0 = INPUT boss = pinNo r = read/check if exist in InPin list
        if (pinData(0, boss, 'r') == "Error")
        {
            return "Error";
        };

        // 1 = OUTPUT slave = pinNo r = read/check if exist in outPin list
        for (size_t i = 0; i < slaveSize; i++)
        {
            // Check if slave pin is present in the good OUTPUT-PIN list of pinData..
            if (pinData(1, slave[i], 'r') == "Error")
            {
                return "Error";
            }

            // We should not let boss pin to be same as one of slaves..
            if (boss == slave[i])
            {
                return "Error";
            }

            // We Can not let any boss to become slave of other...
            for (size_t j = 0; j < __sizeOfPinRel; j++)
            {
                if (slave[i] == pinReLboss[j])
                {
                    return "Error";
                }
            }
        }

        if (pinActiveValidator(boss) == 1)
        {
            return "Error";
        }

        DynamicJsonDocument docOrg(2048);
        deserializeJson(docOrg, __pinRel);
        JsonArray myArray = docOrg["pinRel"].as<JsonArray>();
        String newPinRelation;

        size_t myPinSize = myArray.size();

        myArray[myPinSize]["boss"] = boss;
        myArray[myPinSize]["bInUp"] = bInUp;
        myArray[myPinSize]["bOn"] = bOn;
        for (size_t i = 0; i < slaveSize; i++)
        {
            myArray[myPinSize]["slave"][i] = slave[i];
        }
        myArray[myPinSize]["sOn"] = sOn;

        //Create new string using added element in the Json documant..
        newPinRelation = docOrg.as<String>();

        //Write this new string to memory for pin Relation recovery..
        writeToMemory("/pins/pinRel", newPinRelation);

        __pinRel = newPinRelation;

        //Write all the values again in the struct for Pinrelations..
        writingToStruct();

        pinActive(boss);
        for (size_t i = 0; i < slaveSize; i++)
        {
            pinActive(slave[i]);
        }

        pinPowerTracker();
    }

    return __pinRel;
}

// To remove all the relation with the given boss pin to all other pins..
// ----------------------------------------------
int PinCtrl::pinRelationRemove(int boss = -1)
{
    if (boss != -1)
    {
        int returnStatus = 1;
        DynamicJsonDocument docOrg(2048);
        deserializeJson(docOrg, __pinRel);
        JsonArray myArray = docOrg["pinRel"].as<JsonArray>();
        size_t myPinSize = myArray.size();

        String newPinRelation;

        for (size_t i = 0; i < myPinSize; i++)
        {
            if (myArray[i]["boss"] == boss)
            {

                pinActiveRemove(boss);
                for (size_t indx = 0; indx < myArray[i]["slave"].size(); indx++)
                {
                    Serial.println("Removing the slave for active list..");
                    pinActiveRemove(myArray[i]["slave"][indx]);
                }

                myArray.remove(i);
                returnStatus = 0;
                break;
            }
        }

        //Create new string using added element in the Json documant..
        newPinRelation = docOrg.as<String>();

        //Write this new string to memory for pin Relation recovery..
        writeToMemory("/pins/pinRel", newPinRelation);

        __pinRel = newPinRelation;

        //Write all the values again in the struct for Pin relations update..
        writingToStruct();

        pinPowerTracker();
        return returnStatus;
    }
    return 1;
}

//This function will write the string json of pin show to __pinShowArray for instant use..
// ----------------------------------------------
void PinCtrl::writeToPinShowArr()
{
    DynamicJsonDocument docOrg(512);
    deserializeJson(docOrg, __pinShow);
    JsonArray myArray = docOrg["pinShow"].as<JsonArray>();
    __sizePinShowArr = myArray.size();
    size_t i = 0;
    for (JsonVariant v : myArray)
    {
        __pinShowArr[i] = v;
        i++;
    }
}

//Validates the existance of pin in the Show pin List..
// If exsist returns 1 and not then 0..
int PinCtrl::pinShowValidator(int pinNo = -1)
{
    if (pinNo != -1)
    {
        for (size_t i = 0; i < __sizePinShowArr; i++)
        {
            if (__pinShowArr[i] == pinNo)
            {
                return 1;
            }
        }
    }
    return 0;
}

// Removes the showing pin on home of web server..
int PinCtrl::pinShowRemove(int pinNo = -1)
{
    if (pinNo != -1)
    {
        DynamicJsonDocument docOrg(512);
        deserializeJson(docOrg, __pinShow);
        JsonArray myArray = docOrg["pinShow"].as<JsonArray>();
        size_t myPinSize = myArray.size();

        for (size_t i = 0; i < myPinSize; i++)
        {
            if (myArray[i] == pinNo)
            {
                myArray.remove(i);
                break;
            }
        }

        __pinShow = docOrg.as<String>();

        writeToMemory("/pins/pinShow", __pinShow);

        writeToPinShowArr();
        return 0;
    }
    return 1;
}

//This function must be used for storing the number of pin to show on web or mqtt for toggling..
// ----------------------------------------------
String PinCtrl::pinShow(int pinNo = -1)
{
    if (pinNo != -1)
    {
        DynamicJsonDocument docOrg(512);
        deserializeJson(docOrg, __pinShow);
        JsonArray myArray = docOrg["pinShow"].as<JsonArray>();
        String newPinShow;

        if (pinShowValidator(pinNo) == 0)
        {
            int myPinSize = myArray.size();
            myArray[myPinSize] = pinNo;

            newPinShow = docOrg.as<String>();

            writeToMemory("/pins/pinShow", newPinShow);

            __pinShow = newPinShow;
            toggleThePin(pinNo, 1);
            writeToPinShowArr();
            return newPinShow;
        }
    }
    return __pinShow;
}

// This function will write the string json of active pins to __pinActiveArray for instant use..
// ----------------------------------------------
void PinCtrl::writeToPinActiveArr()
{
    DynamicJsonDocument docOrg(512);
    deserializeJson(docOrg, __pinActive);
    JsonArray myArray = docOrg["pinActive"].as<JsonArray>();
    __sizePinActiveArr = myArray.size();
    for (size_t i = 0; i < __sizePinActiveArr; i++)
    {
        __pinActiveArr[i] = myArray[i];
    }
}

//Validates the existance of pin the active pin List..
int PinCtrl::pinActiveValidator(int pinNo = -1)
{
    if (pinNo != -1)
    {
        for (size_t i = 0; i < __sizePinActiveArr; i++)
        {
            if (__pinActiveArr[i] == pinNo)
            {
                return 1;
            }
        }
    }
    return 0;
}

//This must be validated before operating on any pin because, it keeps pins in use or are active..
// Pins may repeat many and many times..
// ----------------------------------------------
String PinCtrl::pinActive(int pinNo = -1)
{
    if (pinNo != -1)
    {
        DynamicJsonDocument docOrg(512);
        deserializeJson(docOrg, __pinActive);
        JsonArray myArray = docOrg["pinActive"].as<JsonArray>();
        String newPinActive;

        int myPinSize = myArray.size();
        myArray[myPinSize] = pinNo;

        newPinActive = docOrg.as<String>();

        writeToMemory("/pins/pinActive", newPinActive);

        __pinActive = newPinActive;

        writeToPinActiveArr();
        return newPinActive;
    }
    return __pinActive;
}

// ----------------------------------------------
int PinCtrl::pinActiveRemove(int pinNo = -1)
{
    if (pinNo != -1)
    {
        int returnStatus = 1;
        DynamicJsonDocument docOrg(512);
        deserializeJson(docOrg, __pinActive);
        JsonArray myArray = docOrg["pinActive"].as<JsonArray>();
        String newPinActive;

        size_t myPinSize = myArray.size();

        for (size_t i = 0; i < myPinSize; i++)
        {
            if (myArray[i] == pinNo)
            {
                myArray.remove(i);
                returnStatus = 0;
                break;
            }
        }

        newPinActive = docOrg.as<String>();

        writeToMemory("/pins/pinActive", newPinActive);

        __pinActive = newPinActive;

        writeToPinActiveArr();
        return returnStatus;
    }
    return 1;
}

// This must be used for tracking status of any pin..
// ----------------------------------------------
String PinCtrl::pinStatKeep(int pinNo = -1, int state = -1)
{
    if (pinNo != -1 && state != -1)
    {
        DynamicJsonDocument docOrg(512);
        deserializeJson(docOrg, __pinStatKeep);
        JsonArray myArray = docOrg["pinStatKeep"].as<JsonArray>();

        int doOrNotRegister = 0;
        for (JsonVariant v : myArray)
        {
            if (v["no"] == pinNo)
            {
                v["is"] = state;
                break;
            }
            if (v["no"] != pinNo)
            {
                doOrNotRegister = 1;
                break;
            }
        }
        if (myArray.size() == 0 || doOrNotRegister == 1)
        {
            int myPinSize = myArray.size();
            myArray[myPinSize]["no"] = pinNo;
            myArray[myPinSize]["is"] = state;
        }

        String newPinStat = docOrg.as<String>();

        writeToMemory("/pins/pinStatKeep", newPinStat);

        __pinStatKeep = newPinStat;
        return newPinStat;
    }
    return __pinStatKeep;
}

String PinCtrl::pinStatKeepRemove(int pinNo = -1)
{
    if (pinNo != -1)
    {
        DynamicJsonDocument docOrg(512);
        deserializeJson(docOrg, __pinStatKeep);
        JsonArray myArray = docOrg["pinStatKeep"].as<JsonArray>();
        size_t myPinSize = myArray.size();
        for (size_t i = 0; i < myPinSize; i++)
        {
            if (myArray[i]["no"] == pinNo)
            {
                myArray.remove(i);
                break;
            }
        }
        String newPinStat = docOrg.as<String>();

        writeToMemory("/pins/pinStatKeep", newPinStat);

        __pinStatKeep = newPinStat;
        return newPinStat;
    }
    return __pinStatKeep;
}

// ----------------------------------------------
int PinCtrl::toggleThePin(int pinNo = -1, int state = -1)
{
    if (pinNo != -1 && state != -1)
    {
        if (zeroOneValidator(state) == "Error")
        {
            return 1;
        }

        DynamicJsonDocument docOrg2(512);
        deserializeJson(docOrg2, __pinShow);
        JsonArray myShowPin = docOrg2["pinShow"].as<JsonArray>();
        for (JsonVariant u : myShowPin)
        {
            if (u == pinNo)
            {
                DynamicJsonDocument docOrg(512);
                deserializeJson(docOrg, __pinData);
                JsonArray allOutPinArr = docOrg["allOutPin"].as<JsonArray>();

                for (JsonVariant v : allOutPinArr)
                {
                    if (v == pinNo)
                    {
                        pinMode(pinNo, OUTPUT);

                        if (digitalRead(pinNo) != state)
                        {
                            digitalWrite(pinNo, state);
                            __pinPowerMatrix[pinNo] = state;
                            __pinOnOffHour[pinNo] = hour();
                            __pinOnOffMin[pinNo] = minute();
                            pinStatKeep(pinNo, state);
                            return 0;
                        }
                        return 1;
                    }
                }
            }
        }
        return 0;
    }
    return 1;
}

// ----------------------------------------------
void PinCtrl::pinRelationConvertor()
{
    // Successfully tested please don't alter..
    for (size_t i = 0; i < __sizeOfPinRel; i++)
    {

        if (pinReLbOn[i] == 1)
        {
            if (digitalRead(pinReLboss[i]) == 1 && (pinReLcHecker[i] == 1))
            {
                // Serial.println("entered inside.... IF");

                for (size_t j = 0; j < 6; j++)
                {
                    if (pinReLslave[i][j] != -1)
                    {
                        if (pinReLsOn[i] == 1)
                        {
                            Serial.println("trying to high it : ");
                            Serial.println(pinReLslave[i][j]);
                            toggleThePin(pinReLslave[i][j], 1);
                        }
                        else
                        {
                            Serial.println("trying to Low it : ");
                            Serial.println(pinReLslave[i][j]);
                            toggleThePin(pinReLslave[i][j], 0);
                        }
                    }
                }
                pinReLcHecker[i]++;
                return;
            }
            else if (digitalRead(pinReLboss[i]) != 1 && (pinReLcHecker[i] == 2))
            {
                // Serial.println("entered inside.... ELSE");

                for (size_t j = 0; j < 6; j++)
                {
                    if (pinReLslave[i][j] != -1)
                    {
                        if (pinReLsOn[i] == 1)
                        {
                            Serial.println("trying to low it : ");
                            Serial.println(pinReLslave[i][j]);
                            toggleThePin(pinReLslave[i][j], 0);
                        }
                        else
                        {
                            Serial.println("trying to high it : ");
                            Serial.println(pinReLslave[i][j]);
                            toggleThePin(pinReLslave[i][j], 1);
                        }
                    }
                }
                pinReLcHecker[i]--;
            };
            return;
        }

        if (pinReLbOn[i] == 0)
        {
            if (digitalRead(pinReLboss[i]) != 1 && (pinReLcHecker[i] == 1))
            {

                for (size_t j = 0; j < 6; j++)
                {
                    if (pinReLslave[i][j] != -1)
                    {
                        if (pinReLsOn[i] == 1)
                        {
                            Serial.println("trying to high it : ");
                            Serial.println(pinReLslave[i][j]);
                            toggleThePin(pinReLslave[i][j], 1);
                        }
                        else
                        {
                            Serial.println("trying to low it : ");
                            Serial.println(pinReLslave[i][j]);
                            toggleThePin(pinReLslave[i][j], 0);
                        }
                    }
                }
                pinReLcHecker[i]++;
                return;
            }
            else if (digitalRead(pinReLboss[i]) == 1 && (pinReLcHecker[i] == 2))
            {
                // Serial.println("entered inside.... ELSE");

                for (size_t j = 0; j < 6; j++)
                {
                    if (pinReLslave[i][j] != -1)
                    {
                        if (pinReLsOn[i] == 1)
                        {
                            Serial.println("trying to low it : ");
                            Serial.println(pinReLslave[i][j]);
                            toggleThePin(pinReLslave[i][j], 0);
                        }
                        else
                        {
                            Serial.println("trying to high it : ");
                            Serial.println(pinReLslave[i][j]);
                            toggleThePin(pinReLslave[i][j], 1);
                        }
                    }
                }
                pinReLcHecker[i]--;
            };
            return;
        }
    }
}

String PinCtrl::onOffStatusJson(char isHalf = 'n')
{
    String forReturn = "";
    DynamicJsonDocument docOrg2(512);
    JsonArray myShowPin = docOrg2["pinOnOff"].to<JsonArray>();

    size_t myJ = 0;
    for (size_t i = 0; i < __sizePinShowArr; i++)
    {
        if (isHalf == 'h')
        {
            if (digitalRead(__pinShowArr[i]) == __pinPowerMatrixHistory[__pinShowArr[i]])
            {
                continue;
            }
            else
            {
                __pinPowerMatrixHistory[__pinShowArr[i]] = digitalRead(__pinShowArr[i]);
                myShowPin[myJ]["no"] = __pinShowArr[i];
                myShowPin[myJ]["is"] = __pinPowerMatrix[__pinShowArr[i]];
                myShowPin[myJ]["hr"] = __pinOnOffHour[__pinShowArr[i]];
                myShowPin[myJ]["min"] = __pinOnOffMin[__pinShowArr[i]];
                myJ++;
            }
        }
        else
        {
            myShowPin[i]["no"] = __pinShowArr[i];
            myShowPin[i]["is"] = __pinPowerMatrix[__pinShowArr[i]];
            myShowPin[i]["hr"] = __pinOnOffHour[__pinShowArr[i]];
            myShowPin[i]["min"] = __pinOnOffMin[__pinShowArr[i]];
        }
    }

    forReturn = docOrg2.as<String>();

    return forReturn;
}

//Main constructor function for this class...
//Anything in this function is call automatically as soon as this class is instantiated outside in main arduino script..
PinCtrl::PinCtrl()
{
    // Mount the fiel system..
    if (LittleFS.begin())
    {

        // DeserializationError err = deserializeJson(docNew, myModDoc);

        // if (LittleFS.exists("/pins/") == false)
        // {
        //     LittleFS.mkdir("/pins");
        // }
        // if (LittleFS.exists("/pins/pinData") == false)
        // {
        //     File myF = LittleFS.open("/pins/pinData", "w");
        //     myF.print("{\"allInPin\":[],\"allOutPin\":[]}");
        //     myF.close();
        // }

        // Open the directory..
        Dir dir = LittleFS.openDir("/pins");

        // Loop through all single files in the directory..
        while (dir.next())
        {
            String fName = dir.fileName(); // names like pinData, pinName, pinRel, pinShow, ..
            if (dir.fileSize())
            {
                File f = dir.openFile("r");
                String pinInfo; //creating temperory string ...
                // loop through all the single character in the current file..
                while (f.available())
                {
                    char alp = f.read();
                    pinInfo.concat(alp);
                }
                f.close();

                //conditionally copying to varalbles..
                if (fName == "pinData")
                {
                    __pinData = pinInfo;
                    continue;
                }
                if (fName == "pinName")
                {
                    __pinName = pinInfo;
                    // __pinName = "{\"pinTheme\":[]}";
                    continue;
                }
                if (fName == "pinRel")
                {
                    __pinRel = pinInfo;
                    // __pinRel = "{\"pinRel\":[]}";
                    continue;
                }
                if (fName == "pinShow")
                {
                    __pinShow = pinInfo;
                    // __pinShow = "{\"pinShow\":[]}";
                    continue;
                }
                if (fName == "pinStatKeep")
                {
                    __pinStatKeep = pinInfo;
                    continue;
                }
                if (fName == "pinActive")
                {
                    __pinActive = pinInfo;
                    // __pinActive = "{\"pinActive\":[]}";
                    continue;
                }
            }
        }
    }
    LittleFS.end();

    // Loading for instantly needed data into int arrays for quick access..
    writingToStruct();
    writeToPinActiveArr();
    writeToPinShowArr();
    pinPowerTracker();
}

#endif
