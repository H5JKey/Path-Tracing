#pragma once
#include <SFML/Graphics.hpp>
#include "box.h"
#include "sphere.h"
#include "player.h"


struct Settings {
	int reflections;
	int samples;

	Settings(int reflections, int samples) {
		this->reflections = reflections;
		this->samples = samples;
	}
};


class Render
{
	
	sf::Shader shader;
	std::vector<sf::RenderTexture> textures;
	std::vector<sf::Sprite> sprites;
	std::vector<sf::Sprite> flippedSprites;

	int frame;
	
public:
	Settings settings;

	Render(int width, int height);

	void operator()(sf::RenderWindow& window);

	void setShaderUniforms(Player player, std::vector<Box>& boxes, std::vector<Sphere>& spheres, sf::Vector2f window_size, sf::Time time);
	void resetFrames();

	~Render();
};

