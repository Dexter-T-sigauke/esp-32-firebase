#include <WiFi.h>
#include <FirebaseESP32.h>
#include <DHT.h>

// Replace with your network credentials
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

// Replace with your Firebase project details
#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""

// DHT22 sensor setup
#define DHTPIN 4       // Pin where the DHT22 is connected
#define DHTTYPE DHT22  // DHT 22 (AM2302)
DHT dht(DHTPIN, DHTTYPE);

// MQ-2 sensor setup
#define MQ2_PIN 34     // Analog pin where the MQ-2 is connected

// Firebase objects
FirebaseData firebaseData;
FirebaseConfig config;
FirebaseAuth auth;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Initialize Firebase
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Initialize DHT sensor
  dht.begin();

  // Initialize MQ-2 sensor (no setup required for analog pin)
}

void loop() {
  // Read temperature and humidity from DHT22
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Read gas concentration from MQ-2 sensor
  int gasValue = analogRead(MQ2_PIN);

  // Determine if gas is detected (true if gasValue >= 350)
  bool gases = gasValue >= 400;

  // Check if any reads failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print sensor values to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C\t");
  Serial.print("Gas Value: ");
  Serial.print(gasValue);
  Serial.print("\tGases Detected: ");
  Serial.println(gases ? "Yes" : "No");

  // Send data to Firebase
  if (Firebase.setFloat(firebaseData, "/humidity", humidity) &&
      Firebase.setFloat(firebaseData, "/temperature", temperature) &&
      Firebase.setInt(firebaseData, "/gas_value", gasValue) &&
      Firebase.setBool(firebaseData, "/gases", gases)) {
    Serial.println("Data sent to Firebase successfully!");
  } else {
    Serial.println("Failed to send data to Firebase.");
    Serial.println("Reason: " + firebaseData.errorReason());
  }

  // Wait for 5 seconds before the next reading
  delay(4000);
}