#ifndef RAY
#define RAY
#include "Vector.hpp"

struct Ray {
    Vector3 origin, direction;

    Ray() {}
    Ray(Vector3 o, Vector3 d) : origin(o), direction(d) {}

    Vector3 at(double t) const {
        return origin + t * direction;
    }
};

#endif