//handles input for the window platform

#ifndef WindowInput_h
#define WindowInput_h

#include <glm.hpp>

class Input
{
	//vars
private:
	static double mouseXPos, mouseYPos, mouseXScroll, mouseYScroll;

	//methods
public:

	//links the events needed for input
	static void LinkEvents();

	//returns the state of a key
	static bool GetKey(int keycode);
	//returns the state of the mouse button
	static bool GetMouseButton(int button);
	
	//returns the mouse position
	static inline glm::vec2 GetMousePosition() { return glm::vec2(mouseXPos, mouseYPos); }
	//returns the mouse scroll
	static inline glm::vec2 GetMouseScroll() { return glm::vec2(mouseXScroll, mouseYScroll); }

public:

	//updates mouse position
	static inline void UpdateMousePos(double xPos, double yPos) { mouseXPos = xPos; mouseYPos = yPos; }
	//updates mouse scroll
	static inline void UpdateMouseScroll(double xOffset, double yOffset) { mouseXScroll = xOffset; mouseYScroll = yOffset; }
};

#endif