#pragma once
#include <memory>
#include <string>

#include "Interfaces/Light/A_Light.hpp"
#include "3dDatas/Point3D.hpp"
#include "3dDatas/Ray.hpp"
#include "Draw/hit.hpp"

class Spot : public RayTracer::A_Lights {
 public:
    Spot();
    void Init(std::unordered_map<std::string, std::any> &settings) override;
    float getLuminescence(hitDatas &datas,
        std::shared_ptr<I_Light> Light,
        std::shared_ptr<I_Primitive> head) override;
    bool checkBlockingLight(std::shared_ptr<RayTracer::I_Primitive> &obj,
        std::shared_ptr<RayTracer::I_Primitive> &head, RayTracer::Ray &r,
        float distLight);
 private:
    float specular(hitDatas &datas, std::shared_ptr<I_Light> Light);
};
