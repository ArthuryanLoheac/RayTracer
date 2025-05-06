#pragma once
#include <memory>

#include "Interfaces/Light/A_Light.hpp"
#include "3dDatas/Point3D.hpp"
#include "3dDatas/Ray.hpp"


class Ambient : public RayTracer::A_Lights {
 public:
    Ambient();
    void Init() override;
    float getLuminescence(RayTracer::Point3D intersection,
        std::shared_ptr<I_Light> Light,
        std::shared_ptr<I_Primitive> obj) override;
};
