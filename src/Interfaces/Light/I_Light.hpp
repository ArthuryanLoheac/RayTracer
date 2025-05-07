#pragma once
#include <memory>

#include "Interfaces/Primitive/I_Primitive.hpp"

namespace RayTracer {
class I_Light : public I_Primitive {
 public:
    virtual ~I_Light() = default;
    virtual float getLuminescence(RayTracer::Point3D intersection,
        std::shared_ptr<I_Light> Light, std::shared_ptr<I_Primitive> obj,
        std::shared_ptr<I_Primitive> head) = 0;
    virtual float getIntensity() = 0;
    virtual float getAngle() = 0;
};
}  // namespace RayTracer

// extern "C" std::unique_ptr<I_Light> getLight();
