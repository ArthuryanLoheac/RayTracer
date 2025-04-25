#include "Primitive/Sphere.hpp"

bool RayTracer::Sphere::hits(RayTracer::Ray ray) {
    Vector3D oc = ray.origin - center;

    // Quadratic coefficients
    double a = ray.direction.dot(ray.direction);
    double b = 2.0 * oc.dot(ray.direction);
    double c = oc.dot(oc) - radius * radius;

    // Discriminant
    double discriminant = b * b - 4 * a * c;

    return discriminant >= 0;
}
