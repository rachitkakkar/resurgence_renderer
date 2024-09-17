#ifndef OBJECT
#define OBJECT

#include "Interval.hpp"
#include "Vector.hpp"
#include "Ray.hpp"

struct Hit {
    bool occured = false;

    Vector3 point;
    Vector3 normal;
    double t;
    bool frontFace;

    inline void setFaceNormal(const Ray& ray, const Vector3& outwardNormal) {
        frontFace = ray.direction.dot(outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Object {
public:
    virtual Hit hit (const Ray& ray, Interval rayT) const = 0;
};

class Sphere : public Object {
public:
    Vector3 center;
    double radius;

    Sphere() {}
    Sphere(Vector3 c, double r) : center(c), radius(r) {};

    virtual Hit hit(const Ray& ray, Interval rayT) const override {
        Hit hit;

        Vector3 sphereToRay = ray.origin - center;
        double a = ray.direction.dot(ray.direction);
        double half_b = sphereToRay.dot(ray.direction);
        double c = sphereToRay.dot(sphereToRay) - radius*radius;

        double discriminant = half_b*half_b - a*c;
        if (discriminant < 0)
            return hit;
        float sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        double root = (-half_b - sqrtd) / a;
        if (!rayT.surrounds(root)) {
            root = (-half_b + sqrtd) / a;
            if (!rayT.surrounds(root)) {
                return hit;
            }
        }

        hit.t = root;
        hit.point = ray.at(hit.t);
        hit.normal = (hit.point - center) / radius;
        hit.occured = true;
        Vector3 outwardNormal = (hit.point - center) / radius;
        hit.setFaceNormal(ray, outwardNormal);
        return hit;
    };
};

#endif