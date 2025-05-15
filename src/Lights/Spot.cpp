#include <memory>
#include <vector>
#include <string>

#include "Lights/Spot.hpp"
#include "Scene/Scene.hpp"

extern "C" std::unique_ptr<RayTracer::I_Light> getLight() {
    return std::make_unique<Spot>();
}

Spot::Spot() {
}

void Spot::Init(std::unordered_map<std::string, std::any> &settings) {
    angle = std::any_cast<float>(settings["angle"]);
    position = std::any_cast<RayTracer::Point3D>(settings["position"]);
    color = std::any_cast<sf::Color>(settings["color"]);
    intensity = std::any_cast<float>(settings["intensity"]);
    rotation = std::any_cast<RayTracer::Vector3D>(settings["rotation"]);
}

bool Spot::checkBlockingLight(std::shared_ptr<I_Primitive> &obj,
    std::shared_ptr<I_Primitive> &head, RayTracer::Ray &r, float distLight) {
    RayTracer::Point3D inter;
    if (head != obj && head->hits(r, inter)) {
        if ((inter - r.origin).length() < distLight)
            return true;
    }
    for (std::shared_ptr<I_Primitive> &c : head->getChildrens())
        if (checkBlockingLight(obj, c, r, distLight))
            return true;
    return false;
}

float Spot::getLuminescence(RayTracer::Point3D intersection,
std::shared_ptr<I_Light> Light, std::shared_ptr<I_Primitive> obj,
std::shared_ptr<I_Primitive> head) {
    RayTracer::Vector3D toLight = Light->getPosition() - intersection;
    float distanceToLight = toLight.length();
    toLight = toLight.normalize();

    RayTracer::Vector3D N = obj->getNormalAt(intersection);
    float angleToSurface = std::acos(N.dot(toLight));

    float lum = 0.f;
    if (angleToSurface < M_PI/2
        && angleToSurface < this->angle * (M_PI/180.0f)) {
        lum = intensity * (1.f - (angleToSurface / (M_PI/2)));
    } else {
        return 0.f;
    }
    RayTracer::Point3D origin = intersection + toLight * 1e-4f;
    RayTracer::Ray shadowRay(origin, toLight);
    float transmittance = 1.f;
    std::vector<std::shared_ptr<I_Primitive>> stack = { head };
    while (!stack.empty() && transmittance > 1e-3f) {
        auto current = stack.back();
        stack.pop_back();
        if (current != obj) {
            RayTracer::Point3D hitP;
            if (current->hits(shadowRay, hitP)) {
                float d = (hitP - intersection).length();
                if (d < distanceToLight) {
                    RayTracer::Vector3D uv = current->getUV(hitP);
                    float alpha = current->getMaterial()
                                      ->getColorAt(uv.x, uv.y).a / 255.f;
                    float blockerTransparency = 1.f - alpha;
                    transmittance *= blockerTransparency;
                    if (transmittance < 1e-3f)
                        break;
                }
            }
        }
        for (auto &ch : current->getChildrens())
            stack.push_back(ch);
    }
    return lum * transmittance / (distanceToLight * distanceToLight);
}
