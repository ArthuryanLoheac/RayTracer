#include <memory>
#include <vector>
#include <utility>
#include <string>

#include "Material/PerlinMat.hpp"

#include "Consts/const.hpp"

extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial() {
    return std::make_unique<PerlinMat>();
}

PerlinMat::PerlinMat() {
}

float PerlinMat::Fade(float t) {
    return ((6*t - 15)*t + 10)*t*t*t;
}

float PerlinMat::Lerp(float t, float a1, float a2) {
    return a1 + t*(a2-a1);
}

void PerlinMat::Shuffle(std::vector<float> &arrayToShuffle) {
    unsigned int seed = time(nullptr);
    for (size_t e = arrayToShuffle.size() - 1; e > 0; e--) {
        int index = rand_r(&seed) % e;
        std::swap(arrayToShuffle[e], arrayToShuffle[index]);
    }
}

std::vector<float> PerlinMat::MakePermutation() {
    for (float i = 0; i < 256; i++)
        Permutation.push_back(i);
    Shuffle(Permutation);
    for (float i = 0; i < 256; i++)
        Permutation.push_back(Permutation[i]);
    return Permutation;
}

RayTracer::Vector3D PerlinMat::GetConstantVector(int v) {
    int h = v % 4;

    if (h == 0)
        return RayTracer::Vector3D(1.0, 1.0, 0);
    else if (h == 1)
        return RayTracer::Vector3D(-1.0, 1.0, 0);
    else if (h == 2)
        return RayTracer::Vector3D(-1.0, -1.0, 0);
    else
        return RayTracer::Vector3D(1.0, -1.0, 0);
}

float PerlinMat::Noise2D(float x, float y) {
    int xi = (static_cast<int>(floor(x - 10000))) % repeatX;
    int yi = (static_cast<int>(floor(y))) % repeatY;

    if (xi < 0) xi += repeatX;
    if (yi < 0) yi += repeatY;

    int X = xi % 256;
    int Y = yi % 256;

    float xf = x-floor(x);
    float yf = y-floor(y);

    RayTracer::Vector3D topRight = RayTracer::Vector3D(xf-1.0, yf-1.0, 0);
    RayTracer::Vector3D topLeft = RayTracer::Vector3D(xf, yf-1.0, 0);
    RayTracer::Vector3D bottomRight = RayTracer::Vector3D(xf-1.0, yf, 0);
    RayTracer::Vector3D bottomLeft = RayTracer::Vector3D(xf, yf, 0);

    float valueTopRight = Permutation[Permutation[X+1]+Y+1];
    float valueTopLeft = Permutation[Permutation[X]+Y+1];
    float valueBottomRight = Permutation[Permutation[X+1]+Y];
    float valueBottomLeft = Permutation[Permutation[X]+Y];

    float dotTopRight = topRight.dot(GetConstantVector(valueTopRight));
    float dotTopLeft = topLeft.dot(GetConstantVector(valueTopLeft));
    float dotBottomRight = bottomRight.dot(GetConstantVector(valueBottomRight));
    float dotBottomLeft = bottomLeft.dot(GetConstantVector(valueBottomLeft));

    float u = Fade(xf);
    float v = Fade(yf);

    return Lerp(u,
        Lerp(v, dotBottomLeft, dotTopLeft),
        Lerp(v, dotBottomRight, dotTopRight));
}

void PerlinMat::Init(std::unordered_map<std::string, std::any> &settings) {
    scale = std::any_cast<RayTracer::Vector3D>(settings["scale"]);
    rotation = std::any_cast<RayTracer::Vector3D>(settings["rotation"]);
    c1 = std::any_cast<sf::Color>(settings["color1"]);
    c2 = std::any_cast<sf::Color>(settings["color2"]);
    repeatX = std::any_cast<int>(settings["repeatX"]);
    repeatY = std::any_cast<int>(settings["repeatY"]);
    Permutation = MakePermutation();
}

sf::Color PerlinMat::getColorAt(float u, float v) {
    if (scale.x == 0 || scale.y == 0)
        return PINK_ERROR;  // error pink
    u /= scale.x;
    v /= -scale.y;
    u += rotation.x;
    v += rotation.y;
    if (u < 0)
        u = -u;
    if (v < 0)
        v = -v;

    float n = 0;
    float tt = 0;
    int nbOctave = 8;
    float frequency = 1;
    float amplitude = 1;

    for (float i = 1; i <= nbOctave; i++) {
        n += amplitude * Noise2D(u * frequency, v * frequency);
        tt += amplitude;
        frequency *= 2;
        amplitude /= 2;
    }

    n += tt;
    n /= tt*2;

    sf::Color c(
        (c1.r * n) + (c2.r * (1-n)),
        (c1.g * n) + (c2.g * (1-n)),
        (c1.b * n) + (c2.b * (1-n)));
    return c;
}

bool PerlinMat::isReflective() const {
    return false;
}
