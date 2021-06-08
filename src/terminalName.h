const char terminalName[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html lang="en"> <head> <meta charset="UTF-8"/> <meta http-equiv="X-UA-Compatible" content="IE=edge"/> <meta name="viewport" content="width=device-width, initial-scale=1.0"/> <link rel="stylesheet" href="/style.css"/> <script src="/jquery.js"></script> <style>th, td{height: 70px;}tr{height: 20px; text-align: center;}input{width: 250px;}</style> <title>Naming Pins</title> </head> <body> <div id="inActivator"></div><div id="root"> <center> <div class="middleIt"> <br/><br/> <div class="card middleIt"> <table style="padding: 5px; width: 100%"> <tr id="tableTitle"> <td style="border-bottom: 1px solid rgb(209, 206, 206)"> <p style="font-size: 10px; color: #ae1100; font-weight: 700"> Available terminals </p></td><td style="border-bottom: 1px solid rgb(209, 206, 206)"> <h2 style="font-size: 20px; padding-left: 20px"> Name Terminals </h2> </td></tr><tr id="demoRow"> <td><h1 id="demoTerminal">P2</h1></td><td><input type="text" id="demoInput" placeholder="Name"/></td></tr><tr id="response"> <td></td><td style="text-align: start; padding-left: 70px"> <p style="font-size: 14px; color: green"> Set successfully.. </p></td></tr><tr> <td style="border-top: 1px solid rgb(209, 206, 206)"></td><td style=" width: 300px; height: 100px; border-top: 1px solid rgb(209, 206, 206); " > <button class="red" style="margin-left: -30px" id="submit"> Save It </button> </td></tr></table> </div></div></center> </div><div><button id="menuBtn">&#9776;</button></div> %MENU% </body><script>$(function(){let e=$("#demoRow").hide(),o=$("#response").hide(),t=[-1];$.getJSON("/pinCount",(i,n)=>{if("success"==n){let o=!0;i.allInPin.forEach(i=>{if(o=!0,t.forEach(e=>{e==i&&(o=!1)}),1==o){t.push(i);let o=e.clone();o.attr("id","row"+i),e.find("#demoRow").attr("id","row"+i),o.find("#demoTerminal").attr("id","P"+i).text("P"+i).css({color:"rgb(209, 206, 13)"}),o.find("#demoInput").attr("id","name"+i),e.after(o),o.show()}}),i.allOutPin.forEach(i=>{if(o=!0,t.forEach(e=>{e==i&&(o=!1)}),1==o){t.push(i);let o=e.clone();o.attr("id","row"+i),e.find("#demoRow").attr("id","row"+i),o.find("#demoTerminal").attr("id","P"+i).text("P"+i).css({color:"rgb(209, 206, 13)"}),o.find("#demoInput").attr("id","name"+i),e.before(o),o.show()}$.getJSON("/pinName",(e,o)=>{"success"==o&&e.pinTheme.forEach(e=>{$("#name"+e.no).val(e.name)})})})}$("#submit").hover(()=>{$("#submit").css({"background-color":"#ae1100",color:"white"})},()=>{$("#submit").css({"background-color":"#ebecf0",color:"#ae1100"})}),$("#submit").on({click:()=>{t.shift();let e={pinTheme:[]};t.forEach(o=>{if(""!=$("#name"+o).val()){let t={};t.no=o;let i=$("#name"+o).val().trim();t.name=i,e.pinTheme.push(t)}});let i=JSON.stringify(e);console.log(e),$.ajax({url:"/setPinName",headers:{setName:i}}).done(function(e){"ok"==e&&(o.slideDown(150),setInterval(()=>o.slideUp(150),2e3))})}})})});</script><script src="/jquery.js?menu"></script></html>
)rawliteral";