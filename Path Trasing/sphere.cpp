#include "sphere.h"

Sphere::Sphere(sf::Vector3f position, float size, sf::Vector3f color, float diffusness, float opacity, bool lighEmitter) {
	this->material.color = color;
	this->position = position;
	this->size = size;
	material.diffuseness = diffusness;
	material.lightEmitter = lighEmitter;
	material.opacity = opacity;
}

sf::Vector3f Sphere::getPosition() {
	return position;
}

float Sphere::getSize() {
	return size;
}

bool Sphere::collide(sf::Vector3f point)
{
	return ((point.x - position.x) * (point.x - position.x) + (point.y - position.y) * (point.y - position.y) + (point.z - position.z) * (point.z - position.z) <= size * size);
}

Material& Sphere::getMaterial()
{
	return material;
}
