#include <SPI.h>
#include <LoRa.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// LoRa Pins
#define LORA_SS   10
#define LORA_RST  9
#define LORA_DIO0 2

// GPS Pins
#define GPS_RX 4
#define GPS_TX 3

// User Button (STM32)
#define USER_BUTTON PC13

SoftwareSerial gpsSerial(GPS_RX, GPS_TX);
TinyGPSPlus gps;

void setup() {
    Serial.begin(115200);
    gpsSerial.begin(9600);
    pinMode(USER_BUTTON, INPUT);

    Serial.println("GPS + LoRa Transmitter Initializing...");

    LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
    if (!LoRa.begin(433E6)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }

    Serial.println("LoRa Initialized.");
}

void loop() {
    // Read GPS data
    while (gpsSerial.available() > 0) {
        gps.encode(gpsSerial.read());
    }

    if (gps.location.isUpdated()) {
        float lat = gps.location.lat();
        float lon = gps.location.lng();

        Serial.print("Lat: "); Serial.print(lat, 6);
        Serial.print(" | Lon: "); Serial.println(lon, 6);

        String message;

        // Emergency Button Check
        if (digitalRead(USER_BUTTON) == LOW) {
            Serial.println("EMERGENCY BUTTON PRESSED!");
            message = "EMERGENCY," + String(lat, 6) + "," + String(lon, 6);
        } else {
            message = String(lat, 6) + "," + String(lon, 6);
        }

        // Send via LoRa
        LoRa.beginPacket();
        LoRa.print(message);
        LoRa.endPacket();

        Serial.println("Sent via LoRa: " + message);
        delay(1000);
    }
}
