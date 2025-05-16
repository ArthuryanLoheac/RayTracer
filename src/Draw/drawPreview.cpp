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
#include <condition_variable>
#include <queue>

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
#include "Draw/skybox.hpp"
#include "Draw/hit.hpp"

int sizePixelPreview = 16;
static sf::Color checkHitAt(RayTracer::Ray r, int &maxBounce,
std::shared_ptr<Prim> exclude);

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

static void computeLuminescence(hitDatas &datas, sf::Vector3f &cLight) {
    for (std::shared_ptr<Light> Light : RayTracer::Scene::i->Lights) {
        double lum = Light->getLuminescence(datas, Light,
            RayTracer::Scene::i->ObjectHead);
        cLight.x += (Light->getColor().r/255) * lum;
        cLight.y += (Light->getColor().g/255) * lum;
        cLight.z += (Light->getColor().b/255) * lum;
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
        maxBounce -= 1;
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

        if (!datas.obj->getMaterial()->isReflective()) {
            computeLuminescence(datas, cLight);

            editColor(c, cLight, origin);
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
    for (float j = 0; j < cam.image_height; j+= sizePixelPreview) {
        colors.clear();
        colors.push_back(checkHitAtRay(i, j, 0, 0, cam));
        for (float x = 0; x < sizePixelPreview; x++) {
            for (float y = 0; y < sizePixelPreview; y++) {
                if (x + i < cam.image_width && y + j < cam.image_height)
                    averageAllImages(i + x, j + y, image, colors, true);
            }
        }
    }
}

int generateImagePreview(sf::RenderWindow &window, my_Image &image,
int pixels) {
    sizePixelPreview = pixels;
    int configChanged = 0;
    // THREADS DATAS
    std::vector<std::thread> threadVector;
    unsigned int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threadPool;
    std::queue<float> taskQueue;
    std::mutex queueMutex;
    std::condition_variable cv;
    bool done = false;
    RayTracer::Camera &cam = RayTracer::Camera::i();

    showImage(window, image);
    image.image.create(cam.image_width, cam.image_height, sf::Color::Black);

    for (float i = 0; i < cam.image_width; i += sizePixelPreview)
        taskQueue.push(i);
    for (unsigned int t = 0; t < numThreads; ++t) {
        threadPool.emplace_back([&]() {
            while (true) {
                float i;
                {
                    std::unique_lock<std::mutex> lock(queueMutex);
                    cv.wait(lock, [&]() { return !taskQueue.empty() || done; });
                    if (done && taskQueue.empty()) break;
                    i = taskQueue.front();
                    taskQueue.pop();
                }
                generatePixelColumn(i, RayTracer::Camera::i(), image);
            }
        });
    }

    {
        std::unique_lock<std::mutex> lock(queueMutex);
        done = true;
    }
    cv.notify_all();
    for (auto &t : threadPool) {
        if (t.joinable())
            t.join();
    }
    showImage(window, image);
    return configChanged;
}
