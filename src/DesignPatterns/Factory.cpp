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
    std::pair<std::string, std::string> cone =
        {"./libs/primitive_cone.so", "getPrimitive"};
    std::pair<std::string, std::string> trans =
        {"libs/mat_trans.so", "getMaterial"};
    std::pair<std::string, std::string> flat =
        {"libs/mat_flat.so", "getMaterial"};
    std::pair<std::string, std::string> chess =
        {"libs/mat_chess.so", "getMaterial"};
    _arg_list.insert({"sphere", sphere});
    _arg_list.insert({"none", none});
    _arg_list.insert({"cylinder", cylinder});
    _arg_list.insert({"plane", plane});
    _arg_list.insert({"ambient", ambient});
    _arg_list.insert({"spot", spot});
    _arg_list.insert({"cone", cone});
    _arg_list.insert({"trans", trans});
    _arg_list.insert({"flat", flat});
    _arg_list.insert({"chess", chess});
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

std::unique_ptr<Mat> Factory::createMaterial
    (std::string material) {
    try {
        std::pair<std::string, std::string> args = _arg_list.at(material);
        return (dlLoader<Mat>::getLib(args.first, args.second));
    } catch(const std::exception& e) {
        return nullptr;
    }
}
