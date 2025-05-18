
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

void Parsing::checkChildren(const libconfig::Setting &children,
std::shared_ptr<I_Primitive> &primObj) {
    for (int i = 0; i < children.getLength(); i++) {
        const libconfig::Setting &child = children[i];
        parsePrimitive(child, primObj);
    }
}

void Parsing::parsePrimitive(const libconfig::Setting &primitive,
std::shared_ptr<I_Primitive> &parent) {
    std::unordered_map<std::string, std::any> settings;
    std::string type = "none";
    std::string filename = "tests/obj_file/shrek.obj";
    float radius = 0.0f;
    float angle = 0.0f;
    float height = 0.0f;

    primitive.lookupValue("type", type);
    primitive.lookupValue("radius", radius);
    primitive.lookupValue("angle", angle);
    primitive.lookupValue("height", height);
    primitive.lookupValue("filename", filename);
    settings["position"] = parsePosition(primitive);
    settings["rotation"] = parseRotation(primitive);
    settings["scale"] = parseScalePoint(primitive);
    settings["material"] = parseMaterial(primitive);
    settings["radius"] = radius;
    settings["angle"] = angle;
    settings["height"] = height;
    settings["filename"] = filename;
    std::shared_ptr<I_Primitive> primObj = Factory<Prim>::i().create(type);
    primObj->Init(settings);
    if (primitive.exists("children"))
        checkChildren(primitive.lookup("children"), primObj);
    parent->AddChildren(primObj);
}

void Parsing::parsePrimitives(const libconfig::Setting &primitives) {
    for (int i = 0; i < primitives.getLength(); i++) {
        const libconfig::Setting &primitive = primitives[i];
        parsePrimitive(primitive, Scene::i->ObjectHead);
    }
}

}  // namespace RayTracer
