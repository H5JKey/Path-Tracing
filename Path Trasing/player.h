#pragma once
#include <SFML/Graphics.hpp>

class Player
{
	sf::Vector3f position;
	sf::Vector3f rotation;

	float speed;

public:
	Player(sf::Vector3f position);

	bool update(sf::Time ellapsed);
	bool rotate(const sf::RenderWindow& window);
	sf::Vector3f getPosition();
	sf::Vector3f getRotation();
};

