#pragma once
#include <memory>
#include <string>

#include "Interfaces/Light/A_Light.hpp"
#include "3dDatas/Point3D.hpp"
#include "3dDatas/Ray.hpp"


class Ambient : public RayTracer::A_Lights {
 public:
    Ambient();
    void Init(std::unordered_map<std::string, std::any> &settings) override;
    float getLuminescence(RayTracer::Point3D intersection,
        std::shared_ptr<I_Light> Light,
        std::shared_ptr<I_Primitive> obj,
        std::shared_ptr<I_Primitive> head) override;
};
