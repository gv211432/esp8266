
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "ESPAsyncWebServer.h"
#include <ESPAsyncTCP.h>

#define MSG_BUFFER_SIZE (50)

const char *ssid = "GalaxyM30s";
const char *password = "9224410961";
const char *ap_ssid = "VishwakarmaHome2";
const char *ap_password = "9224410961";

const char *mqtt_server = "35.154.104.64";
// String deviceID(1234567890);
// char outTopic[MSG_BUFFER_SIZE];
// char inTopic[MSG_BUFFER_SIZE];

// every esp should containg different device id

// we will publish button status on outTopic
const char *outTopic = "1234567890/outTopic";
// we wiil read commands on inTopic
const char *inTopic = "1234567890/inTopic";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
char msg[MSG_BUFFER_SIZE];
char sendStatus[MSG_BUFFER_SIZE];

// Never try to send data to mqttserve when its not connected it will crash esp
// to send data mqttMode must be 1
// initilizing mqttMode
int mqttMode = 0;

int counter0 = 0;
int checker0 = 1;
int counter1 = 0;
int checker1 = 1;
int counter3 = 0;
int checker3 = 1;
int counter4 = 0;
int checker4 = 1;
int counter5 = 0;
int checker5 = 1;

// reChecks are litteraly status of the output pins, mind it!!
int reCheck0 = 0;
int reCheck1 = 0;
int reCheck3 = 0;
int reCheck4 = 0;
int reCheck5 = 0;

int Lstatus = 900000;

// Setting up wifi networks and never try to connect gaurav whenever its already connected

void setup_wifi()
{
    WiFi.mode(WIFI_AP_STA);

    if (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin(ssid, password);
        delay(1000);
    }

    WiFi.softAP(ap_ssid, ap_password);
    delay(1000);
}

void callback(char *topic, byte *payload, unsigned int length)
{

    if (mqttMode == 1)
    {
        if ((char)payload[0] == 'z')
        {
            // naming this process as numMetrix for this project
            Lstatus = 900000;
            if (reCheck1 == 1)
            {
                Lstatus += 10000;
            };
            if (reCheck0 == 1)
            {
                Lstatus += 1000;
            };
            if (reCheck3 == 1)
            {
                Lstatus += 100;
            };
            if (reCheck4 == 1)
            {
                Lstatus += 10;
            };
            if (reCheck5 == 1)
            {
                Lstatus += 1;
            };

            snprintf(sendStatus, MSG_BUFFER_SIZE, "%d", Lstatus);
            client.publish(outTopic, sendStatus);
            Lstatus = 900000;
        }
        else
        {
            if ((char)payload[0] == 'a')
            {
                if ((char)payload[1] == 'a')
                {
                    digitalWrite(16, HIGH);
                    // client.publish(outTopic, "aa");
                    reCheck1 = 1;
                }
                else
                {
                    if ((char)payload[1] == 'b')
                    {
                        digitalWrite(16, LOW);
                        // client.publish(outTopic, "ab");
                        reCheck1 = 0;
                    }
                    else
                    {
                        if ((char)payload[1] == 'c')
                        {
                            digitalWrite(0, HIGH);
                            // client.publish(outTopic, "ac");
                            reCheck0 = 1;
                        }
                        else
                        {
                            if ((char)payload[1] == 'd')
                            {
                                digitalWrite(0, LOW);
                                // client.publish(outTopic, "ad");
                                reCheck0 = 0;
                            }
                            else
                            {
                                if ((char)payload[1] == 'e')
                                {
                                    digitalWrite(14, HIGH);
                                    // client.publish(outTopic, "ae");
                                    reCheck3 = 1;
                                }
                                else
                                {
                                    if ((char)payload[1] == 'f')
                                    {
                                        digitalWrite(14, LOW);
                                        // client.publish(outTopic, "af");
                                        reCheck3 = 0;
                                    }
                                    else
                                    {
                                        if ((char)payload[1] == 'g')
                                        {
                                            digitalWrite(15, HIGH);
                                            // client.publish(outTopic, "ag");
                                            reCheck4 = 1;
                                        }
                                        else
                                        {
                                            if ((char)payload[1] == 'h')
                                            {
                                                digitalWrite(15, LOW);
                                                // client.publish(outTopic, "ah");
                                                reCheck4 = 0;
                                            }
                                            else
                                            {
                                                if ((char)payload[1] == 'i')
                                                {
                                                    digitalWrite(1, HIGH);
                                                    // client.publish(outTopic, "ai");
                                                    reCheck5 = 1;
                                                }
                                                else
                                                {
                                                    if ((char)payload[1] == 'j')
                                                    {
                                                        digitalWrite(1, LOW);
                                                        // client.publish(outTopic, "aj");
                                                        reCheck5 = 0;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if ((char)payload[0] == 'b')
            {
                // This is for range means fan
            }
            // Thia is added because we are not sending status in aplpha codes
            // we are sending in numMatrix mode
            Lstatus = 900000;
            if (reCheck1 == 1)
            {
                Lstatus += 10000;
            };
            if (reCheck0 == 1)
            {
                Lstatus += 1000;
            };
            if (reCheck3 == 1)
            {
                Lstatus += 100;
            };
            if (reCheck4 == 1)
            {
                Lstatus += 10;
            };
            if (reCheck5 == 1)
            {
                Lstatus += 1;
            };

            snprintf(sendStatus, MSG_BUFFER_SIZE, "%d", Lstatus);
            client.publish(outTopic, sendStatus);
            Lstatus = 900000;
        }
        Lstatus = 900000;
    }
}

AsyncWebServer server(80);
String readStatus()
{
    // this numMetrix for our dear offline server
    Lstatus = 900000;
    if (reCheck1 == 1)
    {
        Lstatus += 10000;
    };
    if (reCheck0 == 1)
    {
        Lstatus += 1000;
    };
    if (reCheck3 == 1)
    {
        Lstatus += 100;
    };
    if (reCheck4 == 1)
    {
        Lstatus += 10;
    };
    if (reCheck5 == 1)
    {
        Lstatus += 1;
    };
    return String(Lstatus);
    Lstatus = 900000;
}

String jsButton1()
{
    if (reCheck1 == 0)
    {
        digitalWrite(16, HIGH);
        if (mqttMode == 1)
        {
            client.publish(outTopic, "aa");
        }
        reCheck1 = 1;
    }
    else if (reCheck1 == 1)
    {
        digitalWrite(16, LOW);
        if (mqttMode == 1)
        {
            client.publish(outTopic, "ab");
        }
        reCheck1 = 0;
    };
    return String("ok");
}
String jsButton2()
{
    if (reCheck0 == 0)
    {
        digitalWrite(0, HIGH);
        if (mqttMode == 1)
        {
            client.publish(outTopic, "ac");
        }
        reCheck0 = 1;
    }
    else if (reCheck0 == 1)
    {
        digitalWrite(0, LOW);
        if (mqttMode == 1)
        {
            client.publish(outTopic, "ad");
        }
        reCheck0 = 0;
    };
    return String("ok");
}
String jsButton3()
{
    if (reCheck3 == 0)
    {
        digitalWrite(14, HIGH);
        if (mqttMode == 1)
        {
            client.publish(outTopic, "ae");
        }
        reCheck3 = 1;
    }
    else if (reCheck3 == 1)
    {
        digitalWrite(14, LOW);
        if (mqttMode == 1)
        {
            client.publish(outTopic, "af");
        }
        reCheck3 = 0;
    };
    return String("ok");
}
String jsButton4()
{
    if (reCheck4 == 0)
    {
        digitalWrite(15, HIGH);
        if (mqttMode == 1)
        {
            client.publish(outTopic, "ag");
        }
        reCheck4 = 1;
    }
    else if (reCheck4 == 1)
    {
        digitalWrite(15, LOW);
        if (mqttMode == 1)
        {
            client.publish(outTopic, "ah");
        }
        reCheck4 = 0;
    };
    return String("ok");
}
String jsButton5()
{
    if (reCheck5 == 0)
    {
        digitalWrite(1, HIGH);
        if (mqttMode == 1)
        {
            client.publish(outTopic, "ai");
        }
        reCheck5 = 1;
    }
    else if (reCheck5 == 1)
    {
        digitalWrite(1, LOW);
        if (mqttMode == 1)
        {
            client.publish(outTopic, "aj");
        }
        reCheck5 = 0;
    };
    return String("ok");
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<style>
    :root {
        --navbar-bg-color: hsl(0, 0%, 15%);
        --navbar-text-color: hsl(0, 0%, 85%);
        --navbar-text-color-focus: white;
        --navbar-bg-contrast: hsl(0, 0%, 25%);
    }

    * {
        box-sizing: border-box;
        margin: 0;
        padding: 0;
    }

    body {
        height: 100vh;
        font-family: Arial, Helvetica, sans-serif;
        line-height: 1.6;
        background-color: rgb(30, 43, 54);
        overflow-y: auto;
    }

    * {
        margin: 0;
        padding: 0;
        box-sizing: border-box;
    }

    /* html,
    body {
        height: 100%;
    }

    body {
        display: grid;
        place-items: center;
        background: #dde1e7;
        text-align: center;
    } */

    .clock {
        position: relative;
        display: flex;
        margin-left: auto;
        margin-right: auto;
        align-items: center;
        justify-content: center;
        background: #dde1e7;
        height: 250px;
        width: 250px;
        border-radius: 50%;
        box-shadow: -3px -3px 7px #f8f8f854,
            3px 3px 7px rgba(0, 0, 0, 0.356);
    }

    .clock:before {
        position: absolute;
        content: '';
        height: 220px;
        width: 220px;
        background: #dde1e7;
        border-radius: 50%;
        box-shadow: inset -3px -3px 7px #ffffff73,
            inset 3px 3px 5px rgba(94, 104, 121, 0.288);
    }

    .clock:after {
        position: absolute;
        content: '';
        height: 120px;
        width: 120px;
        background: #dde1e7;
        border-radius: 50%;
        box-shadow: -1px -1px 5px #ffffff73,
            1px 1px 3px rgba(94, 104, 121, 0.288);
    }

    .clock .center-nut {
        height: 15px;
        width: 15px;
        background: #404040;
        border-radius: 50%;
        z-index: 2;
        position: absolute;
    }

    .clock .center-nut2 {
        height: 9px;
        width: 9px;
        background: #3498db;
        border-radius: 50%;
        z-index: 15;
        position: absolute;
    }

    .indicators div {
        position: absolute;
        width: 2px;
        height: 5px;
        background: #404040;
    }

    .indicators div:nth-child(1) {
        transform: rotate(30deg) translateY(-100px);
    }

    .indicators div:nth-child(2) {
        transform: rotate(60deg) translateY(-100px);
    }

    .indicators div:nth-child(3) {
        background: #3498db;
        transform: rotate(90deg) translateY(-100px);
    }

    .indicators div:nth-child(4) {
        transform: rotate(120deg) translateY(-100px);
    }

    .indicators div:nth-child(5) {
        transform: rotate(150deg) translateY(-100px);
    }

    .indicators div:nth-child(6) {
        background: #3498db;
        transform: rotate(180deg) translateY(-100px);
    }

    .indicators div:nth-child(7) {
        transform: rotate(210deg) translateY(-100px);
    }

    .indicators div:nth-child(8) {
        transform: rotate(240deg) translateY(-100px);
    }

    .indicators div:nth-child(9) {
        background: #3498db;
        transform: rotate(270deg) translateY(-100px);
    }

    .indicators div:nth-child(10) {
        transform: rotate(300deg) translateY(-100px);
    }

    .indicators div:nth-child(11) {
        transform: rotate(330deg) translateY(-100px);
    }

    .indicators div:nth-child(12) {
        background: #3498db;
        transform: rotate(360deg) translateY(-100px);
    }

    .sec-hand,
    .min-hand,
    .hr-hand {
        position: absolute;
    }

    .sec-hand,
    .sec {
        height: 180px;
        width: 180px;
        z-index: 6;
    }

    .min-hand,
    .min {
        height: 140px;
        width: 140px;
        z-index: 5;
    }

    .hr-hand,
    .hr {
        height: 110px;
        width: 110px;
        z-index: 4;
    }

    .sec,
    .min,
    .hr {
        display: flex;
        justify-content: center;
        position: absolute;
    }

    .sec:before {
        position: absolute;
        content: '';
        height: 110px;
        width: 3px;
        background: #3498db;
    }

    .sec:after {
        position: absolute;
        content: '';
        height: 35px;
        width: 7px;
        background: #3498db;
        top: 105px;
        border-radius: 5px;
    }

    .min:before {
        position: absolute;
        content: '';
        width: 1px;
        top: -15px;
        border-left: 3px solid transparent;
        border-right: 3px solid transparent;
        border-bottom: 60px solid #e95949;
    }

    .min:after {
        position: absolute;
        content: '';
        width: 3px;
        top: 40px;
        border-left: 2px solid transparent;
        border-right: 2px solid transparent;
        border-top: 30px solid #e95949;
    }

    .hr:before {
        position: absolute;
        content: '';
        width: 1px;
        border-left: 3px solid transparent;
        border-right: 3px solid transparent;
        border-bottom: 35px solid #303030;
    }

    .hr:after {
        position: absolute;
        content: '';
        width: 3px;
        top: 34px;
        border-left: 2px solid transparent;
        border-right: 2px solid transparent;
        border-top: 25px solid #303030;
    }


    .container {
        max-width: 1000px;
        padding-left: 1.4rem;
        padding-right: 1.4rem;
        margin-left: auto;
        margin-right: auto;
    }

    #navbar {
        --navbar-height: 64px;
        position: fixed;
        height: var(--navbar-height);
        background-color: var(--navbar-bg-color);
        left: 0;
        right: 0;
        /* box-shadow: 0 2px 4px rgba(0, 0, 0, 0.15);
         */
        box-shadow: 4px 4px 10px #000000b0,
            -0.9px -0.9px 10px #daf3fd69;

    }


    .navbar-container {
        display: flex;
        justify-content: space-between;
        height: 100%;
        align-items: center;
    }

    .navbar-item {
        margin: 0.4em;
        width: 100%;
    }

    .home-link,
    .navbar-link {
        color: var(--navbar-text-color);
        transition: color 0.2s ease-in-out;
        text-decoration: none;
        display: flex;
        font-weight: 400;
        align-items: center;
        transition: background-color 0.2s ease-in-out,
            color 0.2s ease-in-out;
    }

    .home-link:focus,
    .home-link:hover {
        color: var(--navbar-text-color-focus);
    }

    .navbar-link {
        justify-content: center;
        width: 100%;
        padding: 0.4em 0.8em;
        border-radius: 5px;
    }

    .navbar-link:focus,
    .navbar-link:hover {
        color: var(--navbar-text-color-focus);
        background-color: var(--navbar-bg-contrast);
    }

    .navbar-logo {
        background-color: var(--navbar-text-color-focus);
        border-radius: 50%;
        width: 40px;
        height: 40px;
        margin-right: 0.5em;
        box-shadow: 4px 4px 10px #000000b0,
            -0.9px -0.9px 10px #daf3fd69;
    }

    .navbar-toggle {
        cursor: pointer;
        border: none;
        background-color: transparent;
        width: 40px;
        height: 40px;
        display: flex;
        align-items: center;
        justify-content: center;
        flex-direction: column;
        box-shadow: 4px 4px 10px #000000b0,
            -0.9px -0.9px 10px #daf3fd69;
    }

    .icon-bar {
        display: block;
        width: 25px;
        height: 4px;
        margin: 2px;
        transition: background-color 0.2s ease-in-out,
            transform 0.2s ease-in-out,
            opacity 0.2s ease-in-out;
        background-color: var(--navbar-text-color);
    }

    .navbar-toggle:focus .icon-bar,
    .navbar-toggle:hover .icon-bar {
        background-color: var(--navbar-text-color-focus);
    }

    #navbar.opened .navbar-toggle .icon-bar:first-child,
    #navbar.opened .navbar-toggle .icon-bar:last-child {
        position: absolute;
        margin: 0;
        width: 30px;
    }

    #navbar.opened .navbar-toggle .icon-bar:first-child {
        transform: rotate(45deg);
    }

    #navbar.opened .navbar-toggle .icon-bar:nth-child(2) {
        opacity: 0;
    }

    #navbar.opened .navbar-toggle .icon-bar:last-child {
        transform: rotate(-45deg);
    }

    .navbar-menu {
        position: fixed;
        top: var(--navbar-height);
        bottom: 0;
        transition: opacity 0.2s ease-in-out,
            visibility 0.2s ease-in-out;
        opacity: 0;
        visibility: hidden;
        left: 0;
        right: 0;
    }

    #navbar.opened .navbar-menu {
        background-color: rgba(0, 0, 0, 0.4);
        opacity: 1;
        visibility: visible;
    }

    .navbar-links {
        list-style-type: none;
        max-height: 0;
        overflow: hidden;
        position: absolute;
        background-color: var(--navbar-bg-color);
        display: flex;
        flex-direction: column;
        align-items: center;
        left: 0;
        right: 0;
        margin: 1.4rem;
        border-radius: 5px;
        box-shadow: 0 0 20px rgba(0, 0, 0, 0.3);
    }

    #navbar.opened .navbar-links {
        padding: 1em;
        max-height: none;
    }

    @media screen and (min-width: 700px) {
        .navbar-toggle {
            display: none;
        }

        #navbar .navbar-menu,
        #navbar.opened .navbar-menu {
            visibility: visible;
            opacity: 1;
            position: static;
            display: block;
            height: 100%;
        }

        #navbar .navbar-links,
        #navbar.opened .navbar-links {
            margin: 0;
            padding: 0;
            box-shadow: none;
            position: static;
            flex-direction: row;
            list-style-type: none;
            max-height: max-content;
            width: 100%;
            height: 100%;
        }

        #navbar .navbar-link:last-child {
            margin-right: 0;
        }
    }

    button.on,
    button.off {
        display: block;
        margin-top: 5px;
        margin-bottom: 5px;
        margin-left: auto;
        margin-right: auto;
        line-height: 60px;
        font-weight: bold;
        padding: 0 100px;
        background: rgb(156, 138, 136);
        border: none;
        align-items: center;
        /* background: linear-gradient(-45deg, rgba(0, 0, 0, 0.22), rgba(255, 255, 255, 0.25)); */
        border-radius: 50px;
        background: linear-gradient(145deg, #454546, #f0f0f0);
        box-shadow: 4px 4px 10px #000000b0,
            -0.9px -0.9px 10px #daf3fd69;

    }

    button.off {
        background: rgb(255, 191, 184);
    }

    button.on {
        background: rgb(213, 255, 174);
    }

    button.off:hover {
        background: rgb(255, 165, 162);

    }

    button.on:hover {


        background: rgb(186, 252, 132);
    }

    p {
        margin-top: auto;
    }

    .slidecontainer {
        width: 100%;

    }

    .slider {
        display: block;
        margin-right: auto;
        margin-left: auto;
        -webkit-appearance: none;
        margin-top: 10px;
        margin-bottom: 10px;
        width: 390px;
        height: 25px;
        border-radius: 50px;
        background: #ececec;
        outline: none;
        opacity: 1;
        -webkit-transition: .2s;
        transition: opacity .2s;
        box-shadow: 4px 4px 10px #000000b0,
            -0.9px -0.9px 10px #daf3fd69;
    }

    .slider:hover {
        opacity: 1;
    }

    .slider::-webkit-slider-thumb {
        -webkit-appearance: none;
        appearance: none;
        width: 40px;
        height: 40px;
        border-radius: 50%;
        background: rgb(213, 255, 174);
        cursor: pointer;
        box-shadow: 4px 4px 10px #000000b0,
            -0.9px -0.9px 10px #daf3fd69;
    }

    .slider::-moz-range-thumb {
        width: 40px;
        height: 40px;
        border-radius: 50%;
        background: rgb(213, 255, 174);
        cursor: pointer;
        box-shadow: 4px 4px 10px #000000b0,
            -0.9px -0.9px 10px #daf3fd69;
    }
</style>

<body onload="getStatusOnce()">

    <header id="navbar" style="z-index: 100;">
        <nav class="navbar-container container">
            <a href="/" class="home-link">
                <div class="navbar-logo">
                    <h1 style="margin-left: 7px; margin-top: -6px; color: rgb(0, 128, 145); font-size: 38px;">V</h1>
                </div>
                <h3> Vishwakarma Home Automation</h3>

            </a>
            <button type="button" class="navbar-toggle" aria-label="Open navigation menu">
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
            </button>
            <div class="navbar-menu">
                <ul class="navbar-links">
                    <li class="navbar-item"><a class="navbar-link" href="/about">About</a></li>
                    <li class="navbar-item"><a class="navbar-link" href="/blog">Blog</a></li>
                    <li class="navbar-item"><a class="navbar-link" href="/careers">Careers</a></li>
                    <li class="navbar-item"><a class="navbar-link" href="/contact">Contact</a></li>
                </ul>
            </div>
        </nav>
    </header>

    <br><br><br><br>

    <div class="clock">
        <div class="center-nut">
        </div>
        <div class="center-nut2">
        </div>
        <div class="indicators">
            <div>
            </div>
            <div>
            </div>
            <div>
            </div>
            <div>
            </div>
            <div>
            </div>
            <div>
            </div>
            <div>
            </div>
            <div>
            </div>
            <div>
            </div>
            <div>
            </div>
            <div>
            </div>
            <div>
            </div>
        </div>
        <div class="sec-hand">
            <div class="sec">
            </div>
        </div>
        <div class="min-hand">
            <div class="min">
            </div>
        </div>
        <div class="hr-hand">
            <div class="hr">
            </div>
        </div>
    </div>

    <p1><br><br></p1>
    <br><br><br>


    <script>
        const navbar = document.getElementById("navbar");
        const navbarToggle = navbar.querySelector(".navbar-toggle");

        function openMobileNavbar() {
            navbar.classList.add("opened");
            navbarToggle.setAttribute("aria-label", "Close navigation menu.");
        }

        function closeMobileNavbar() {
            navbar.classList.remove("opened");
            navbarToggle.setAttribute("aria-label", "Open navigation menu.");
        }

        navbarToggle.addEventListener("click", () => {
            if (navbar.classList.contains("opened")) {
                closeMobileNavbar();
            } else {
                openMobileNavbar();
            }
        });

        const navbarMenu = navbar.querySelector(".navbar-menu");
        const navbarLinksContainer = navbar.querySelector(".navbar-links");

        navbarLinksContainer.addEventListener("click", (clickEvent) => {
            clickEvent.stopPropagation();
        });

        navbarMenu.addEventListener("click", closeMobileNavbar);

    </script>
    <script>
        var payloadRepeat;
        var payloadOnce;
        var proceeder = 0;

        var proceederCopy = 0;

        var getStatusOnce = function () {
            var xhr = new XMLHttpRequest;
            xhr.onreadystatechange = () => {
                if (xhr.readyState === 4) {
                    if (xhr.status === 200) {
                        var payloadOnce = xhr.responseText;

                        while (payloadOnce[proceederCopy]) {

                            if (payloadOnce[proceederCopy] == 9) {
                                proceeder = proceederCopy;
                                proceeder++;
                                while (payloadOnce[proceeder] == 1 || payloadOnce[proceeder] == 0) {
                                    if (payloadOnce[proceeder] == 1) {

                                        // 1. Create the button
                                        var button = document.createElement("button");
                                        button.innerHTML = "ON*";
                                        button.classList.add('on');
                                        button.classList.add("btn" + proceeder);
                                        button.setAttribute("id", "btn" + proceeder);
                                        button.setAttribute('marker', "button" + proceeder)

                                        var br = document.createElement("br");

                                        var body = document.getElementsByTagName("p1")[0];
                                        body.appendChild(button);
                                        body.appendChild(br);

                                        button.addEventListener("click", function () {
                                            let mark = this.getAttribute("marker");
                                            
                                            let xhr = new XMLHttpRequest;
                                            xhr.open('GET', mark, true);
                                            xhr.send();

                                        });

                                    }
                                    else if (payloadOnce[proceeder] == 0) {

                                        // 1. Create the button
                                        var button = document.createElement("button");
                                        button.innerHTML = "OFF";
                                        button.classList.add('off');
                                        button.classList.add("btn" + proceeder);
                                        button.setAttribute("id", "btn" + proceeder);
                                        button.setAttribute('marker', "button" + proceeder)


                                        var br = document.createElement("br");

                                        // 2. Append somewhere
                                        var body = document.getElementsByTagName("p1")[0];
                                        body.appendChild(button);
                                        body.appendChild(br);

                                        // 3. Add event handler
                                        button.addEventListener("click", function () {
                                            let mark = this.getAttribute("marker");

                                            let xhr = new XMLHttpRequest;
                                            xhr.open('GET', mark, true);
                                            xhr.send();
                                        });

                                    }
                                    proceeder++;
                                }
                            }
                            else if (payloadOnce[proceederCopy] == "8") {
                                let myAdder = 0;
                                let myFanVar = [0, 0, 0];
                                console.log('hi dude')

                                proceeder = proceederCopy;
                                proceeder++;
                                while (payloadOnce[proceeder] == 1 || payloadOnce[proceeder] == 0) {
                                    if (payloadOnce[proceeder] == 1) {
                                        myFanVar[myAdder] = "1";
                                        myAdder++;
                                    } else if (payloadOnce[proceeder] == 0) {
                                        myFanVar[myAdder] = "0";
                                        myAdder++;
                                    }
                                    proceeder++;

                                }

                                myAdder = 0;
                                if (myFanVar[0] == "1") {

                                    var slider = document.createElement("input");
                                    slider.classList.add('slider');
                                    slider.classList.add(proceeder);
                                    slider.setAttribute("type", "range");
                                    slider.setAttribute("min", "1");
                                    slider.setAttribute("max", "5");
                                    slider.setAttribute("value", "5");
                                    slider.setAttribute("id", "range" + proceeder);

                                    var br = document.createElement("br");

                                    var body = document.getElementsByTagName("p1")[0];
                                    body.appendChild(slider);
                                    body.appendChild(br);

                                    slider.addEventListener("click", function () {
                                        // alert("did something");

                                    });

                                    myFanVar = [0, 0, 0];

                                } else if (myFanVar[1] == "1" && myFanVar[2] == "1") {
                                    var slider = document.createElement("input");
                                    slider.classList.add('slider');
                                    slider.classList.add(proceeder);
                                    slider.setAttribute("type", "range");
                                    slider.setAttribute("min", "1");
                                    slider.setAttribute("max", "5");
                                    slider.setAttribute("value", "4");
                                    slider.setAttribute("id", "range" + proceeder);


                                    var br = document.createElement("br");

                                    var body = document.getElementsByTagName("p1")[0];
                                    body.appendChild(slider);
                                    body.appendChild(br);

                                    slider.addEventListener("click", function () {
                                        // let d = document.getElementsByClassName('1');
                                        // alert("did something");

                                    });

                                    myFanVar = [0, 0, 0];

                                } else if (myFanVar[1] == "1") {
                                    var slider = document.createElement("input");
                                    slider.classList.add('slider');
                                    slider.classList.add(proceeder);
                                    slider.setAttribute("type", "range");
                                    slider.setAttribute("min", "1");
                                    slider.setAttribute("max", "5");
                                    slider.setAttribute("value", "3");
                                    slider.setAttribute("id", "range" + proceeder);


                                    var br = document.createElement("br");

                                    var body = document.getElementsByTagName("p1")[0];
                                    body.appendChild(slider);
                                    body.appendChild(br);

                                    slider.addEventListener("click", function () {
                                        // let d = document.getElementsByClassName('1');
                                        // alert("did something");

                                    });
                                    myFanVar = [0, 0, 0];

                                } else if (myFanVar[2] == "1") {
                                    var slider = document.createElement("input");
                                    slider.classList.add('slider');
                                    slider.classList.add(proceeder);
                                    slider.setAttribute("type", "range");
                                    slider.setAttribute("min", "1");
                                    slider.setAttribute("max", "5");
                                    slider.setAttribute("value", "2");
                                    slider.setAttribute("id", "range" + proceeder);


                                    var br = document.createElement("br");

                                    var body = document.getElementsByTagName("p1")[0];
                                    body.appendChild(slider);
                                    body.appendChild(br);

                                    slider.addEventListener("click", function () {
                                        // let d = document.getElementsByClassName('1');
                                        // alert("did something");

                                    });
                                    myFanVar = [0, 0, 0];

                                } else if (myFanVar[0] == "0" && myFanVar[1] == "0" && myFanVar[2] == "0") {
                                    var slider = document.createElement("input");
                                    slider.classList.add('slider');
                                    slider.classList.add(proceeder);
                                    slider.setAttribute("type", "range");
                                    slider.setAttribute("min", "1");
                                    slider.setAttribute("max", "5");
                                    slider.setAttribute("value", "1");
                                    slider.setAttribute("id", "range" + proceeder);


                                    var br = document.createElement("br");

                                    var body = document.getElementsByTagName("p1")[0];
                                    body.appendChild(slider);
                                    body.appendChild(br);

                                    slider.addEventListener("click", function () {
                                        // let d = document.getElementsByClassName('1');
                                        // alert("did something");

                                    });
                                    myFanVar = [0, 0, 0];

                                }

                            };


                            proceederCopy++;
                        }

                    }
                }
            }
            xhr.open("GET", "/sendStatus", true);
            xhr.send();
        }



        function getButtonStatus() {
            var xhr = new XMLHttpRequest();
            var statusCounter = 0;
            var statusCounterCopy = 0;
            xhr.onreadystatechange = () => {
                if (xhr.readyState === 4) {
                    if (xhr.status === 200) {
                        var payloadRepeat = xhr.responseText;

                        while (payloadRepeat[statusCounter]) {
                            if (payloadRepeat[statusCounter] == 9) {
                                statusCounterCopy = statusCounter;
                                statusCounterCopy++;
                                while (payloadRepeat[statusCounterCopy] == 1 || payloadRepeat[statusCounterCopy] == 0) {
                                    if (payloadRepeat[statusCounterCopy] == 1) {
                                        let dop = document.getElementById("btn" + statusCounterCopy);
                                        dop.classList.remove("off");
                                        dop.classList.add("on");
                                        dop.innerHTML = "ON*";
                                    }
                                    else if (payloadRepeat[statusCounterCopy] == 0) {
                                        let dop = document.getElementById("btn" + statusCounterCopy);
                                        dop.classList.remove("on");
                                        dop.classList.add("off");
                                        dop.innerHTML = "OFF";
                                    }
                                    statusCounterCopy++;
                                }
                            } else if (payloadRepeat[statusCounter] == 8) {
                                let myAdder = 0;
                                let myFanVar = [0, 0, 0];
                                console.log('hi dude')

                                statusCounterCopy = statusCounter;
                                statusCounterCopy++;

                                while (payloadRepeat[statusCounterCopy] == 1 || payloadRepeat[statusCounterCopy] == 0) {
                                    if (payloadRepeat[statusCounterCopy] == 1) {
                                        myFanVar[myAdder] = "1";
                                        myAdder++;
                                    } else if (payloadRepeat[statusCounterCopy] == 0) {
                                        myFanVar[myAdder] = "0";
                                        myAdder++;
                                    }
                                    statusCounterCopy++;
                                }
                                myAdder = 0;
                                if (myFanVar[0] == "1") {
                                    let dop = document.getElementById("range" + statusCounterCopy);
                                    dop.setAttribute("value", "5");
                                } else if (myFanVar[1] == "1" && myFanVar[2] == "1") {
                                    let dop = document.getElementById("range" + statusCounterCopy);
                                    dop.setAttribute("value", "4");
                                } else if (myFanVar[1] == "1") {
                                    let dop = document.getElementById("range" + statusCounterCopy);
                                    dop.setAttribute("value", "3");
                                } else if (myFanVar[2] == "1") {
                                    let dop = document.getElementById("range" + statusCounterCopy);
                                    dop.setAttribute("value", "2");
                                } else if (myFanVar[0] == "0" && myFanVar[1] == "0" && myFanVar[2] == "0") {
                                    let dop = document.getElementById("range" + statusCounterCopy);
                                    dop.setAttribute("value", "1");
                                }

                            }
                            statusCounter++;
                        }

                    }
                }
            }
            xhr.open("GET", "/sendStatus", true);
            xhr.send();
        }
        setInterval(getButtonStatus, 1000);

    </script>

    <script>
        const sec = document.querySelector(".sec");
        const min = document.querySelector(".min");
        const hr = document.querySelector(".hr");
        setInterval(function () {
            let time = new Date();
            let secs = time.getSeconds() * 6;
            let mins = time.getMinutes() * 6;
            let hrs = time.getHours() * 30;
            sec.style.transform = `rotateZ(${secs}deg)`;
            min.style.transform = `rotateZ(${mins}deg)`;
            hr.style.transform = `rotateZ(${hrs + (mins / 12)}deg)`;
        });
    </script>
</body>

</html>
)rawliteral";

const char favicon_html[] PROGMEM = R"rawliteral(
<h4 style="color: rgb(31, 36, 34); font-size: 20px;">&#128507;</h4>
)rawliteral";

void serverSetup()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", index_html);
    });
    server.on("/sendStatus", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", readStatus().c_str());
    });
    server.on("/button1", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", jsButton1().c_str());
    });
    server.on("/button2", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", jsButton2().c_str());
    });
    server.on("/button3", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", jsButton3().c_str());
    });
    server.on("/button4", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", jsButton4().c_str());
    });
    server.on("/button5", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", jsButton5().c_str());
    });
    server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", favicon_html);
    });
    server.begin();
}

void reconnect()
{
    if (!client.connected())
    {
        String clientId = "ESP8266-";
        clientId += String(random(0xffffffff), HEX);
        if (client.connect(clientId.c_str()))
        {
            client.subscribe(inTopic);
            mqttMode = 1;
        }
        else
        {
            mqttMode = 0;
        }
    }
}

void repeatThis()
{
    // Code for hardware swith for offline switching
    // And this must be repeated every time for knowing switch states

    if (digitalRead(4) == 1 && (checker0 == (counter0 + 1)))
    {
        digitalWrite(0, HIGH);
        checker0++;
        if (mqttMode == 1)
        {
            client.publish(outTopic, "ac");
        }
        reCheck0 = 1;
        delay(10);
    }
    else if (digitalRead(4) != 1 && (checker0 == (counter0 + 2)))
    {
        digitalWrite(0, LOW);
        checker0--;
        if (mqttMode == 1)
        {
            client.publish(outTopic, "ad");
        }
        reCheck1 = 0;
        delay(10);
    };

    if (digitalRead(3) == 1 && (checker1 == (counter1 + 1)))
    {
        digitalWrite(16, HIGH);
        checker1++;
        if (mqttMode == 1)
        {
            client.publish(outTopic, "aa");
        }
        reCheck1 = 1;
        delay(10);
    }
    else if (digitalRead(3) != 1 && (checker1 == (counter1 + 2)))
    {
        digitalWrite(16, LOW);
        checker1--;
        if (mqttMode == 1)
        {
            client.publish(outTopic, "ab");
        }
        reCheck1 = 0;
        delay(10);
    };

    if (digitalRead(5) == 1 && (checker3 == (counter3 + 1)))
    {
        digitalWrite(14, HIGH);
        checker3++;
        if (mqttMode == 1)
        {
            client.publish(outTopic, "ae");
        }
        reCheck3 = 1;
        delay(10);
    }
    else if (digitalRead(5) != 1 && (checker3 == (counter3 + 2)))
    {
        digitalWrite(14, LOW);
        checker3--;
        if (mqttMode == 1)
        {
            client.publish(outTopic, "af");
        }
        reCheck3 = 0;
        delay(10);
    };

    if (digitalRead(12) == 1 && (checker4 == (counter4 + 1)))
    {
        digitalWrite(15, HIGH);
        checker4++;
        if (mqttMode == 1)
        {
            client.publish(outTopic, "ag");
        }
        reCheck4 = 1;
        delay(10);
    }
    else if (digitalRead(12) != 1 && (checker4 == (counter4 + 2)))
    {
        digitalWrite(15, LOW);
        checker4--;
        if (mqttMode == 1)
        {
            client.publish(outTopic, "ah");
        }
        reCheck4 = 0;
        delay(10);
    };

    if (digitalRead(13) == 1 && (checker5 == (counter5 + 1)))
    {
        digitalWrite(1, HIGH);
        checker5++;
        if (mqttMode == 1)
        {
            client.publish(outTopic, "ai");
        }
        reCheck5 = 1;
        delay(10);
    }
    else if (digitalRead(13) != 1 && (checker5 == (counter5 + 2)))
    {
        digitalWrite(1, LOW);
        checker5--;
        if (mqttMode == 1)
        {
            client.publish(outTopic, "aj");
        }
        reCheck5 = 0;
        delay(10);
    };
}

void setup()
{
    setup_wifi();
    pinMode(3, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);
    pinMode(13, INPUT_PULLUP);

    pinMode(16, OUTPUT);
    pinMode(0, OUTPUT);
    pinMode(14, OUTPUT);
    pinMode(15, OUTPUT);
    pinMode(1, OUTPUT);

    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
    serverSetup();
}

void loop()
{
    repeatThis();
    reconnect();
    client.loop();
}