#pragma once
#include <string>

#include "dlLoader/dlLoader.hpp"
#include "3dDatas/Vector3D.hpp"
#include "Scene/Scene.hpp"
#include "Consts/const.hpp"

class Factory {
 public:
    Factory();
    ~Factory();

    void createPrimitive(std::string path, std::string type);
};
