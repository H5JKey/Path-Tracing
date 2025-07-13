#include "render.h"


void Render::init(sf::RenderWindow& window) {
	shader.loadFromFile("shader.glsl", sf::Shader::Fragment);
	int width = window.getSize().x;
	int height = window.getSize().y;
	texture.create(width, height);
	sprite = sf::Sprite(texture.getTexture());
	flippedSprite = sf::Sprite(texture.getTexture());
	flippedSprite.setScale(1, -1);
	flippedSprite.setPosition(0, height);


	frame = 1;
}


Render::Render(sf::RenderWindow& window) :settings(8, 2) {
	init(window);
}

Render::Render():settings(8, 2) {}


void Render::operator()(sf::RenderWindow& window) {

	texture.draw(flippedSprite, &shader);
	window.draw(flippedSprite);
	frame++;

}

void Render::setShaderUniforms(Player player, World& world, sf::Vector2f window_size, sf::Time time) {
	shader.setUniform("time", time.asSeconds());
	shader.setUniform("u_resolution", window_size);
	std::vector<Box> boxes = world.getBoxes();
	std::vector<Sphere> spheres = world.getSpheres();
	for (int i = 0; i < boxes.size(); i++) {
		shader.setUniform("boxes[" + std::to_string(i) + "].position", boxes[i].getPosition());
		shader.setUniform("boxes[" + std::to_string(i) + "].size", boxes[i].getSize());
		shader.setUniform("boxes[" + std::to_string(i) + "].color", boxes[i].getMaterial().color);
		shader.setUniform("boxes[" + std::to_string(i) + "].diffuseness", boxes[i].getMaterial().diffuseness);
		shader.setUniform("boxes[" + std::to_string(i) + "].lightEmitter", boxes[i].getMaterial().lightEmitter);
		shader.setUniform("boxes[" + std::to_string(i) + "].opacity", boxes[i].getMaterial().opacity);
	}
	for (int i = 0; i < spheres.size(); i++) {
		shader.setUniform("spheres[" + std::to_string(i) + "].position", spheres[i].getPosition());
		shader.setUniform("spheres[" + std::to_string(i) + "].size", spheres[i].getSize());
		shader.setUniform("spheres[" + std::to_string(i) + "].color", spheres[i].getMaterial().color);
		shader.setUniform("spheres[" + std::to_string(i) + "].diffuseness", spheres[i].getMaterial().diffuseness);
		shader.setUniform("spheres[" + std::to_string(i) + "].lightEmitter", spheres[i].getMaterial().lightEmitter);
		shader.setUniform("spheres[" + std::to_string(i) + "].opacity", spheres[i].getMaterial().opacity);
	}
	shader.setUniform("position", player.getPosition());
	shader.setUniform("u_rotation", player.getRotation());
	shader.setUniform("samples", settings.samples);
	shader.setUniform("reflections", settings.reflections);
	//shader.setUniform("u_sample_part", 1.0f / frame);
	shader.setUniform("Nbox", int(boxes.size()));
	shader.setUniform("Nsphere", int(spheres.size()));
	//shader.setUniform("u_sample", texture.getTexture());
}

void Render::resetFrames()
{
	frame = 0;
}

Render::~Render() {

}