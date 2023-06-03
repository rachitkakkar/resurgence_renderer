#ifndef VECTOR
#define VECTOR

#include <cmath>

struct Vector3 {
    double x, y, z;

    Vector3() : x(0.0), y(0.0), z(0.0) {}
    Vector3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

    // Vector negation
    Vector3 operator-() const {
        return Vector3(-x, -y, -z);
    }

    // Vector addition
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    // Vector subtraction
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    // Vector scalar multiplication (from left)
    Vector3 operator*(double scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    // Vector scalar multiplication (from right)
    friend Vector3 operator*(double scalar, const Vector3& vector) {
        return Vector3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
    }

    // Vector scalar division (from left)
    Vector3 operator/(double scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    // Vector scalar division (from right)
    friend Vector3 operator/(double scalar, const Vector3& vector) {
        return Vector3(vector.x / scalar, vector.y / scalar, vector.z / scalar);
    }

    // Vector dot product
    float dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Vector cross product
    Vector3 cross(const Vector3& other) const {
        return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

    // Vector magnitude
    float magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Normalize the vector
    Vector3 normalize() const {
        float mag = magnitude();
        if (mag != 0.0f)
            return Vector3(x / mag, y / mag, z / mag);
        else
            return Vector3();
    }
};

#endif