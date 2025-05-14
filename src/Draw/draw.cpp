#include <cstdio>
#include <cmath>
#include <iostream>
#include <memory>
#include <algorithm>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "3dDatas/Vector3D.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Scene.hpp"
#include "Primitive/I_Primitive.hpp"
#include "3dDatas/Point3D.hpp"
#include "Consts/const.hpp"
#include "Generation/tools.hpp"
#include "Draw/my_Image.hpp"

static void editColor(sf::Color &c, sf::Vector3f &cLight,
    sf::Color &origin, float &minRayLen, RayTracer::Point3D &intersection,
    RayTracer::Ray &ray) {
    // Edit color with luminescence values
    int r = std::min(255, static_cast<int>(
        (c.r * cLight.x)));
    int g = std::min(255, static_cast<int>(
        (c.g * cLight.y)));
    int b = std::min(255, static_cast<int>(
        (c.b * cLight.z)));

    // Edit color with transparency values
    float percentA = (c.a != 0.f) ? (c.a / 255.f) : 0.f;
    float len = intersection.distance(ray.origin);
    if (len > minRayLen)  // object is behind other object
        percentA = 1 - percentA;
    else
        minRayLen = len;

    c = sf::Color((r * percentA) + (origin.r * (1 - percentA)),
                    (g * percentA) + (origin.g * (1 - percentA)),
                    (b * percentA) + (origin.b * (1 - percentA)));
}

void computeLuminescence(RayTracer::Point3D &intersection,
std::shared_ptr<Prim> &s, sf::Vector3f &cLight) {
    for (std::shared_ptr<Light> Light : RayTracer::Scene::i->Lights) {
        double lum = Light->getLuminescence(intersection, Light, s,
            RayTracer::Scene::i->ObjectHead);
        cLight.x += (Light->getColor().r/255) * lum;
        cLight.y += (Light->getColor().g/255) * lum;
        cLight.z += (Light->getColor().b/255) * lum;
    }
}

static void hit(std::unique_ptr<my_Image> &image, int i, int j,
RayTracer::Ray &r, std::shared_ptr<Prim> &s, RayTracer::Point3D &intersection,
float &minRayLen) {
    try {
        // Get base colors
        sf::Color origin = image->getPixel(i, j);
        RayTracer::Vector3D uv = s->getUV(intersection);
        sf::Color c = s->getMaterial()->getColorAt(uv.x, uv.y);
        sf::Vector3f cLight = sf::Vector3f(0, 0, 0);

        computeLuminescence(intersection, s, cLight);

        editColor(c, cLight, origin, minRayLen, intersection, r);
        image->setPixel(i, j, c);
    } catch (std::exception &e) {
        image->setPixel(i, j,
            sf::Color(234, 58, 247));  // error pink
        return;
    }
}

static void checkHitsAtPixel(double i, double j, RayTracer::Ray r,
std::unique_ptr<my_Image> &image, std::shared_ptr<Prim> &obj,
float &minRayLength) {
    RayTracer::Point3D intersection;
    if (obj->hits(r, intersection)) {
        hit(image, static_cast<int>(i), static_cast<int>(j), r,
            obj, intersection, minRayLength);
    }
    for (std::shared_ptr<Prim> &o : obj->getChildrens())
        checkHitsAtPixel(i, j, r, image, o, minRayLength);
}

static void checkHitAt(float i, float j, float iplus, float jplus,
RayTracer::Camera cam, std::unique_ptr<my_Image> &image) {
    float minRayLength = 10000000.f;

    RayTracer::Ray r = cam.ray((i + iplus) / WIDTH, (j + jplus) / HEIGHT);
    checkHitsAtPixel(i, j, r, image,
        RayTracer::Scene::i->ObjectHead, minRayLength);
}

void generatePixelColumn(float i, RayTracer::Camera cam,
    my_Image &image, std::vector<std::unique_ptr<my_Image>> &images) {

    int samplesPerSide = static_cast<int>(std::sqrt(images.size()));
    float stepSize = 1.0f / samplesPerSide;

    for (float j = 0; j < HEIGHT; j++) {
        int sampleIndex = 0;
        for (int sy = 0; sy < samplesPerSide; sy++) {
            for (int sx = 0; sx < samplesPerSide; sx++) {
                float offsetX = (sx * stepSize) - 0.5f + (stepSize / 2.0f);
                float offsetY = (sy * stepSize) - 0.5f + (stepSize / 2.0f);
                if (sampleIndex < static_cast<int>(images.size())) {
                    checkHitAt(i, j, offsetX, offsetY, cam,
                        images[sampleIndex]);
                    sampleIndex++;
                }
            }
        }
        averageAllImages(i, j, image, images);
    }
}

int generateImage(sf::RenderWindow &window, my_Image &image, std::string
    sceneFile, int aa) {
    RayTracer::Camera cam;
    std::vector<std::thread> threadVector;
    std::vector<std::unique_ptr<my_Image>> images;
    int configChanged = 0;

    showImage(window, image);
    createListImages(images, image, aa * aa);
    for (float i = 0; i < WIDTH; i++) {
        threadVector.emplace_back(generatePixelColumn, i,
            std::ref(cam), std::ref(image), std::ref(images));
    }

    configChanged = displayImage(window, image, sceneFile);

    for (auto &t : threadVector) {
        if (t.joinable())
            t.join();
    }
    return configChanged;
}
