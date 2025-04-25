#include "Ray.hpp"

RayTracer::Ray::Ray(Point3D _origin, Vector3D _direction) {
    origin = _origin;
    direction = _direction;
}

void RayTracer::Ray::normalized() {
    direction /= direction.length();
}
