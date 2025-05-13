#include <memory>
#include <vector>

#include "Lights/Ambient.hpp"

extern "C" std::unique_ptr<RayTracer::I_Light> getLight() {
    return std::make_unique<Ambient>();
}

Ambient::Ambient() {
    Init();
}

void Ambient::Init() {
    angle = 360;
    intensity = 0.1f;
    position = RayTracer::Point3D(-0.15f, 0.45f, -2.f);
    color = sf::Color(255, 255, 255, 255);
}

float Ambient::getLuminescence(RayTracer::Point3D intersection,
std::shared_ptr<I_Light> Light, std::shared_ptr<I_Primitive> obj,
std::shared_ptr<I_Primitive> head) {
    (void) Light;
    RayTracer::Vector3D lightDir = this->position - intersection;
    float lightDistance = lightDir.length();
    lightDir = lightDir.normalize();
    RayTracer::Ray shadowRay(intersection + lightDir * 0.001f, lightDir);
    float totalTransparency = 1.0f;
    std::vector<std::shared_ptr<I_Primitive>> stack = { head };
    while (!stack.empty()) {
        auto current = stack.back(); stack.pop_back();
        RayTracer::Point3D hitPoint;
        if (current != obj && current->hits(shadowRay, hitPoint)) {
            float hitDistance = hitPoint.distance(intersection);
            if (hitDistance < lightDistance) {
                RayTracer::Vector3D uv = current->getUV(hitPoint);
                float alpha =
                    current->getMaterial()->getColorAt(uv.x, uv.y).a / 255.f;
                float transparency = 1.0f - alpha;
                totalTransparency *= transparency;
                if (totalTransparency < 0.01f)
                    return 0.0f;
            }
        }
        for (auto &child : current->getChildrens())
            stack.push_back(child);
    }
    return intensity * totalTransparency;
}
