#include <memory>

#include "Lights/Spot.hpp"

extern "C" std::unique_ptr<RayTracer::I_Light> getLight() {
    return std::make_unique<Spot>();
}

Spot::Spot() {
    Init();
}

void Spot::Init() {
    angle = 360;
    intensity = 20.f;
    position = RayTracer::Point3D(0, 0, 20);
    rotation = RayTracer::Point3D(1, 0, 0);
}

float Spot::getLuminescence(RayTracer::Point3D intersection,
std::shared_ptr<I_Light> Light, std::shared_ptr<I_Primitive> obj) {
    RayTracer::Vector3D lightDir =
        (Light->getPosition() - intersection).normalize();
    RayTracer::Vector3D localNormal = obj->getNormalAt(intersection);

    double angle = std::acos(localNormal.dot(lightDir));
    double distance = (Light->getPosition() - intersection).length();
    double luminescencetmp = intensity;

    if (angle < M_PI / 2 && angle < this->angle)
        luminescencetmp *= (1 - (angle / (M_PI / 2)));
    else
        luminescencetmp = 0;

    return luminescencetmp / std::pow(distance, 2);
}
