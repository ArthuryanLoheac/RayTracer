#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

#include <libconfig.h++>

#include "Parsing/Parsing.hpp"
#include "Scene/Scene.hpp"
#include "DesignPatterns/Factory.hpp"

namespace RayTracer {

void Parsing::parseArgs(int argc, char **argv) {
    if (argc < 2)
        throw ParsingError("Missing scene file argument.");
    if (argc > 2)
        throw ParsingError("Too many arguments.");
    if (std::string(argv[1]) == "-help") {
        std::cout << "USAGE: ./rayTracer <SCENE_FILE>" << std::endl;
        std::cout << "  SCENE_FILE: scene configuration" << std::endl;
        exit(0);
    }
    sceneFile = argv[1];
}

void Parsing::parseSceneFile() {
    libconfig::Config cfg;

    try {
        cfg.readFile(sceneFile.c_str());
        const libconfig::Setting &raytracer = cfg.lookup("raytracer");
            Scene::i->ObjectHead = Factory<Prim>::i().create("none");

        // AMBIENT LIGHT
        std::shared_ptr<Prim> ambient =
            Factory<Prim>::i().create("ambient");
        std::unordered_map<std::string, std::any> ambientSettings;
        ambientSettings["intensity"] = std::make_any<float>(0.2);
        ambientSettings["color"] = std::make_any<sf::Color>(
            sf::Color(255, 255, 255));
        ambientSettings["angle"] = std::make_any<float>(0.0);
        ambientSettings["position"] = std::make_any<Point3D>(Point3D(0, 0, 0));
        ambient->Init(ambientSettings);
        Scene::i->ObjectHead->AddChildren(ambient);

        // SPOT
        std::shared_ptr<Prim> spot =
            Factory<Prim>::i().create("spot");
        std::unordered_map<std::string, std::any> spotSettings;
        spotSettings["intensity"] = std::make_any<float>(6);
        spotSettings["color"] = std::make_any<sf::Color>(sf::Color(
            255, 0, 0));
        spotSettings["angle"] = std::make_any<float>(180.0);
        spotSettings["position"] = std::make_any<Point3D>(Point3D(0, 2, 2));
        spotSettings["rotation"] = std::make_any<Vector3D>(Vector3D(0, 0, 0));
        spot->Init(spotSettings);
        Scene::i->ObjectHead->AddChildren(spot);


        std::shared_ptr<Mat> mat =
            Factory<Mat>::i().create("perlin");
        std::unordered_map<std::string, std::any> matSettings;
        matSettings["color1"] = std::make_any<sf::Color>(sf::Color(
            255, 255, 255));
        matSettings["color2"] = std::make_any<sf::Color>(sf::Color(0, 0, 255));
        matSettings["repeatX"] = std::make_any<int>(64);
        matSettings["repeatY"] = std::make_any<int>(64);
        matSettings["scale"] = std::make_any<RayTracer::Vector3D>(
            RayTracer::Vector3D(1, 1, 0));
        matSettings["rotation"] = std::make_any<RayTracer::Vector3D>(
            RayTracer::Vector3D(0, 0, 0));
        mat->Init(matSettings);

        // PLANE
        std::shared_ptr<Prim> plane =
            Factory<Prim>::i().create("plane");
        std::unordered_map<std::string, std::any> planeSettings;
        planeSettings["position"] = std::make_any<Point3D>(Point3D(0, 0, 0));
        planeSettings["rotation"] = std::make_any<Vector3D>(Vector3D(0, 0, 0));
        planeSettings["radius"] = std::make_any<float>(10.0);
        planeSettings["material"] = std::make_any<std::shared_ptr<Mat>>(mat);
        plane->Init(planeSettings);
        Scene::i->ObjectHead->AddChildren(plane);

        std::shared_ptr<Mat> chess =
            Factory<Mat>::i().create("chess");
        std::unordered_map<std::string, std::any> chessSettings;
        chessSettings["col1"] = std::make_any<sf::Color>(sf::Color(
            255, 255, 255));
        chessSettings["col2"] = std::make_any<sf::Color>(sf::Color(0, 0, 0));
        chessSettings["scale"] = std::make_any<RayTracer::Vector3D>(
            RayTracer::Vector3D(1, 1, 0));
        chess->Init(chessSettings);

        std::shared_ptr<Prim> plane2 =
            Factory<Prim>::i().create("plane");
        std::unordered_map<std::string, std::any> plane2Settings;
        plane2Settings["position"] = std::make_any<Point3D>(Point3D(1, 2, 10));
        plane2Settings["rotation"] = std::make_any<Vector3D>(Vector3D(0, 0, 90));
        plane2Settings["radius"] = std::make_any<float>(10.0);
        plane2Settings["material"] = std::make_any<std::shared_ptr<Mat>>(chess);
        plane2->Init(plane2Settings);
        Scene::i->ObjectHead->AddChildren(plane2);

        // parseCamera(raytracer);
        parsePrimitive(raytracer);
        // parseLights(raytracer);
    } catch (const libconfig::FileIOException &fioex) {
        throw ParsingError("I/O error while reading file.");
    } catch (const libconfig::ConfigException &ex) {
        throw ParsingError("Error in configuration file.");
    }
}

Parsing::ParsingError::ParsingError(const std::string &message)
: message("ParsingError: " + message) {}

const char *Parsing::ParsingError::what() const noexcept {
    return message.c_str();
}

}  // namespace RayTracer
