#pragma once
#include <vector>
#include <memory>

#include "Interfaces/Light/I_Light.hpp"
#include "Primitive/I_Primitive.hpp"

namespace RayTracer {
class Scene {
 public:
    static Scene *i;

    std::vector<std::unique_ptr<I_Light>> lights;
    std::unique_ptr<I_Primitive> ObjectHead;

    Scene();
};
}  // namespace RayTracer
