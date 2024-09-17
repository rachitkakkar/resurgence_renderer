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

    Hit hit(const Ray& ray, Interval rayT) const {
        Hit hit;
        hit.occured = false;
        double closestObjectSoFar = rayT.max;

        for (const auto& object : objects) {
            Hit objectHit = object->hit(ray, Interval(rayT.min, closestObjectSoFar));
            if (objectHit.occured) {
                closestObjectSoFar = objectHit.t;
                hit = objectHit;
            }
        }

        return hit;
    }
};

#endif