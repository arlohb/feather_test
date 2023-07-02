#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>

#include <array>
#include <memory>

#include "Status.h"
#include "secrets.h"

#define NP_PIN 32
#define NP_LEDS 32

Adafruit_NeoPixel np(NP_LEDS, NP_PIN, NEO_GRB + NEO_KHZ800);

std::array<Status, 2> statuses = CreateStatuses();

int t = 0;

void setup() {
    Serial.begin(115200);

    np.begin();
    np.setBrightness(3);
    np.fill(0);
    np.show();

    WiFi.begin(secrets::ssid.c_str(), secrets::password.c_str());

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    np.fill(np.Color(255, 255, 255));
    np.show();

    delay(2000);
}

void loop() {
    np.clear();

    int i = 0;
    for(Status& status : statuses) {
        const std::string& s = status.name;

        auto green = np.Color(0, 255, 0);
        auto red = np.Color(255, 0, 0);

        bool isAlive = status.isAlive();

        for(int j = 0; j < 4; j++)
            np.setPixelColor(i + j * 8, isAlive ? green : red);

        i++;
    }

    np.show();

    t++;

    delay(1000);
}

