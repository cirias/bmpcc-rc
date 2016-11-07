#include <Arduino.h>
#include "PinChangeInterrupt.h"

volatile int currentPWM1 = 0;
volatile int lastPWM1 = 0;
volatile int startTime1 = 0;
int pin1;

void (*handler1)(volatile int, volatile int);

void onPWMChange1() {
  if (digitalRead(pin1) == HIGH) {
    startTime1 = micros();
    return;
  }

  if (startTime1 == 0) {
    return;
  }

  lastPWM1 = currentPWM1;
  currentPWM1 = micros() - startTime1;

  handler1(lastPWM1, currentPWM1);
}

void attachPWM1(int pin, int pcint,
    void (*handler)(volatile int, volatile int)) {
  pinMode(pcint, INPUT_PULLUP);

  pin1 = pin;
  handler1 = handler;

  attachPCINT(pcint, onPWMChange1, CHANGE);
}
