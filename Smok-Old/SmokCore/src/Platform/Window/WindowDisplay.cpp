#include <smpch.h>
#include "WindowDisplay.h"

#include <Core\Events\InputEvents.h>
#include <Core\Events\WindowEvents.h>

using namespace std;

static bool GLFWIsInit = false;

//inits the display
bool WindowDisplay::Init(const unsigned int width, const unsigned int height, const string& name)
{
	//init GLFW if not
	if (!GLFWIsInit)
	{

		if (!glfwInit())
		{
			Logger::LogErrorAlways("Display", "GLFW could not be initalized.");
			isRunning = false;
			return false;
		}

		GLFWIsInit = true;
	}

	//set hints
	glfwWindowHint(GLFW_RESIZABLE, true);

	//make window
	window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	if (!window)
	{
		Logger::LogErrorAlways("Display", "Window could not be initalized.");
		glfwTerminate();
		isRunning = false;
		return false;
	}
	//Make the window's context current
	glfwMakeContextCurrent(window);

	glfwSetErrorCallback(GLFWErrorCallBack);

	//allows resizing
	glfwWindowHint(GLFW_RESIZABLE, true);

	//set method call backs
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 	//resize
	glfwSetWindowCloseCallback(window, window_close_callback); //closes the window when the exit button is pressed
	glfwSetKeyCallback(window, key_callback);//key input
	glfwSetMouseButtonCallback(window, mouse_button_callback); //mouse input
	glfwSetCursorPosCallback(window, cursor_position_callback);//mouse move
	glfwSetScrollCallback(window, scroll_callback);//mouse scroll
	glfwSetCharCallback(window, character_callback); //type input

	//inits graphic context
	context = GraphicContext::Create();
	context->Init(window);

	//sets window size
	OnResize(width, height);

	//render setings
	context->EnableBlending();
	//context->EnableFaceCulling();
	//context->EnableZBuffer();
	EnableVSync();

	//link to window events
	WindowResizeEvent::AddMethod(&WindowDisplay::Instance(), &WindowDisplay::OnResize);
	WindowCloseEvent::AddMethod(&WindowDisplay::Instance(), &WindowDisplay::Destroy);

	return true;
}

//destroys the display
void WindowDisplay::Destroy()
{
	context->Destroy();
	glfwSetWindowShouldClose(window, true);
	isRunning = false;
	glfwDestroyWindow(window);
	glfwTerminate();
}

//shutdown the window
void WindowDisplay::Shutdown()
{
	glfwSetWindowShouldClose(window, true);
	isRunning = false;
}

//updates the window || swaps the render buffers and polls for input
void WindowDisplay::Update()
{
	context->SwapRenderBuffer();
	glfwPollEvents();
}

//resizes the window
void WindowDisplay::OnResize(unsigned int width, unsigned int height)
{
	screenWidth = width; screenHeight = height;
	context->Resize(0, 0, width, height);
}

//enables V-Sync
void WindowDisplay::EnableVSync(bool enable)
{
	if (enable)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);
}

//locks and unlocks the mouse
void WindowDisplay::LockMouse(bool enable)
{
	if (enable)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	isLocked = enable;
}

//cals the delta time
void WindowDisplay::CalDeltaTime()
{
	float current = glfwGetTime();
	deltaTime = lastFrame - current;
	lastFrame = current;
}

//------GLFW CALL BACK METHODS-----------//
//logs errors
void GLFWErrorCallBack(int error, const char* description)
{
	//LogErrorAlways("GLFW: " + to_string(error), (string)description);
	Logger::LogErrorAlways("GLFW (" + to_string(error) + ')', description);
	//printf("GLFW Error (%i): %s\n", error, description);
}

//allows the window to resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	WindowResizeEvent::Call(width, height);
}

//allows the exit window button to be pressed || closes the window
void window_close_callback(GLFWwindow* window)
{
	WindowCloseEvent::Call();
}

//allows mouse move events to be triggered
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	MouseMoveEvent::Call(xpos, ypos);
}

//allows mouse scroll events
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	MouseScrollEvent::Call(xoffset, yoffset);
}

//allows keyboard pressed events to be triggered
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//send to input
	switch (action)
	{
	case GLFW_PRESS:
		KeyPressEvent::Call(key, false);
		break;

	case GLFW_REPEAT:
		KeyPressEvent::Call(key, true);
		break;

	case GLFW_RELEASE:
		KeyReleasedEvent::Call(key);
		break;
	}
}

//char callback allows typing
void character_callback(GLFWwindow* window, unsigned int keycode)
{
	KeyTypedEvent::Call(keycode);
}

//allows mouse pressed events to be triggered
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	//send to input
	switch (action)
	{
	case GLFW_PRESS:
		MousePressEvent::Call(button);
		break;

	case GLFW_RELEASE:
		MouseReleasedEvent::Call(button);
		break;
	}
}