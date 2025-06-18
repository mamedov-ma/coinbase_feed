#pragma once

class EmaCalculator {
public:
    EmaCalculator(double alpha);

    void add(double value);
    bool has_value() const;
    double value() const;

private:
    double alpha_;
    double current_ema_;
    bool initialized_;
};