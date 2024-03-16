#pragma once
#include <SFML/Graphics.hpp>

struct Material {
	sf::Vector3f color;
	float diffuseness;
	bool lightEmitter;
	float opacity;
};

class Box
{
private:
	sf::Vector3f size;
	sf::Vector3f position;
	Material material;
public:

	Box() {};
	Box(sf::Vector3f position, sf::Vector3f size, sf::Vector3f color, float diffusness, float opacity, bool lighEmitter);

	sf::Vector3f getPosition();
	sf::Vector3f getSize();
	Material& getMaterial();

	bool collide(sf::Vector3f point);
};

