#include <string>

#include "DesignPatterns/Factory.hpp"

Factory::Factory() {
}

Factory::~Factory() {
}

void Factory::createPrimitive(std::string path, std::string type) {
    RayTracer::Scene::i->ObjectHead = dlLoader<Prim>::getLib(
        path, type);
}
