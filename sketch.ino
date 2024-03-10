#include <SD.h>
#include <DHT.h>
const int chipSelect = 10;  // CS pin connected to digital pin 10
const int DHTPin = 2;
const int DHTType = DHT22; 

DHT dht(DHTPin, DHTType);

void setup() {
  Serial.begin(9600);
  // Check if the SD card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialized successfully.");
  // Create or open the CSV file for writing
  File dataFile = SD.open("data.csv", FILE_WRITE);
  dataFile = SD.open("data.csv");

   if (dataFile) {
    Serial.println("Writing data to data.csv...");

    // Write data to the file
    dataFile.println("Humidity,Temperature,DHT_Humidity,DHT_Temperature");  // Updated CSV header

    // Close the file
    dataFile.close();

    Serial.println("Data written successfully.");
  } else {
    Serial.println("Error creating or opening data.csv");
  }

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
   File dataFile = SD.open("data.csv", FILE_WRITE);

  // Check if the file opened successfully
  if (dataFile) {
    // Read DHT22 sensor data
    float dhtHumidity = dht.readHumidity();
    float dhtTemperature = dht.readTemperature();

    // Print DHT22 data to Serial Monitor
    Serial.print("DHT Humidity: ");
    Serial.print(dhtHumidity);
    Serial.print("%, DHT Temperature: ");
    Serial.println(dhtTemperature);

    // Read data from the DHT22 and write to the file
    dataFile.print(dhtHumidity);
    dataFile.print(",");
    dataFile.print(dhtTemperature);
    dataFile.println();

    // Close the file
    dataFile.close();
  } else {
    Serial.println("Error opening data.csv");
  }

  // Delay for a moment
  delay(5000); // Adjust the delay according to your needs
}
