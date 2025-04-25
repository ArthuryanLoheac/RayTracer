#include <cstdio>
#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "3dDatas/Vector3D.hpp"
#include "Camera/Camera.hpp"
#include "Primitive/Sphere.hpp"
#include "3dDatas/Point3D.hpp"
#include "Consts/const.hpp"

void showImage(sf::RenderWindow &window, sf::Image &image) {
    sf::Sprite sp;
    sf::Texture txt;

    txt.loadFromImage(image);
    sp.setTexture(txt);
    window.clear();
    window.draw(sp);
    window.display();
}

void displayImage(sf::RenderWindow &window, sf::Image &image) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        showImage(window, image);
    }
}

void generateImage(sf::RenderWindow &window, sf::Image &image) {
    RayTracer::Camera cam;
    RayTracer::Sphere s(RayTracer::Point3D(0.02f, 0.17f, -1), 0.1);

    for (float i = 0; i < WIDTH; i++) {
        for (float j = 0; j < HEIGHT; j++) {
            double u = i / WIDTH;
            double v = j / HEIGHT;
            RayTracer::Ray r = cam.ray(u, v);

            if (s.hits(r))
                image.setPixel(static_cast<int>(i), static_cast<int>(j),
                    sf::Color::Red);
            else
                image.setPixel(static_cast<int>(i), static_cast<int>(j),
                    sf::Color::Blue);
        }
        showImage(window, image);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ray Tracer");
    sf::Image image;
    image.create(WIDTH, HEIGHT, sf::Color::Black);

    generateImage(window, image);
    displayImage(window, image);
}
