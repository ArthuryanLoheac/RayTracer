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
     void parseSceneFile();
    //  void parseCamera(const libconfig::Setting &camera);
     void parsePrimitives(const libconfig::Setting &primitives);
     void parsePrimitive(const libconfig::Setting &primitive,
        const std::string &type);
     std::shared_ptr<I_Material> parseMaterial(
        const libconfig::Setting &material);
    //  void parseLights(const libconfig::Setting &lights);

     class ParsingError : public std::exception {
      private:
          std::string message;

      public:
          explicit ParsingError(const std::string &message);
          const char *what() const noexcept override;
     };
};
}  // namespace RayTracer
