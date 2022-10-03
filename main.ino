#include <LiquidCrystal_I2C.h>

const int LDR_PIN = 2;

const int SPEAKER_PIN = 8;

// LDR Characteristics
const float GAMMA = 0.7;
const float RL10 = 50;

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
    pinMode(LDR_PIN, INPUT);

    lcd.init();
    lcd.backlight();

    tone(8, 262, 250);
}

void loop() {
    int analogValue = analogRead(A0);
    float voltage = analogValue / 1024. * 5;
    float resistance = 2000 * voltage / (1 - voltage / 5);
    float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));

    lcd.setCursor(1, 0);
    lcd.print("Status: ");

    if (lux < 50) {
        tone(8, 262, 250);
        lcd.print("Alert");
    } else {
        lcd.print("Clear");
    }

    delay(100);
}
