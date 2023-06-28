#include "Adafruit_NeoPixel.h"
#include "Arduino.h"

#define NP_PIN 32
#define NP_LEDS 32

Adafruit_NeoPixel np(NP_LEDS, NP_PIN, NEO_GRB + NEO_KHZ800);

int t = 0;

void setup() {
    Serial.begin(115200);

    np.begin();
    np.setBrightness(3);
}

void loop() {
    Serial.println("Hello!");

    np.rainbow(t * 50 % 65535);
    np.show();

    t++;

    delay(1);
}

