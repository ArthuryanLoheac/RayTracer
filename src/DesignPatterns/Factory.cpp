#include <string>

#include "DesignPatterns/Factory.hpp"

Factory::Factory() {
}

Factory::~Factory() {
}

std::unique_ptr<Prim> Factory::createPrimitive
    (std::string path, std::string type) {
    return (dlLoader<Prim>::getLib(path, type));
}
