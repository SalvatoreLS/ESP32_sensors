#include <WiFi.h>

const char* ssid = "";
const char* password = "";

// LED pins
#define RED_LED_PIN 2
#define YELLOW_LED_PIN 3
#define BLUE_LED_PIN 4

// Piezo buzzer pin
#define PIEZO_PIN 10

// Servo pin
#define SERVO_PIN 9

WiFiServer server(80);

String header;
String body;

void setup() {
  Serial.begin(115200);

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

            client.println("<!DOCTYPE html>");
            client.println("<html>");

            // HTML CODE
            // ...
            // ...

            client.println("</html>");

            client.println();
            break;
          } else{
            currentLine = "";
          }
        } else if (c != '\r'){
          currentLine += c;
        }

        // REQUEST HANDLING CODE

      }
    }
  }
}