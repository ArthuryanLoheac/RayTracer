#include <string>
#include <memory>
#include <vector>

#include "Interfaces/Light/A_Light.hpp"

std::vector<std::shared_ptr<RayTracer::I_Primitive>>
&RayTracer::A_Lights::getChildrens() {
    return childrens;
}

std::shared_ptr<RayTracer::I_Primitive> &RayTracer::A_Lights::AddChildren(
    std::shared_ptr<I_Primitive> child) {
    childrens.push_back(child);
    return childrens.back();
}

std::shared_ptr<RayTracer::I_Material> RayTracer::A_Lights::getMaterial() {
    return material;
}

void RayTracer::A_Lights::setMaterial(std::shared_ptr<I_Material> material) {
    this->material = material;
}

RayTracer::Point3D RayTracer::A_Lights::getPosition() {
    return position;
}

void RayTracer::A_Lights::setPosition(Point3D pos) {
    position = pos;
}

RayTracer::Vector3D RayTracer::A_Lights::getRotation() {
    return rotation;
}

void RayTracer::A_Lights::setRotation(Vector3D rot) {
    rotation = rot;
}

RayTracer::Point3D RayTracer::A_Lights::getScale() {
    return scale;
}

void RayTracer::A_Lights::setScale(Point3D scale) {
    this->scale = scale;
}

float RayTracer::A_Lights::getLuminescence(
    RayTracer::Point3D intersection, std::shared_ptr<I_Light> Light,
    std::shared_ptr<I_Primitive> obj,
    std::shared_ptr<I_Primitive> head) {
    (void) intersection;
    (void) Light;
    (void) obj;
    (void) head;
    return intensity;
}

RayTracer::Vector3D RayTracer::A_Lights::getNormalAt(RayTracer::Point3D point) {
    (void) point;
    return RayTracer::Vector3D(0, 0, 0);
}

bool RayTracer::A_Lights::hits(RayTracer::Ray ray,
    RayTracer::Point3D &intersection) {
    (void) ray;
    (void) intersection;
    return false;
}

float RayTracer::A_Lights::getIntensity() {
    return intensity;
}

float RayTracer::A_Lights::getAngle() {
    return angle;
}

sf::Color RayTracer::A_Lights::getColor() {
    return color;
}

RayTracer::A_Lights::LightError::LightError(const std::string &message)
    : message("A_Lights" + message) {}
