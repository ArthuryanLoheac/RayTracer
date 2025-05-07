#pragma once
#include <string>
#include <libconfig.h++>

#include "Scene/Scene.hpp"

namespace RayTracer {
class Parsing {
 private:
     std::string sceneFile;

 public:
    void parseArgs(int argc, char **argv);
    Scene parseSceneFile();
    void parseCamera(Scene &scene, libconfig::Config &cfg);
    double getDouble(libconfig::Setting &setting);

    class ParsingError : public std::exception {
     private:
        std::string message;

     public:
        explicit ParsingError(const std::string &message);
        const char *what() const noexcept override;
    };
};
}  // namespace RayTracer
