//defines a orthographic camera component

#ifndef OrthographicCamera_h
#define OrthographicCamera_h

#include <glm.hpp>

struct OrthographicCamera
{
	float viewLength = 5, viewHeight = 5;
	bool isActive = true;
};

#endif