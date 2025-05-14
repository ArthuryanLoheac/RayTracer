#include <thread>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <mutex>
#include <iostream>

#include "Generation/tools.hpp"
#include "Draw/my_Image.hpp"
#include "Scene/Camera.hpp"

#include "Consts/const.hpp"
#include "Scene/Scene.hpp"
#include "DesignPatterns/Factory.hpp"

int renderImage(my_Image &image, std::string sceneFile) {
    // ! TO DELETE AFTER CONFIG FILE HANDLING

    RayTracer::Scene::i->ObjectHead = Factory<Prim>::i().create("none");

    RayTracer::Scene::i->ObjectHead->AddChildren(
        Factory<Prim>::i().create("ambient"));
    RayTracer::Scene::i->ObjectHead->AddChildren(Factory<Prim>::i().
        create("spot"));
    RayTracer::Scene::i->ObjectHead->AddChildren(Factory<Prim>::i().
        create("spot"));
    RayTracer::Scene::i->ObjectHead->AddChildren(Factory<Prim>::i().
        create("spot"));
    RayTracer::Scene::i->ObjectHead->AddChildren(Factory<Prim>::i().
        create("sphere"));
    RayTracer::Scene::i->ObjectHead->AddChildren(Factory<Prim>::i().
        create("plane"));
    RayTracer::Scene::i->ObjectHead->AddChildren(Factory<Prim>::i().
        create("cone"));
    RayTracer::Scene::i->ObjectHead->AddChildren(Factory<Prim>::i().
        create("cylinder"));

    computeTreeValues(RayTracer::Scene::i->ObjectHead);

    // ! TO DELETE AFTER CONFIG FILE HANDLING

    RayTracer::Camera cam;
    std::vector<std::thread> threadVector;
    std::vector<std::unique_ptr<my_Image>> images;

    (void)sceneFile;

    createListImages(images, image);
    for (float i = 0; i < WIDTH; i++) {
        threadVector.emplace_back(generatePixelColumn, i,
            std::ref(cam), std::ref(image), std::ref(images));
    }

    for (auto &t : threadVector) {
        if (t.joinable())
            t.join();
    }

    createPPMFile(image.image, "renders/render-" +
        getTimestampAsString() + ".ppm");
    return 0;
}
