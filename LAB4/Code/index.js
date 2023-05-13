const express = require("express");
const app = express();

var LED1_state = "off"
var Led1_c = "";
var LED2_state = "off";
var Led2_c = "";
var LED3_state = "off";
var Led3_c = "";
var LED4_state = "off";
var Led4_c = "";
var sw1 = "";
var sw2 = "";
var shine = "0";

app.use(express.static('./public'));

app.get("/index", (req, res) => {
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
        if (req.query.LED3_state == "on") {
            Led3_c = "checked";
            LED3_state = "on";
        } else {
            Led3_c = "";
        }
        if (req.query.LED4_state == "on") {
            Led4_c = "checked";
            LED4_state = "on";
        } else {
            Led4_c = "";
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
        if (req.query.LED3_state == "on") {
            Led3_c = "checked";
            LED3_state = "off";
        } else {
            Led3_c = "";
        }
        if (req.query.LED4_state == "on") {
            Led4_c = "checked";
            LED4_state = "off";
        } else {
            Led4_c = "";
        }
        sw1 = "";
        sw2 = "checked";
    }
    if (req.query.shineT != "") {
        shine = req.query.shineT
    }
    if (shine != "0") {
        controlLED("LED1", LED1_state);
        controlLED("LED2", LED2_state);
        controlLED("LED3", LED3_state);
        controlLED("LED4", LED4_state);
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
					<input type="checkbox" id="LED3_state" name="LED3_state" ${Led3_c}>
					<label for="LED3">LED3</label>

					<input type="checkbox" id="LED4_state" name="LED4_state" ${Led4_c}>
					<label for="LED4">LED4</label>
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
				<p>LED3 ${LED3_state}</p>
				<p>LED4 ${LED4_state}</p>

				<hr>
				<h2>LED Switch Frequency</h2>
				<input type="text" name="shineT" value=${shine}>
				<br>
				<input type="submit" value="Mode_Shine">
				<br>
				<p>Mode_Shine_time: ${shine}</p>

			</form>
		</body>
		</html>`;
    res.send(response)
});

function controlLED(LED, POWER) {
    let child_process = require("child_process");
    let process = child_process.execFile('sudo', ["./C++/gpio_main", LED, POWER]);
    process.stdout.on('data', (data) => {
        console.log(`stdout: ${data}`);
    });
    process.stderr.on('data', (data) => {
        console.error(`stderr: ${data}`);
    });
}

const PORT = process.env.PORT || 8000;
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}.`);
});