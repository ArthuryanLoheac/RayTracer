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
#include "Draw/hit.hpp"

int sizePixelPreview = 16;

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
        b * percentA + (origin.b * (1 - percentA)), 100);
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

static void setPixels(my_Image &image, int i, int j, sf::Color c) {
    for (int x = 0; x < sizePixelPreview; ++x) {
        for (int y = 0; y < sizePixelPreview; ++y) {
            if (i + x >= WIDTH || j + y >= HEIGHT)
                continue;
            image.setPixel(i + x, j + y, c);
        }
    }
}

static void hit(my_Image &image, int i, int j,
hitDatas &datas) {
    try {
        // Get base colors
        sf::Color origin = image.getPixel(i, j);
        RayTracer::Vector3D uv = datas.obj->getUV(datas.intersection);
        sf::Color c = datas.obj->getMaterial()->getColorAt(uv.x, uv.y);
        sf::Vector3f cLight = sf::Vector3f(0, 0, 0);

        computeLuminescence(datas.intersection, datas.obj, cLight);

        editColor(c, cLight, origin);
        setPixels(image, i, j, c);
    } catch (std::exception &e) {
        setPixels(image, i, j,
            sf::Color(234, 58, 247));  // error pink
        return;
    }
}

static void checkHitsAtPixel(double i, double j, RayTracer::Ray r,
my_Image &image, std::shared_ptr<Prim> &obj,
std::vector<hitDatas> &lst) {
    RayTracer::Point3D intersection;
    if (obj->hits(r, intersection)) {
        hitDatas h;
        h.intersection = intersection;
        h.len = r.origin.distance(intersection);
        h.obj = obj;
        lst.push_back(h);
    }
    for (std::shared_ptr<Prim> &o : obj->getChildrens())
        checkHitsAtPixel(i, j, r, image, o, lst);
}

static void checkHitAt(float i, float j, float iplus, float jplus,
RayTracer::Camera cam, my_Image &image) {
    RayTracer::Ray r = cam.ray((i + iplus) / WIDTH, (j + jplus) / HEIGHT);
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
}

static void generatePixelColumn(float i, RayTracer::Camera cam,
my_Image &image) {
    for (float j = 0; j < HEIGHT; j += sizePixelPreview) {
        checkHitAt(i, j, 0, 0, cam, image);
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

    showImage(window, image);
    image.image.create(WIDTH, HEIGHT, sf::Color::Black);

    for (float i = 0; i < WIDTH; i += sizePixelPreview)
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
