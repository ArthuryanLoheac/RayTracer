#pragma once
#include <string>
#include <memory>
#include <libconfig.h++>

#include "Scene/Scene.hpp"

namespace RayTracer {
class Parsing {
 public:
     std::string sceneFile = "";
     bool noWindowMode = false;
     void parseArgs(int argc, char **argv);

     void parseSceneFile();

     void parseCamera(const libconfig::Setting &camera);
     void parseCam(const libconfig::Setting &camera);

     void parsePrimitives(const libconfig::Setting &primitives);
     void parsePrimitive(const libconfig::Setting &primitive,
        const std::string &type);
     void parseSphere(const libconfig::Setting &sphere);
     void parsePlane(const libconfig::Setting &plane);
     void parseCylinder(const libconfig::Setting &cylinder);
     void parseLimCylinder(const libconfig::Setting &limCylinder);
     void parseCone(const libconfig::Setting &cone);
     void parseLimCone(const libconfig::Setting &limCone);
     void parseObject(const libconfig::Setting &object);
     void parseNone(const libconfig::Setting &none);
     std::shared_ptr<I_Material> parseMaterial(
        const libconfig::Setting &material);

     void parseLights(const libconfig::Setting &lights);
     void parseLight(const libconfig::Setting &light,
        const std::string &type);
     void parseAmbiant(const libconfig::Setting &ambient);
     void parseSpot(const libconfig::Setting &spot);

     Point3D parsePosition(const libconfig::Setting &setting);
     Vector3D parseRotation(const libconfig::Setting &setting);
     Point3D parseScalePoint(const libconfig::Setting &setting);
     Vector3D parseScaleVector(const libconfig::Setting &setting);
     sf::Image parseImage(const libconfig::Setting &setting);
     sf::Color parseColor(const libconfig::Setting &setting);

     class ParsingError : public std::exception {
      private:
          std::string message;

      public:
          explicit ParsingError(const std::string &message);
          const char *what() const noexcept override;
     };
};
}  // namespace RayTracer
