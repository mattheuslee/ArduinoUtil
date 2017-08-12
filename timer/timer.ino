#include "Timer.hpp"

uint8_t const LED_PIN = 13;

void flipLed() {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

// Identical methods of defining the same timer
Timer timer1(1.0_s);
Timer timer2(1000_ms);
Timer timer3(1.0_hz);

// Timer that activates its own callback
CallbackTimer timer4(1.0_hz, flipLed);

void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    // Comment out the timer not currently being used
    //timer1.reset();
    timer4.reset();
}

void loop() {
    // Comment out the timer not currently being used
    //if (timer1.has_elapsed()) flipLed();
    timer4.update();
}
