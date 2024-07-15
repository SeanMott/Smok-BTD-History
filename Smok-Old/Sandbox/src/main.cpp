
#include <Core\Application.h>
#include <Core\AssetManager.h>
#include <Core\ECS\EntityManager.h>
#include <Core\Logger.h>

#include <Core\ECS\Components\Transform.h>

#include <SmokGUI\Core\GUIRenderer.h>

#include "Scenes\SceneManager.h"

#include <glm.hpp>

#ifndef SMOK_DIST
#include "Editor\Editor.h"
#include <iostream>
#endif

using namespace std; using namespace glm;

const unsigned int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 800;

int main(int args, char* argv[]) //use EntryPoint in other apps for multiplatform
{
	//inits app
	Application::Init(SCREEN_WIDTH, SCREEN_HEIGHT);

	//load assets
	//AssetManager::LoadAssetFile(/*filepath to asset file*/);

	//link Systems
	GUIRenderer::Init();

#ifndef SMOK_DIST
	Editor::Init();
#endif

	//game loop
	Application::Run();

	//clean up Entities
	EntityManager::DestroyAllEntitiesIndependent();

	//clean up assets
	AssetManager::DestroyAllAssets();

	//clear scene
	SceneManager::Destroy();

	//clean up Systems
#ifndef SMOK_DIST
	Editor::Shutdown();
#endif
	GUIRenderer::Shutdown();

	//clean up app
	Application::Destroy();

#ifndef SMOK_DIST
	cin.get();
#endif
	return 0;
}