
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

static Point3D parsePosition(const libconfig::Setting &position) {
    float pos[3] = {0.0f, 0.0f, 0.0f};

    position.lookupValue("x", pos[0]);
    position.lookupValue("y", pos[1]);
    position.lookupValue("z", pos[2]);
    return Point3D(pos[0], pos[1], pos[2]);
}

static Vector3D parseRotation(const libconfig::Setting &rotation) {
    float rot[3] = {0.0f, 0.0f, 0.0f};

    rotation.lookupValue("x", rot[0]);
    rotation.lookupValue("y", rot[1]);
    rotation.lookupValue("z", rot[2]);
    return Vector3D(rot[0], rot[1], rot[2]);
}

static Point3D parseScale(const libconfig::Setting &scale) {
    float sc[3] = {1.0f, 1.0f, 1.0f};

    scale.lookupValue("x", sc[0]);
    scale.lookupValue("y", sc[1]);
    scale.lookupValue("z", sc[2]);
    return Point3D(sc[0], sc[1], sc[2]);
}

static sf::Image parseImage(const libconfig::Setting &image) {
    std::string path;
    sf::Image img;

    image.lookupValue("path", path);
    if (!img.loadFromFile(path))
        img.create(100, 100, sf::Color(234, 58, 247));
    return img;
}

void Parsing::parsePrimitive(const libconfig::Setting &primitive,
const std::string &type) {
    std::shared_ptr<I_Primitive> primObj =
        Factory<Prim>::i().create(type);
    std::unordered_map<std::string, std::any> settings;

    settings["position"] = parsePosition(primitive.lookup("position"));
    settings["rotation"] = parseRotation(primitive.lookup("rotation"));
    settings["scale"] = parseScale(primitive.lookup("scale"));
    settings["material"] = parseMaterial(primitive.lookup("material"));
    if (type == "sphere" || type == "plane" ||
        type == "cylinder" || type == "limcylinder") {
        float radius = 0.0f;
        primitive.lookupValue("radius", radius);
        settings["radius"] = radius;
    }
    if (type == "cone") {
        float angle = 0.0f;
        primitive.lookupValue("angle", angle);
        settings["angle"] = angle;
    }
    if (type == "limcylinder") {
        float height = 0.0f;
        primitive.lookupValue("height", height);
        settings["height"] = height;
    }
    if (type == "obj")
        settings["filename"] = parseImage(primitive.lookup("path"));
    primObj->Init(settings);
    Scene::i->ObjectHead->AddChildren(primObj);
}

void Parsing::parsePrimitives(const libconfig::Setting &primitives) {
    try {
        const libconfig::Setting &spheres = primitives.lookup("spheres");
        for (int i = 0; i < spheres.getLength(); i++) {
            const libconfig::Setting &sphere = spheres[i];
            parsePrimitive(sphere, "sphere");
        }
        const libconfig::Setting &planes = primitives.lookup("planes");
        for (int i = 0; i < planes.getLength(); i++) {
            const libconfig::Setting &plane = planes[i];
            parsePrimitive(plane, "plane");
        }
        const libconfig::Setting &cylinders = primitives.lookup("cylinders");
        for (int i = 0; i < cylinders.getLength(); i++) {
            const libconfig::Setting &cylinder = cylinders[i];
            parsePrimitive(cylinder, "cylinder");
        }
        const libconfig::Setting &limcylinders =
            primitives.lookup("limcylinders");
        for (int i = 0; i < limcylinders.getLength(); i++) {
            const libconfig::Setting &limcylinder = limcylinders[i];
            parsePrimitive(limcylinder, "limcylinder");
        }
        const libconfig::Setting &cones = primitives.lookup("cones");
        for (int i = 0; i < cones.getLength(); i++) {
            const libconfig::Setting &cone = cones[i];
            parsePrimitive(cone, "cone");
        }
        const libconfig::Setting &objects = primitives.lookup("objects");
        for (int i = 0; i < objects.getLength(); i++) {
            const libconfig::Setting &object = objects[i];
            parsePrimitive(object, "obj");
        }
        const libconfig::Setting &nones = primitives.lookup("none");
        for (int i = 0; i < nones.getLength(); i++) {
            const libconfig::Setting &none = nones[i];
            parsePrimitive(none, "none");
        }
    } catch (const libconfig::SettingNotFoundException &nfex) {
        throw ParsingError("Missing primitives in configuration file.");
    } catch (const libconfig::SettingTypeException &tex) {
        throw ParsingError("Invalid primitives type in configuration file.");
    }
}

}  // namespace RayTracer
