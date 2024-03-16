#pragma once
#include "box.h"
#include "sphere.h"


class World
{
public:
    std::vector<Box> boxes;
    std::vector<Sphere> spheres;

    World();

    std::vector<Box>& getBoxes();
    std::vector<Sphere>& getSpheres();
};
