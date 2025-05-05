#pragma once
#include "Interfaces/Light/A_Light.hpp"
#include "3dDatas/Point3D.hpp"
#include "3dDatas/Ray.hpp"

class Spot : public RayTracer::A_Lights {
 public:
    Spot();
    void Init() override;
    float getLuminescence(float angle) override;
    bool hits(RayTracer::Ray ray, RayTracer::Point3D &intersection) override;
};
