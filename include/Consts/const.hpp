#pragma once
#include "Interfaces/Primitive/I_Primitive.hpp"
#include "Interfaces/Material/I_Material.hpp"
#include "Interfaces/Light/I_Light.hpp"

const int WIDTH = 800;
const int HEIGHT = 800;
constexpr float EPSILON = 1e-4f;

typedef RayTracer::I_Primitive Prim;
typedef RayTracer::I_Material Mat;
typedef RayTracer::I_Light Light;
