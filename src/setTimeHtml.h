const char give_time[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Time settings</title>
    <link rel="stylesheet" href="/style.css" />
    <script src="/jquery.js"></script>
    <!-- <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script> -->
    <style>
      .middleIt {
        display: flex;
        justify-content: center;
        text-align: center;
      }
    </style>
  </head>
  <body>
    <div class="middleIt">
      <div
        class="middleIt"
        style="
          width: 380px;
          box-shadow: -2px -2px 5px #fff, 2px 2px 5px #babecc;
          border-radius: 20px;
          margin-bottom: 10px;
        "
      >
        <div id="timeMain" style="width: 330px">
          <br />
          <h1 style="font-size: 30px">Time Settings..</h1>
          <h2>Your Browser's time</h2>
          <h1 id="bTime">....</h1>
          <h2>Your Device's time</h2>
          <h1 id="deviceTime">....</h1>

          <button class="red" id="setBtime">Set Browser's time</button>
          <h2 id="setInfo" style="color: #d1ce0d"></h2>
          <br /><br />

          <!-- Start----------------------------------------------- -->

          <h1>OR set it maunally down here...</h1>
          <h2>You can change any number of values here.</h2>

          <div id="myTime">
            <input
              type="text"
              placeholder="Hours"
              id="hour"
              style="width: 96px; display: inline"
            />
            <input
              type="text"
              placeholder="Minutes"
              id="minute"
              style="width: 96px; display: inline"
            />
            <input
              type="text"
              placeholder="Second"
              id="second"
              style="width: 96px; display: inline"
            />
          </div>
          <!-- End ----------------------------------------------- -->
          <br /><br />

          <!-- Start----------------------------------------------- -->

          <div id="myDate">
            <input
              type="text"
              placeholder="Day"
              id="day"
              style="width: 96px; display: inline"
            />
            <input
              type="text"
              placeholder="Month"
              id="month"
              style="width: 96px; display: inline"
            />
            <input
              type="text"
              placeholder="Year"
              id="year"
              style="width: 96px; display: inline"
            />
          </div>
          <br /><br />
          <!-- End ----------------------------------------------- -->

          <button class="red" id="setManually">OR Set Manually</button>

          <h1 style="color: #d1ce0d" id="dateWarn"></h1>

          <br /><br /><br />
        </div>
      </div>
    </div>
  </body>
  <script>
    let time = {
      this: "hi",
    };
    $(function () {
      let dTime = $("#deviceTime");
      let setInfo = $("#setInfo");
      setInfo.hide();
      let dw = $("#dateWarn");
      dw.hide();

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

      let bTime = $("#bTime");
      setInterval(() => {
        let myTime = new Date();
        bTime.text(myTime);
      }, 1000);

      let setBtime = $("#setBtime");
      setBtime.hover(
        function () {
          setInfo
            .text(
              "This will set the device time and date to, as same as your browser's.."
            )
            .slideDown(150);
          $(this).css({ "background-color": "#ae1100", color: "white" });
        },
        function () {
          $(this).css({ "background-color": "#ebecf0", color: "#ae1100" });
          setInfo.slideUp(150);
        }
      );
      setBtime.click(function () {
        let d = new Date();
        let setTheDate =
          "?h=" +
          d.getHours() +
          "&m=" +
          d.getMinutes() +
          "&s=" +
          (d.getSeconds() + 2) +
          "&d=" +
          d.getDate() +
          "&M=" +
          (d.getMonth() + 1) +
          "&y=" +
          d.getFullYear();

        $.get("/settime" + setTheDate, function () {
          setTimeout(() => {
            window.location.reload();
          }, 1500);
        });
      });

      let hr = $("#hour");
      let min = $("#minute");
      let sec = $("#second");
      let day = $("#day");
      let mon = $("#month");
      let yr = $("#year");

      let sethr = -1;
      let setmin = -1;
      let setsec = -1;
      let setday = -1;
      let setmon = -1;
      let setyr = -1;

      let setManStatus = false;
      $("#setManually").hover(
        function () {
          setManStatus = true;
          if (hr.val()) {
            if (hr.val() >= 24 || hr.val() < 0 || isNaN(hr.val())) {
              setManStatus = false;
              dw.text("Hour can be in range 0-23, (24hr-format)!!");
              dw.slideDown(150);

              return;
            }
            sethr = hr.val();
          }

          if (min.val()) {
            if (min.val() >= 60 || min.val() < 0 || isNaN(hr.val())) {
              setManStatus = false;
              dw.text("Minutes can be in range 0-59!!");
              dw.slideDown(150);

              return;
            }
            setmin = min.val();
          }

          if (sec.val()) {
            if (sec.val() >= 60 || sec.val() < 0 || isNaN(sec.val())) {
              setManStatus = false;
              dw.text("Problem with seconds!!");
              dw.slideDown(150);

              return;
            }
            setsec = sec.val();
          }

          if (day.val()) {
            if (day.val() >= 32 || day.val() < 1 || isNaN(day.val())) {
              setManStatus = false;
              dw.text("Problem with day!!");
              dw.slideDown(150);

              return;
            }
            setday = day.val();
          }

          if (mon.val()) {
            if (mon.val() >= 13 || mon.val() < 1 || isNaN(mon.val())) {
              setManStatus = false;
              dw.text("Problem with month!!");
              dw.slideDown(150);

              return;
            }
            setmon = mon.val();
          }

          if (yr.val()) {
            // let myYr = yr.val();
            if (isNaN(yr.val()) || yr.val().length != 4) {
              setManStatus = false;
              dw.text("Problem with year.. Mention full year!!");
              dw.slideDown(150);

              return;
            }
            setyr = yr.val();
          }

          $(this).css({
            "background-color": "#ae1100",
            color: "white",
          });
        },
        function () {
          dw.text("");
          dw.slideUp(150);

          $(this).css({ "background-color": "#ebecf0", color: "#ae1100" });
        }
      );

      $("#setManually").click(function () {
        if (
          sethr == -1 &&
          setmin == -1 &&
          setsec == -1 &&
          setday == -1 &&
          setmon == -1 &&
          setyr == -1
        ) {
          return;
        }
        if (setManStatus == true) {
          let setTheDate =
            "?h=" +
            sethr +
            "&m=" +
            setmin +
            "&s=" +
            setsec +
            "&d=" +
            setday +
            "&M=" +
            setmon +
            "&y=" +
            setyr;

          console.log(setTheDate);
          $.get("/settime" + setTheDate, function () {
            setTimeout(() => {
              window.location.reload();
            }, 1500);
          });
        }
      });
    });
  </script>
</html>

)rawliteral";