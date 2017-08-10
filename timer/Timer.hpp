#pragma once

#ifndef TIMER_HPP_
#define TIMER_HPP_

namespace arduinoutil {

struct Duration {
    unsigned long val;
    friend Duration operator"" _ms(unsigned long val) {
        return Duration{val};
    }
    friend Duration operator"" _s(double val) {
        return Duration{val * 1000};
    }
};

struct Rate {
    double val;
    friend Rate operator"" _hz(double val) {
        return Rate(val);
    }
};

class Timer {

public:

private:

};

}

#endif // TIMER_HPP_
