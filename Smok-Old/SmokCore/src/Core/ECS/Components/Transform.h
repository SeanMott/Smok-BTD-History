//defines a transform component

#ifndef Transform_h
#define Transform_h

#include <glm.hpp>

struct Transform
{
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

	//returns the front of the entitie's Transform
	inline glm::vec3 Front() { return position + WorldForward(); } // glm::vec3(position.x, position.y, position.z - 1.0f); }
	//returns the back of the entitie's Transform
	inline glm::vec3 Back() { return position + WorldBackward(); } //glm::vec3(position.x, position.y, position.z + 1.0f); }
	//returns the left of the entitie's Transform
	inline glm::vec3 Left() { return position + WorldLeft(); } //glm::vec3(position.x - 1.0f, position.y, position.z); }
	//returns the right of the entitie's Transform
	inline glm::vec3 Right() { return position + WorldRight(); }//glm::vec3(position.x + 1.0f, position.y, position.z); }
	//returns the top of the entitie's Transform
	inline glm::vec3 Top() { return position + WorldUp(); }//glm::vec3(position.x, position.y + 1.0f, position.z); }
	//returns the bottom of the entitie's Transform
	inline glm::vec3 Bottom() { return position + WorldDown(); } //glm::vec3(position.x, position.y - 1.0f, position.z); }

	//returns a vec3 pointing up (0.0f, 1.0f, 0.0f)
	static inline glm::vec3 WorldUp() { return glm::vec3(0.0f, 1.0f, 0.0f); }
	//returns a vec3 pointing down (0.0f, -1.0f, 0.0f)
	static inline glm::vec3 WorldDown() { return glm::vec3(0.0f, 1.0f, 0.0f); }
	//returns a vec3 pointing left (-1.0f, 0.0f, 0.0f)
	static inline glm::vec3 WorldLeft() { return glm::vec3(-1.0f, 0.0f, 0.0f); }
	//returns a vec3 pointing right (1.0f, 0.0f, 0.0f)
	static inline glm::vec3 WorldRight() { return glm::vec3(1.0f, 0.0f, 0.0f); }
	//returns a vec3 pointing forward (0.0f, 0.0f, -1.0f)
	static inline glm::vec3 WorldForward() { return glm::vec3(0.0f, 0.0f, -1.0f); }
	//returns a vec3 pointing backwards (0.0f, 0.0f, 1.0f)
	static inline glm::vec3 WorldBackward() { return glm::vec3(0.0f, 0.0f, 1.0f); }
};

#endif