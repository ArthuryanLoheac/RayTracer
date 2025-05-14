
#include <iostream>
#include <string>
#include <libconfig.h++>

#include "Parsing/Parsing.hpp"
#include "Scene/Scene.hpp"
#include "DesignPatterns/Factory.hpp"
#include "Primitive/PrimSphere.hpp"

namespace RayTracer {

void Parsing::parsePrimitive(const libconfig::Setting &setting) {
    try {
        const libconfig::Setting &primitives = setting.lookup("primitives");
        const libconfig::Setting &spheres = primitives.lookup("spheres");
        for (int i = 0; i < spheres.getLength(); i++) {
            const libconfig::Setting &sphere = spheres[i];
            parseSphere(sphere);
        }
    } catch (const libconfig::SettingNotFoundException &nfex) {
        throw ParsingError("Missing primitives in configuration file.");
    } catch (const libconfig::SettingTypeException &tex) {
        throw ParsingError("Invalid type for primitives in configuration file.");
    }
}

}  // namespace RayTracer
