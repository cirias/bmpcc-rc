#include <Arduino.h>
#include "PWM.h"
#include "LANC.h"

volatile int led_last_status = HIGH;

void toggle() {
  if (led_last_status == HIGH) {
    led_last_status = LOW;
    digitalWrite(LED_BUILTIN, led_last_status);
  } else {
    led_last_status = HIGH;
    digitalWrite(LED_BUILTIN, led_last_status);
  }
}

int lancOutPin = 7;
int lancInPin = 11;

void onChange(volatile int lastPWM, volatile int currentPWM) {
  if (lastPWM > 2000 || lastPWM < 1000 ||
      currentPWM > 2000 || currentPWM < 1000) return;

  if (0 == ((lastPWM - currentPWM) / 333)) return;

  toggle();
  rec();
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  setupLANC(lancOutPin, lancInPin);
  Serial.begin(115200);

  toggle();

  attachPWM1(A4, 12, onChange);
}

void loop() {
}
