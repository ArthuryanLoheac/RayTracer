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
#include "Draw/skybox.hpp"

static sf::Color checkHitAt(RayTracer::Ray r, int &maxBounce,
std::shared_ptr<Prim> exclude);

static void editColor(sf::Color &c, sf::Vector3f &cLight,
    sf::Color &origin, sf::Vector3f cLightPhong) {
    // Edit color with luminescence values
    int r = std::min(255, static_cast<int>(
        (c.r * cLight.x)));
    int g = std::min(255, static_cast<int>(
        (c.g * cLight.y)));
    int b = std::min(255, static_cast<int>(
        (c.b * cLight.z)));

    int phong_r = 255 * cLightPhong.x;
    int phong_g = 255 * cLightPhong.y;
    int phong_b = 255 * cLightPhong.z;
    phong_r = std::min(255, phong_r);
    phong_g = std::min(255, phong_g);
    phong_b = std::min(255, phong_b);

    // Edit color with transparency values
    float percentA = c.a / 255.f;
    int r_tt = static_cast<int>(
        (r * percentA + (origin.r * (1 - percentA)) + phong_r));
    int g_tt = static_cast<int>(
        (g * percentA + (origin.g * (1 - percentA)) + phong_g));
    int b_tt = static_cast<int>(
        (b * percentA + (origin.b * (1 - percentA)) + phong_b));

    c = sf::Color(std::min(255, r_tt),
        std::min(255, g_tt),
        std::min(255, b_tt));
}

static void editColorReflect(sf::Color &c,
    sf::Color &origin, sf::Vector3f cLightPhong) {

    int phong_r = 255 * cLightPhong.x;
    int phong_g = 255 * cLightPhong.y;
    int phong_b = 255 * cLightPhong.z;
    phong_r = std::min(255, phong_r);
    phong_g = std::min(255, phong_g);
    phong_b = std::min(255, phong_b);

    int r_tt = static_cast<int>(
        (origin.r + phong_r));
    int g_tt = static_cast<int>(
        (origin.g + phong_g));
    int b_tt = static_cast<int>(
        (origin.b + phong_b));

    c = sf::Color(std::min(255, r_tt),
        std::min(255, g_tt),
        std::min(255, b_tt));
}

static void computeLuminescence(hitDatas &datas, sf::Vector3f &cLight,
sf::Vector3f &cLightPhong) {
    for (std::shared_ptr<Light> Light : RayTracer::Scene::i->Lights) {
        // Light
        double lum = Light->getLuminescence(datas, Light,
            RayTracer::Scene::i->ObjectHead);
        cLight.x += (Light->getColor().r/255) * lum;
        cLight.y += (Light->getColor().g/255) * lum;
        cLight.z += (Light->getColor().b/255) * lum;
        // Phong
        double lum2 = Light->getLuminescencePhong(datas, Light);
        cLightPhong.x += (Light->getColor().r/255) * lum2;
        cLightPhong.y += (Light->getColor().g/255) * lum2;
        cLightPhong.z += (Light->getColor().b/255) * lum2;
    }
}

static sf::Color getColorReflected(hitDatas &datas, RayTracer::Vector3D uv,
int &maxBounce) {
    sf::Color c(0, 0, 0);
    if (datas.obj->getMaterial()->isReflective() && maxBounce > 0) {
        RayTracer::Vector3D normal = datas.obj->getNormalAt(datas.intersection);
        RayTracer::Vector3D reflected(datas.direction - normal *
            2*(datas.direction.normalized().dot(normal)));
        RayTracer::Ray r(datas.intersection, reflected);
        maxBounce-= 1;
        c = checkHitAt(r, maxBounce, datas.obj);
    } else {
        c = datas.obj->getMaterial()->getColorAt(uv.x, uv.y);
    }
    return c;
}

static void hit(
hitDatas &datas, sf::Color &color, int &maxBounce) {
    try {
        // Get base colors
        sf::Color origin = color;
        RayTracer::Vector3D uv = datas.obj->getUV(datas.intersection);
        sf::Color c = getColorReflected(datas, uv, maxBounce);
        sf::Vector3f cLight = sf::Vector3f(0, 0, 0);
        sf::Vector3f cLightPhong = sf::Vector3f(0, 0, 0);

        computeLuminescence(datas, cLight, cLightPhong);
        if (!datas.obj->getMaterial()->isReflective()) {
            editColor(c, cLight, origin, cLightPhong);
        } else {
            editColorReflect(c, c, cLightPhong);
        }
        color = c;
    } catch (std::exception &e) {
        color = sf::Color(234, 58, 247);
        return;
    }
}

static void checkHitsAtPixel(RayTracer::Ray r, std::shared_ptr<Prim> &obj,
std::vector<hitDatas> &lst, std::shared_ptr<Prim> exclude) {
    RayTracer::Point3D intersection;
    if ((exclude == nullptr || (exclude != nullptr && obj != exclude))
        && obj->hits(r, intersection)) {
        hitDatas h;
        h.intersection = intersection;
        h.origin = r.origin;
        h.direction = r.direction;
        h.len = r.origin.distance(intersection);
        h.obj = obj;
        lst.push_back(h);
    }
    for (std::shared_ptr<Prim> &o : obj->getChildrens())
        checkHitsAtPixel(r, o, lst, exclude);
}

static sf::Color checkHitAt(RayTracer::Ray r, int &maxBounce,
std::shared_ptr<Prim> exclude) {
    std::vector<hitDatas> lst;
    sf::Color c = skybox::i().getColorAt(skybox::i().getAngle(r));

    checkHitsAtPixel(r,
        RayTracer::Scene::i->ObjectHead, lst, exclude);
    // sort from the farthest to the closest
    std::sort(lst.begin(), lst.end(),
        [](const hitDatas &a, const hitDatas &b) {
            return a.len > b.len;
        });
    for (hitDatas &h : lst) {
        hit(h, c, maxBounce);
    }
    return c;
}

static sf::Color checkHitAtRay(float i, float j, float iplus, float jplus,
    RayTracer::Camera cam) {
    int maxBounce = 5;
    RayTracer::Ray r = cam.ray((i + iplus) / cam.image_width,
        (j + jplus) / cam.image_height);
    return checkHitAt(r, maxBounce, nullptr);
}

static void generatePixelColumn(float i, RayTracer::Camera cam,
my_Image &image) {
    std::vector<sf::Color> colors;
    for (float j = 0; j < cam.image_height; j++) {
        colors.clear();
        colors.push_back(checkHitAtRay(i, j, 0, 0, cam));
        colors.push_back(checkHitAtRay(i, j, 0, -0.5f, cam));
        colors.push_back(checkHitAtRay(i, j, 0, 0.5f, cam));
        colors.push_back(checkHitAtRay(i, j, -0.5f, 0, cam));
        colors.push_back(checkHitAtRay(i, j, -0.5f, -0.5f, cam));
        colors.push_back(checkHitAtRay(i, j, -0.5f, 0.5f, cam));
        colors.push_back(checkHitAtRay(i, j, 0.5f, 0, cam));
        colors.push_back(checkHitAtRay(i, j, 0.5f, -0.5f, cam));
        colors.push_back(checkHitAtRay(i, j, 0.5f, 0.5f, cam));
        averageAllImages(i, j, image, colors);
    }
}

int generateImage(sf::RenderWindow &window, my_Image &image, std::string
    sceneFile) {
    RayTracer::Camera &cam = RayTracer::Camera::i();
    std::vector<std::thread> threadVector;
    int configChanged = 0;

    showImage(window, image);
    for (float i = 0; i < cam.image_width; i++) {
        threadVector.emplace_back(generatePixelColumn, i,
            std::ref(RayTracer::Camera::i()),
            std::ref(image));
    }

    configChanged = displayImage(window, image, sceneFile);

    for (auto &t : threadVector) {
        if (t.joinable())
            t.join();
    }
    return configChanged;
}

int renderImage(my_Image &image) {
    std::vector<std::thread> threadVector;
    RayTracer::Camera &cam = RayTracer::Camera::i();

    for (float i = 0; i < cam.image_width; i++) {
        threadVector.emplace_back(generatePixelColumn, i,
            std::ref(RayTracer::Camera::i()),
            std::ref(image));
    }

    for (auto &t : threadVector) {
        if (t.joinable())
            t.join();
    }
    createPPMFile(image.image, "renders/render-" +
        getTimestampAsString() + ".ppm");
    return 0;
}
