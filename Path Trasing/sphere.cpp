#include "sphere.h"
#include <iostream>


Sphere::Sphere(sf::Vector3f position, float size, sf::Vector3f color, float diffusness, float opacity, bool lighEmitter) {
	this->material.color = color;
	this->position = position;
	this->size = size;
	material.diffuseness = diffusness;
	material.lightEmitter = lighEmitter;
	material.opacity = opacity;
}

Sphere::Sphere() {
	this->material.color = { 1,1,1 };
	this->position = { 0,0,0 };
	this->size = 1;
	material.diffuseness = 1;
	material.lightEmitter = false;
	material.opacity = 0;
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

Material Sphere::getMaterial()
{
	return material;
}

void Sphere::setMaterial(Material material)
{
	this->material = material;
}

void Sphere::setPosition(sf::Vector3f position)
{
	this->position = position;
}

void Sphere::setSize(float size)
{
	this->size = size;
}