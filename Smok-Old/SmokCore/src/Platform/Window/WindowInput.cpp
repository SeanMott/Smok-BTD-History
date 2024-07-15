#include <smpch.h>
#include "WindowInput.h"
#include "WindowDisplay.h"

#include <Core\Events\InputEvents.h>

double Input::mouseXPos; double Input::mouseYPos; double Input::mouseXScroll; double Input::mouseYScroll;

//links the events needed for input
void Input::LinkEvents()
{
	MouseMoveEvent::AddMethod(&Input::UpdateMousePos);
	MouseScrollEvent::AddMethod(&Input::UpdateMouseScroll);
}

//returns the state of a key
bool Input::GetKey(int keycode)
{
	return glfwGetKey(WindowDisplay::Instance().GetWindow(), keycode);
}

//returns the state of the mouse button
bool Input::GetMouseButton(int button)
{
	return glfwGetMouseButton(WindowDisplay::Instance().GetWindow(), button);
}