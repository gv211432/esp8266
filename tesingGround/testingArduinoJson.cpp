#include "iostream"
#include "stdio.h"
#include "./ArduinoJson-v6.18.4.h"
#include "string.h"
using namespace std;

int main()
{
    DynamicJsonDocument docs1(1024);
    JsonArray arr = docs1["pinActive"].to<JsonArray>();
    // String json = docs2.as<String>();
    cout << docs1 << endl;

    docs1.clear();

    arr = docs1["allInPin"].to<JsonArray>();
    arr[0] = 1;
    arr[1] = 5;
    arr[2] = 12;
    arr[3] = 13;
    arr[4] = 14;

    arr = docs1["allOutPin"].to<JsonArray>();
    arr[0] = 1;
    arr[1] = 5;
    arr[2] = 17;
    arr[3] = 21;
    arr[4] = 22;

    cout << docs1 << endl;

    docs1.clear();

    arr = docs1["pinBoss"].to<JsonArray>();
    cout << docs1 << endl;

    // printf("%s", json);
    return 0;
}
