#pragma once
#include <vector>

#include "Lights/I_Lights.hpp"
#include "Primitive/I_Primitive.hpp"

namespace RayTracer {
class Scene {
 public:
    std::vector<I_Lights> lights;
    std::unique_ptr<I_Primitive> ObjectHead;
};
} // namespace RayTracer