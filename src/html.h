const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Wifi Settings..</title>
  </head>
  <body style="font-size: 16px">
    <div>
      <center>
        <h2>Wifi Settings..</h2>
        <fieldset style="width: 350px; border-radius: 8px">
          <br />
          <form
            method="GET"
            action="#"
            id="login-form"
            class="login-form"
            autocomplete="off"
            role="main"
          >
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
                onclick="hidePass()"
                style="cursor: pointer; text-decoration: underline"
                >Show Passwords!!
              </span>
            </div>
            <br />
            <input
              type="submit"
              name="submit"
              value="Save Settings"
              id="toSubmit"
            />
          </form>
          <br />
        </fieldset>
      </center>
    </div>
    <script>
      var myOBJ = %OBJ%;
      put = () => {
        let wifiName = document.getElementById("wifiname");
        wifiName.value = myOBJ.wifi;

        let wifiPass = document.getElementById("wifipass");
        wifiPass.value = myOBJ.wifipw;

        let hotName = document.getElementById("hotname");
        hotName.value = myOBJ.ap;

        let hotPass = document.getElementById("hotpass");
        hotPass.value = myOBJ.appw;

        let userName = document.getElementById("username");
        userName.value = myOBJ.user;

        let lockPass = document.getElementById("lockpass");
        lockPass.value = myOBJ.lock;
      };
      put();

      document.getElementById("toSubmit").addEventListener("click", (e) => {
        e.preventDefault();
        var confirmIt = confirm(
          "You are one step back to change system settings. This process will reset your device!! Press OK to confirm..."
        );
        if (confirmIt === true) {
          let wifiName = document.getElementById("wifiname").value;
          let wifiPass = document.getElementById("wifipass").value;
          let hotName = document.getElementById("hotname").value;
          let hotPass = document.getElementById("hotpass").value;
          let userName = document.getElementById("username").value;
          let lockPass = document.getElementById("lockpass").value;

          let myLink = `/changesettings?wifiname=${wifiName}&wifipass=${wifiPass}&hotname=${hotName}&hotpass=${hotPass}&lockpass=${lockPass}&user=${userName}&submit=save+settings#`;

          var xhttp1 = new XMLHttpRequest();
          xhttp1.open("GET", myLink, true);
          xhttp1.send();
        }
      });

      function hidePass() {
        let wifiPass = document.getElementById("wifipass");
        let hotPass = document.getElementById("hotpass");
        let lockPass = document.getElementById("lockpass");

        wifiPass.type = "text";
        hotPass.type = "text";
        lockPass.type = "text";
        return;
      }
    </script>
  </body>
</html>
)rawliteral";