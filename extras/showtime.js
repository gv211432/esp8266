$.getJSON("http://192.168.45.221/gettime", (data, status) => {
  var myWeekDay = ["omit", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"];
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
