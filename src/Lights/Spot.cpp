#include <memory>

#include "Lights/Spot.hpp"
#include "Scene/Scene.hpp"

extern "C" std::unique_ptr<RayTracer::I_Light> getLight() {
    return std::make_unique<Spot>();
}

Spot::Spot() {
    Init();
}

void Spot::Init() {
    static int i = 0;
    i++;
    if (i == 1) {
        position = RayTracer::Point3D(2.5f, -2, 3);
        color = sf::Color(255, 0, 0, 255);
    } else if (i == 2) {
        position = RayTracer::Point3D(-2.5f, -2, 3);
        color = sf::Color(0, 255, 0, 255);
    } else  {
        position = RayTracer::Point3D(0, -2, 1);
        color = sf::Color(0, 0, 255, 255);
    }
    angle = 360;
    intensity = 1.f;
    rotation = RayTracer::Point3D(1, 0, 0);
}

bool Spot::checkBlockingLight(std::shared_ptr<I_Primitive> &obj,
    std::shared_ptr<I_Primitive> &head, RayTracer::Ray &r) {
    RayTracer::Point3D inter;
    if (head != obj && head->hits(r, inter))
        return true;
    for (std::shared_ptr<I_Primitive> &c : head->getChildrens())
        if (checkBlockingLight(obj, c, r))
            return true;
    return false;
}

float Spot::getLuminescence(RayTracer::Point3D intersection,
std::shared_ptr<I_Light> Light, std::shared_ptr<I_Primitive> obj,
std::shared_ptr<I_Primitive> head) {
    (void) head;
    RayTracer::Vector3D lightDir =
        (Light->getPosition() - intersection).normalize();
    RayTracer::Vector3D localNormal = obj->getNormalAt(intersection);

    double angle = std::acos(localNormal.dot(lightDir));
    double distance = (Light->getPosition() - intersection).length();
    double luminescencetmp = intensity;

    if (angle < M_PI / 2 && angle < this->angle * (M_PI / 180.0))
        luminescencetmp *= (1 - (angle / (M_PI / 2)));
    else
        luminescencetmp = 0;

    RayTracer::Ray ray(intersection, lightDir);
    if (checkBlockingLight(obj, head, ray))
        return 0;

    return luminescencetmp / std::pow(distance, 2);
}
