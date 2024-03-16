#pragma once
#include <SFML/Graphics.hpp>
#include "box.h"



class Sphere
{
private:
	float size;
	sf::Vector3f position;
	Material material;
public:

	Sphere() {};

	Sphere(sf::Vector3f position, float size, sf::Vector3f color, float diffusness, float opacity, bool lighEmitter);

	sf::Vector3f getPosition();

	float getSize();

	sf::Vector3f getColor();

	float getDiffuseness();

	float getOpacity();

	bool isLightEmitter();
};

