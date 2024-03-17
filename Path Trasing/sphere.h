#pragma once
#include <SFML/Graphics.hpp>
#include "material.h"



class Sphere
{
private:

public:
	float size;
	sf::Vector3f position;
	Material material;

	Sphere();
	Sphere(sf::Vector3f position, float size, sf::Vector3f color, float diffusness, float opacity, bool lighEmitter);
	sf::Vector3f getPosition();
	float getSize();
	Material getMaterial();

	bool collide(sf::Vector3f point);

	void setMaterial(Material material);
	void setPosition(sf::Vector3f position);
	void setSize(float size);
};

