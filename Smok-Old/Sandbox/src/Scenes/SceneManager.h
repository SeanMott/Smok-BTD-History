//stores scene data and loads/unloads it

#ifndef SceneManager_h
#define SceneManager_h

#include <string>
#include <unordered_map>

class SceneManager
{
	//vars
private:

	static std::unordered_map<std::string, std::string> scenes; //name, scene preprocessed source
	static std::string currentScene;

	//methods
public:

	//adds a scene to the scene list
	static void AddScene(const std::string& filePath, const std::string& name);
	//removes a scene from the scene list
	static void RemoveScene(const std::string& name);

	//loads a scene
	static void LoadScene(const std::string& name);
	//unloads a scene
	static void UnloadScene(const std::string& name);

	//saves the current scene
	static void SaveScene();
	//reloads the current scene
	static inline void Reload() { if (currentScene == "") return; RemoveScene(currentScene); AddScene("res\\Scenes\\" + currentScene + ".Scene", currentScene); }
	//reloads the scene
	static inline void Reload(const std::string& name) { RemoveScene(name); AddScene("res\\Scenes\\" + name + ".Scene", name); }

	//gets the current scene
	static inline std::string GetCurrentScene() { return currentScene; }
	//deletes all scene data
	static inline void Destroy() { scenes.clear(); }
	//gets scenes
	static inline std::unordered_map<std::string, std::string>& GetScenes() { return scenes; }

private:

	//checks if there is a Scene
	static bool IsScene(const std::string& name);
};

#endif