#include "render.h"





Render::Render(int width, int height):textures(2),flippedSprites(2),sprites(2),settings(8,2) {
	shader.loadFromFile("shader.glsl", sf::Shader::Fragment);

	textures[0].create(width, height);
	sprites[0] = sf::Sprite(textures[0].getTexture());
	flippedSprites[0] = sf::Sprite(textures[0].getTexture());
	flippedSprites[0].setScale(1, -1);
	flippedSprites[0].setPosition(0, height);

	textures[1].create(width, height);
	sprites[1] = sf::Sprite(textures[1].getTexture());
	flippedSprites[1] = sf::Sprite(textures[1].getTexture());
	flippedSprites[1].setScale(1, -1);
	flippedSprites[1].setPosition(0, height);

	frame = 1;
}

void Render::operator()(sf::RenderWindow& window) {

	textures[0].draw(flippedSprites[0], &shader);
	window.draw(flippedSprites[0]);
	frame++;

}

void Render::setShaderUniforms(Player player, std::vector<Box>& boxes, std::vector<Sphere>& spheres, sf::Vector2f window_size, sf::Time time) {
	shader.setUniform("time", time.asSeconds());
	shader.setUniform("resolution", window_size);
	for (int i = 0; i < boxes.size(); i++) {
		shader.setUniform("boxes[" + std::to_string(i) + "].position", boxes[i].getPosition());
		shader.setUniform("boxes[" + std::to_string(i) + "].size", boxes[i].getSize());
		shader.setUniform("boxes[" + std::to_string(i) + "].color", boxes[i].getColor());
		shader.setUniform("boxes[" + std::to_string(i) + "].diffuseness", boxes[i].getDiffuseness());
		shader.setUniform("boxes[" + std::to_string(i) + "].lightEmitter", boxes[i].isLightEmitter());
		shader.setUniform("boxes[" + std::to_string(i) + "].opacity", boxes[i].getOpacity());
	}
	for (int i = 0; i < spheres.size(); i++) {
		shader.setUniform("spheres[" + std::to_string(i) + "].position", spheres[i].getPosition());
		shader.setUniform("spheres[" + std::to_string(i) + "].size", spheres[i].getSize());
		shader.setUniform("spheres[" + std::to_string(i) + "].color", spheres[i].getColor());
		shader.setUniform("spheres[" + std::to_string(i) + "].diffuseness", spheres[i].getDiffuseness());
		shader.setUniform("spheres[" + std::to_string(i) + "].lightEmitter", spheres[i].isLightEmitter());
		shader.setUniform("spheres[" + std::to_string(i) + "].opacity", spheres[i].getOpacity());
	}
	shader.setUniform("position", player.getPosition());
	shader.setUniform("rotation", player.getRotation());
	shader.setUniform("samples", settings.samples);
	shader.setUniform("reflections", settings.reflections);
	shader.setUniform("u_sample_part", 1.0f / frame);
	shader.setUniform("Nbox", int(boxes.size()));
	shader.setUniform("Nsphere", int(spheres.size()));
	shader.setUniform("u_sample", textures[0].getTexture());
}

void Render::resetFrames()
{
	frame = 0;
}

Render::~Render() {

}