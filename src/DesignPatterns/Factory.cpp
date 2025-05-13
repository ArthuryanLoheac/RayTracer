#include <string>
#include <memory>
#include <utility>
#include <iostream>

#include "DesignPatterns/Factory.hpp"

Factory::Factory() {
    std::string prim = "getPrimitive";
    std::string mat = "getMaterial";
    std::string light = "getLight";

    _arg_list.insert({"sphere", {"plugins/primitive_sphere.so", prim}});
    _arg_list.insert({"none", {"plugins/primitive_none.so", prim}});
    _arg_list.insert({"cylinder", {"plugins/primitive_cylinder.so", prim}});
    _arg_list.insert({"cone", {"plugins/primitive_cone.so", prim}});
    _arg_list.insert({"plane", {"plugins/primitive_plane.so", prim}});
    _arg_list.insert({"ambient", {"plugins/light_ambient.so", light}});
    _arg_list.insert({"spot", {"plugins/light_spot.so", light}});
    _arg_list.insert({"flat", {"plugins/mat_flat.so", mat}});
    _arg_list.insert({"chess", {"plugins/mat_chess.so", mat}});
    _arg_list.insert({"perlin", {"plugins/mat_perlin.so", mat}});
    _arg_list.insert({"image", {"plugins/mat_image.so", mat}});
}

Factory::~Factory() {
}

std::unique_ptr<Prim> Factory::create
    (std::string primitive) {
    try {
        std::pair<std::string, std::string> args = _arg_list.at(primitive);
        return (dlLoader<Prim>::getLib(args.first, args.second));
    } catch(const std::exception& e) {
        std::cerr << "Primitive not found: " << primitive << std::endl;
        return (dlLoader<Prim>::getLib
            ("plugins/primitive_none.so", "getPrimitive"));
    }
}
