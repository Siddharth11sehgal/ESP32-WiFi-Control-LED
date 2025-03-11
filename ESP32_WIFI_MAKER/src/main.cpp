#include <WiFi.h>

const char *ssid = "ESP32_Control";
const char *password = "12345678";

// wifi server on port 80
WiFiServer server(80);

const int ledPin = 13;

void setup() {
  Serial.begin(115200);
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  WiFi.softAP(ssid, password);
  
  Serial.println("Wi-Fi Access Point Started!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());  // print ESP32 ipadress

  server.begin();  // start web server
}

void loop() {
  WiFiClient client = server.available();  // Check if a client connected
  if (!client) return;

  Serial.println("New client connected");
  String request = client.readStringUntil('\r');  // Read the request
  client.flush();
  
  // requests
  if (request.indexOf("/LEDON") != -1) {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED turned ON");
  }
  if (request.indexOf("/LEDOFF") != -1) {
    digitalWrite(ledPin, LOW);
    Serial.println("LED turned OFF");
  }

  // HTML webpage
  String webpage = "<html>\
  <head>\
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\
    <title>ESP32 LED Control</title>\
    <style>\
      body { font-family: 'Arial', sans-serif; background-color: #f2f2f2; text-align: center; padding: 20px; }\
      h1 { color: #333; font-size: 2em; margin-bottom: 30px; }\
      .container { max-width: 400px; margin: 0 auto; background-color: #fff; border-radius: 10px; box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); padding: 20px; }\
      .button { padding: 15px 30px; font-size: 20px; margin: 10px; border-radius: 5px; text-decoration: none; display: inline-block; width: 150px; cursor: pointer; transition: all 0.3s ease; }\
      .on { background-color: #28a745; color: white; border: none; }\
      .off { background-color: #dc3545; color: white; border: none; }\
      .button:hover { opacity: 0.8; }\
      .footer { margin-top: 30px; font-size: 14px; color: #888; }\
    </style>\
  </head>\
  <body>\
    <div class='container'>\
      <h1>ESP32 LED Control</h1>\
      <a href='/LEDON'><button class='button on'>Turn LED ON</button></a>\
      <a href='/LEDOFF'><button class='button off'>Turn LED OFF</button></a>\
    </div>\
    <div class='footer'>\
      <p>Control your LED with ESP32 over Wi-Fi!</p>\
    </div>\
  </body>\
</html>";

  // send the webpage to the client
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  client.println(webpage);
  client.println();
  
  delay(10);  // timing
  client.stop();
  Serial.println("Client disconnected");
}