const express = require("express");
const app = express();

var LED1_state = "off"
var Led1_c = "";
var LED2_state = "off";
var Led2_c = "";
var sw1 = "";
var sw2 = "";
var shine = "0";
var DETECT = -1;
var LIGHTR = -1;

app.use(express.static('./public'));

app.get("/index", (req, res) => {
    if (req.query.sw_detect == "DETECT"){
        DETECT = 1;
    }
    else{
        DETECT = 0;
    }
    if(DETECT == 0){
        if (req.query.sw == "ON") {
            if (req.query.LED1_state == "on") {
                Led1_c = "checked";
                LED1_state = "on";
            } else {
                Led1_c = "";
            }
            if (req.query.LED2_state == "on") {
                Led2_c = "checked";
                LED2_state = "on";
            } else {
                Led2_c = "";
            }
            sw1 = "checked";
            sw2 = "";
        } else if (req.query.sw == "OFF") {
            if (req.query.LED1_state == "on") {
                Led1_c = "checked";
                LED1_state = "off";
            } else {
                Led1_c = "";
            }
            if (req.query.LED2_state == "on") {
                Led2_c = "checked";
                LED2_state = "off";
            } else {
                Led2_c = "";
            }
            sw1 = "";
            sw2 = "checked";
        }
        if (req.query.shineT != "") {
            shine = req.query.shineT;
        }
        if (shine == "0") {
            if(LED1_state == "on"){
                controlLED("LED1", "on");
            }
            else if(LED1_state == "off"){
                controlLED("LED1", "off");
            }
            if(LED2_state == "on"){
                controlLED("LED2", "on");
            }
            else if(LED2_state == "off"){
                controlLED("LED2", "off");
            }
            //alert("NOOOOOOOOOOOOOOO");
        } else {
            controlLED("Mode_Shine", shine);
            //alert("YESSSSSSSSS");
        }
        //console.log("%d %d %d %d",LED1_state,LED2_state,LED3_state,LED4_state)
        var response = `
            <!DOCTYPE html>
            <html lang="en">
            <head>
                <meta charset="UTF-8">
                <meta name="viewport" connect="width=\, initial-scale=1.0">
                <title>Nodejs</title>
            </head>
            <body>
                <p>
                    <h1>Nodejs</h1>
                </p>
                <hr>
                <form action="/index" method="get">
                    <h2>LED Control Panel</h2>
                    <div>
                        <input type="checkbox" id="LED1_state" name="LED1_state" ${Led1_c}>
                        <label for="LED1">LED1</label>

                        <input type="checkbox" id="LED2_state" name="LED2_state" ${Led2_c}>
                        <label for="LED2">LED2</label>
                    </div>
                    <div>

                        <input type="radio" id="on" name="sw" value="ON" ${sw1}>
                        <label for="on">ON</label>

                        <input type="radio" id="off" name="sw" value="OFF" ${sw2}>
                        <label for="off">OFF</label>
                    </div>
                    <br>
                    <input type="submit" value="Submit">

                    <p>LED1 ${LED1_state}</p>
                    <p>LED2 ${LED2_state}</p>

                    <hr>
                    <h2>LED Switch Frequency</h2>
                    <input type="text" name="shineT" value=${shine}>
                    <br>
                    <input type="submit" value="Mode_Shine">
                    <br>
                    <p>Mode_Shine_time: ${shine}</p>
                    <hr><br>
                    <div>
                    <input type="submit" value="Submit">
                    <input type="radio" id="DETECT" name="sw_detect" value="DETECT">
                    <label for="DETECT">DETECT</label>
        
                    <input type="radio" id="NO_DETECT" name="sw_detect" value="NO_DETECT">
                    <label for="NO_DETECT">NO_DETECT</label>
                </div>
                </form>
            </body>
            </html>`;
    }
    else if (DETECT == 1)
    {
        var getPromise = getR().catch(function(e) {
            console.log(e); // "Uh-oh!"
          });
        console.log(getPromise);
        getPromise = 0;
        var response=`
        <!DOCTYPE html>
        <html lang="en">
        
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" connect="width=, initial-scale=1.0">
            <title>Nodejs</title>
        </head>
        
        <body>
            <p>
                <h1>Nodejs</h1>
            </p>
            <hr>
            <form action="/index" method="get">
            <b>感測器偵測中</b><br>
            <p id="word">adc_value= ${getPromise}</p><br>
            <div>
                <input type="submit" value="Submit">
                <input type="radio" id="DETECT" name="sw_detect" value="DETECT">
                <label for="DETECT">DETECT</label>
    
                <input type="radio" id="NO_DETECT" name="sw_detect" value="NO_DETECT">
                <label for="NO_DETECT">NO_DETECT</label>
            </div>
            <br>
            </form>
        </body>
        <script>
          setInterval(GetResult, 1000);
          console.log("run Interval");
          function GetResult(){
              $.ajax({
                  type:"get",
                  url:"/index",
                  success:function(result){
                      $('#word').text(result);
                      console.log("word change");
                  },
                  error:function(){
                      alert("error QAQ");
                  }
              })
          }
      </script>
        </html>  
        `
    }
    res.send(response)
});

function controlLED(LED, POWER) {
    let child_process = require("child_process");
    let process = child_process.execFile('sudo', ["./C++/gpio_main", LED, POWER]);
    process.stdout.on('data', (data) => {
        console.log(`control stdout: ${data}`);
    });
    process.stderr.on('data', (data) => {
        console.error(`control stderr: ${data}`);
    });
}

function getR(){
    return new Promise(function(resolve, reject){
        let child_process = require("child_process");
        let process = child_process.exec('python', ["./LAB5.py"]);
        process.stdout.on('data', (data) => {
            console.log(`getR stdout: ${data}`);
            resolve(data);
        });
        process.stderr.on('data', (data) => {
            console.error(`getR stderr: ${data}`);
            reject(data);
        });
    })
}

const PORT = process.env.PORT || 8001;
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}.`);
});