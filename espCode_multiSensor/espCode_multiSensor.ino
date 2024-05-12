#include <WiFi.h>
#include <WiFiClient.h>
#include <Servo.h>

const char* ssid = "";
const char* password = "";

// LED pins
#define RED_LED_PIN 2
#define YELLOW_LED_PIN 4
#define BLUE_LED_PIN 5

// RGB LED pins
#define RGB_RED_LED_PIN 14
#define RGB_GREEN_LED_PIN 12
#define RGB_BLUE_LED_PIN 13

// Piezo buzzer pin
#define PIEZO_PIN 10

// Servo pin
#define SERVO_PIN 26

void htmlCodePrint(WiFiClient);
int handleGetRequest(String);

void RGBledColor(String);
void servoPosition(String);

WiFiServer server(80);

String header;
String valueString = String(5);
int pos1 = 0, pos2 = 0;

Servo servoMotor;

void setup() {
  Serial.begin(74880);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);

  pinMode(RGB_RED_LED_PIN, OUTPUT);
  pinMode(RGB_GREEN_LED_PIN, OUTPUT);
  pinMode(RGB_BLUE_LED_PIN, OUTPUT);

  servoMotor.attach(SERVO_PIN);

  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client){
    Serial.println("New Client.");
    char currentLine[1000];
    int fl = 0;
    int i = 0;
    while (client.connected()){
      
      if (client.available()){
        if (!fl) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();

          htmlCodePrint(client);

          client.println();
          fl = 1;
        }

        char c = client.read();


        if (c == '\n'){
          // GET request handlerSerial.write(c);
          currentLine[i] = '\0';
          String buff(currentLine);
          if (handleGetRequest(buff)) break;
          i = 0;
        }
        else {
          currentLine[i++] = c;
        }
      }
      else {
        i = 0;
      }
    }
    fl = 0;
  }
}


int handleGetRequest(String header){
  if (header.indexOf("GET") == -1) return 0;

  // RED LED
  Serial.println(header);
  if (header.indexOf("GET /?redLED=")>=0) {
    pos1 = header.indexOf("=");
    pos2 = header.indexOf("&");
    valueString = header.substring(pos1+1, pos2);
    Serial.println(valueString);

    // Turn on/off the red LED
    if (valueString == "on") {
      digitalWrite(RED_LED_PIN, HIGH);
      Serial.println("Red LED on");
    } else if (valueString == "off") {
      digitalWrite(RED_LED_PIN, LOW);
      Serial.println("Red LED off");
    }
  }

  // YELLOW LED
  else if (header.indexOf("GET /?yellowLED=")>=0) {
    pos1 = header.indexOf('/?yellowLED=');
    pos2 = header.indexOf('&');
    valueString = header.substring(pos1+1, pos2);
    Serial.println(valueString);

    // Turn on/off the yellow LED
    if (valueString == "on") {
      digitalWrite(YELLOW_LED_PIN, HIGH);
      Serial.println("Yellow LED on");
    } else if (valueString == "off") {
      digitalWrite(YELLOW_LED_PIN, LOW);
      Serial.println("Yellow LED off");
    }
  }

  // BLUE LED
  else if (header.indexOf("GET /?blueLED=")>=0) {
    pos1 = header.indexOf('/?blueLED=');
    pos2 = header.indexOf('&');
    valueString = header.substring(pos1+1, pos2);
    Serial.println(valueString);

    // Turn on/off the blue LED
    if (valueString == "on") {
      digitalWrite(BLUE_LED_PIN, HIGH);
      Serial.println("Blue LED on");
    } else if (valueString == "off") {
      digitalWrite(BLUE_LED_PIN, LOW);
      Serial.println("Blue LED off");
    }
  }

  // RGB LED
  else if(header.indexOf("GET /?RGB=")>=0){
    pos1 = header.indexOf('/?RGB=#');
    pos2 = header.indexOf('&');
    valueString = header.substring(pos1+1, pos2);
    
    // Turn on/off the RGB LED
    RGBledColor(valueString);
  }

  // SERVO
  else if (header.indexOf("GET /?servo=")>=0) {
    pos1 = header.indexOf('/?servo=');
    pos2 = header.indexOf('&');
    valueString = header.substring(pos1+1, pos2);

    // Move servo
    servoPosition(valueString);
  }

  // PIEZO
  else if (header.indexOf("GET /?song=")>=0) {
    pos1 = header.indexOf('/?song=');
    pos2 = header.indexOf('&');
    valueString = header.substring(pos1+1, pos2);

    // Play song

    // TO BE IMPLEMENTED

  }

  // ULTRASONIC SENSOR
  else if (header.indexOf("GET /?value=ultrasonic&")>=0) {
    // Get ultrasonic sensor value

    // TO BE IMPLEMENTED
  }
  return 1;
}

void RGBledColor(String color){

  // Given color as HEX value change color on RGB led
  int red = 0, green = 0, blue = 0;

  red = (int)strtol(color.substring(1, 3).c_str(), NULL, 16);
  green = (int)strtol(color.substring(3, 5).c_str(), NULL, 16);
  blue = (int)strtol(color.substring(5, 7).c_str(), NULL, 16);

  analogWrite(RGB_RED_LED_PIN, red);
  analogWrite(RGB_GREEN_LED_PIN, green);
  analogWrite(RGB_BLUE_LED_PIN, blue);    

  // NOT YET TESTED

  return;
}

void servoPosition(String angle){

  // Convert string to integer
  int servoAngle = angle.toInt();
  
  servoMotor.write(servoAngle);
  delay(15);

  return;
}


void htmlCodePrint(WiFiClient client){
  client.println("<!DOCTYPE html>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta charset=\"utf-8\">\n<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n<title>Sensors Interface</title>\n<meta name=\"description\" content=\"\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");

  client.println("<style>");
  client.println(".grid_container{");
  client.println("    display: grid;");
  client.println("    grid-template-columns: 1fr 1fr;");
  client.println("    grid-template-rows: 1fr 1fr;");
  client.println("    gap: 10px;");
  client.println("}");
  client.println(".grid_el{");
  client.println("    background-color: #ddd;");
  client.println("    padding: 20px;");
  client.println("    text-align: center;");
  client.println("}");
  client.println(".title_sensor {");
  client.println("    font-size: 20px;");
  client.println("    display: flex;");
  client.println("    border-bottom: 1px solid #495057;");
  client.println("}");
  client.println("#main_title{");
  client.println("    font-size: 30px;");
  client.println("    padding: 10px;");
  client.println("    text-align: center;");
  client.println("    border-bottom: 3px solid #495057;");
  client.println("}");
  client.println("#id1{");
  client.println("    grid-column: 1;");
  client.println("    grid-row: 1;");
  client.println("}");
  client.println("#id2{");
  client.println("    grid-column: 2;");
  client.println("    grid-row: 1;");
  client.println("}");
  client.println("#id3{");
  client.println("    grid-column: 1;");
  client.println("    grid-row: 2;");
  client.println("}");
  client.println("#id4{");
  client.println("    grid-row: 2;");
  client.println("    grid-column: 2;");
  client.println("}");
  client.println("#id5{");
  client.println("    grid-row: 3;");
  client.println("    grid-column: 2;");
  client.println("}");
  client.println(".toggle-switch {");
  client.println("    position: relative;");
  client.println("    display: inline-block;");
  client.println("    width: 60px;");
  client.println("    height: 34px;");
  client.println("}");
  client.println(".toggle-switch input {");
  client.println("    opacity: 0;");
  client.println("    width: 0;");
  client.println("    height: 0;");
  client.println("}");
  client.println(".slider {");
  client.println("    position: absolute;");
  client.println("    cursor: pointer;");
  client.println("    top: 0;");
  client.println("    left: 0;");
  client.println("    right: 0;");
  client.println("    bottom: 0;");
  client.println("    background-color: #ccc;");
  client.println("    transition: .4s;");
  client.println("    border-radius: 34px;");
  client.println("}");
  client.println(".slider:before {");
  client.println("    position: absolute;");
  client.println("    content: \"\";");
  client.println("    height: 26px;");
  client.println("    width: 26px;");
  client.println("    left: 4px;");
  client.println("    bottom: 4px;");
  client.println("    background-color: white;");
  client.println("    transition: .4s;");
  client.println("    border-radius: 50%;");
  client.println("}");
  client.println("#redLed{");
  client.println("    border-bottom: 3px solid red;");
  client.println("}");
  client.println("#blueLed{");
  client.println("    border-bottom: 3px solid blue;");
  client.println("}");
  client.println("#yellowLed{");
  client.println("    border-bottom: 3px solid yellow;");
  client.println("}");
  client.println(".red input:checked+.slider {");
  client.println("    background-color: red;");
  client.println("}");
  client.println(".red input:focus+.slider {");
  client.println("    box-shadow: 0 0 1px red;");
  client.println("}");
  client.println(".red input:checked+.slider::before {");
  client.println("    transform: translateX(26px);");
  client.println("}");
  client.println(".blue input:checked+.slider {");
  client.println("    background-color: blue;");
  client.println("}");
  client.println(".blue input:focus+.slider {");
  client.println("    box-shadow: 0 0 1px blue;");
  client.println("}");
  client.println(".blue input:checked+.slider::before {");
  client.println("    transform: translateX(26px);");
  client.println("}");
  client.println(".yellow input:checked+.slider {");
  client.println("    background-color: yellow;");
  client.println("}");
  client.println(".yellow input:focus+.slider {");
  client.println("    box-shadow: 0 0 1px yellow;");
  client.println("}");
  client.println(".yellow input:checked+.slider::before {");
  client.println("    transform: translateX(26px);");
  client.println("}");
  client.println(".buttons{");
  client.println("    display: flex;");
  client.println("    justify-content: center;");
  client.println("    gap: 50px;");
  client.println("}");
  client.println(".stepsBox{");
  client.println("    display: flex;");
  client.println("    align-items: center;");
  client.println("    justify-content: center;");
  client.println("}");
  client.println(".servoBox{");
  client.println("    display: flex;");
  client.println("    justify-content: center;");
  client.println("    align-items: center;");
  client.println("    gap: 30px;");
  client.println("}");
  client.println(".ultra_sensor_box{");
  client.println("    font-size: 24px;");
  client.println("    padding: 10px 0px;");
  client.println("    border: 2px solid black;");
  client.println("    justify-content: center;");
  client.println("    align-items: center;");
  client.println("}");
  client.println(".info{");
  client.println("    font-size: 15px;");
  client.println("    border: 1px solid black;");
  client.println("    padding: 7px;");
  client.println("    align-items: center;");
  client.println("    justify-content: center;");
  client.println("    width: 30px;");
  client.println("    height: 30px;");
  client.println("    border-radius: 50%;");
  client.println("}");
  client.println(".piezoBox{");
  client.println("    display: flex;");
  client.println("    gap: 10px;");
  client.println("}");
  client.println(".sliderServo{");
  client.println("    position: relative;");
  client.println("    width: 80%;");
  client.println("    display: block;");
  client.println("}");
  client.println("</style>");

  client.println("</head>");

  client.println("<body>");

  client.println("<h1 id=\"main_title\">Multi-Sensors</h1>");
  client.println("<div class=\"grid_container\">");

  client.println("<div class=\"grid_el\" id=\"el1\"><h2 class=\"title_sensor\">LED</h2><div class=\"buttons\"><label class=\"toggle-switch red\" id=\"redLed\"><input type=\"checkbox\" onchange=\"toggleLed('redLED', this)\" id=\"redButton\">");
  client.println("<span class=\"slider\"></span></label><label class=\"toggle-switch yellow\" id=\"yellowLed\"><input type=\"checkbox\" onchange=\"toggleLed('yellowLED', this)\" id=\"yellowButton\"><span class=\"slider\"></span></label><label class=\"toggle-switch blue\" id=\"blueLed\"><input type=\"checkbox\" onchange=\"toggleLed('blueLED', this)\" id=\"blueButton\"><span class=\"slider\"></span></label></div></div>");

  client.println("<div class=\"grid_el\" id=\"el2\"><h2 class=\"title_sensor\">RGB LED</h2><div><input type=\"color\" onchange=\"rgbLEDchange('RGB', this)\" id=\"RGBselector\"><label for=\"rgbLed_input\"></label></div></div>");

  client.println("<div class=\"grid_el\" id=\"el3\"><h2 class=\"title_sensor\">PIEZO</h2><div class=\"piezoBox\"><div class=\"songSelection\"><label for=\"song-select\">Choose a song:</label><select name=\"songs\" id=\"song-select\"><option value=\"none\">--Please choose an option--</option>");
  client.println("<option value=\"song1\">Song 1</option><option value=\"song2\">Song 2</option><option value=\"song3\">Song 3</option><option value=\"song4\">Song 4</option><option value=\"song5\">Song 5</option><option value=\"song6\">Song 6</option></select><button type=\"button\" id=\"playButton\" onclick=\"songSelection('song')\">PLAY</button></div></div></div>");

  client.println("<div class=\"grid_el\" id=\"el4\"><h2 class=\"title_sensor servoDiv\">SERVO</h2><div class=\"servoBox\"\><p>Position: <span id=\"servoPos\"></span></p><input type=\"range\" min=\"0\" max=\"180\" class=\"sliderServo\" id=\"servoSlider\" onchange=\"servo(this.value)\"></div></div><div class=\"grid_el\" id=\"el5\"><h2 class=\"title_sensor\">ULTRASONIC SENSOR</h2><div class=\"ultra_sensor_box\" id=\"ultrasonicBox\"></div></div>");
  
  client.println("</div>");

  client.println("<script>");
  client.println("const redLed = document.querySelector(\"#red\");");
  client.println("const blueLed = document.querySelector(\"#blue\");");
  client.println("const yellowLed = document.querySelector(\"#yellow\");");
  client.println("");
  client.println("function toggleLed(id, element) {");
  client.println("    console.log(`${id}: New state selected: ` + element.value);");
  client.println("");
  client.println("    fetch(\"/?\" + id + \"=\" + element.value + \"&\")");
  client.println("        .then(response => {");
  client.println("            if (response.ok) {");
  client.println("                console.log(id + \" \" + element.value + \" success\");");
  client.println("            } else {");
  client.println("                console.log(id + \" \" + element.value + \" error\");");
  client.println("            }");
  client.println("        })");
  client.println("        .catch(error => {");
  client.println("            console.log(id + \" \" + element.value + \" error: \" + error);");
  client.println("        });");
  client.println("");
  client.println("    element.value = element.value == \"on\" ? \"off\" : \"on\";");
  client.println("}");
  client.println("");
  client.println("const RGBselect = document.querySelector(\"#RGBselector\");");
  client.println("");
  client.println("function rgbLEDchange(id, element) {");
  client.println("    console.log(`${id}: New color selected: ` + element.value);");
  client.println("");
  client.println("    fetch(\"/?\" + id + \"=\" + element.value + \"&\")");
  client.println("        .then(response => {");
  client.println("            if (response.ok) {");
  client.println("                console.log(id + \" \" + element.value + \" success\");");
  client.println("            } else {");
  client.println("                console.log(id + \" \" + element.value + \" error\");");
  client.println("            }");
  client.println("        })");
  client.println("        .catch(error => {");
  client.println("            console.log(id + \" \" + element.value + \" error: \" + error);");
  client.println("        });");
  client.println("}");
  client.println("");
  client.println("var servoP = document.getElementById(\"servoPos\");");
  client.println("servoP.innerHTML = slider.value;");
  client.println("");
  client.println("function servo(pos) {");
  client.println("    fetch(\"/?servo=\" + pos + \"&\")");
  client.println("        .then(response => {");
  client.println("            if (response.ok) {");
  client.println("                console.log(\"Servo position set to: \" + pos);");
  client.println("            } else {");
  client.println("                console.log(\"Error setting servo position\");");
  client.println("            }");
  client.println("        })");
  client.println("        .catch(error => {");
  client.println("            console.log(\"Error setting servo position: \" + error);");
  client.println("        });");
  client.println("}");
  client.println("");
  client.println("slider.oninput = function () {");
  client.println("    slider.value = this.value;");
  client.println("    servoP.innerHTML = this.value;");
  client.println("}");
  client.println("");
  client.println("const playBtn = document.querySelector(\"#playButton\");");
  client.println("const songSelector = document.querySelector(\"#song-select\");");
  client.println("");
  client.println("function songSelection(id) {");
  client.println("");
  client.println("    console.log(`${id}: New song selected`);");
  client.println("    fetch(\"/?song=\" + songSelector.value + \"&\")");
  client.println("        .then(response => {");
  client.println("            if (response.ok) {");
  client.println("                console.log(id + \" \" + songSelector.value + \" success\");");
  client.println("            } else {");
  client.println("                console.log(id + \" \" + songSelector.value + \" error\");");
  client.println("            }");
  client.println("        })");
  client.println("        .catch(error => {");
  client.println("            console.log(id + \" \" + songSelector.value + \" error: \" + error);");
  client.println("        });");
  client.println("}");
  client.println("");
  client.println("const ultrasonicBox = document.querySelector(\"#ultrasonicBox\");");
  client.println("");
  client.println("setInterval(function () {");
  client.println("");
  client.println("    fetch(\"/?value=ultrasonic&\")");
  client.println("        .then(response => {");
  client.println("            if (response.ok) {");
  client.println("                response.text().then(data => {");
  client.println("                    ultrasonicBox.innerHTML = data + \" cm\";");
  client.println("                });");
  client.println("            } else {");
  client.println("                console.log(\"Error getting ultrasonic value\");");
  client.println("            }");
  client.println("        })");
  client.println("        .catch(error => {");
  client.println("            console.log(\"Error getting ultrasonic value: \" + error);");
  client.println("        });");
  client.println("}, 1000);");
  client.println("</script>");

  client.println("</body>");

  client.println("</html>");
}
