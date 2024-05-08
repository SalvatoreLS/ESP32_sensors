#include <WiFi.h>
#include <WiFiClient.h>

const char* ssid = "Redmi Note 10";
const char* password = "coronapilus";

// LED pins
#define RED_LED_PIN 2
#define YELLOW_LED_PIN 3
#define BLUE_LED_PIN 5

// Piezo buzzer pin
#define PIEZO_PIN 10

// Servo pin
#define SERVO_PIN 9

void htmlCodePrint(WiFiClient);
void handleGetRequest(String);

void RGBledColor(String);
void servoPosition(String);

WiFiServer server(80);

String header;
String valueString = String(5);
int pos1 = 0, pos2 = 0;

void setup() {
  Serial.begin(74880);

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
    String currentLine = "";
    while (client.connected()){
      if (client.available()){
        char c = client.read();
        Serial.write(c);
        if (c == '\n'){

          if (currentLine.length() == 0){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            htmlCodePrint(client);

            client.println();

            break;
          } else{
            currentLine = "";
          }
        } else if (c != '\r'){
          currentLine += c;
        }

        // GET request handler
        handleGetRequest(header);

      }
    }
  }
}

void handleGetRequest(String header){

  // RED LED
  if (header.indexOf("GET /redLED/")>=0) {
    pos1 = header.indexOf('/redLED/');
    pos2 = header.indexOf('/?');
    valueString = header.substring(pos1+1, pos2);

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
    pos1 = header.indexOf('=');
    pos2 = header.indexOf('&');
    valueString = header.substring(pos1+1, pos2);

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
    pos1 = header.indexOf('=');
    pos2 = header.indexOf('&');
    valueString = header.substring(pos1+1, pos2);

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
    pos1 = header.indexOf('=');
    pos2 = header.indexOf('&');
    valueString = header.substring(pos1+1, pos2);
    
    // Turn on/off the RGB LED
    RGBledColor(valueString);
  }

  // SERVO
  else if (header.indexOf("GET /?servo=")>=0) {
    pos1 = header.indexOf('=');
    pos2 = header.indexOf('&');
    valueString = header.substring(pos1+1, pos2);

    // Move servo
    servoPosition(valueString);
  }

  // PIEZO
  else if (header.indexOf("GET /?song=")>=0) {
    pos1 = header.indexOf('=');
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
}

void RGBledColor(String color){

  // TO BE IMPLEMENTED

  return;
}

void servoPosition(String angle){
  // Complete this function to move the servo to the desired angle
  
  // TO BE IMPLEMENTED

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

  client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
  client.println("<script src=\"https://code.jquery.com/jquery-3.3.1.min.js\"></script>");

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

  // SCRIPT
  client.println("<script>");
  client.println("$.ajaxSetup({timeout:1000});");
  client.println("const redLed = document.querySelector(\"#redButton\");");
  client.println("const blueLed = document.querySelector(\"#blueButton\");");
  client.println("const yellowLed = document.querySelector(\"#yellowButton\");");

  client.println("function toggleLed(id, element) {");
  client.println("  console.log(`${id}: New state selected: ` + element.value);");
  client.println("  $.ajax({");
  client.println("    type: 'GET',");
  client.println("    dataType: 'jsonp',");
  client.println("    url: window.location.href + id + '/' + element.value + '/',");
  client.println("    headers: {");
  client.println("      'Authorization': 'Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhcHBWZXIiOiIwLjAuMCIsImV4cCI6NDcyNjM4OTEyMiwibG9jYWxlIjoiIiwibWFzdGVyVmVyIjoiIiwicGxhdGZvcm0iOiIiLCJwbGF0Zm9ybVZlciI6IiIsInVzZXJJZCI6IiJ9.QIZbmB5_9Xlap_gDhjETfMI6EAmR15yBtIQkWFWJkrg',");
  client.println("    },");
  client.println("    success: function (data, status, xhr) {");
  client.println("      console.log(id + ' ' + element.value + ' success');");
  client.println("    },");
  client.println("    error: function (jqXhr, textStatus, errorMessage) {");
  client.println("      console.log(id + ' ' + element.value + ' error');");
  client.println("    }");
  client.println("  });");
  client.println("  element.value = element.value == 'on' ? 'off' : 'on';");
  client.println("}");

  client.println("const RGBselect = document.querySelector(\"#RGBselector\");");
  client.println("function rgbLEDchange(id, element) {");
  client.println("  console.log(`${id}: New color selected: ` + element.value);");
  client.println("  $.get(\"/?\" + id + \"=\" + element.value + \"&\", {Connection: \"close\"});");
  client.println("}");

  client.println("var slider = document.getElementById(\"servoSlider\");");
  client.println("var servoP = document.getElementById(\"servoPos\");");
  client.println("servoP.innerHTML = slider.value;");

  client.println("function servo(pos) {");
  client.println("  $.get(\"/?slider=\" + pos + \"&\", {Connection: \"close\"});");
  client.println("}");

  client.println("slider.oninput = function() {");
  client.println("  slider.value = this.value;");
  client.println("  servoP.innerHTML = this.value;");
  client.println("}");

  client.println("const playBtn = document.querySelector(\"#playButton\");");
  client.println("const songSelector = document.querySelector(\"#song-select\");");
  
  client.println("function songSelection(id) {");
  client.println("  console.log(`${id}: New song selected`);");
  client.println("  $.get(\"/?\" + id + \"=\" + songSelector.value + \"&\", {Connection: \"close\"});");
  client.println("}");

  client.println("const ultrasonicBox = document.querySelector(\"#ultrasonicBox\");");

  client.println("setInterval(function() {");
  client.println("  $.get(\"/?value=ultrasonic&\", function(data) {");
  client.println("    console.log(data);");
  client.println("    ultrasonicBox.innerHTML = data + \" cm\";");
  client.println("  }, {Connection: \"close\"});");
  client.println("}, 1000);");

  client.println("</script>");

  client.println("</body>");

  client.println("</html>");
}