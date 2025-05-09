#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <utility>

#include "dlLoader/dlLoader.hpp"
#include "3dDatas/Vector3D.hpp"
#include "Scene/Scene.hpp"
#include "Consts/const.hpp"
#include "Interfaces/Primitive/I_Primitive.hpp"

class Factory {
 public:
    Factory();
    ~Factory();

    std::unique_ptr<Prim> createPrimitive(std::string primitive);
 private:
    std::unordered_map<std::string,
        std::pair<std::string, std::string>> _arg_list;
};
