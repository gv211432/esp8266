const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Wifi Settings</title>
    <link rel="stylesheet" href="/style.css" />
    <style>
      .middleIt {
        display: flex;
        justify-content: center;
        text-align: center;
      }
    </style>
    <script src="/jquery.js"></script>
  </head>
  <body style="font-size: 16px">
    <div class="middleIt">
      <div
        class="middleIt"
        id="mainForm"
        style="
          width: 380px;
          box-shadow: -2px -2px 5px #fff, 2px 2px 5px #babecc;
          border-radius: 20px;
          margin-bottom: 10px;
        "
      >
        <form
          method="GET"
          action="#"
          id="login-form"
          class="login-form"
          autocomplete="off"
          role="main"
        >
          <h2>Wifi-Hotspot Settings..</h2>

          <div>
            <label for="wifiname">Wifi Name* </label>
            <input
              type="text"
              class="text"
              name="wifiname"
              id="wifiname"
              placeholder="Wifi Name"
              tabindex="1"
              required
            />
          </div>
          <br />
          <div>
            <label for="wifipass">Wifi Password*</label>
            <input
              type="password"
              class="text"
              name="wifipass"
              itemid="wifipass"
              id="wifipass"
              placeholder="Wifi Password"
              tabindex="1"
              required
            />
          </div>
          <br />
          <div>
            <label for="hotname">Hotspot Name*</label>
            <input
              type="text"
              class="text"
              name="hotname"
              id="hotname"
              placeholder="Hotspot Name"
              tabindex="1"
              required
            />
          </div>
          <br />
          <div>
            <label for="hotpass">Hotspot Password*</label>
            <input
              type="password"
              class="text"
              name="hotpass"
              id="hotpass"
              placeholder="Hotspot Password"
              tabindex="1"
              required
            />
          </div>
          <br />
          <div>
            <label for="hotname">User Name*</label>
            <input
              type="text"
              class="text"
              name="username"
              id="username"
              placeholder="User Name"
              tabindex="1"
              required
            />
          </div>
          <br />
          <div>
            <label for="lockpass">Lock Password*</label>
            <input
              type="password"
              class="text"
              name="lockpass"
              id="lockpass"
              placeholder="Lock Password"
              tabindex="1"
              required
            />
          </div>
          <br />
          <div>
            <span
              id="showPassword"
              style="
                cursor: pointer;
                text-decoration: underline;
                font-weight: 600;
              "
              >Show Passwords!!
            </span>
          </div>
          <br />
          <p
            id="showTime"
            style="color: #d1ce0d; font-size: 14px; font-weight: 600"
          ></p>

          <button
            type="submit"
            name="submit"
            value="Save Settings"
            id="toSubmit"
            class="red"
          >
            Save Settings
          </button>
        </form>
      </div>
      <br />
    </div>
    <script>
      var myOBJ = %OBJ%;

      $(function () {
        let wifiName = $("#wifiname");
        let wifiPass = $("#wifipass");
        let hotName = $("#hotname");
        let hotPass = $("#hotpass");
        let userName = $("#username");
        let lockPass = $("#lockpass");
        let dTime = $("#showTime");

        wifiName.val(myOBJ.wifi);
        wifiPass.val(myOBJ.wifipw);
        hotName.val(myOBJ.ap);
        hotPass.val(myOBJ.appw);
        userName.val(myOBJ.user);
        lockPass.val(myOBJ.lock);

        $("#toSubmit").click(function () {
          var confirmIt = confirm(
            "You are one step back to change system settings. This process will reset your device!! Press OK to confirm..."
          );

          if (confirmIt === true) {
            let myLink = `/changesettings?wifiname=${wifiName.val()}&wifipass=${wifiPass.val()}&hotname=${hotName.val()}&hotpass=${hotPass.val()}&lockpass=${lockPass.val()}&user=${userName.val()}&submit=save+settings#`;

            console.log(myLink);

            var xhttp1 = new XMLHttpRequest();
            xhttp1.open("GET", myLink, true);
            xhttp1.send();
          }
        });

        let showPwCheck = 0;
        let showPass = $("#showPassword");
        showPass.hover(
          function () {
            $(this).css({ color: "#0077ff", "font-weight": "800" });
          },
          function () {
            $(this).css({ color: "#babecc", "font-weight": "600" });
          }
        );

        showPass.click(function () {
          if (showPwCheck == 0) {
            wifiPass.attr("type", "text");
            lockPass.attr("type", "text");
            hotPass.attr("type", "text");
            showPwCheck = 1;
            return;
          }
          showPwCheck = 1;
          wifiPass.attr("type", "password");
          lockPass.attr("type", "password");
          hotPass.attr("type", "password");
        });

        $.getJSON("/gettime", (data, status) => {
          var myWeekDay = [
            "omit",
            "Sun",
            "Mon",
            "Tue",
            "Wed",
            "Thu",
            "Fri",
            "Sat",
          ];
          let myMonth = [
            "omit",
            "Jan",
            "Feb",
            "Mar",
            "Apr",
            "May",
            "Jun",
            "Jul",
            "Aug",
            "Sep",
            "Oct",
            "Nov",
            "Dec",
          ];
          let secIncre = data.sec;
          let minIncre = data.min;

          setInterval(() => {
            if (secIncre == 60) {
              minIncre++;
              secIncre = 0;
            }
            if (minIncre == 60) {
              window.location.reload();
            }
            let showTime =
              "" +
              myWeekDay[data.wDay] +
              " " +
              myMonth[data.mon] +
              " " +
              data.day +
              " " +
              data.yr +
              " " +
              data.hr +
              ":" +
              minIncre +
              ":" +
              secIncre +
              " (Local Time)";
            dTime.text(showTime);
            secIncre++;
          }, 1000);
        });
      });
    </script>
  </body>
</html>

)rawliteral";