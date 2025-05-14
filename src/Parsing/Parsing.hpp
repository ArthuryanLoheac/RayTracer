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
    //  void parseCamera(const libconfig::Setting &setting, Scene &scene);
     void parsePrimitive(const libconfig::Setting &setting, Scene &scene);
    //  void parseLights(const libconfig::Setting &setting, Scene &scene);

     class ParsingError : public std::exception {
      private:
          std::string message;

      public:
          explicit ParsingError(const std::string &message);
          const char *what() const noexcept override;
     };
};
}  // namespace RayTracer
