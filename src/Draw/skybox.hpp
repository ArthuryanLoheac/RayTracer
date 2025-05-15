#pragma once
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "3dDatas/Vector3D.hpp"
#include "3dDatas/Ray.hpp"

class skybox {
 private:
    bool isImage;
    sf::Image img;
    sf::Color cl;
 public:
    static skybox &i() {
        static skybox instance;
        return instance;
    }

    skybox();
    void setColor(sf::Color color);
    void setImage(std::string path);
    sf::Color getColorAt(RayTracer::Vector3D vec);
    RayTracer::Vector3D getAngle(RayTracer::Ray r);

    class skyboxException : public std::exception {
     public:
        skyboxException(const std::string &msg) : msg(msg) {}
        const char *what() const noexcept override {
            return msg.c_str();
        }
     private:
        std::string msg;
    };
};
