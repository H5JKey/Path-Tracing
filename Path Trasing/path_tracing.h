#pragma once
#include <SFML/Graphics.hpp>
#include "render.h"
#include "player.h"


class PathTracingProgramm
{
public:
    Render render;
    sf::RenderWindow window;
    sf::Time ellapsed;
    sf::Time programmTime;
    sf::Clock clock;
    bool rotating;

    std::vector<Box> boxes;
    std::vector<Sphere> spheres;
    Player player;

public:
    PathTracingProgramm();

    void update();

    ~PathTracingProgramm();
};




