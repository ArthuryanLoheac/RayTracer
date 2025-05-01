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
    std::unique_ptr<Prim> &s, RayTracer::Point3D &intersection,
    std::unique_ptr<Light> &Light) {
    try {
        // Get base colors
        sf::Color origin = image.getPixel(i, j);
        sf::Color c = s->getMaterial()->getColorAt(i, j);

        double luminescence = getLuminescence(intersection, Light);

        // Edit color with luminescence values
        int r = static_cast<int>(c.r * luminescence);
        int g = static_cast<int>(c.g * luminescence);
        int b = static_cast<int>(c.b * luminescence);

        // Edit color with transparency values
        float percentA = 255 / c.a;
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

void checkHitsAtPixel(double i, double j, RayTracer::Ray r, sf::Image &image,
    std::unique_ptr<Light> &Light) {
    RayTracer::Point3D intersection;

    if (RayTracer::Scene::i->ObjectHead->hits(r, intersection)) {
        hit(image, static_cast<int>(i), static_cast<int>(j),
            RayTracer::Scene::i->ObjectHead, intersection, Light);
    }
}

void generateImage(sf::RenderWindow &window, sf::Image &image,
    std::unique_ptr<Light> &Light) {
    RayTracer::Camera cam;

    for (float i = 0; i < WIDTH; i++) {
        for (float j = 0; j < HEIGHT; j++) {
            RayTracer::Ray r = cam.ray(i / WIDTH, j / HEIGHT);
            checkHitsAtPixel(i, j, r, image, Light);
        }
        showImage(window, image);
    }
}
