//defines a Rigidbody for 2D

#ifndef Rigidbody_h
#define Rigidbody_h

#include <Core\Logger.h>

//sets the direction for applying force
enum class ForceDirection
{
	None,
	Up,
	Down,
	Left,
	Right
};

struct Rigidbody
{
	float mass = 0.5f;
	ForceDirection forceDir = ForceDirection::None;
	float force = 0.0f;

	bool isActive = true;
};

#endif