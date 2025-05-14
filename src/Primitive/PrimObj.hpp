#pragma once

#include <string>
#include <vector>
#include "Interfaces/Primitive/A_Primitive.hpp"
#include "3dDatas/Point3D.hpp"
#include "3dDatas/Vector3D.hpp"
#include "3dDatas/Ray.hpp"

struct Triangle {
    RayTracer::Point3D v0, v1, v2;
    RayTracer::Vector3D normal;
};

class PrimObj : public RayTracer::A_Primitive {
 private:
    std::string filename;
    std::vector<RayTracer::Point3D> vertices;
    std::vector<RayTracer::Vector3D> normals;
    std::vector<RayTracer::Vector3D> textureCoords;
    std::vector<Triangle> triangles;
    bool loadObjFile(const std::string& path);
    void faceCreation(std::istringstream &iss);
    bool rayTriangleIntersect(const Triangle& triangle,
        const RayTracer::Ray& ray, RayTracer::Point3D& intersection, float& t);

 public:
    PrimObj();
    bool hits(RayTracer::Ray ray, RayTracer::Point3D &intersection) override;
    RayTracer::Vector3D getNormalAt(RayTracer::Point3D point) override;
    RayTracer::Vector3D getUV(RayTracer::Point3D point) override;
    void Init() override;
    void setObjFile(const std::string& path);
};
