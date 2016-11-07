#include <Arduino.h>
#include "PWM.h"

int led_last_status = HIGH;

void toggle() {
  if (led_last_status == HIGH) {
    led_last_status = LOW;
    digitalWrite(LED_BUILTIN, led_last_status);
  } else {
    led_last_status = HIGH;
    digitalWrite(LED_BUILTIN, led_last_status);
  }
}

/*
 * void onSwitchChange(volatile int* pwm, int* last_value, void(*func)(void)) {
 *   if (*pwm > 2000 || *pwm < 1000) return;
 * 
 *   int value = (*pwm - 1000) / 333;
 * 
 *   if (*last_value == value) {
 *     return;
 *   }
 * 
 *   if (*last_value == -1) {
 *     *last_value = value;
 *     return;
 *   }
 * 
 *   *last_value = value;
 *   func();
 * }
 * 
 * void setup() {
 *   setupPWM();
 * 
 *   pinMode(LED_BUILTIN, OUTPUT);
 * 
 *   Serial.begin(115200);
 *   toggle();
 * }
 * 
 * void loop() {
 *   [> Serial.print(pwm_value_1); <]
 *   [> Serial.print(" "); <]
 *   [> Serial.println(pwm_value_2); <]
 * 
 *   onSwitchChange(&pwm_value_1, &pwm_last_value_1, toggle);
 * 
 *   delay(40);
 * }
*/

void onChange(int* lastPWM, int* currentPWM) {
  if (*lastPWM > 2000 || *lastPWM < 1000 ||
      *currentPWM > 2000 || *currentPWM < 1000) return;

  if (0 == ((*lastPWM - *currentPWM) / 333)) return;

  toggle();
}

void setup() {
  PWM pwm(A4, 12, onChange);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  toggle();
  pwm.start();
}

void loop() {
}
