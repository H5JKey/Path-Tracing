#pragma once
#include <SFML/Graphics.hpp>
#include "box.h"
#include "sphere.h"
#include "player.h"
#include "world.h"


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
	sf::RenderTexture texture;
	sf::Sprite sprite;
	sf::Sprite flippedSprite;

	int frame;
	
public:
	Settings settings;

	Render(sf::RenderWindow& window);
	Render();

	void init(sf::RenderWindow& window);

	void operator()(sf::RenderWindow& window);

	void setShaderUniforms(Player player, World& world, sf::Vector2f window_size, sf::Time time);
	void resetFrames();

	~Render();
};

