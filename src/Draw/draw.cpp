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
#include "Primitive/I_Primitive.hpp"
#include "3dDatas/Point3D.hpp"
#include "Consts/const.hpp"

#include <fstream>
#include <iostream>

static void showImage(sf::RenderWindow &window, sf::Image &image) {
    sf::Sprite sp;
    sf::Texture txt;

    txt.loadFromImage(image);
    sp.setTexture(txt);
    window.clear();
    window.draw(sp);
    window.display();
}

void createPPMFile(const sf::Image& image,
    const std::string& filename) {
    unsigned int width;
    unsigned int height;
    std::ofstream out(filename);

    width = image.getSize().x;
    height = image.getSize().y;
    out << "P3\n" << width << " " << height << "\n255\n";
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            sf::Color color = image.getPixel(x, y);
            out << static_cast<int>(color.r) << " "
                << static_cast<int>(color.g) << " "
                << static_cast<int>(color.b) << "  ";
        }
        out << "\n";
    }
    out.close();
}

void displayImage(sf::RenderWindow &window, sf::Image &image) {
    while (window.isOpen()) {
        sf::Event event;
        sf::Texture texture;
        sf::Image screenshot;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed
                || event.key.code == sf::Keyboard::Escape){
                texture.create(window.getSize().x, window.getSize().y);
                texture.update(window);
                screenshot  = texture.copyToImage();
                createPPMFile(screenshot, "renders/render.ppm");
                window.close();
            }
        }
        showImage(window, image);
    }
}

static void hit(sf::Image &image, int i, int j,
    std::unique_ptr<Prim> &s, RayTracer::Point3D &intersection,
    std::unique_ptr<Light> &Light) {
    try {
        sf::Color c = s->getMaterial()->getColorAt(i, j);
        double distance = intersection.distance(Light->getPosition());
        double angle = 0;
        double luminescence = Light->getLuminescence(distance, angle);
        int r = std::min(255, static_cast<int>(c.r * luminescence));
        int g = std::min(255, static_cast<int>(c.g * luminescence));
        int b = std::min(255, static_cast<int>(c.b * luminescence));
        c = sf::Color(r, g, b);
        image.setPixel(i, j, c);
    } catch (std::exception &e) {
        image.setPixel(i, j,
            sf::Color(234, 58, 247));  // error pink
        return;
    }
}

void generateImage(sf::RenderWindow &window, sf::Image &image,
    std::unique_ptr<Prim> &s, std::unique_ptr<Light> &Light) {
    RayTracer::Camera cam;

    for (float i = 0; i < WIDTH; i++) {
        for (float j = 0; j < HEIGHT; j++) {
            double u = i / WIDTH;
            double v = j / HEIGHT;
            RayTracer::Ray r = cam.ray(u, v);
            RayTracer::Point3D intersection;

            if (s->hits(r, intersection))
                hit(image, static_cast<int>(i), static_cast<int>(j), s,
                    intersection, Light);
        }
        showImage(window, image);
    }
}
