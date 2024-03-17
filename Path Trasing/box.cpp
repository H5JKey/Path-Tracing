#include "box.h"

Box::Box(sf::Vector3f position, sf::Vector3f size, sf::Vector3f color, float diffusness, float opacity, bool lighEmitter) {
	this->material.color = color;
	this->position = position;
	this->size = size;
	material.diffuseness = diffusness;
	material.lightEmitter = lighEmitter;
	material.opacity = opacity;
}

sf::Vector3f Box::getPosition() {
	return position;
}

sf::Vector3f Box::getSize() {
	return size;
}

Material Box::getMaterial()
{
	return material;
}

bool Box::collide(sf::Vector3f point)
{
	return (point.y < position.y + size.y && point.y > position.y - size.y) && (point.x >position.x - size.x && point.x <position.x + size.x) && (point.z >position.z - size.z && point.z <position.z + size.z);
}

void Box::setMaterial(Material material)
{
	this->material = material;
}

void Box::setPosition(sf::Vector3f position)
{
	this->position = position;
}

void Box::setSize(sf::Vector3f size)
{
	this->size = size;
}