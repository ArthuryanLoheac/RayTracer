#pragma once
#include <string>
#include <libconfig.h++>

#include "Scene/Scene.hpp"

namespace RayTracer {
class Parsing {
 private:
     std::string sceneFile;

 public:
    bool noWindowMode = false;
    void parseArgs(int argc, char **argv);
    void parseSceneFile();
    //  void parseCamera(const libconfig::Setting &setting);
     void parsePrimitive(const libconfig::Setting &setting);
    //  void parseLights(const libconfig::Setting &setting);

     class ParsingError : public std::exception {
      private:
          std::string message;

      public:
          explicit ParsingError(const std::string &message);
          const char *what() const noexcept override;
     };
};
}  // namespace RayTracer
