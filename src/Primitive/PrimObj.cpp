#include <memory>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits>
#include <iostream>
#include <vector>
#include <string>

#include "Primitive/PrimObj.hpp"
#include "dlLoader/dlLoader.hpp"
#include "Consts/const.hpp"

extern "C" std::unique_ptr<RayTracer::I_Primitive> getPrimitive() {
    return std::make_unique<PrimObj>();
}

PrimObj::PrimObj() {
    Init();
}

void PrimObj::Init() {
    position = RayTracer::Point3D(0, 0, 5);
    rotation = RayTracer::Vector3D(0, 0, 0);
    scale = RayTracer::Point3D(10, 10, 10);

    filename = "assets/gun.obj";

    try {
        loadObjFile(filename);
        material = dlLoader<Mat>::getLib("libs/mat_flat.so", "getMaterial");
    } catch (std::exception &e) {
        std::cerr << "Error initializing OBJ primitive: " << e.what()
            << std::endl;
        material = nullptr;
    }
}

bool PrimObj::loadObjFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << path << std::endl;
        return false;
    }

    vertices.clear();
    normals.clear();
    textureCoords.clear();
    triangles.clear();

    // Add basic data to the first element just like OBJ files
    vertices.push_back(RayTracer::Point3D(0, 0, 0));
    normals.push_back(RayTracer::Vector3D(0, 0, 0));
    textureCoords.push_back(RayTracer::Vector3D(0, 0, 0));

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            float x, y, z;
            iss >> x >> y >> z;
            vertices.push_back(RayTracer::Point3D(x, y, z));
        } else if (type == "vn") {
            float x, y, z;
            iss >> x >> y >> z;
            normals.push_back(RayTracer::Vector3D(x, y, z));
        } else if (type == "vt") {
            float u, v;
            iss >> u >> v;
            textureCoords.push_back(RayTracer::Vector3D(u, v, 0));
        } else if (type == "f") {
            std::string vertex;
            std::vector<int> vertexIndices;
            std::vector<int> textureIndices;
            std::vector<int> normalIndices;
            while (iss >> vertex) {
                std::istringstream vertexIss(vertex);
                std::string indexStr;
                std::getline(vertexIss, indexStr, '/');
                if (!indexStr.empty()) {
                    vertexIndices.push_back(std::stoi(indexStr));
                }
                std::getline(vertexIss, indexStr, '/');
                if (!indexStr.empty()) {
                    textureIndices.push_back(std::stoi(indexStr));
                }
                std::getline(vertexIss, indexStr, '/');
                if (!indexStr.empty()) {
                    normalIndices.push_back(std::stoi(indexStr));
                }
            }
            if (vertexIndices.size() >= 3) {
                for (size_t i = 0; i < vertexIndices.size() - 2; ++i) {
                    Triangle triangle;
                    triangle.v0 = vertices[vertexIndices[0]];
                    triangle.v1 = vertices[vertexIndices[i+1]];
                    triangle.v2 = vertices[vertexIndices[i+2]];
                    if (normalIndices.empty()) {
                        RayTracer::Vector3D edge1 = triangle.v1 - triangle.v0;
                        RayTracer::Vector3D edge2 = triangle.v2 - triangle.v0;
                        triangle.normal = RayTracer::Vector3D(
                            edge1.y * edge2.z - edge1.z * edge2.y,
                            edge1.z * edge2.x - edge1.x * edge2.z,
                            edge1.x * edge2.y - edge1.y * edge2.x)
                        .normalize();
                    } else {
                        triangle.normal = normals[normalIndices[0]];
                    }
                    triangles.push_back(triangle);
                }
            }
        }
    }
    return true;
}

void PrimObj::setObjFile(const std::string& path) {
    filename = path;
    loadObjFile(filename);
}

bool PrimObj::rayTriangleIntersect(const Triangle& triangle,
    const RayTracer::Ray& ray, RayTracer::Point3D& intersection, float& t) {
    const float EPSILON = 0.0000001;
    RayTracer::Point3D v0 = triangle.v0;
    RayTracer::Point3D v1 = triangle.v1;
    RayTracer::Point3D v2 = triangle.v2;

    RayTracer::Vector3D scaleVec(scale.x, scale.y, scale.z);
    v0 = RayTracer::Point3D(v0.x * scaleVec.x, v0.y * scaleVec.y, v0.z *
        scaleVec.z) + position;
    v1 = RayTracer::Point3D(v1.x * scaleVec.x, v1.y * scaleVec.y, v1.z *
        scaleVec.z) + position;
    v2 = RayTracer::Point3D(v2.x * scaleVec.x, v2.y * scaleVec.y, v2.z *
        scaleVec.z) + position;

    RayTracer::Vector3D edge1 = v1 - v0;
    RayTracer::Vector3D edge2 = v2 - v0;

    RayTracer::Vector3D h(
        ray.direction.y * edge2.z - ray.direction.z * edge2.y,
        ray.direction.z * edge2.x - ray.direction.x * edge2.z,
        ray.direction.x * edge2.y - ray.direction.y * edge2.x);
    float a = edge1.dot(h);
    if (a > -EPSILON && a < EPSILON)
        return false;
    float f = 1.0 / a;
    RayTracer::Point3D rayOrigin(ray.origin.x, ray.origin.y, ray.origin.z);
    RayTracer::Vector3D s = rayOrigin - v0;
    float u = f * s.dot(h);
    if (u < 0.0 || u > 1.0)
        return false;
    RayTracer::Vector3D q(
        s.y * edge1.z - s.z * edge1.y,
        s.z * edge1.x - s.x * edge1.z,
        s.x * edge1.y - s.y * edge1.x);
    RayTracer::Vector3D rayDir(ray.direction.x, ray.direction.y,
        ray.direction.z);
    float v = f * rayDir.dot(q);
    if (v < 0.0 || u + v > 1.0)
        return false;
    float tt = f * edge2.dot(q);
    if (tt > EPSILON) {
        t = tt;
        RayTracer::Vector3D dir(ray.direction.x, ray.direction.y,
            ray.direction.z);
        intersection = RayTracer::Point3D(
            rayOrigin.x + dir.x * t,
            rayOrigin.y + dir.y * t,
            rayOrigin.z + dir.z * t);
        return true;
    }
    return false;
}

bool PrimObj::hits(RayTracer::Ray ray, RayTracer::Point3D &intersection) {
    if (triangles.empty())
        return false;

    float closest = std::numeric_limits<float>::max();
    bool hit = false;

    for (const auto& triangle : triangles) {
        float t;
        RayTracer::Point3D tempIntersection;
        if (rayTriangleIntersect(triangle, ray, tempIntersection, t)) {
            if (t < closest) {
                closest = t;
                intersection = tempIntersection;
                hit = true;
            }
        }
    }
    return hit;
}

RayTracer::Vector3D PrimObj::getNormalAt(RayTracer::Point3D point) {
    float minDist = std::numeric_limits<float>::max();
    RayTracer::Vector3D normal;

    for (const auto& triangle : triangles) {
        RayTracer::Point3D v0 = triangle.v0;
        RayTracer::Point3D v1 = triangle.v1;
        RayTracer::Point3D v2 = triangle.v2;

        RayTracer::Vector3D scaleVec(scale.x, scale.y, scale.z);
        v0 = RayTracer::Point3D(v0.x * scaleVec.x, v0.y * scaleVec.y, v0.z *
            scaleVec.z) + position;
        v1 = RayTracer::Point3D(v1.x * scaleVec.x, v1.y * scaleVec.y, v1.z *
            scaleVec.z) + position;
        v2 = RayTracer::Point3D(v2.x * scaleVec.x, v2.y * scaleVec.y, v2.z *
            scaleVec.z) + position;

        RayTracer::Point3D centroid = RayTracer::Point3D(
            (v0.x + v1.x + v2.x) / 3.0,
            (v0.y + v1.y + v2.y) / 3.0,
            (v0.z + v1.z + v2.z) / 3.0);
        RayTracer::Vector3D distVec = point - centroid;
        float dist = distVec.length();

        if (dist < minDist) {
            minDist = dist;
            normal = triangle.normal;
        }
    }
    return normal.normalize();
}

RayTracer::Vector3D PrimObj::getUV(RayTracer::Point3D point) {
    float u = std::fmod(std::abs(point.x - position.x), 1.0f);
    float v = std::fmod(std::abs(point.z - position.z), 1.0f);

    return RayTracer::Vector3D(u, v, 0);
}
