//the window implementation of the display

#ifndef WindowDisplay_h
#define WindowDisplay_h

#include <string>

#include <Renderer\GraphicContext.h>

#include "../../Library/GLFW/include/GLFW/glfw3.h"

class WindowDisplay
{
	//vars
private:

	GLFWwindow* window;
	GraphicContext* context;

	bool isRunning = true, isLocked = false;
	float lastFrame, deltaTime;
	unsigned int screenWidth, screenHeight;

	//methods
public:

	~WindowDisplay() { Destroy(); }

	//gets a staic instance
	static inline WindowDisplay& Instance() { static WindowDisplay d; return d; }

	// Inherited via Display
	bool Init(unsigned int width, unsigned int height, const std::string& name = "Sandbox") ;
	void Destroy() ;
	void OnResize(unsigned int width, unsigned int height);
	void Update() ;
	void LockMouse(bool enable = true) ;
	void EnableVSync(bool enable = true) ;
	void CalDeltaTime() ;
	inline GLFWwindow* GetWindow()  { return window; }
	inline GraphicContext* GetContext()  { return context; }
	inline bool IsRunning()  { return isRunning; }
	inline bool IsLocked()  { return isLocked; }
	inline float GetDeltaTime()  { return deltaTime; }

	//shutdown the window
	void Shutdown();

	//gets the screen width
	inline unsigned GetScreenWidth() { return screenWidth; }
	//gets the screen height
	inline unsigned GetScreenHeight() { return screenHeight; }
};

//-----------------GLFW METHOD CALL BACKS-------------//
//logs errors
void GLFWErrorCallBack(int error, const char* description);
//allows the window to resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//allows the exit window button to be pressed || closes the window
void window_close_callback(GLFWwindow* window);
//allows mouse move events to be triggered
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
//allows mouse scroll events
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//allows keyboard pressed events to be triggered
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
//allows mouse pressed events to be triggered
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
//char callback allows typing
void character_callback(GLFWwindow* window, unsigned int keycode);

#endif