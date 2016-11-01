#include "PinChangeInterrupt.h"

#define pcintThrottle 12 // A4
#define pinThrottle A4
#define pcintAileron 13 // A5
#define pinAileron A5

volatile int thro_pwm_value = 0;
volatile int thro_prev_time = 0;
volatile int aile_pwm_value = 0;
volatile int aile_prev_time = 0;

void throChange(void) {
  int val = digitalRead(pinThrottle);
  if (val == HIGH) {
    thro_prev_time = micros();
  } else {
    thro_pwm_value = micros() - thro_prev_time;
  }
  /* Serial.println("throChange"); */
}

void aileChange(void) {
  int val = digitalRead(pinAileron);
  if (val == HIGH) {
    aile_prev_time = micros();
  } else {
    aile_pwm_value = micros() - aile_prev_time;
  }
  /* Serial.println("aileChange"); */
}

void setup() {
  // set pin to input with a pullup, led to output
  pinMode(pcintThrottle, INPUT_PULLUP);
  pinMode(pcintAileron, INPUT_PULLUP);

  // Attach the new PinChangeInterrupt and enable event function below
  attachPCINT(pcintThrottle, throChange, CHANGE);
  attachPCINT(pcintAileron, aileChange, CHANGE);

  Serial.begin(115200);
}

void loop() {
  Serial.print(thro_pwm_value);
  Serial.print(" ");
  Serial.println(aile_pwm_value);
  delay(500);
}
