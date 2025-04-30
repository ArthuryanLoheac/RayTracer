#pragma once
#include "Interfaces/Light/A_Light.hpp"

class Ambient : public RayTracer::A_Lights {
 public:
    void Init() override;
    float getLuminescence(float distance, float angle) override;
    bool hits(RayTracer::Ray ray) override;
};
