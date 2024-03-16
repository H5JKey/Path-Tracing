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

sf::Vector3f Box::getColor() {
	return material.color;
}


float Box::getDiffuseness() {
	return material.diffuseness;
}

float Box::getOpacity()
{
	return material.opacity;
}

bool Box::isLightEmitter() {
	return material.lightEmitter;
}