#include <string>
#include <memory>
#include <utility>

#include "DesignPatterns/Factory.hpp"

Factory::Factory() {
    std::pair<std::string, std::string> sphere =
        {"libs/primitive_sphere.so", "getPrimitive"};
    std::pair<std::string, std::string> none =
        {"libs/primitive_none.so", "getPrimitive"};
    std::pair<std::string, std::string> cylinder =
        {"libs/primitive_cylinder.so", "getPrimitive"};
    std::pair<std::string, std::string> plane =
        {"libs/primitive_plane.so", "getPrimitive"};
    std::pair<std::string, std::string> ambient =
        {"libs/light_ambient.so", "getLight"};
    std::pair<std::string, std::string> spot =
        {"libs/light_spot.so", "getLight"};
    _arg_list.insert({"sphere", sphere});
    _arg_list.insert({"none", none});
    _arg_list.insert({"cylinder", cylinder});
    _arg_list.insert({"plane", plane});
    _arg_list.insert({"ambient", ambient});
    _arg_list.insert({"spot", spot});
}

Factory::~Factory() {
}

std::unique_ptr<Prim> Factory::createPrimitive
    (std::string primitive) {
    try {
        std::pair<std::string, std::string> args = _arg_list.at(primitive);
        return (dlLoader<Prim>::getLib(args.first, args.second));
    } catch(const std::exception& e) {
        return (dlLoader<Prim>::getLib
            ("libs/primitive_none.so", "getPrimitive"));
    }
}
