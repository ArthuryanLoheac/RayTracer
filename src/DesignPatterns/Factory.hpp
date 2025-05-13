#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <utility>
#include <iostream>

#include "dlLoader/dlLoader.hpp"
#include "3dDatas/Vector3D.hpp"
#include "Scene/Scene.hpp"
#include "Consts/const.hpp"
#include "Interfaces/Primitive/I_Primitive.hpp"

template <typename T>
class Factory {
 public:
    static Factory<T> &i() {
        static Factory<T> instance;
        return instance;
    }

    Factory();
    ~Factory();

    std::unique_ptr<T> create(std::string primitive);
 private:
    std::unordered_map<std::string,
        std::pair<std::string, std::string>> _arg_list;
};

template <typename T>
Factory<T>::Factory() {
    std::string prim = "getPrimitive";
    std::string mat = "getMaterial";
    std::string light = "getLight";

    _arg_list.insert({"sphere", {"libs/primitive_sphere.so", prim}});
    _arg_list.insert({"none", {"libs/primitive_none.so", prim}});
    _arg_list.insert({"cylinder", {"libs/primitive_cylinder.so", prim}});
    _arg_list.insert({"cone", {"libs/primitive_cone.so", prim}});
    _arg_list.insert({"plane", {"libs/primitive_plane.so", prim}});
    _arg_list.insert({"ambient", {"libs/light_ambient.so", light}});
    _arg_list.insert({"spot", {"libs/light_spot.so", light}});
    _arg_list.insert({"flat", {"libs/mat_flat.so", mat}});
    _arg_list.insert({"chess", {"libs/mat_chess.so", mat}});
    _arg_list.insert({"perlin", {"libs/mat_perlin.so", mat}});
    _arg_list.insert({"image", {"libs/mat_image.so", mat}});
    _arg_list.insert({"trans", {"libs/mat_trans.so", mat}});
}

template <typename T>
Factory<T>::~Factory() {
}

template <typename T>
std::unique_ptr<T> Factory<T>::create
    (std::string primitive) {
    try {
        std::pair<std::string, std::string> args = _arg_list.at(primitive);
        return (dlLoader<T>::getLib(args.first, args.second));
    } catch(const std::exception& e) {
        std::cerr << "Primitive not found: " << primitive << std::endl;
        return (dlLoader<T>::getLib
            ("libs/primitive_none.so", "getPrimitive"));
    }
}
