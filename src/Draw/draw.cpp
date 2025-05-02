#include <cstdio>
#include <cmath>
#include <iostream>
#include <memory>
#include <algorithm>
#include <fstream>
#include <string>

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
    RayTracer::Vector3D lightRotation;
    lightRotation = Light->getRotation();
    RayTracer::Vector3D vect = Light->getPosition() - intersection;

    lightRotation.normalize();
    vect.normalize();

    double dotProduct = lightRotation.dot(vect);
//    dotProduct = std::min(1.0, std::max(-1.0, dotProduct));

    double angle = std::acos(dotProduct) * 180.0 / M_PI;

    double distance = intersection.distance(Light->getPosition());
    return Light->getLuminescence(distance, angle);
}

static void hit(sf::Image &image, int i, int j, RayTracer::Ray &ray,
    std::shared_ptr<Prim> &s, RayTracer::Point3D &intersection,
    std::unique_ptr<Light> &Light, float &minRayLen) {
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
        float percentA = (c.a != 0) ? (255 / c.a) : 1.0f;
        float len = intersection.distance(ray.origin);
        if (len > minRayLen)  // object is behind other object
            percentA = 1 - percentA;
        else
            minRayLen = len;
        c = sf::Color((r * percentA) + (origin.r * (1 - percentA)),
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
float &minRayLength) {
    RayTracer::Point3D intersection;

    if (obj->hits(r, intersection)) {
        hit(image, static_cast<int>(i), static_cast<int>(j), r,
            obj, intersection, Light, minRayLength);
    }
    for (std::shared_ptr<Prim> &o : obj->getChildrens())
        checkHitsAtPixel(i, j, r, image, Light, o, minRayLength);
}

void generateImage(sf::RenderWindow &window, sf::Image &image,
    std::unique_ptr<Light> &Light) {
    RayTracer::Camera cam;

    for (float i = 0; i < WIDTH; i++) {
        for (float j = 0; j < HEIGHT; j++) {
            float minRayLength = 10000000.f;

            RayTracer::Ray r = cam.ray(i / WIDTH, j / HEIGHT);
            checkHitsAtPixel(i, j, r, image, Light,
                RayTracer::Scene::i->ObjectHead, minRayLength);
        }
        showImage(window, image);
    }
}
