#pragma once
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <iostream>

struct Material {
	sf::Vector3f color;
	float diffuseness;
	bool lightEmitter;
	float opacity;
};




struct Polygon {
public:
    sf::Vector3f normal;
    std::vector<sf::Vector3f> vertices;

    Polygon():vertices(3) {}
};

class Model {
public:
    std::vector<sf::Vector3f> vertices;
    std::vector<sf::Vector3f> normals;
    std::vector<Polygon> polygons;

    Model(const std::string& filename) {
        std::ifstream file(filename);


        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string prefix;
            ss >> prefix;
            if (prefix == "v") {
                sf::Vector3f vertex;
                ss >> vertex.x >> vertex.y >> vertex.z;
                vertices.push_back(vertex);
            }
            else if (prefix == "vn") {
                sf::Vector3f normal;
                ss >> normal.x >> normal.y >> normal.z;
                normals.push_back(normal);
            }
            else if (prefix == "f") {
                Polygon polygon;
                for (int i = 0; i < 3; ++i) {
                    std::string data;
                    ss >> data;
                    std::istringstream iss(data);
                    std::string vertexIndexStr, normalIndexStr;
                    std::getline(iss, vertexIndexStr, '/');
                    std::getline(iss, normalIndexStr, '/');
                    int vertexIndex = std::stoi(vertexIndexStr);
                    int normalIndex = std::stoi(normalIndexStr);
                    polygon.vertices[i] = vertices[vertexIndex - 1];
                    //polygon.normal = normals[normalIndex - 1];
                }
                polygons.push_back(polygon);
            }
        }
    }

    void print() {
        for (const auto& polygon : polygons) {
            std::cout << "Polygon normal: " << polygon.normal.x << ", " << polygon.normal.y << ", " << polygon.normal.z << std::endl;
            std::cout << "Polygon vertices: " << std::endl;
            for (const auto& vertex : polygon.vertices) {
                std::cout << vertex.x << ", " << vertex.y << ", " << vertex.z << std::endl;
            }
        }
    }

};