#pragma once

#include "Primitive/A_Primitive.hpp"
#include "3dDatas/Point3D.hpp"
#include "3dDatas/Vector3D.hpp"
#include "3dDatas/Ray.hpp"

class PrimSphere : public RayTracer::A_Primitive {
    public:
        RayTracer::Point3D center;
        double radius;
        PrimSphere() = default;
        PrimSphere(RayTracer::Point3D p, double r) : center(p), radius(r) {}
        bool hits(RayTracer::Ray ray) override;
        void Init() override {
            center = RayTracer::Point3D(0.02f, 0.17f, -1);
            radius = 0.1f;
        }
};
