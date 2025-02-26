#pragma once
#include <SFML/Graphics.hpp>
#include "render.h"
#include "player.h"
#include "world.h"
#include <Windows.h>


class PathTracingProgramm
{
public:
    Render render;
    sf::RenderWindow window;
    sf::Time ellapsed;
    sf::Time programmTime;
    sf::Clock clock;
    bool rotating;
    World world;
    Player player;

public:
    PathTracingProgramm();

    void update();

    ~PathTracingProgramm();
};




