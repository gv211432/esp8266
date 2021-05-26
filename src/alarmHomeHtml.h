const char alarmHome_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html lang="en"><head><meta charset="UTF-8" /><meta http-equiv="X-UA-Compatible" content="IE=edge" /><meta name="viewport" content="width=device-width, initial-scale=1.0" /><title>Alarms</title><link rel="stylesheet" href="/style.css" /><style>.card{width:380px;border-radius:20px;margin-bottom:10px;box-shadow:-2px -2px 5px #fff,2px 2px 5px #babecc}.middleIt{display:flex;justify-content:center;position:relative}</style><script src="/jquery.js"></script></head><body id="body"><br /><br /><div id="mainBody" class="middleIt"><div style=" position: absolute; background-color: pink; width: 380px; height: 380px; border-radius: 20px 20px 0 0; z-index: -1; opacity: 0; " id="hider0"></div><div class="card"><form action="" id="formNum0"><div class="custom-select"><button class="unit special" type="button" id="buttonNum0" style=" float: left; box-shadow: inset 2px 2px 5px #babecc, inset -5px -5px 10px #fff; margin-right: 30px; "> -- </button><select id="select0"><option value="option">Select Appliance &#9662;</option></select></div><br /><br /><h2 id="alarmInfo"></h2><h1 id="alarmAssist"></h1><input type="text" id="onHr0" placeholder="On Hr" style="width: 90px; display: inline" /><span style="float: right; width: 220px; margin-top: -10px"><h2 id="showOnceInfo"> You can only use ON function or OFF function. If On is filled OFF will be IGNORED.. This alarm will be disabled once its completed. No date means todays date applied.</h2></span><button class="unit" type="button" id="buttonMon0" ison="0"> mon </button><button class="unit" type="button" id="buttonTue0" ison="0"> Tue </button><button class="unit" type="button" id="buttonWed0" ison="0"> wed </button><br /><br /><input type="text" placeholder="On Min" id="onMin0" style="width: 90px; display: inline" /><button class="unit" type="button" id="buttonThu0" ison="0"> Thu </button><button class="unit" type="button" id="buttonFri0" ison="0"> Fri </button><button class="unit" type="button" id="buttonSat0" ison="0"> Sat </button><br /><br /><input type="text" placeholder="Off Hr" id="offHr0" style="width: 90px; display: inline" /><button class="unit special del" type="button" id="buttonDel0" isdel="0" style=" width: 129px; border-radius: 320px; background-color: #ec4a4a33; "> Delete </button><button class="unit" type="button" id="buttonSun0" ison="0"> Sun </button><br /><br /><input type="text" placeholder="Off Min" id="offMin0" style="width: 90px; display: inline" /><button class="unit special once" type="button" id="buttonOnce0" isonce="0" style="padding: 27px"> Once </button><button class="unit special enable" type="button" id="enable0" isenable="0" style="width: 129px; border-radius: 320px"> Enable </button><br /><br /><h2 id="manifest"></h2><div id="myDate"><input type="text" placeholder="Day" id="day0" style="width: 96px; display: inline" /><input type="text" placeholder="Month" id="month0" style="width: 96px; display: inline" /><input type="text" placeholder="Year" id="year0" style="width: 96px; display: inline" /><br /><br /><br /></div><button class="red" type="button" id="addAlarm0" isok="0"> Add New Alarm </button><h2 id="allErr" style="text-align: center; color: #d47304"></h2></form><br /></div></div><br /><br /></body><script>$(function(){let alarmInfo0=$("#alarmInfo").hide();let alarmAssist0=$("#alarmAssist").hide();let allError=$("#allErr").hide();let select0=$("#select0");let onHr0=$("#onHr0");let onMin0=$("#onMin0");let offHr0=$("#offHr0");let offMin0=$("#offMin0");let myShowOnceInfo=$("#showOnceInfo");let buttonMon0=$("#buttonMon0");let buttonTue0=$("#buttonTue0");let buttonWed0=$("#buttonWed0");let buttonThu0=$("#buttonThu0");let buttonFri0=$("#buttonFri0");let buttonSat0=$("#buttonSat0");let buttonSun0=$("#buttonSun0");let dayButton=$(".unit").not(".special");let enable0=$("#enable0");let buttonOnce=$("#buttonOnce0");let day0=$("#day0");let month0=$("#month0");let year0=$("#year0");let myDate=$("#myDate");let addAlarm0=$("#addAlarm0");let appliances={1:"Hall_Fan",2:"Kitchen_Light"};let myOption1=$("<option></option>").attr("value","1").text(appliances[1]);let myOption2=$("<option></option>").attr("value","2").text(appliances[2]);select0.append(myOption1);select0.append(myOption2);$("input").on({focus:function(){alarmInfo0.text("Alarm must be written in 24Hr format!! where 0 equals 12am and 12 equals 12pm");alarmInfo0.slideDown(150);},keyup:function(){if($(this).attr("id")=="onHr0"){alarmAssist0.text("Valid time is in between 0 and 23, ON time in hour is : "+ $(this).val());alarmAssist0.slideDown(150);return;}if($(this).attr("id")=="onMin0"){alarmAssist0.text("Valid time is in between 0 and 59, ON time in minutes is : "+ $(this).val());alarmAssist0.slideDown(150);return;}if($(this).attr("id")=="offHr0"){alarmAssist0.text("Valid time is in between 0 and 23, OFF time in hour is : "+ $(this).val());alarmAssist0.slideDown(150);return;}if($(this).attr("id")=="offMin0"){alarmAssist0.text("Valid time is in between 0 and 59, OFF time in minutes is : "+ $(this).val());alarmAssist0.slideDown(150);return;}},});buttonMon0.click(()=>{$(this).attr("ison")==1?$(this).attr("ison","0"):$(this).attr("ison","1");});buttonTue0.click(()=>{$(this).attr("ison")==1?$(this).attr("ison","0"):$(this).attr("ison","1");});buttonWed0.click(()=>{$(this).attr("ison")==1?$(this).attr("ison","0"):$(this).attr("ison","1");});buttonThu0.click(()=>{$(this).attr("ison")==1?$(this).attr("ison","0"):$(this).attr("ison","1");});buttonFri0.click(()=>{$(this).attr("ison")==1?$(this).attr("ison","0"):$(this).attr("ison","1");});buttonSat0.click(()=>{$(this).attr("ison")==1?$(this).attr("ison","0"):$(this).attr("ison","1");});buttonSun0.click(()=>{$(this).attr("ison")==1?$(this).attr("ison","0"):$(this).attr("ison","1");});enable0.click(()=>{enable0.attr("isenable")==0?enable0.attr("isenable","1").css({"background-color":"rgba(143, 235, 135, 0.4)"}).text("Enabled"):enable0.attr("isenable","0").css({"background-color":"#ebecf0"}).text("Enable");});buttonOnce.on("click",function(){if($(this).attr("isonce")==0){$(this).css("background-color","hsla(64, 97%, 62%, 0.4)");myDate.slideDown("slow");$(this).attr("isonce","1");dayButton.hide();myShowOnceInfo.fadeIn("slow");return;} myShowOnceInfo.hide();dayButton.fadeIn("slow");myDate.slideUp("slow");$(this).attr("isonce","0").css("background-color","#ebecf0");});addAlarm0.hover(function(){if(select0.children("option:selected").val()=="option"){allError.text("Select any appliance form the select button to apply changes..").css("color","#d47304");allError.slideDown(150);return;}if(onHr0.val()>=24||onHr0.val()<0||onHr0.val()==""){if(offHr0.val()>=24||offHr0.val()<0||offHr0.val()==""){allError.text("Problem with ON hour.. ON or OFF must be filled!!");allError.slideDown(150);$(this).attr("isok","0");return;}}if(offHr0.val()>=24||offHr0.val()<0||offHr0.val()==""){if(onHr0.val()>=24||onHr0.val()<0||onHr0.val()==""){allError.text("Problem with OFF hour..");allError.slideDown(150);$(this).attr("isok","0");return;}}if(onMin0.val()>=60||onMin0.val()<0){allError.text("Problem with ON minute..");allError.slideDown(150);$(this).attr("isok","0");return;}if(offMin0.val()>=60||offMin0.val()<0){allError.text("Problem with OFF minute..");allError.slideDown(150);$(this).attr("isok","0");return;}if(buttonOnce.attr("isonce")==0){if(onHr0.val()==""||offHr0.val()==""){allError.text("Please mention On Hour and Off Hour..");allError.slideDown(150);return;} allError.text("This alarm will switch ON "+ appliances[select0.children("option:selected").val()]+" at "+ Number(onHr0.val())+":"+ Number(onMin0.val())+" and switch it OFF at "+ Number(offHr0.val())+":"+ Number(offMin0.val())).css("color","green");allError.slideDown(150);}if(buttonOnce.attr("isonce")==1){if(onHr0.val()!=""){allError.text("This alarm will switch ON "+ appliances[select0.children("option:selected").val()]+" at "+ Number(onHr0.val())+":"+ Number(onMin0.val())+" and disable it after execution.").css("color","green");allError.slideDown(150);}else{allError.text("This alarm will switch OFF "+ appliances[select0.children("option:selected").val()]+" at "+ Number(offHr0.val())+":"+ Number(offMin0.val())+" and disable it after execution.").css("color","green");allError.slideDown(150);}} $(this).css({"background-color":"#ae1100",color:"white"}).attr("isok","1");},function(){$(this).css({"background-color":"#ebecf0",color:"#ae1100"});allError.slideUp(150);});addAlarm0.click(function(){let setTheAlarm;if(buttonOnce.attr("isonce")==1){if($(this).attr("isok")==1){let switchType=0;if(onHr0.val()!="")switchType=1;setTheAlarm="?shot="+ switchType+"&onHr="+ onHr0.val()+"&onMin="+ onMin0.val()+"&offHr="+ offHr0.val()+"&offMin="+ offMin0.val()+"&pin="+ select0.children("option:selected").val()+"&enable="+ enable0.attr("isenable");}}else if($(this).attr("isok")==1){setTheAlarm="?shot=2"+"&onHr="+ onHr0.val()+"&onMin="+ onMin0.val()+"&offHr="+ offHr0.val()+"&offMin="+ offMin0.val()+"&pin="+ select0.children("option:selected").val()+"&sun="+ buttonSun0.attr("ison")+"&mon="+ buttonMon0.attr("ison")+"&tue="+ buttonTue0.attr("ison")+"&wed="+ buttonWed0.attr("ison")+"&thu="+ buttonThu0.attr("ison")+"&fri="+ buttonFri0.attr("ison")+"&sat="+ buttonSat0.attr("ison")+"&enable="+ enable0.attr("isenable");} allError.slideDown();$.get("/setalarm"+setTheAlarm,function(){setTimeout(()=>window.location.reload(),1000);});});$("#myDate").hide();$("#showOnceInfo").hide();$.getJSON("/alarmjson",function(result){let alarmCount=1;let timeForClone=new Date();$.each(result,(i,field)=>{if(field.free==1){if(field.oneShot==0){}if(field.oneShot==1){} let myClon=$("#mainBody").clone().attr("id",i);let myHider=myClon.find("#hider0").attr("id",i+"hider");let newAlarmInfo=myClon.find("#alarmInfo");newAlarmInfo.attr("id",i+alarmInfo);let newAlarmAssist=myClon.find("#alarmAssist");newAlarmAssist.attr("id",i+"alarmAssist");let myAddAlarm=myClon.find("#addAlarm0").attr("id",i+"edit").text("Edit Alarm").css({color:"#babecc"});let myAllErr=myClon.find("#allErr").attr("id",i+"Err");myAllErr.hide();let myEnable=myClon.find("#enable0");let myDel=myClon.find("#buttonDel0").attr("id",i+"Del");let formEle=myClon.find("#formNum0").attr("id",i+"form");let once=myClon.find("#buttonOnce0").attr("id",i+"once");let myDate=myClon.find("#myDate").attr("id",i+"mydate");let myShowOnceInfo=myClon.find("#showOnceInfo").attr("id",i+"onceInfo");let dayButton=myClon.find(".unit").not(".special");let myDay=myClon.find("#day0").attr("id",i+"day");let myMonth=myClon.find("#month0").attr("id",i+"month");let myYear=myClon.find("#year0").attr("id",i+"year");let selectAppliance=myClon.find("#select0").attr("id",i+"app");selectAppliance.children("[value='"+2+"']").attr("selected","");selectAppliance.change(function(){let selectedApp=$(this).children("option:selected").val();});myClon.find("#buttonNum0").text(alarmCount);alarmCount++;let myOnHr=myClon.find("#onHr0");myOnHr.attr({id:i+"onHr",value:field.onHr});let myOnMin=myClon.find("#onMin0");myOnMin.attr({id:i+"onMin",value:field.onMin});let myOffHr=myClon.find("#offHr0").attr({id:i+"offHr",value:field.offHr});let myOffMin=myClon.find("#offMin0");myOffMin.attr({id:i+"offMin",value:field.offMin});let myMon=myClon.find("#buttonMon0");myMon.attr("id",i+"mon");if(field.mon==1){myMon.css({"background-color":"rgba(181, 219, 251, 0.4)"});myMon.attr("ison","1");} let myTue=myClon.find("#buttonTue0");myTue.attr("id",i+"tue");if(field.tue==1){myTue.css({"background-color":"rgba(181, 219, 251, 0.4)"});myTue.attr("ison","1");} let myWed=myClon.find("#buttonWed0");myWed.attr("id",i+"wed");if(field.wed==1){myWed.css({"background-color":"rgba(181, 219, 251, 0.4)"});myWed.attr("ison","1");} let myThu=myClon.find("#buttonThu0");myThu.attr("id",i+"thu");if(field.thu==1){myThu.css({"background-color":"rgba(181, 219, 251, 0.4)"});myThu.attr("ison","1");} let myFri=myClon.find("#buttonFri0");myFri.attr("id",i+"fri");if(field.fri==1){myFri.css({"background-color":"rgba(181, 219, 251, 0.4)"});myFri.attr("ison","1");} let mySat=myClon.find("#buttonSat0");mySat.attr("id",i+"sat");if(field.sat==1){mySat.css({"background-color":"rgba(181, 219, 251, 0.4)"});mySat.attr("ison","1");} let mySun=myClon.find("#buttonSun0");mySun.attr("id",i+"sun");if(field.sun==1){mySun.css({"background-color":"rgba(181, 219, 251, 0.4)"});mySun.attr("ison","1");} myEnable.attr("id",i+"enable");if(field.enable==1){myEnable.css({"background-color":"rgba(143, 235, 135, 0.4)"}).text("Enabled").attr("isenable","1");}if(field.enable==0){myEnable.css({"background-color":"rgba(143, 235, 135, 0.4)"}).text("Disabled").attr("isenable","0");} myEnable.click(function(){if($(this).attr("isenable")==1){$(this).css({"background-color":"#ebecf0"}).attr("isenable","0").text("Disable");myAddAlarm.css({color:"green"}).attr("isok","1").text("Disable Alarm!!");if(once.attr("isonce")==1){myHider.css({height:"480px"});} myHider.css({"z-index":"0"}).click(function(){myEnable.css({"background-color":"rgba(143, 235, 135, 0.4)"}).attr("isenable","1").text("Enabled");myAddAlarm.css({"background-color":"#ebecf0",color:"#babecc"}).attr("isok","0").text("Edit Alarm");myHider.css({"z-index":"-1",height:"420px"}).off();});return;}if($(this).attr("isenable")==0){$(this).css({"background-color":"#ebecf0"}).attr("isenable","1").text("Enable");myAddAlarm.css({color:"green"}).attr("isok","1").text("Enable Alarm!!");if(once.attr("isonce")==1){myHider.css({height:"480px"});} myHider.css({"z-index":"0"}).click(function(){myEnable.css({"background-color":"rgba(143, 235, 135, 0.4)"}).attr("isenable","0").text("Disabled");myAddAlarm.css({"background-color":"#ebecf0",color:"#babecc"}).attr("isok","0").text("Edit Alarm");myHider.css({"z-index":"-1",height:"420px"}).off();});}});myDel.click(function(){if($(this).attr("isdel")==0){$(this).css({"background-color":"#ebecf0"}).attr("isdel","1");myAddAlarm.css({color:"#ae1100",}).attr("isok","1").text("Delete Alarm!!!!");newAlarmAssist.text("");if(once.attr("isonce")==1){myHider.css({height:"480px"});} myHider.css({"z-index":"0"}).click(function(){myDel.css({"background-color":"#ec4a4a33"}).attr("isdel","0");myAddAlarm.css({"background-color":"#ebecf0",color:"#babecc",}).attr("isok","0").text("Edit Alarm");myHider.css({"z-index":"-1",height:"420px"}).off();});}});function validationKeyPress(){if(field.oneShot==2){if(once.attr("isonce")==1){if(myOnHr.val()!=""||myOffHr.val()!=""){if(myOffHr.val()!=""){if(myOnHr.val()>23||myOnHr.val()<0||isNaN(myOnHr.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}}if(myOnMin.val()!=""){if(myOnMin.val()>59||myOnMin.val()<0||isNaN(myOnMin.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}}if(myOffHr.val()!=""){if(myOffHr.val()>23||myOffHr.val()<0||isNaN(myOffHr.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}}if(myOffMin.val()!=""){if(myOffMin.val()>59||myOffMin.val()<0||isNaN(myOffMin.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}}if(myDay.val()!=""){if(myDay.val()<1||myDay.val()>31||isNaN(myDay.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}}if(myMonth.val()!=""){if(myMonth.val()<1||myMonth.val()>12||isNaN(myMonth.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}}if(myYear.val()!=""){if(myYear.val()<timeForClone.getFullYear()||myYear.val()>2060||isNaN(myYear.val())||myYear.val().length!=4){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}} myAddAlarm.css({color:"#ae1100"}).attr("isok","1");return;}else{myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}}if(once.attr("isonce")==0){if(myOnHr.val()==""||myOnHr.val()>23||myOnHr.val()<0||isNaN(myOnHr.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}if(myOnMin.val()==""||myOnMin.val()>59||myOnMin.val()<0||isNaN(myOnMin.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}if(myOffHr.val()==""||myOffHr.val()>23||myOffHr.val()<0||isNaN(myOffHr.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}if(myOffMin.val()==""||myOffMin.val()>59||myOffMin.val()<0||isNaN(myOffMin.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}if(myOnHr.val()!=field.onHr||myOnMin.val()!=field.onMin||myOffHr.val()!=field.offHr||myOffMin.val()!=field.offMin){myAddAlarm.css({color:"#ae1100"}).attr("isok","1");return;}else{myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}}}if(field.oneShot==0||field.oneShot==1){if(once.attr("isonce")==0){if(myOnHr.val()==""||myOnHr.val()>23||myOnHr.val()<0||isNaN(myOnHr.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}if(myOnMin.val()==""||myOnMin.val()>59||myOnMin.val()<0||isNaN(myOnMin.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}if(myOffHr.val()==""||myOffHr.val()>23||myOffHr.val()<0||isNaN(myOffHr.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}if(myOffMin.val()==""||myOffMin.val()>59||myOffMin.val()<0||isNaN(myOffMin.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}if(myOnHr.val()!=field.onHr||myOnMin.val()!=field.onMin||myOffHr.val()!=field.offHr||myOffMin.val()!=field.offMin){myAddAlarm.css({color:"#ae1100"}).attr("isok","1");return;}else{myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}}if(myOnHr.val()!=""&&isNaN(myOnHr.val())==false){if(myOnHr.val()>23||myOnHr.val()<0||isNaN(myOnHr.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}if(myOnMin.val()==""||myOnMin.val()>59||myOnMin.val()<0||isNaN(myOnMin.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}if(myDay.val()!=""){if(myDay.val()<1||myDay.val()>31||isNaN(myDay.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}}if(myMonth.val()!=""){if(myMonth.val()<1||myMonth.val()>12||isNaN(myMonth.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}}if(myYear.val()!=""){if(myYear.val()<timeForClone.getFullYear()||myYear.val()>2060||isNaN(myYear.val())||myYear.val().length!=4){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}}if(myOnHr.val()!=field.onHr||myOnMin.val()!=field.onMin||myDay.val()!=field.day||myMonth.val()!=field.month||myYear.val()!=field.year){myAddAlarm.css({color:"#ae1100"}).attr("isok","1");return;}else{myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}}if(myOffHr.val!=""&&isNaN(myOffHr.val())==false){if(myOffHr.val()>23||myOffHr.val()<0||isNaN(myOffHr.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}if(myOffMin.val()==""||myOffMin.val()>59||myOffMin.val()<0||isNaN(myOffMin.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}if(myDay.val()!=""){if(myDay.val()<1||myDay.val()>31||isNaN(myDay.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}}if(myMonth.val()!=""){if(myMonth.val()<1||myMonth.val()>12||isNaN(myMonth.val())){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}}if(myYear.val()!=""){if(myYear.val()<timeForClone.getFullYear()||myYear.val()>2060||isNaN(myYear.val())||myYear.val().length!=4){myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}}if(myOffHr.val()!=field.offHr||myOffMin.val()!=field.offMin||myDay.val()!=field.day||myMonth.val()!=field.month||myYear.val()!=field.year){myAddAlarm.css({color:"#ae1100"}).attr("isok","1");return;}else{myAddAlarm.css({color:"#babecc"}).attr("isok","0");return;}}} myAddAlarm.css({color:"#babecc"}).attr("isok","0");} formEle.children("input").keyup(function(){validationKeyPress();});myDate.children("input").keyup(function(){validationKeyPress();});let butPressKeep=[];formEle.children("button[ison]").on({click:function(){let butId=$(this).attr("id").substr(6);if($(this).attr("ison")!=field[butId]){butPressKeep.pop(1);if(butPressKeep.length==0){$("#"+i+"edit").css({color:"#babecc"}).attr("isok","0");} return;} butPressKeep.push(1);$("#"+i+"edit").css({color:"#ae1100"}).attr("isok","1");},});let myManifest=myClon.find("#manifest").text("This alarm will switch on "+ appliances[selectAppliance.children("option:selected").val()]+" at "+ field.onHr+":"+ field.onMin+" and switch it off at "+ field.offHr+":"+ field.offMin);function toggelOnce(){if(once.attr("isonce")==0){once.css("background-color","hsla(64, 97%, 62%, 0.4)");myDate.slideDown(150);once.attr("isonce","1");myClon.find(".unit").not(".special").hide();myShowOnceInfo.fadeIn(150);return;} myShowOnceInfo.hide();dayButton.fadeIn(150);myDate.slideUp(150);once.attr("isonce","0").css("background-color","#ebecf0");} once.on("click",function(){toggelOnce();validationKeyPress();});myAddAlarm.hover(function(){if(selectAppliance.children("option:selected").val()=="option"){myAllErr.text("Select any appliance form the select button to apply changes..").css("color","#d47304");myAllErr.slideDown(150);return;}if($(this).attr("isok")==1){if(myEnable.attr("isenable")!=field.enable){$(this).css({"background-color":"green",color:"white",});return;}if(myDel.attr("isdel")==1){$(this).css({"background-color":"#ae1100",color:"white",});return;} $(this).css({"background-color":"#ae1100",color:"white",});}},function(){myAllErr.slideUp(150);if($(this).attr("isok")==1){if(once.attr("isonce")==1){}if(once.attr("isonce")==0){}if(myEnable.attr("isenable")!=field.enable){$(this).css({"background-color":"#ebecf0",color:"green",});return;} $(this).css({"background-color":"#ebecf0",color:"#ae1100",});return;} $(this).css({"background-color":"#ebecf0",color:"#babecc",});});myAddAlarm.click(function(){if(myDel.attr("isdel")==1||myEnable.attr("isenable")!=field.enable||$(this).attr("isok")==1){let setTheAlarm;if(myDel.attr("isdel")==1){setTheAlarm="?del=1&aID="+i.substr(5);}else if(myEnable.attr("isenable")!=field.enable){setTheAlarm="?enable="+ myEnable.attr("isenable")+"&aID="+ i.substr(5);}else if($(this).attr("isok")==1){if(selectAppliance.children("option:selected").val()=="option"){return;}if(once.attr("isonce")==1){if(myOffHr.val()!=""&&isNaN(myOffHr.val())==false){setTheAlarm="?shot=0";}if(myOnHr.val()!=""&&isNaN(myOnHr.val())==false){setTheAlarm="?shot=1";} setTheAlarm+="&onHr="+ myOnHr.val()+"&onMin="+ myOnMin.val()+"&offHr="+ myOffHr.val()+"&offMin="+ myOffMin.val()+"&pin="+ selectAppliance.children("option:selected").val()+"&sun="+ mySun.attr("ison")+"&mon="+ myMon.attr("ison")+"&tue="+ myTue.attr("ison")+"&wed="+ myWed.attr("ison")+"&thu="+ myThu.attr("ison")+"&fri="+ myFri.attr("ison")+"&sat="+ mySat.attr("ison")+"&aID="+ i.substr(5)+"&day="+ myDay.val()+"&month="+ myMonth.val()+"&year="+ myYear.val()+"&enable="+ myEnable.attr("isenable");}else{setTheAlarm="?shot=2"+"&onHr="+ myOnHr.val()+"&onMin="+ myOnMin.val()+"&offHr="+ myOffHr.val()+"&offMin="+ myOffMin.val()+"&pin="+ selectAppliance.children("option:selected").val()+"&sun="+ mySun.attr("ison")+"&mon="+ myMon.attr("ison")+"&tue="+ myTue.attr("ison")+"&wed="+ myWed.attr("ison")+"&thu="+ myThu.attr("ison")+"&fri="+ myFri.attr("ison")+"&sat="+ mySat.attr("ison")+"&aID="+ i.substr(5)+"&enable="+ myEnable.attr("isenable");}} console.log(setTheAlarm);$.get("/setalarm"+setTheAlarm,function(){setTimeout(()=>window.location.reload(),1000);});}});$("#mainBody").before(myClon);if(field.oneShot==0){toggelOnce();myOnHr.val("----");myOnMin.val("----");myDay.val(field.day);myMonth.val(field.month);myYear.val(field.year);myManifest.text("This alarm will switch OFF "+ appliances[selectAppliance.children("option:selected").val()]+" at "+ field.offHr+":"+ field.offMin+" on "+ field.day+"-"+ field.month+"-"+ field.year+" and will be disabled after execution.");}if(field.oneShot==1){toggelOnce();myOffHr.val("----");myOffMin.val("----");myDay.val(field.day);myMonth.val(field.month);myYear.val(field.year);myManifest.text("This alarm will switch ON "+ appliances[selectAppliance.children("option:selected").val()]+" at "+ field.onHr+":"+ field.onMin+" on "+ field.day+"-"+ field.month+"-"+ field.year+" and will be disabled after execution.");}}});$(".unit").not(".special").click(function(){if($(this).css("background-color")!="rgb(235,236,240)"){$(this).css({"background-color":"rgb(235,236,240)"});$(this).attr("ison","0");}else{$(this).css({"background-color":"rgba(181, 219, 251, 0.4)"});$(this).attr("ison","1");}});let myShowTime=$("<h2></h2>");myShowTime.attr({id:"showTime"}).css({color:"#d1ce0d","text-align":"center"});$("#addAlarm0").before(myShowTime);let dTime=$("#showTime");$.getJSON("/gettime",(data,status)=>{var myWeekDay=["omit","Sun","Mon","Tue","Wed","Thu","Fri","Sat",];let myMonth=["omit","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec",];let secIncre=data.sec;let minIncre=data.min;setInterval(()=>{if(secIncre==60){minIncre++;secIncre=0;}if(minIncre==60){window.location.reload();} let showTime=""+ myWeekDay[data.wDay]+" "+ myMonth[data.mon]+" "+ data.day+" "+ data.yr+" "+ data.hr+":"+ minIncre+":"+ secIncre+" (Local Time)";dTime.text(showTime);secIncre++;},1000);});});});</script></html>
)rawliteral";