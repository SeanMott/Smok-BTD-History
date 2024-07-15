#include "SceneParser.h"

#include <Core\Logger.h>

#include <fstream>

using namespace std; using namespace glm;

string SceneParser::data = "";

string SceneParser::PreprocessSceneFile(const string& filepath)
{
	//load file
	ifstream readStream(filepath);
	//ifstream readStream(filepath, ios::binary);
	if (!readStream.is_open())
	{
		Logger::LogErrorAlways("Scene", "Failed to open scene file at " + filepath);
		return "";
	}
	
	//check if valid scene file and get name

	//get source
	string source = "";
	readStream.seekg(0, ios::end);
	source.resize(readStream.tellg());
	readStream.seekg(0, ios::beg);
	readStream.read(&source[0], source.size());
	readStream.close();

	//preprocess file
	Parser parser(source);
	string s = "";

	while (parser.GetNextChar() != -1)
	{
		if (parser.currentChar == '\n')
		{
			s += ' ';
			continue;
		}

		s += parser.currentChar;
	}

	return s;
}

void SceneParser::LoadScene(const std::string& source)
{
	if (source == "")
		return;

	Parser parser(source);

	//parse file into tokens
	string word = "";
	vector<string> words;

	//process source into words
	while (parser.GetNextChar() != -1)
	{
		//process word
		if (parser.currentChar == ' ' || parser.currentChar == '"')
		{
			//if string data
			if (parser.currentChar == '"')
				words.emplace_back(GetStringData(&parser));

			//if anything else
			else
				words.emplace_back(word);

			word = "";
		}

		//builds word
		else
			word += parser.currentChar;
	}

	//process words into Entites
	Entity* currentEntity = nullptr;
	for (unsigned int i = 0; i < words.size(); i++)
	{
		//makes new Entity
		if (words[i] == "Entity")
		{
			i++;
			Entity en = EntityManager::Create(words[i]);
			currentEntity = EntityManager::GetEntity(en.name);
			i += 2;
			currentEntity->layer = words[i];
		}

		//process Components
		else if (words[i] == "Component")
		{
			i++;

			//Transform
			if (words[i] == "Transform")
			{
				//Position
				i++;
				float posX = strtof(words[i].c_str(), nullptr);
				i++;
				float posY = strtof(words[i].c_str(), nullptr);
				i++;
				float posZ = strtof(words[i].c_str(), nullptr);

				//Rotation
				i++;
				float rotX = strtof(words[i].c_str(), nullptr);
				i++;
				float rotY = strtof(words[i].c_str(), nullptr);
				i++;
				float rotZ = strtof(words[i].c_str(), nullptr);

				//Scale
				i++;
				float scaleX = strtof(words[i].c_str(), nullptr);
				i++;
				float scaleY = strtof(words[i].c_str(), nullptr);
				i++;
				float scaleZ = strtof(words[i].c_str(), nullptr);

				currentEntity->AddComponent<Transform>(vec3(posX, posY, posZ), vec3(rotX, rotY, rotZ), vec3(scaleX, scaleY, scaleZ));
			}

			//link Smok2D
#ifdef Smok2D_Link

			//Sprite
			else if (words[i] == "Sprite")
			{
				i++;
				string texture = words[i];
				i++;
				unsigned int textureSlot = atoi(words[i].c_str());
				i += 2;
				string shader = words[i];
				i += 2;
				float red = strtof(words[i].c_str(), nullptr);
				i++;
				float green = strtof(words[i].c_str(), nullptr);
				i++;
				float blue = strtof(words[i].c_str(), nullptr);
				i++;
				unsigned int layer = atoi(words[i].c_str());
				i++;
				bool isActive = (words[i] == "Yes" ? true : false);
				currentEntity->AddComponent<Sprite>(texture, textureSlot, shader, vec3(red, green, blue), layer, isActive);
			}

			//Orthographic Camera
			else if (words[i] == "OrthographicCamera")
			{
				i++;
				float viewLength = strtof(words[i].c_str(), nullptr);
				i++;
				float heightLength = strtof(words[i].c_str(), nullptr);
				i++;
				bool isActive = (words[i] == "Yes" ? true : false);
				currentEntity->AddComponent<OrthographicCamera>(viewLength, heightLength, isActive);
			}

			//Rigidbody
#endif

			//link Smok3D
#ifdef Smok3D_Link
#endif
		}
	}
}

void SceneParser::SaveScene(const std::string& filepath)
{
	data = "";
	vector<Entity> entities = EntityManager::GetAllEntities();

	//goes through each entity and writes it's data and components
	for (Entity entity : entities)
	{
		if (entity.layer == "Editor")
			continue;

		//stores name and layer
		data += "Entity\n\"" + entity.name + "\"\n\"" + entity.layer + "\"\n";

		//stores Transform
		if (entity.HasComponent<Transform>())
		{
			Transform* trans = entity.GetComponent<Transform>();
			data += "Component Transform\n" +
				to_string(trans->position.x) + ' ' + to_string(trans->position.y) + ' ' + to_string(trans->position.z) + '\n' +
				to_string(trans->rotation.x) + ' ' + to_string(trans->rotation.y) + ' ' + to_string(trans->rotation.z) + '\n' +
				to_string(trans->scale.x) + ' ' + to_string(trans->scale.y) + ' ' + to_string(trans->scale.z) + '\n';
		}

#ifdef Smok2D_Link
		//stores Sprite
		if (entity.HasComponent<Sprite>())
		{
			Sprite* sprite = entity.GetComponent<Sprite>();
			data += "Component Sprite\n\"" +
				sprite->texture + "\"\n" + to_string(sprite->textureSlot) +
				"\n\"" + sprite->shader + "\"\n" +
				to_string(sprite->color.r) + ' ' + to_string(sprite->color.g) + ' ' + to_string(sprite->color.b) + '\n' +
				to_string(sprite->layer) + '\n' +
				(sprite->isActive == true ? "Yes" : "No") + '\n';
		}

		//stores Orthographic Camera
		if (entity.HasComponent<OrthographicCamera>())
		{
			OrthographicCamera* cam = entity.GetComponent<OrthographicCamera>();
			data += "Component OrthographicCamera\n" +
				to_string(cam->viewLength) + ' ' + to_string(cam->viewLength) + '\n' +
				(cam->isActive == true ? "Yes" : "No") + '\n';
		}

		//stores Rigidbody
#endif

#ifdef Smok3D_Link
		//stores Mesh

		//stores Rigidbody

#endif

		//data += "}\n";
	}

	//write data to file
	ofstream writeStream;
	/*writeStream.open(filepath, ios::binary);*/ writeStream.open(filepath);
	if (!writeStream.is_open())
	{
		Logger::LogErrorAlways("Scene", "Failed to write data to " + filepath);
		return;
	}

	/*writeStream.write((char*)&data, sizeof(data));
	writeStream.close();
	if (!writeStream.good())
	{
		Logger::LogErrorAlways("Scene", "Error while writing scene to file"); //add scene name here
		return;
	}*/

	writeStream << data;
	writeStream.close();
}

string SceneParser::GetStringData(Parser* parser)
{
	string data = "";

	while (parser->GetNextChar() != -1)
	{
		if (parser->currentChar == '"')
			break;

		//allows backslash chars
		else if (parser->currentChar == '\\')
		{
			//quotes
			if (parser->GetNextChar() == '"')
				data += '"';
			//tab
			if (parser->GetNextChar() == 't')
				data += '\t';
			//slash
			if (parser->GetNextChar() == '\\')
				data += '\\';
			//new line
			if (parser->GetNextChar() == 'n')
				data += '\n';

			parser->currentChar++;
			continue;
		}

		else
			data += parser->currentChar;
	}

	return data;
}
