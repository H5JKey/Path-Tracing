#include "player.h"
#include <iostream>
#define PI 3.141592



Player::Player(sf::Vector3f position)
{
	this->speed = 10;
	this->position = position;
	rotation = { -90,0,0 };
}

bool Player::update(sf::Time ellapsed)
{
	bool moved = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			position.x += sin(rotation.y / 180 * PI)* speed * ellapsed.asSeconds();
			position.z -= -cos(rotation.y / 180 * PI)* speed * ellapsed.asSeconds();
			moved = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			position.x += sin((rotation.y+180) / 180 * PI) * speed * ellapsed.asSeconds();
			position.z -= -cos((rotation.y+180) / 180 * PI) * speed * ellapsed.asSeconds();
			moved = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			position.x += sin((rotation.y+90) / 180 * PI) * speed * ellapsed.asSeconds();
			position.z -= -cos((rotation.y+90) / 180 * PI) * speed * ellapsed.asSeconds();
			moved = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			position.x += sin((rotation.y-90) / 180 * PI) * speed * ellapsed.asSeconds();
			position.z -= -cos((rotation.y-90) / 180 * PI) * speed * ellapsed.asSeconds();
			moved = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			position.y += speed*ellapsed.asSeconds();
			moved = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			position.y -= speed * ellapsed.asSeconds();
			moved = true;
		}
		return moved;

}

sf::Vector3f Player::getRotation()
{
	return rotation;
}

bool Player::rotate(const sf::RenderWindow& window)
{
	bool moved = false;

	float x1 = sf::Mouse::getPosition().x;
	float y1 = sf::Mouse::getPosition().y;

	float x2 = window.getPosition().x + window.getSize().x / 2;
	float y2 = window.getPosition().y + window.getSize().y / 2;

	if (abs(x2 - x1) > 0.5)
		moved = true;
	if (abs(y2 - y1) > 0.5)
		moved = true;

	rotation.x = std::max(-90.f, std::min(90.f, rotation.x));

	rotation.y += -(x2 - x1) / 4;
	rotation.x += (y2 - y1) / 4;

	sf::Mouse::setPosition(sf::Vector2i(x2, y2));

	return moved;

}
	

sf::Vector3f Player::getPosition()
{
	return position;
}


Sphere* Player::getSphereLookingAt(World& world, float& distance)
{
	sf::Vector3f rd = sf::Vector3f(sin(rotation.y / 180 * 3.1415), (tan(rotation.x / 180 * 3.1415)), cos(rotation.y / 180 * 3.1415));
	sf::Vector3f ro = position;

	for (float s = 0; s <= 10; s += 0.5) {//  Ray Casting
		sf::Vector3f p = ro + rd * (s);
		for (Sphere& sphere : world.getSpheres()) {
			if (sphere.collide(p)) {
				distance = s;
				return &sphere;
			}
		}
	}
	return nullptr;
}

Box* Player::getBoxLookingAt(World& world, float& distance)
{
	sf::Vector3f rd = sf::Vector3f(sin(rotation.y / 180 * 3.1415), (tan(rotation.x / 180 * 3.1415)), cos(rotation.y / 180 * 3.1415));
	sf::Vector3f ro = position;

	for (float s = 0; s <= 10; s += 0.5) {//  Ray Casting
		sf::Vector3f p = ro + rd * (s);
		for (Box& box : world.getBoxes()) {
			if (box.collide(p)) {
				distance = s;
				return &box;
			}
		}
	}
	return nullptr;
}