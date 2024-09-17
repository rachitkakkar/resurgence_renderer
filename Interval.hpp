#include "Utilities.hpp"

struct Interval {
    double min, max;

    Interval() : min(+INFINITY_), max(-INFINITY_) {}
    Interval(double min_, double max_) : min(min_), max(max_) {}

    bool contains(double x) const {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const {
        return min < x && x < max;
    }

    double clamp(double x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    static const Interval EMPTY, UNIVERSE;
};