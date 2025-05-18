
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <libconfig.h++>

#include "Parsing/Parsing.hpp"
#include "Scene/Scene.hpp"
#include "DesignPatterns/Factory.hpp"
#include "Primitive/PrimSphere.hpp"

namespace RayTracer {

void Parsing::parsePrimitive(const libconfig::Setting &primitive,
const std::string &type) {
    std::shared_ptr<I_Primitive> primObj =
        Factory<Prim>::i().create(type);
    std::unordered_map<std::string, std::any> settings;
    float radius = 0.0f;
    float angle = 0.0f;
    float height = 0.0f;

    primitive.lookupValue("radius", radius);
    primitive.lookupValue("angle", angle);
    primitive.lookupValue("height", height);
    settings["position"] = parsePosition(primitive);
    settings["rotation"] = parseRotation(primitive);
    settings["scale"] = parseScalePoint(primitive);
    settings["material"] = parseMaterial(primitive);
    settings["radius"] = radius;
    settings["angle"] = angle;
    settings["height"] = height;
    settings["filename"] = parseImage(primitive);
    primObj->Init(settings);
    Scene::i->ObjectHead->AddChildren(primObj);
}

void Parsing::parseSphere(const libconfig::Setting &sphere) {
    for (int i = 0; i < sphere.getLength(); i++) {
        const libconfig::Setting &s = sphere[i];
        parsePrimitive(s, "sphere");
    }
}

void Parsing::parsePlane(const libconfig::Setting &plane) {
    for (int i = 0; i < plane.getLength(); i++) {
        const libconfig::Setting &p = plane[i];
        parsePrimitive(p, "plane");
    }
}

void Parsing::parseCylinder(const libconfig::Setting &cylinder) {
    for (int i = 0; i < cylinder.getLength(); i++) {
        const libconfig::Setting &c = cylinder[i];
        parsePrimitive(c, "cylinder");
    }
}

void Parsing::parseLimCylinder(const libconfig::Setting &limCylinder) {
    for (int i = 0; i < limCylinder.getLength(); i++) {
        const libconfig::Setting &lc = limCylinder[i];
        parsePrimitive(lc, "limcylinder");
    }
}

void Parsing::parseCone(const libconfig::Setting &cone) {
    for (int i = 0; i < cone.getLength(); i++) {
        const libconfig::Setting &c = cone[i];
        parsePrimitive(c, "cone");
    }
}

void Parsing::parseLimCone(const libconfig::Setting &limCone) {
    for (int i = 0; i < limCone.getLength(); i++) {
        const libconfig::Setting &lc = limCone[i];
        parsePrimitive(lc, "limcone");
    }
}

void Parsing::parseObject(const libconfig::Setting &object) {
    for (int i = 0; i < object.getLength(); i++) {
        const libconfig::Setting &o = object[i];
        parsePrimitive(o, "obj");
    }
}

void Parsing::parseNone(const libconfig::Setting &none) {
    for (int i = 0; i < none.getLength(); i++) {
        const libconfig::Setting &n = none[i];
        parsePrimitive(n, "none");
    }
}

void Parsing::parsePrimitives(const libconfig::Setting &primitives) {
    if (primitives.exists("spheres"))
        parseSphere(primitives.lookup("spheres"));
    if (primitives.exists("planes"))
        parsePlane(primitives.lookup("planes"));
    if (primitives.exists("cylinders"))
        parseCylinder(primitives.lookup("cylinders"));
    if (primitives.exists("limcylinders"))
        parseLimCylinder(primitives.lookup("limcylinders"));
    if (primitives.exists("cones"))
        parseCone(primitives.lookup("cones"));
    if (primitives.exists("limcones"))
        parseLimCone(primitives.lookup("limcones"));
    if (primitives.exists("objects"))
        parseObject(primitives.lookup("objects"));
    if (primitives.exists("nones"))
        parseNone(primitives.lookup("nones"));
}

}  // namespace RayTracer
