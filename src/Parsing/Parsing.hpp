#pragma once
#include "Scene/Scene.hpp"

namespace RayTracer {
class Parsing {
 private:
     std::string sceneFile;

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
