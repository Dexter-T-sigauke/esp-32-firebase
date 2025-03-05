# Firebase ESP32 Sensor Data Logger

This project demonstrates how to use an ESP32 microcontroller to read data from a DHT22 temperature and humidity sensor and an MQ-2 gas sensor, and then send the data to a Firebase Realtime Database.

## Components Used

- ESP32 Development Board
- DHT22 Temperature and Humidity Sensor
- MQ-2 Gas Sensor
- Firebase Realtime Database

## Libraries Required

- `WiFi.h`: For connecting to Wi-Fi.
- `FirebaseESP32.h`: For interacting with Firebase.
- `DHT.h`: For reading data from the DHT22 sensor.

## Setup

1. **Network Credentials**: Replace the placeholders for `WIFI_SSID` and `WIFI_PASSWORD` with your Wi-Fi network credentials.

   ```cpp
   #define WIFI_SSID "your-ssid"
   #define WIFI_PASSWORD "your-password"
   ```

2. **Firebase Project Details**: Replace the placeholders for [FIREBASE_HOST](http://_vscodecontentref_/0) and [FIREBASE_AUTH](http://_vscodecontentref_/1) with your Firebase project details.

   ```cpp
   #define FIREBASE_HOST "your-firebase-host"
   #define FIREBASE_AUTH "your-firebase-auth"
   ```

3. **DHT22 Sensor Setup**: The DHT22 sensor is connected to pin 4 of the ESP32.

   ```cpp
   #define DHTPIN 4
   #define DHTTYPE DHT22
   ```

4. **MQ-2 Sensor Setup**: The MQ-2 sensor is connected to analog pin 34 of the ESP32.
   ```cpp
   #define MQ2_PIN 34
   ```

## How It Works

1. **Setup**:

   - Initializes the Serial Monitor.
   - Connects to the specified Wi-Fi network.
   - Initializes the Firebase connection.
   - Initializes the DHT22 sensor.

2. **Loop**:
   - Reads temperature and humidity data from the DHT22 sensor.
   - Reads gas concentration data from the MQ-2 sensor.
   - Checks if the gas concentration exceeds a threshold (400).
   - Prints the sensor values to the Serial Monitor.
   - Sends the sensor data to Firebase.
   - Waits for 4 seconds before taking the next reading.

## Code

The main code is located in the [firebase_esp.ino](http://_vscodecontentref_/2) file.

## Usage

1. Open the [firebase_esp.ino](http://_vscodecontentref_/3) file in the Arduino IDE.
2. Install the required libraries via the Arduino Library Manager.
3. Upload the code to your ESP32 board.
4. Open the Serial Monitor to view the sensor readings and Firebase status.

## Troubleshooting

- Ensure that the Wi-Fi credentials and Firebase project details are correctly entered.
- Check the wiring of the DHT22 and MQ-2 sensors.
- Make sure the required libraries are installed.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

---

Feel free to modify the code and adapt it to your needs. Happy coding!

import { initializeApp } from "firebase/app";
import { getDatabase, ref, onValue } from "firebase/database";
import "firebase/database";

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const db = getDatabase();

export { db, ref, onValue };
