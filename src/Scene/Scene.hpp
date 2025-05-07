#pragma once
#include <vector>
#include <memory>

#include "Interfaces/Light/I_Light.hpp"
#include "Primitive/I_Primitive.hpp"

namespace RayTracer {
class Scene {
 public:
    static Scene *i;

    std::shared_ptr<I_Primitive> ObjectHead;
    std::vector<std::shared_ptr<I_Light>> Lights;

    Scene();
};
}  // namespace RayTracer
