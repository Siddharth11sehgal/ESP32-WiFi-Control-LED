# ESP32 LED Control - Wi-Fi Remote Controller

This project demonstrates how to control an LED connected to an ESP32 using a **Wi-Fi network**. The ESP32 acts as an **Access Point (AP)**, and you can connect your phone or computer to the Wi-Fi to control the LED through a simple **web page**.

## Features

- **Control the LED** via a web page hosted by the ESP32.
- **Responsive Design**: The page works on both mobile and desktop devices.
- **No external servers or cloud** needed — everything is self-contained on the ESP32.
- **Simple user interface** with "Turn LED ON" and "Turn LED OFF" buttons.

## How It Works

1. The ESP32 creates a Wi-Fi hotspot with the SSID **`ESP32_Control`**.
2. Connect to the Wi-Fi using the password **`12345678`**.
3. Open a web browser and visit the IP address **`192.168.4.1`** to access the control page.
4. Use the **ON** and **OFF** buttons to control the onboard LED (connected to GPIO 13).

## Getting Started

### Requirements:

- **Hardware:**
  - ESP32 board (e.g., ESP32 DevKitC)
  - LED (optional if you're using the onboard LED)

- **Software:**
  - Arduino IDE with ESP32 support installed
  - Platform for uploading code to the ESP32

### Uploading the Code:

1. Open the Arduino IDE and select your ESP32 board and port.
2. Copy the code from this repository and paste it into the Arduino IDE.
3. Upload the code to your ESP32.

### Connecting to Wi-Fi:

- Once the ESP32 is powered on, it will create a Wi-Fi network named **`ESP32_Control`**.
- Connect your phone or laptop to this Wi-Fi network using the password **`12345678`**.
- Open a browser and go to **`http://192.168.4.1`** to see the LED control page.

### Controlling the LED:

- **Click the "Turn LED ON" button** to turn the LED on.
- **Click the "Turn LED OFF" button** to turn the LED off.

### Code

Got it! Here's how you can include the code section in your `README.md`:

---

### **Code**

Here is the full code for the **ESP32 LED Control** project:

```cpp
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
```

---

## Code Explanation

The ESP32 acts as a Wi-Fi **Access Point** and hosts a simple **web server**. The code checks the incoming HTTP requests to see if they contain the **/LEDON** or **/LEDOFF** paths, and then it controls the onboard LED (or an external LED) based on the request.

## License

This project is open-source and available under the MIT License.

---

Feel free to modify the project, expand on it, and share your own creative ideas. If you use this project, don’t forget to give credit!
