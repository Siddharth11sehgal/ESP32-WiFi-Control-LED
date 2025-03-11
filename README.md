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

## Code Explanation

The ESP32 acts as a Wi-Fi **Access Point** and hosts a simple **web server**. The code checks the incoming HTTP requests to see if they contain the **/LEDON** or **/LEDOFF** paths, and then it controls the onboard LED (or an external LED) based on the request.

## Customizations:

- You can modify the GPIO pin for the LED by changing the `ledPin` variable in the code.
- Customize the webpage design and controls to suit your project needs.

## License

This project is open-source and available under the MIT License.

---

Feel free to modify the project, expand on it, and share your own creative ideas. If you use this project, don’t forget to give credit!
