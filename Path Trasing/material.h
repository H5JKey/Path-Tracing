#pragma once
#include <SFML/Graphics.hpp>

struct Material {
	sf::Vector3f color;
	float diffuseness;
	bool lightEmitter;
	float opacity;

	void operator=(const Material material) {
		color = material.color;
		diffuseness = material.diffuseness;
		lightEmitter = material.lightEmitter;
		opacity = material.opacity;
	}

	Material() {
		color = { 0,0,0 };
		diffuseness = 0;
		lightEmitter = false;
		opacity = 0;
	}
};
