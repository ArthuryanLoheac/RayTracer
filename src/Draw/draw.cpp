#include <cstdio>
#include <cmath>
#include <iostream>
#include <memory>
#include <algorithm>

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

static double getLuminescence(RayTracer::Point3D &intersection,
    std::unique_ptr<Light> &Light) {
    double distance = intersection.distance(Light->getPosition());
    double angle = 0;

    return Light->getLuminescence(distance, angle);
}

static void hit(sf::Image &image, int i, int j,
    std::shared_ptr<Prim> &s, RayTracer::Point3D &intersection,
    std::unique_ptr<Light> &Light, float &z) {
    try {
        // Get base colors
        sf::Color origin = image.getPixel(i, j);
        sf::Color c = s->getMaterial()->getColorAt(i, j);

        double luminescence = getLuminescence(intersection, Light);

        // Edit color with luminescence values
        int r = std::min(255, static_cast<int>(c.r * luminescence));
        int g = std::min(255, static_cast<int>(c.g * luminescence));
        int b = std::min(255, static_cast<int>(c.b * luminescence));

        // Edit color with transparency values
        float percentA = 255 / c.a;
        if (intersection.z < z) //  object is behind other object
            percentA = 1 - percentA;
        else
            z = intersection.z;
        c = sf::Color(  (r * percentA) + (origin.r * (1 - percentA)),
                        (g * percentA) + (origin.g * (1 - percentA)),
                        (b * percentA) + (origin.b * (1 - percentA)));
        image.setPixel(i, j, c);
    } catch (std::exception &e) {
        image.setPixel(i, j,
            sf::Color(234, 58, 247));  // error pink
        return;
    }
}

static void checkHitsAtPixel(double i, double j, RayTracer::Ray r,
sf::Image &image, std::unique_ptr<Light> &Light, std::shared_ptr<Prim> &obj,
float &z) {
    RayTracer::Point3D intersection;

    if (obj->hits(r, intersection)) {
        hit(image, static_cast<int>(i), static_cast<int>(j),
            obj, intersection, Light, z);
    }
    for (std::shared_ptr<Prim> &o : obj->getChildrens())
        checkHitsAtPixel(i, j, r, image, Light, o, z);
}

void generateImage(sf::RenderWindow &window, sf::Image &image,
    std::unique_ptr<Light> &Light) {
    RayTracer::Camera cam;

    for (float i = 0; i < WIDTH; i++) {
        for (float j = 0; j < HEIGHT; j++) {
            float z = -10000000.f;

            RayTracer::Ray r = cam.ray(i / WIDTH, j / HEIGHT);
            checkHitsAtPixel(i, j, r, image, Light,
                RayTracer::Scene::i->ObjectHead, z);
        }
        showImage(window, image);
    }
}
