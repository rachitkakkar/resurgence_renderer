#ifndef CAMERA
#define CAMERA

#include "Vector.hpp"

class Camera {
private:
    Vector3 origin;
    Vector3 lowerLeftCorner;
    Vector3 horizontal;

public:
    Camera(double aspectRatio) {
        double screenWidth = 2.0;

    }
};

#endif