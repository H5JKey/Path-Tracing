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

sf::Vector3f Sphere::getColor() {
	return material.color;
}


float Sphere::getDiffuseness() {
	return material.diffuseness;
}

float Sphere::getOpacity()
{
	return material.opacity;
}

bool Sphere::isLightEmitter() {
	return material.lightEmitter;
}