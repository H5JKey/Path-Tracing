#include "world.h"

World::World():boxes(0),spheres(0)
{
    boxes.push_back(Box(
        sf::Vector3f{ 5.5 - 20,25.5,94.7 },
        sf::Vector3f{ 40,40,0.2 },
        sf::Vector3f{ 1,1,1 },
        0, 0, true));

    boxes.push_back(Box(
        sf::Vector3f{ -100,-1,-100 },
        sf::Vector3f{ 200,1,200 },
        sf::Vector3f{ 1,1,1 },
        0.8, 0, false));

    boxes.push_back(Box(
        sf::Vector3f{ 7,0,7 },
        sf::Vector3f{ 3,6,3 },
        sf::Vector3f{ 0.5,0.5,0.5 },
        0.99, 0, false));

    /* boxes.push_back(Box(
         sf::Vector3f{ 0,0,15 },
         sf::Vector3f{ 15,15,0.4 },
         sf::Vector3f{ 1,0,0 },
         0.8,0, false));*/

    boxes.push_back(Box(
        sf::Vector3f{ 0,0,0 },
        sf::Vector3f{ 15,15,0.4 },
        sf::Vector3f{ 0,0,1 },
        0.8, 0, false));

    boxes.push_back(Box(
        sf::Vector3f{ 15,0,0 },
        sf::Vector3f{ 0.4,15,15 },
        sf::Vector3f{ 1,0,0 },
        0.8, 0, false));

    boxes.push_back(Box(
        sf::Vector3f{ 0,0,0 },
        sf::Vector3f{ 0.4,15,15 },
        sf::Vector3f{ 0,1,0 },
        1, 0, false));


    boxes.push_back(Box(
        sf::Vector3f{ 0,15,0 },
        sf::Vector3f{ 15,0.4,15 },
        sf::Vector3f{ 1,1,1 },
        1, 0, false));

    spheres.push_back(Sphere(
        sf::Vector3f{ 9,7,9 },
        1.0,
        sf::Vector3f{ 0.5,0.5,0.5 },
        0.99, 0.5, false));
}

std::vector<Box>& World::getBoxes()
{
    return boxes;
}

std::vector<Sphere>& World::getSpheres()
{
    return spheres;
}


