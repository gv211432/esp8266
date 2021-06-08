const char alarmHome_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html lang="en"> <head> <meta charset="UTF-8"/> <meta http-equiv="X-UA-Compatible" content="IE=edge"/> <meta name="viewport" content="width=device-width, initial-scale=1.0"/> <title>Alarms</title> <link rel="stylesheet" href="/style.css"/> <style>.card{width: 380px; border-radius: 20px; margin-bottom: 10px; box-shadow: -2px -2px 5px #fff, 2px 2px 5px #babecc;}.middleIt{display: flex; justify-content: center; position: relative;}</style> <script src="/jquery.js"></script> </head> <body id="body"> <div id="inActivator"></div><br/><br/> <div id="root"> <div id="mainBody" class="middleIt"> <div style=" position: absolute; background-color: pink; width: 380px; height: 380px; border-radius: 20px 20px 0 0; z-index: -1; opacity: 0; " id="hider0" ></div><div class="card"> <form action="" id="formNum0"> <div class="custom-select"> <button class="unit special" type="button" id="buttonNum0" style=" float: left; box-shadow: inset 2px 2px 5px #babecc, inset -5px -5px 10px #fff; margin-right: 30px; " > -- </button> <select id="select0"> <option value="option">Select Appliance &#9662;</option> </select> </div><br/><br/> <h2 id="alarmInfo"></h2> <h1 id="alarmAssist"></h1> <input type="text" id="onHr0" placeholder="On Hr" style="width: 90px; display: inline"/> <span style="float: right; width: 220px; margin-top: -10px" ><h2 id="showOnceInfo"> You can only use ON function or OFF function. If On is filled OFF will be IGNORED.. This alarm will be disabled once its completed. No date means todays date applied. </h2> </span> <button class="unit" type="button" id="buttonMon0" ison="0"> mon </button> <button class="unit" type="button" id="buttonTue0" ison="0"> Tue </button> <button class="unit" type="button" id="buttonWed0" ison="0"> wed </button> <br/> <br/> <input type="text" placeholder="On Min" id="onMin0" style="width: 90px; display: inline"/> <button class="unit" type="button" id="buttonThu0" ison="0"> Thu </button> <button class="unit" type="button" id="buttonFri0" ison="0"> Fri </button> <button class="unit" type="button" id="buttonSat0" ison="0"> Sat </button> <br/> <br/> <input type="text" placeholder="Off Hr" id="offHr0" style="width: 90px; display: inline"/><button class="unit special del" type="button" id="buttonDel0" isdel="0" style=" width: 129px; border-radius: 320px; background-color: #ec4a4a33; " > Delete </button> <button class="unit" type="button" id="buttonSun0" ison="0"> Sun</button ><br/> <br/> <input type="text" placeholder="Off Min" id="offMin0" style="width: 90px; display: inline"/> <button class="unit special once" type="button" id="buttonOnce0" isonce="0" style="padding: 27px" > Once </button> <button class="unit special enable" type="button" id="enable0" isenable="0" style="width: 129px; border-radius: 320px" > Enable </button> <br/> <br/> <h2 id="manifest"></h2> <div id="myDate"> <input type="text" placeholder="Day" id="day0" style="width: 96px; display: inline"/> <input type="text" placeholder="Month" id="month0" style="width: 96px; display: inline"/> <input type="text" placeholder="Year" id="year0" style="width: 96px; display: inline"/><br/><br/><br/> </div><button class="red" type="button" id="addAlarm0" isok="0"> Add New Alarm </button> <h2 id="allErr" style="text-align: center; color: #d47304"></h2> </form> <br/> </div></div><br/><br/> </div><div><button id="menuBtn">&#9776;</button></div> %MENU% </body> <script>$(function(){let t=$("#alarmInfo").hide(),a=$("#alarmAssist").hide(),o=$("#allErr").hide(),i=$("#select0"),e=$("#onHr0"),s=$("#onMin0"),l=$("#offHr0"),n=$("#offMin0"),r=$("#showOnceInfo"),c=$("#buttonMon0"),d=$("#buttonTue0"),v=$("#buttonWed0"),b=$("#buttonThu0"),f=$("#buttonFri0"),h=$("#buttonSat0"),u=$("#buttonSun0"),k=$(".unit").not(".special"),m=$("#enable0"),g=$("#buttonOnce0"),N=($("#day0"),$("#month0"),$("#year0"),$("#myDate")),w=$("#addAlarm0"),p={1:"Hall_Fan",2:"Kitchen_Light"},x=$("<option></option>").attr("value","1").text(p[1]),y=$("<option></option>").attr("value","2").text(p[2]);i.append(x),i.append(y),$("input").on({focus:function(){t.text("Alarm must be written in 24Hr format!! where 0 equals 12am and 12 equals 12pm"),t.slideDown(150)},keyup:function(){return"onHr0"==$(this).attr("id")?(a.text("Valid time is in between 0 and 23, ON time in hour is : "+$(this).val()),void a.slideDown(150)):"onMin0"==$(this).attr("id")?(a.text("Valid time is in between 0 and 59, ON time in minutes is : "+$(this).val()),void a.slideDown(150)):"offHr0"==$(this).attr("id")?(a.text("Valid time is in between 0 and 23, OFF time in hour is : "+$(this).val()),void a.slideDown(150)):"offMin0"==$(this).attr("id")?(a.text("Valid time is in between 0 and 59, OFF time in minutes is : "+$(this).val()),void a.slideDown(150)):void 0}}),c.click(()=>{1==$(this).attr("ison")?$(this).attr("ison","0"):$(this).attr("ison","1")}),d.click(()=>{1==$(this).attr("ison")?$(this).attr("ison","0"):$(this).attr("ison","1")}),v.click(()=>{1==$(this).attr("ison")?$(this).attr("ison","0"):$(this).attr("ison","1")}),b.click(()=>{1==$(this).attr("ison")?$(this).attr("ison","0"):$(this).attr("ison","1")}),f.click(()=>{1==$(this).attr("ison")?$(this).attr("ison","0"):$(this).attr("ison","1")}),h.click(()=>{1==$(this).attr("ison")?$(this).attr("ison","0"):$(this).attr("ison","1")}),u.click(()=>{1==$(this).attr("ison")?$(this).attr("ison","0"):$(this).attr("ison","1")}),m.click(()=>{0==m.attr("isenable")?m.attr("isenable","1").css({"background-color":"rgba(143, 235, 135, 0.4)"}).text("Enabled"):m.attr("isenable","0").css({"background-color":"#ebecf0"}).text("Enable")}),g.on("click",function(){if(0==$(this).attr("isonce"))return $(this).css("background-color","hsla(64, 97%, 62%, 0.4)"),N.slideDown("slow"),$(this).attr("isonce","1"),k.hide(),void r.fadeIn("slow");r.hide(),k.fadeIn("slow"),N.slideUp("slow"),$(this).attr("isonce","0").css("background-color","#ebecf0")}),w.hover(function(){if("option"==i.children("option:selected").val())return o.text("Select any appliance form the select button to apply changes..").css("color","#d47304"),void o.slideDown(150);if((e.val()>=24||e.val()<0||""==e.val())&&(l.val()>=24||l.val()<0||""==l.val()))return o.text("Problem with ON hour.. ON or OFF must be filled!!"),o.slideDown(150),void $(this).attr("isok","0");if((l.val()>=24||l.val()<0||""==l.val())&&(e.val()>=24||e.val()<0||""==e.val()))return o.text("Problem with OFF hour.."),o.slideDown(150),void $(this).attr("isok","0");if(s.val()>=60||s.val()<0)return o.text("Problem with ON minute.."),o.slideDown(150),void $(this).attr("isok","0");if(n.val()>=60||n.val()<0)return o.text("Problem with OFF minute.."),o.slideDown(150),void $(this).attr("isok","0");if(0==g.attr("isonce")){if(""==e.val()||""==l.val())return o.text("Please mention On Hour and Off Hour.."),void o.slideDown(150);o.text("This alarm will switch ON "+p[i.children("option:selected").val()]+" at "+Number(e.val())+":"+Number(s.val())+" and switch it OFF at "+Number(l.val())+":"+Number(n.val())).css("color","green"),o.slideDown(150)}1==g.attr("isonce")&&(""!=e.val()?(o.text("This alarm will switch ON "+p[i.children("option:selected").val()]+" at "+Number(e.val())+":"+Number(s.val())+" and disable it after execution.").css("color","green"),o.slideDown(150)):(o.text("This alarm will switch OFF "+p[i.children("option:selected").val()]+" at "+Number(l.val())+":"+Number(n.val())+" and disable it after execution.").css("color","green"),o.slideDown(150))),$(this).css({"background-color":"#ae1100",color:"white"}).attr("isok","1")},function(){$(this).css({"background-color":"#ebecf0",color:"#ae1100"}),o.slideUp(150)}),w.click(function(){let t;if(1==g.attr("isonce")){if(1==$(this).attr("isok")){let a=0;""!=e.val()&&(a=1),t="?shot="+a+"&onHr="+e.val()+"&onMin="+s.val()+"&offHr="+l.val()+"&offMin="+n.val()+"&pin="+i.children("option:selected").val()+"&enable="+m.attr("isenable")}}else 1==$(this).attr("isok")&&(t="?shot=2&onHr="+e.val()+"&onMin="+s.val()+"&offHr="+l.val()+"&offMin="+n.val()+"&pin="+i.children("option:selected").val()+"&sun="+u.attr("ison")+"&mon="+c.attr("ison")+"&tue="+d.attr("ison")+"&wed="+v.attr("ison")+"&thu="+b.attr("ison")+"&fri="+f.attr("ison")+"&sat="+h.attr("ison")+"&enable="+m.attr("isenable"));o.slideDown(),$.get("/setalarm"+t,function(){setTimeout(()=>window.location.reload(),1e3)})}),$("#myDate").hide(),$("#showOnceInfo").hide(),$.getJSON("/alarmjson",function(t){let a=1,o=new Date;$.each(t,(t,i)=>{if(1==i.free){i.oneShot,i.oneShot;let l=$("#mainBody").clone().attr("id",t),n=l.find("#hider0").attr("id",t+"hider");l.find("#alarmInfo").attr("id",t+alarmInfo);let r=l.find("#alarmAssist");r.attr("id",t+"alarmAssist");let c=l.find("#addAlarm0").attr("id",t+"edit").text("Edit Alarm").css({color:"#babecc"}),d=l.find("#allErr").attr("id",t+"Err");d.hide();let v=l.find("#enable0"),b=l.find("#buttonDel0").attr("id",t+"Del"),f=l.find("#formNum0").attr("id",t+"form"),h=l.find("#buttonOnce0").attr("id",t+"once"),u=l.find("#myDate").attr("id",t+"mydate"),k=l.find("#showOnceInfo").attr("id",t+"onceInfo"),m=l.find(".unit").not(".special"),g=l.find("#day0").attr("id",t+"day"),N=l.find("#month0").attr("id",t+"month"),w=l.find("#year0").attr("id",t+"year"),x=l.find("#select0").attr("id",t+"app");x.children("[value='2']").attr("selected",""),x.change(function(){$(this).children("option:selected").val()}),l.find("#buttonNum0").text(a),a++;let y=l.find("#onHr0");y.attr({id:t+"onHr",value:i.onHr});let D=l.find("#onMin0");D.attr({id:t+"onMin",value:i.onMin});let M=l.find("#offHr0").attr({id:t+"offHr",value:i.offHr}),H=l.find("#offMin0");H.attr({id:t+"offMin",value:i.offMin});let O=l.find("#buttonMon0");O.attr("id",t+"mon"),1==i.mon&&(O.css({"background-color":"rgba(181, 219, 251, 0.4)"}),O.attr("ison","1"));let F=l.find("#buttonTue0");F.attr("id",t+"tue"),1==i.tue&&(F.css({"background-color":"rgba(181, 219, 251, 0.4)"}),F.attr("ison","1"));let S=l.find("#buttonWed0");S.attr("id",t+"wed"),1==i.wed&&(S.css({"background-color":"rgba(181, 219, 251, 0.4)"}),S.attr("ison","1"));let T=l.find("#buttonThu0");T.attr("id",t+"thu"),1==i.thu&&(T.css({"background-color":"rgba(181, 219, 251, 0.4)"}),T.attr("ison","1"));let A=l.find("#buttonFri0");A.attr("id",t+"fri"),1==i.fri&&(A.css({"background-color":"rgba(181, 219, 251, 0.4)"}),A.attr("ison","1"));let I=l.find("#buttonSat0");I.attr("id",t+"sat"),1==i.sat&&(I.css({"background-color":"rgba(181, 219, 251, 0.4)"}),I.attr("ison","1"));let E=l.find("#buttonSun0");function e(){if(2==i.oneShot){if(1==h.attr("isonce"))return""!=y.val()||""!=M.val()?""!=M.val()&&(y.val()>23||y.val()<0||isNaN(y.val()))?void c.css({color:"#babecc"}).attr("isok","0"):""!=D.val()&&(D.val()>59||D.val()<0||isNaN(D.val()))?void c.css({color:"#babecc"}).attr("isok","0"):""!=M.val()&&(M.val()>23||M.val()<0||isNaN(M.val()))?void c.css({color:"#babecc"}).attr("isok","0"):""!=H.val()&&(H.val()>59||H.val()<0||isNaN(H.val()))?void c.css({color:"#babecc"}).attr("isok","0"):""!=g.val()&&(g.val()<1||g.val()>31||isNaN(g.val()))?void c.css({color:"#babecc"}).attr("isok","0"):""!=N.val()&&(N.val()<1||N.val()>12||isNaN(N.val()))?void c.css({color:"#babecc"}).attr("isok","0"):""!=w.val()&&(w.val()<o.getFullYear()||w.val()>2060||isNaN(w.val())||4!=w.val().length)?void c.css({color:"#babecc"}).attr("isok","0"):void c.css({color:"#ae1100"}).attr("isok","1"):void c.css({color:"#babecc"}).attr("isok","0");if(0==h.attr("isonce"))return""==y.val()||y.val()>23||y.val()<0||isNaN(y.val())?void c.css({color:"#babecc"}).attr("isok","0"):""==D.val()||D.val()>59||D.val()<0||isNaN(D.val())?void c.css({color:"#babecc"}).attr("isok","0"):""==M.val()||M.val()>23||M.val()<0||isNaN(M.val())?void c.css({color:"#babecc"}).attr("isok","0"):""==H.val()||H.val()>59||H.val()<0||isNaN(H.val())?void c.css({color:"#babecc"}).attr("isok","0"):y.val()!=i.onHr||D.val()!=i.onMin||M.val()!=i.offHr||H.val()!=i.offMin?void c.css({color:"#ae1100"}).attr("isok","1"):void c.css({color:"#babecc"}).attr("isok","0")}if(0==i.oneShot||1==i.oneShot){if(0==h.attr("isonce"))return""==y.val()||y.val()>23||y.val()<0||isNaN(y.val())?void c.css({color:"#babecc"}).attr("isok","0"):""==D.val()||D.val()>59||D.val()<0||isNaN(D.val())?void c.css({color:"#babecc"}).attr("isok","0"):""==M.val()||M.val()>23||M.val()<0||isNaN(M.val())?void c.css({color:"#babecc"}).attr("isok","0"):""==H.val()||H.val()>59||H.val()<0||isNaN(H.val())?void c.css({color:"#babecc"}).attr("isok","0"):y.val()!=i.onHr||D.val()!=i.onMin||M.val()!=i.offHr||H.val()!=i.offMin?void c.css({color:"#ae1100"}).attr("isok","1"):void c.css({color:"#babecc"}).attr("isok","0");if(""!=y.val()&&0==isNaN(y.val()))return y.val()>23||y.val()<0||isNaN(y.val())?void c.css({color:"#babecc"}).attr("isok","0"):""==D.val()||D.val()>59||D.val()<0||isNaN(D.val())?void c.css({color:"#babecc"}).attr("isok","0"):""!=g.val()&&(g.val()<1||g.val()>31||isNaN(g.val()))?void c.css({color:"#babecc"}).attr("isok","0"):""!=N.val()&&(N.val()<1||N.val()>12||isNaN(N.val()))?void c.css({color:"#babecc"}).attr("isok","0"):""!=w.val()&&(w.val()<o.getFullYear()||w.val()>2060||isNaN(w.val())||4!=w.val().length)?void c.css({color:"#babecc"}).attr("isok","0"):y.val()!=i.onHr||D.val()!=i.onMin||g.val()!=i.day||N.val()!=i.month||w.val()!=i.year?void c.css({color:"#ae1100"}).attr("isok","1"):void c.css({color:"#babecc"}).attr("isok","0");if(""!=M.val&&0==isNaN(M.val()))return M.val()>23||M.val()<0||isNaN(M.val())?void c.css({color:"#babecc"}).attr("isok","0"):""==H.val()||H.val()>59||H.val()<0||isNaN(H.val())?void c.css({color:"#babecc"}).attr("isok","0"):""!=g.val()&&(g.val()<1||g.val()>31||isNaN(g.val()))?void c.css({color:"#babecc"}).attr("isok","0"):""!=N.val()&&(N.val()<1||N.val()>12||isNaN(N.val()))?void c.css({color:"#babecc"}).attr("isok","0"):""!=w.val()&&(w.val()<o.getFullYear()||w.val()>2060||isNaN(w.val())||4!=w.val().length)?void c.css({color:"#babecc"}).attr("isok","0"):M.val()!=i.offHr||H.val()!=i.offMin||g.val()!=i.day||N.val()!=i.month||w.val()!=i.year?void c.css({color:"#ae1100"}).attr("isok","1"):void c.css({color:"#babecc"}).attr("isok","0")}c.css({color:"#babecc"}).attr("isok","0")}E.attr("id",t+"sun"),1==i.sun&&(E.css({"background-color":"rgba(181, 219, 251, 0.4)"}),E.attr("ison","1")),v.attr("id",t+"enable"),1==i.enable&&v.css({"background-color":"rgba(143, 235, 135, 0.4)"}).text("Enabled").attr("isenable","1"),0==i.enable&&v.css({"background-color":"rgba(143, 235, 135, 0.4)"}).text("Disabled").attr("isenable","0"),v.click(function(){if(1==$(this).attr("isenable"))return $(this).css({"background-color":"#ebecf0"}).attr("isenable","0").text("Disable"),c.css({color:"green"}).attr("isok","1").text("Disable Alarm!!"),1==h.attr("isonce")&&n.css({height:"480px"}),void n.css({"z-index":"0"}).click(function(){v.css({"background-color":"rgba(143, 235, 135, 0.4)"}).attr("isenable","1").text("Enabled"),c.css({"background-color":"#ebecf0",color:"#babecc"}).attr("isok","0").text("Edit Alarm"),n.css({"z-index":"-1",height:"420px"}).off()});0==$(this).attr("isenable")&&($(this).css({"background-color":"#ebecf0"}).attr("isenable","1").text("Enable"),c.css({color:"green"}).attr("isok","1").text("Enable Alarm!!"),1==h.attr("isonce")&&n.css({height:"480px"}),n.css({"z-index":"0"}).click(function(){v.css({"background-color":"rgba(143, 235, 135, 0.4)"}).attr("isenable","0").text("Disabled"),c.css({"background-color":"#ebecf0",color:"#babecc"}).attr("isok","0").text("Edit Alarm"),n.css({"z-index":"-1",height:"420px"}).off()}))}),b.click(function(){0==$(this).attr("isdel")&&($(this).css({"background-color":"#ebecf0"}).attr("isdel","1"),c.css({color:"#ae1100"}).attr("isok","1").text("Delete Alarm!!!!"),r.text(""),1==h.attr("isonce")&&n.css({height:"480px"}),n.css({"z-index":"0"}).click(function(){b.css({"background-color":"#ec4a4a33"}).attr("isdel","0"),c.css({"background-color":"#ebecf0",color:"#babecc"}).attr("isok","0").text("Edit Alarm"),n.css({"z-index":"-1",height:"420px"}).off()}))}),f.children("input").keyup(function(){e()}),u.children("input").keyup(function(){e()});let z=[];f.children("button[ison]").on({click:function(){let a=$(this).attr("id").substr(6);if($(this).attr("ison")!=i[a])return z.pop(1),void(0==z.length&&$("#"+t+"edit").css({color:"#babecc"}).attr("isok","0"));z.push(1),$("#"+t+"edit").css({color:"#ae1100"}).attr("isok","1")}});let J=l.find("#manifest").text("This alarm will switch on "+p[x.children("option:selected").val()]+" at "+i.onHr+":"+i.onMin+" and switch it off at "+i.offHr+":"+i.offMin);function s(){if(0==h.attr("isonce"))return h.css("background-color","hsla(64, 97%, 62%, 0.4)"),u.slideDown(150),h.attr("isonce","1"),l.find(".unit").not(".special").hide(),void k.fadeIn(150);k.hide(),m.fadeIn(150),u.slideUp(150),h.attr("isonce","0").css("background-color","#ebecf0")}h.on("click",function(){s(),e()}),c.hover(function(){if("option"==x.children("option:selected").val())return d.text("Select any appliance form the select button to apply changes..").css("color","#d47304"),void d.slideDown(150);if(1==$(this).attr("isok")){if(v.attr("isenable")!=i.enable)return void $(this).css({"background-color":"green",color:"white"});if(1==b.attr("isdel"))return void $(this).css({"background-color":"#ae1100",color:"white"});$(this).css({"background-color":"#ae1100",color:"white"})}},function(){if(d.slideUp(150),1==$(this).attr("isok"))return h.attr("isonce"),h.attr("isonce"),v.attr("isenable")!=i.enable?void $(this).css({"background-color":"#ebecf0",color:"green"}):void $(this).css({"background-color":"#ebecf0",color:"#ae1100"});$(this).css({"background-color":"#ebecf0",color:"#babecc"})}),c.click(function(){if(1==b.attr("isdel")||v.attr("isenable")!=i.enable||1==$(this).attr("isok")){let a;if(1==b.attr("isdel"))a="?del=1&aID="+t.substr(5);else if(v.attr("isenable")!=i.enable)a="?enable="+v.attr("isenable")+"&aID="+t.substr(5);else if(1==$(this).attr("isok")){if("option"==x.children("option:selected").val())return;1==h.attr("isonce")?(""!=M.val()&&0==isNaN(M.val())&&(a="?shot=0"),""!=y.val()&&0==isNaN(y.val())&&(a="?shot=1"),a+="&onHr="+y.val()+"&onMin="+D.val()+"&offHr="+M.val()+"&offMin="+H.val()+"&pin="+x.children("option:selected").val()+"&sun="+E.attr("ison")+"&mon="+O.attr("ison")+"&tue="+F.attr("ison")+"&wed="+S.attr("ison")+"&thu="+T.attr("ison")+"&fri="+A.attr("ison")+"&sat="+I.attr("ison")+"&aID="+t.substr(5)+"&day="+g.val()+"&month="+N.val()+"&year="+w.val()+"&enable="+v.attr("isenable")):a="?shot=2&onHr="+y.val()+"&onMin="+D.val()+"&offHr="+M.val()+"&offMin="+H.val()+"&pin="+x.children("option:selected").val()+"&sun="+E.attr("ison")+"&mon="+O.attr("ison")+"&tue="+F.attr("ison")+"&wed="+S.attr("ison")+"&thu="+T.attr("ison")+"&fri="+A.attr("ison")+"&sat="+I.attr("ison")+"&aID="+t.substr(5)+"&enable="+v.attr("isenable")}console.log(a),$.get("/setalarm"+a,function(){setTimeout(()=>window.location.reload(),1e3)})}}),$("#mainBody").before(l),0==i.oneShot&&(s(),y.val("----"),D.val("----"),g.val(i.day),N.val(i.month),w.val(i.year),J.text("This alarm will switch OFF "+p[x.children("option:selected").val()]+" at "+i.offHr+":"+i.offMin+" on "+i.day+"-"+i.month+"-"+i.year+" and will be disabled after execution.")),1==i.oneShot&&(s(),M.val("----"),H.val("----"),g.val(i.day),N.val(i.month),w.val(i.year),J.text("This alarm will switch ON "+p[x.children("option:selected").val()]+" at "+i.onHr+":"+i.onMin+" on "+i.day+"-"+i.month+"-"+i.year+" and will be disabled after execution."))}}),$(".unit").not(".special").click(function(){"rgb(235, 236, 240)"!=$(this).css("background-color")?($(this).css({"background-color":"rgb(235, 236, 240)"}),$(this).attr("ison","0")):($(this).css({"background-color":"rgba(181, 219, 251, 0.4)"}),$(this).attr("ison","1"))});let i=$("<h2></h2>");i.attr({id:"showTime"}).css({color:"#d1ce0d","text-align":"center"}),$("#addAlarm0").before(i);let e=$("#showTime");$.getJSON("/gettime",(t,a)=>{var o=["omit","Sun","Mon","Tue","Wed","Thu","Fri","Sat"];let i=["omit","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"],s=t.sec,l=t.min;setInterval(()=>{60==s&&(l++,s=0),60==l&&window.location.reload();let a=o[t.wDay]+" "+i[t.mon]+" "+t.day+" "+t.yr+" "+t.hr+":"+l+":"+s+" (Local Time)";e.text(a),s++},1e3)})})});</script> <script src="/jquery.js?menu"></script></html>
)rawliteral";