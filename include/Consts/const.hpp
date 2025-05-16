#pragma once
#include "Interfaces/Primitive/I_Primitive.hpp"
#include "Interfaces/Material/I_Material.hpp"
#include "Interfaces/Light/I_Light.hpp"

typedef RayTracer::I_Primitive Prim;
typedef RayTracer::I_Material Mat;
typedef RayTracer::I_Light Light;

const sf::Color PINK_ERROR(234, 58, 247);
const float EPSILON = 1e-4f;
