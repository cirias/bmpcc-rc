#include <Arduino.h>
#include "PinChangeInterrupt.h"
#include "PWM.h"

/*
 * #define pcint_pwm_1 12 // A4
 * #define pin_pwm_1 A4
 * #define pcint_pwm_2 13 // A5
 * #define pin_pwm_2 A5
 * 
 * volatile int pwm_value_1 = 0;
 * volatile int prev_time_1 = 0;
 * volatile int pwm_value_2 = 0;
 * volatile int prev_time_2 = 0;
 * 
 * int pwm_last_value_1 = 0;
 * 
 * void change1(void) {
 *   int val = digitalRead(pin_pwm_1);
 *   if (val == HIGH) {
 *     prev_time_1 = micros();
 *   } else {
 *     pwm_value_1 = micros() - prev_time_1;
 *   }
 *   [> Serial.println("change1"); <]
 * }
 * 
 * void change2(void) {
 *   int val = digitalRead(pin_pwm_2);
 *   if (val == HIGH) {
 *     prev_time_2 = micros();
 *   } else {
 *     pwm_value_2 = micros() - prev_time_2;
 *   }
 *   [> Serial.println("change2"); <]
 * }
 * 
 * void setupPWM(void) {
 *   // set pin to input with a pullup
 *   pinMode(pcint_pwm_1, INPUT_PULLUP);
 *   pinMode(pcint_pwm_2, INPUT_PULLUP);
 * 
 *   // Attach the new PinChangeInterrupt and enable event function below
 *   attachPCINT(pcint_pwm_1, change1, CHANGE);
 *   attachPCINT(pcint_pwm_2, change2, CHANGE);
 * }
 */

PWM::PWM(int pin, int pcint, void (*_handler)(int, int)) {
  pinMode(pcint, INPUT_PULLUP);

  _pin = pin;
  _pcint = pcint;
  _handler = _handler;
}

void PWM::start(void) {
  int currentPWM = 0;
  int lastPWM = 0;
  int startTime = 0;

  auto onChange = [&] () {
    if (digitalRead(_pin) == HIGH) {
      startTime = micros();
      return;
    }

    if (startTime == 0) {
      return;
    }

    lastPWM = currentPWM;
    currentPWM = micros() - startTime;

    _handler(lastPWM, currentPWM);
  };

  attachPCINT(_pcint, onChange, CHANGE);
}
