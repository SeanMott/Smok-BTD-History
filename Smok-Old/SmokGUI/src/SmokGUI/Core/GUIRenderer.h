//allows GUI to be renderer over a scene

#ifndef GUIRenderer_h
#define GUIRenderer_h

#include <SmokGUI\Core\ImGUIContext.h>

//defines the styles for GUI
enum class GUIStyle
{
	Dark,
	Light,
	Classic
};

//defines the flags for GUI
enum class GUIFlags
{
	ViewPort = 0, //multi viewport / windows
	Docking, //docking support
	Keyboard, //keyboard supprot
	GamePad, //game pad support

	GUIFlagsCount //the number of flags

};

class GUIRenderer
{
	//vars
private:

	static ImGUIContext* context;
	static bool flags[(int)GUIFlags::GUIFlagsCount]; //the flags for GUI

	//methods
public:

	//inits the renderer
	static void Init();
	//shutsdown the renderer
	static void Shutdown();

	//updates the GUI flags for ImGUI
	static void UpdateImGUIFlags();
	//updates the style
	static void SetStyle(GUIStyle style = GUIStyle::Dark);

	//returns the context
	static inline ImGUIContext* GetContext() { return context; }

	//sets a flag state
	static inline void SetFlag(GUIFlags flag, bool state) { flags[(int)flag] = state; }
	//gets the state of a flag
	static inline bool GetFlagState(GUIFlags flag) { return flags[(int)flag]; }

private:

	//starts a section of render code
	static void Begin();
	//ends a section of render code
	static void End();

	//events
	static void KeyPressed(int key, bool isRepeat);
	static void KeyReleased(int key);
	static void KeyTyped(int key);
	static bool MousePressed(int button);
	static bool MouseReleased(int button);
	static void MouseMove(double xPos, double yPos);
	static void MouseScroll(double xOffset, double yOffset);
	static void OnResize(unsigned int width, unsigned int height);
	static void UpdateDeltaTime(float deltaTime);

};

#endif