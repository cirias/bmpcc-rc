#include "PinChangeInterrupt.h"

#define pcint_pwm_1 12 // A4
#define pin_pwm_1 A4
#define pcint_pwm_2 13 // A5
#define pin_pwm_2 A5

volatile int pwm_value_1 = 0;
volatile int prev_time_1 = 0;
volatile int pwm_value_2 = 0;
volatile int prev_time_2 = 0;

int pwm_last_value_1 = 0;
int led_last_status = HIGH;

void change1(void) {
  int val = digitalRead(pin_pwm_1);
  if (val == HIGH) {
    prev_time_1 = micros();
  } else {
    pwm_value_1 = micros() - prev_time_1;
  }
  /* Serial.println("change1"); */
}

void change2(void) {
  int val = digitalRead(pin_pwm_2);
  if (val == HIGH) {
    prev_time_2 = micros();
  } else {
    pwm_value_2 = micros() - prev_time_2;
  }
  /* Serial.println("change2"); */
}

void toggle() {
  if (led_last_status == HIGH) {
    led_last_status = LOW;
    digitalWrite(LED_BUILTIN, led_last_status);
  } else {
    led_last_status = HIGH;
    digitalWrite(LED_BUILTIN, led_last_status);
  }
}

void onSwitchChange(volatile int* pwm, int* last_value, void(*func)(void)) {
  if (*pwm > 2000 || *pwm < 1000) return;

  int value = (*pwm - 1000) / 333;

  if (*last_value == value) {
    return;
  }

  if (*last_value == -1) {
    *last_value = value;
    return;
  }

  *last_value = value;
  func();
}

void setup() {
  // set pin to input with a pullup, led to output
  pinMode(pcint_pwm_1, INPUT_PULLUP);
  pinMode(pcint_pwm_2, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  // Attach the new PinChangeInterrupt and enable event function below
  attachPCINT(pcint_pwm_1, change1, CHANGE);
  attachPCINT(pcint_pwm_2, change2, CHANGE);

  Serial.begin(115200);
  toggle();
}

void loop() {
  /* Serial.print(pwm_value_1); */
  /* Serial.print(" "); */
  /* Serial.println(pwm_value_2); */

  onSwitchChange(&pwm_value_1, &pwm_last_value_1, toggle);

  delay(40);
}
