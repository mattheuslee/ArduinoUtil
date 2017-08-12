#pragma once

#ifndef TIMER_HPP_
#define TIMER_HPP_

struct Duration {
    unsigned long val;
    friend Duration operator"" _ms(unsigned long long val);
    friend Duration operator"" _s(long double val);
};

Duration operator"" _ms(unsigned long long val) {
    return Duration{val};
}

Duration operator"" _s(long double val) {
    return Duration{val * 1000};
}

struct Rate {
    double val;
    friend Rate operator"" _hz(long double val);
};

Rate operator"" _hz(long double val) {
    return Rate{val};
}

class Timer {

public:
    typedef unsigned long interval_t;
    typedef unsigned long time_t;

    Timer(Duration const & duration)
            : Timer() {
        interval_ = duration.val;
    }

    Timer(Rate const & rate)
            : Timer() {
        interval_ = 1000 / rate.val;
    }

    Timer(Timer const &) = delete;

    Timer& operator=(Timer const &) = delete;

    void last_time(time_t const & lastTime) {
        lastTime_ = lastTime;
    }

    time_t last_time() {
        return lastTime_;
    }

    void interval(interval_t const & _interval) {
        interval_ = _interval;
    }

    interval_t interval() {
        return interval_;
    }

    void last_interval(interval_t const & lastInterval) {
        lastInterval_ = lastInterval;
    }

    interval_t last_interval() {
        return lastInterval_;
    }

    void reset() {
        lastTime_ = millis();
    }

    bool has_elapsed() {
        time_t currTime = millis();
        if ((currTime - lastTime_) >= interval_) {
            lastInterval_ = currTime - lastTime_;
            lastTime_ = currTime;
            return true;
        }
        return false;
    }

    bool check_elapsed() {
        time_t currTime = millis();
        return (currTime - lastTime_) >= interval_;
    }

    time_t elapsed_time() {
        time_t currTime = millis();
        return currTime - lastTime_;
    }

protected:
    Timer() : lastTime_(millis()), lastInterval_(0) {}

    time_t lastTime_;
    interval_t interval_;
    interval_t lastInterval_;

};

typedef void(*Callback)();
class CallbackTimer {

public:
    using interval_t = Timer::interval_t;
    using time_t = Timer::time_t;

    CallbackTimer(Duration const & duration, Callback const & callback)
            : CallbackTimer() {
        interval_ = duration.val;
        callback_ = callback;
    }

    CallbackTimer(Rate const & rate, Callback const & callback)
            : CallbackTimer() {
        interval_ = 1000 / rate.val;
        callback_ = callback;
    }

    void reset() {
        lastTime_ = millis();
    }

    void update() {
        time_t currTime = millis();
        if ((currTime - lastTime_) >= interval_) {
            lastTime_ = currTime;
            callback_();
        }
    }

protected:
    CallbackTimer() : lastTime_(millis()) {}

    time_t lastTime_;
    interval_t interval_;
    Callback callback_;

};

#endif // TIMER_HPP_
