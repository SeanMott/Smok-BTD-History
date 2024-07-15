//defines Editor code for debug

#ifndef SMOK_DIST
#ifndef Editor_h
#define Editor_h

#include <Core\ECS\EntityManager.h>
#include <Core\ECS\Components\Transform.h>

class Editor
{
	//vars
private:

	static Entity selectedEntity;
	static Transform* selectedTrans;

	static Entity* editorCam;
	//static Transform* editorTrans;

	static float moveSpeed;

	//methods
public:

	//inits the Editor
	static void Init();
	//shutsdown the Editor
	static void Shutdown();

	//draws the Editor
	static void Draw();
	//allows cams to be switched
	static void CamSwitch(int key, bool isRepeat);
	//allows the editor cam to be controlled
	static void CamCon(float deltaTime);

};

#endif
#endif