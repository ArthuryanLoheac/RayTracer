#pragma once
#include "Interfaces/Primitive/I_Primitive.hpp"

namespace RayTracer {
class I_Lights : public I_Primitive {
 public:
    virtual ~I_Lights() = default;
    virtual void Init() override = 0;
    virtual float getLuminescence(float distance, float angle) = 0;
    virtual float getIntensity() = 0;
    virtual float getAngle() = 0;
};
}  // namespace RayTracer

// extern "C" std::unique_ptr<I_Lights> getLight();