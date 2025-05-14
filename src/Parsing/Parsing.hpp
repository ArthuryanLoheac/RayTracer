#pragma once
#include <string>

#include "Scene/Scene.hpp"

namespace RayTracer {
class Parsing {
 private:
     std::string sceneFile;
     bool noWindowMode;

 public:
     void parseArgs(int argc, char **argv);
     Scene parseSceneFile();

     class ParsingError : public std::exception {
      private:
          std::string message;

      public:
          explicit ParsingError(const std::string &message);
          const char *what() const noexcept override;
     };
};
}  // namespace RayTracer
