#include "Timer.hpp"

Timer timer(1.5_s);

void setup() {
    timer.reset();
}

void loop() {
    if (timer.has_elapsed()) {
        int i = 0;
    }
}
