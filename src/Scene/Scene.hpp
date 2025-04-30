#pragma once
#include <vector>
#include <memory>

#include "Interfaces/Light/I_Light.hpp"
#include "Primitive/I_Primitive.hpp"

namespace RayTracer {
class Scene {
 public:
    std::vector<std::unique_ptr<I_Light>> lights;
    std::unique_ptr<I_Primitive> ObjectHead;
};
}  // namespace RayTracer
