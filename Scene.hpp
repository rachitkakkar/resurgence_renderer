#ifndef SCENE
#define SCENE

#include <memory>
#include <vector>

#include "Objects.hpp"

class Scene {
private:
    std::vector<std::shared_ptr<Object>> objects;

public:
    void clear() { 
        objects.clear();
    }

    void add(std::shared_ptr<Object> object) {
        objects.push_back(object);
    }

    Hit hit(const Ray& ray, double tMin, double tMax) const {
        Hit hit;
        hit.occured = false;
        double closestObjectSoFar = tMax;

        for (const auto& object : objects) {
            Hit objectHit = object->hit(ray, tMin, closestObjectSoFar);
            if (objectHit.occured) {
                closestObjectSoFar = objectHit.t;
                hit = objectHit;
            }
        }

        return hit;
    }
};

#endif