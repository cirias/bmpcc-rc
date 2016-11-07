#ifndef BMPCC_RC_PWM
#define BMPCC_RC_PWM

void attachPWM1(int pin, int pcint,
    void (*handler)(volatile int, volatile int));

#endif
