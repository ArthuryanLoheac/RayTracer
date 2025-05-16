#pragma once
#include <memory>

#include "Interfaces/Primitive/I_Primitive.hpp"
#include "Draw/hit.hpp"

namespace RayTracer {
class I_Light : public I_Primitive {
 public:
    virtual ~I_Light() = default;
    virtual float getLuminescence(hitDatas &datas,
        std::shared_ptr<I_Light> Light,
        std::shared_ptr<I_Primitive> head) = 0;
    virtual float getIntensity() = 0;
    virtual float getAngle() = 0;
    virtual sf::Color getColor() = 0;
};
}  // namespace RayTracer

// extern "C" std::unique_ptr<I_Light> getLight();
