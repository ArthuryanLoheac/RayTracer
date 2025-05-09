#pragma once
#include <string>
#include <memory>

#include "dlLoader/dlLoader.hpp"
#include "3dDatas/Vector3D.hpp"
#include "Scene/Scene.hpp"
#include "Consts/const.hpp"
#include "Interfaces/Primitive/I_Primitive.hpp"

class Factory {
 public:
    Factory();
    ~Factory();

    std::unique_ptr<Prim> createPrimitive(std::string path, std::string type);
};
