
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

    if (!position.lookupValue("x", pos[0]))
        pos[0] = 0;
    if (!position.lookupValue("y", pos[1]))
        pos[1] = 0;
    if (!position.lookupValue("z", pos[2]))
        pos[2] = 5;
    return Point3D(pos[0], pos[1], pos[2]);
}

static Vector3D parseRotation(const libconfig::Setting &rotation) {
    float rot[3] = {0.0f, 0.0f, 0.0f};

    if (!rotation.lookupValue("x", rot[0]))
        rot[0] = 0;
    if (!rotation.lookupValue("y", rot[1]))
        rot[1] = 1;
    if (!rotation.lookupValue("z", rot[2]))
        rot[2] = 0;
    return Vector3D(rot[0], rot[1], rot[2]);
}

static Point3D parseScale(const libconfig::Setting &scale) {
    float sc[3] = {1.0f, 1.0f, 1.0f};

    if (!scale.lookupValue("x", sc[0]))
        sc[0] = 1;
    if (!scale.lookupValue("y", sc[1]))
        sc[1] = 1;
    if (!scale.lookupValue("z", sc[2]))
        sc[2] = 1;
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

    try {
        settings["position"] = parsePosition(primitive.lookup("position"));
    }
    catch(const libconfig::SettingNotFoundException &e) {
        settings["position"] = Point3D(0.f, 0.f, 5.f);
    }
    try {
        settings["rotation"] = parseRotation(primitive.lookup("rotation"));
    }
    catch(const libconfig::SettingNotFoundException &e) {
        settings["rotation"] = Vector3D(0.f, 1.f, 0.f);
    }
    try {
        settings["scale"] = parseScale(primitive.lookup("scale"));
    }
    catch(const libconfig::SettingNotFoundException &e) {
        settings["scale"] = Point3D(1.f, 1.f, 1.f);
    }
    try {
        settings["material"] = parseMaterial(primitive.lookup("material"));
    }
    catch(const libconfig::SettingNotFoundException &e) {
        std::cerr << e.what() << '\n';
    }
    if (type == "sphere" || type == "plane" ||
        type == "cylinder" || type == "limcylinder") {
        float radius = 0.0f;
        primitive.lookupValue("radius", radius);
        settings["radius"] = radius;
    }
    if (type == "cone" || type == "limcone") {
        float angle = 0.0f;
        primitive.lookupValue("angle", angle);
        settings["angle"] = angle;
    }
    if (type == "limcylinder" || type == "limcone") {
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
        try {
            const libconfig::Setting &spheres = primitives.lookup("spheres");
            for (int i = 0; i < spheres.getLength(); i++) {
                const libconfig::Setting &sphere = spheres[i];
                parsePrimitive(sphere, "sphere");
            }
        } catch(const libconfig::SettingNotFoundException &e) {
        }
        try {
            const libconfig::Setting &planes = primitives.lookup("planes");
            for (int i = 0; i < planes.getLength(); i++) {
                const libconfig::Setting &plane = planes[i];
                parsePrimitive(plane, "plane");
            }
        } catch(const libconfig::SettingNotFoundException &e) {
        }
        try {
            const libconfig::Setting &cylinders =
                primitives.lookup("cylinders");
            for (int i = 0; i < cylinders.getLength(); i++) {
                const libconfig::Setting &cylinder = cylinders[i];
                parsePrimitive(cylinder, "cylinder");
            }
        } catch(const libconfig::SettingNotFoundException &e) {
        }
        try {
            const libconfig::Setting &limcylinders =
                primitives.lookup("limcylinders");
            for (int i = 0; i < limcylinders.getLength(); i++) {
                const libconfig::Setting &limcylinder = limcylinders[i];
                parsePrimitive(limcylinder, "limcylinder");
            }
        } catch(const libconfig::SettingNotFoundException &e) {
        }
        try {
            const libconfig::Setting &cones = primitives.lookup("cones");
            for (int i = 0; i < cones.getLength(); i++) {
                const libconfig::Setting &cone = cones[i];
                parsePrimitive(cone, "cone");
            }
        } catch(const libconfig::SettingNotFoundException &e) {
        }
        try {
            const libconfig::Setting &limcones = primitives.lookup("limcones");
            for (int i = 0; i < limcones.getLength(); i++) {
                const libconfig::Setting &limcone = limcones[i];
                parsePrimitive(limcone, "limcone");
            }
        } catch(const libconfig::SettingNotFoundException &e) {
        }
        try {
            const libconfig::Setting &objects = primitives.lookup("objects");
            for (int i = 0; i < objects.getLength(); i++) {
                const libconfig::Setting &object = objects[i];
                parsePrimitive(object, "obj");
            }
        } catch(const libconfig::SettingNotFoundException &e) {
        }
        try {
            const libconfig::Setting &nones = primitives.lookup("none");
            for (int i = 0; i < nones.getLength(); i++) {
                const libconfig::Setting &none = nones[i];
                parsePrimitive(none, "none");
            }
        } catch(const libconfig::SettingNotFoundException &e) {
        }
    } catch (const libconfig::SettingNotFoundException &nfex) {
        throw ParsingError("Missing primitives in configuration file.");
    } catch (const libconfig::SettingTypeException &tex) {
        throw ParsingError("Invalid primitives type in configuration file.");
    }
}

}  // namespace RayTracer
