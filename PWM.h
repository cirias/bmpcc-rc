#ifndef BMPCC_RC_PWM
#define BMPCC_RC_PWM

// #include <Arduino.h>

/*
 * extern volatile int pwm_value_1;
 * extern volatile int pwm_value_2;
 * 
 * extern int pwm_last_value_1;
 * 
 * void setupPWM(void);
 */

class PWM {
  public:
    PWM(int pin, int pcint, void (*_handler)(int lastPWM, int currentPWM));
    void start(void);
  private:
    int _pin;
    int _pcint;
    void (*_handler)(int lastPWM, int currentPWM);
};

#endif
