#include "SceneManager.h"
#include "SceneParser.h"

using namespace std;

unordered_map<string, string> SceneManager::scenes;
string SceneManager::currentScene = "";

void SceneManager::AddScene(const string& filePath, const string& name)
{
	if (filePath == "")
	{
		Logger::LogErrorAlways("Scene", "Null filepath was used, give a real filepath.");
		return;
	}

	if (IsScene(name))
	{
		Logger::LogErrorAlways("Scene", name + " is already a scene name pick another name.");
		return;
	}

	scenes[name] = SceneParser::PreprocessSceneFile(filePath);
}

void SceneManager::RemoveScene(const string& name)
{
	if (!IsScene(name))
	{
		Logger::LogErrorAlways("Scene", name + " is not a scene name pick another name.");
		return;
	}

	scenes.erase(name);
}

void SceneManager::LoadScene(const string& name)
{
	if (!IsScene(name))
	{
		Logger::LogErrorAlways("Scene", name + " is not a scene name pick another name.");
		return;
	}

	if(currentScene != "")
		SceneManager::UnloadScene(currentScene);
	SceneParser::LoadScene(scenes[name]);
	currentScene = name;
}

void SceneManager::UnloadScene(const string& name)
{
	if (!IsScene(name))
	{
		Logger::LogErrorAlways("Scene", name + " is not a scene name pick another name.");
		return;
	}

	EntityManager::DestroyAllEntities();
	currentScene = "";
}

void SceneManager::SaveScene()
{
	if (currentScene == "")
	{
		Logger::LogErrorAlways("Scene", "No Scene is currently selected.");
		return;
	}

	SceneParser::SaveScene("res\\Scenes\\" + currentScene + ".Scene");
}

bool SceneManager::IsScene(const std::string& name)
{
	for (auto& scene : scenes)
	{
		if (scene.first == name)
			return true;
	}

	return false;
}
