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
#include "Draw/hit.hpp"

static void editColor(sf::Color &c, sf::Vector3f &cLight,
    sf::Color &origin) {
    // Edit color with luminescence values
    int r = std::min(255, static_cast<int>(
        (c.r * cLight.x)));
    int g = std::min(255, static_cast<int>(
        (c.g * cLight.y)));
    int b = std::min(255, static_cast<int>(
        (c.b * cLight.z)));

    // Edit color with transparency values
    float percentA = c.a / 255.f;
    c = sf::Color(r * percentA + (origin.r * (1 - percentA)),
        g * percentA + (origin.g * (1 - percentA)),
        b * percentA + (origin.b * (1 - percentA)));
}

static void computeLuminescence(RayTracer::Point3D &intersection,
std::shared_ptr<Prim> &s, sf::Vector3f &cLight) {
    for (std::shared_ptr<Light> Light : RayTracer::Scene::i->Lights) {
        double lum = Light->getLuminescence(intersection, Light, s,
            RayTracer::Scene::i->ObjectHead);
        cLight.x += (Light->getColor().r/255) * lum;
        cLight.y += (Light->getColor().g/255) * lum;
        cLight.z += (Light->getColor().b/255) * lum;
    }
}

static sf::Color checkHit(std::shared_ptr<Prim> &head, RayTracer::Ray r) {
    RayTracer::Point3D inter;
    if (head->hits(r, inter)) {
        RayTracer::Vector3D uv = head->getUV(inter);
        sf::Color c = head->getMaterial()->getColorAt(uv.x, uv.y);
        return c;
    }
    for (std::shared_ptr<Prim> &o : head->getChildrens()) {
        sf::Color c = checkHit(o, r);
        if (c != sf::Color(0, 0, 0))
            return c;
    }
    return sf::Color(0, 0, 0); // skye
}

static sf::Color getColorReflected(hitDatas &datas, RayTracer::Vector3D uv)
{
    sf::Color c(0);
    if (datas.obj->getMaterial()->isReflective()) {
        c = sf::Color(255, 255, 255);
        RayTracer::Vector3D normal = datas.obj->getNormalAt(datas.intersection);
        RayTracer::Vector3D reflected(datas.direction - normal *
            2*(datas.direction.normalized().dot(normal)));
        RayTracer::Ray r(datas.intersection, reflected);
        c = checkHit(RayTracer::Scene::i->ObjectHead, r);
    } else {
        c = datas.obj->getMaterial()->getColorAt(uv.x, uv.y);
    }
    return c;
}

static void hit(std::unique_ptr<my_Image> &image, int i, int j,
hitDatas &datas) {
    try {
        // Get base colors
        sf::Color origin = image->getPixel(i, j);
        RayTracer::Vector3D uv = datas.obj->getUV(datas.intersection);
        sf::Color c = getColorReflected(datas, uv);
        sf::Vector3f cLight = sf::Vector3f(0, 0, 0);

        computeLuminescence(datas.intersection, datas.obj, cLight);

        editColor(c, cLight, origin);
        image->setPixel(i, j, c);
    } catch (std::exception &e) {
        image->setPixel(i, j,
            sf::Color(234, 58, 247));  // error pink
        return;
    }
}

static void checkHitsAtPixel(double i, double j, RayTracer::Ray r,
std::unique_ptr<my_Image> &image, std::shared_ptr<Prim> &obj,
std::vector<hitDatas> &lst) {
    RayTracer::Point3D intersection;
    if (obj->hits(r, intersection)) {
        hitDatas h;
        h.intersection = intersection;
        h.origin = r.origin;
        h.direction = r.direction;
        h.len = r.origin.distance(intersection);
        h.obj = obj;
        lst.push_back(h);
    }
    for (std::shared_ptr<Prim> &o : obj->getChildrens())
        checkHitsAtPixel(i, j, r, image, o, lst);
}

static sf::Color checkHitAt(float i, float j,
std::unique_ptr<my_Image> &image, RayTracer::Ray r) {
    std::vector<hitDatas> lst;

    checkHitsAtPixel(i, j, r, image,
        RayTracer::Scene::i->ObjectHead, lst);
    // sort from the farthest to the closest
    std::sort(lst.begin(), lst.end(),
        [](const hitDatas &a, const hitDatas &b) {
            return a.len > b.len;
        });
    for (hitDatas &h : lst) {
        hit(image, static_cast<int>(i), static_cast<int>(j), h);
    }
    return image.get()->getPixel(i, j);
}

static void checkHitAtRay(float i, float j, float iplus, float jplus,
    RayTracer::Camera cam, std::unique_ptr<my_Image> &image) {
    RayTracer::Ray r = cam.ray((i + iplus) / WIDTH, (j + jplus) / HEIGHT);
    checkHitAt(i, j, image, r);
}

static void generatePixelColumn(float i, RayTracer::Camera cam,
my_Image &image, std::vector<std::unique_ptr<my_Image>> &images) {
    for (float j = 0; j < HEIGHT; j++) {
        checkHitAtRay(i, j, 0, 0, cam, images[0]);
        checkHitAtRay(i, j, 0, -0.5f, cam, images[1]);
        checkHitAtRay(i, j, 0, 0.5f, cam, images[2]);
        checkHitAtRay(i, j, -0.5f, 0, cam, images[3]);
        checkHitAtRay(i, j, -0.5f, -0.5f, cam, images[4]);
        checkHitAtRay(i, j, -0.5f, 0.5f, cam, images[5]);
        checkHitAtRay(i, j, 0.5f, 0, cam, images[6]);
        checkHitAtRay(i, j, 0.5f, -0.5f, cam, images[7]);
        checkHitAtRay(i, j, 0.5f, 0.5f, cam, images[8]);
        averageAllImages(i, j, image, images);
    }
}

int generateImage(sf::RenderWindow &window, my_Image &image, std::string
    sceneFile) {
    std::vector<std::thread> threadVector;
    std::vector<std::unique_ptr<my_Image>> images;
    int configChanged = 0;

    showImage(window, image);
    createListImages(images, image);
    for (float i = 0; i < WIDTH; i++) {
        threadVector.emplace_back(generatePixelColumn, i,
            std::ref(RayTracer::Camera::i()),
            std::ref(image), std::ref(images));
    }

    configChanged = displayImage(window, image, sceneFile);

    for (auto &t : threadVector) {
        if (t.joinable())
            t.join();
    }
    return configChanged;
}
