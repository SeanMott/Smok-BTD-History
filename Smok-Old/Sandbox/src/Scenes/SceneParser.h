//writes and reads binary and text files that represent scenes

#ifndef SceneParser_h
#define SceneParser_h

#include <string>
#include "Parser.h"

#include <Core\ECS\EntityManager.h>
#include <Core\ECS\Components\Transform.h>

#ifdef Smok2D_Link
#include <Smok2D\Components\OrthographicCamera.h>
//#include <Smok2D\Components\Rigidbody.h>
#include <Smok2D\Components\Sprite.h>
#endif

#ifdef Smok3D_Link
#endif

class SceneParser
{
	//vars
private:

	static std::string data;

	//methods
public:

	//preprocess a scene file
	static std::string PreprocessSceneFile(const std::string& filepath);
	//reads scene source
	static void LoadScene(const std::string& source);
	//writes a scene file
	static void SaveScene(const std::string& filepath);

private:

	//gets string data
	static std::string GetStringData(Parser* parser);
};

#endif