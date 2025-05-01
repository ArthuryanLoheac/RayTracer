#include "Scene/Scene.hpp"
namespace RayTracer {
Scene *Scene::i = nullptr;
}  // namespace RayTracer

RayTracer::Scene::Scene() {
    i = this;
}
