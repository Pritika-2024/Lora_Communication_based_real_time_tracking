#include <SPI.h>
#include <LoRa.h>

// LoRa Pins (ESP32)
#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_SS    5
#define LORA_RST   14
#define LORA_DIO0  2

void setup() {
    Serial.begin(115200);
    Serial.println("LoRa Receiver Starting...");

    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);

    LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
    if (!LoRa.begin(433E6)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }

    Serial.println("LoRa Receiver Initialized on 433 MHz");
}

void loop() {
    int packetSize = LoRa.parsePacket();

    if (packetSize) {
        String incoming = "";

        while (LoRa.available()) {
            incoming += (char)LoRa.read();
        }

        Serial.print("Received: ");
        Serial.println(incoming);

        int firstComma = incoming.indexOf(',');
        int secondComma = incoming.indexOf(',', firstComma + 1);

        // Normal GPS data
        if (firstComma > 0 && secondComma == -1) {
            float lat = incoming.substring(0, firstComma).toFloat();
            float lon = incoming.substring(firstComma + 1).toFloat();

            Serial.print("Latitude: "); Serial.println(lat, 6);
            Serial.print("Longitude: "); Serial.println(lon, 6);
        }
        // Emergency data
        else if (firstComma > 0 && secondComma > 0) {
            String alert = incoming.substring(0, firstComma);
            float lat = incoming.substring(firstComma + 1, secondComma).toFloat();
            float lon = incoming.substring(secondComma + 1).toFloat();

            Serial.println("EMERGENCY ALERT RECEIVED");
            Serial.print("Latitude: "); Serial.println(lat, 6);
            Serial.print("Longitude: "); Serial.println(lon, 6);
        }

        Serial.println("---------------------------");
    }
}
