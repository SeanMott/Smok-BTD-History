//defines a sprite component

#ifndef Sprite_h
#define Sprite_h

#include <string>
#include <glm.hpp>

struct Sprite
{
	std::string texture = "";
	unsigned int textureSlot = 0;
	std::string shader = "";

	glm::vec3 color = glm::vec3(1.0f);

	unsigned int layer = 0; //renders sprites from highest layer to lowest ie 12 to 0

	bool isActive = true;
};

#endif