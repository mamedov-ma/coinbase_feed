#include "ema_calculator.hpp"

EmaCalculator::EmaCalculator(double alpha)
    : alpha_(alpha), current_ema_(0.0), initialized_(false) {}

void EmaCalculator::add(double value) {
    if (!initialized_) {
        current_ema_ = value;
        initialized_ = true;
    } else {
        current_ema_ = alpha_ * value + (1 - alpha_) * current_ema_;
    }
}

bool EmaCalculator::has_value() const {
    return initialized_;
}

double EmaCalculator::value() const {
    return current_ema_;
}