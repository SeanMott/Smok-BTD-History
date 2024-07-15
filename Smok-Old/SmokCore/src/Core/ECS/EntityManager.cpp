#include <smpch.h>
#include "EntityManager.h"

using namespace std; using namespace entt;

vector<Entity> EntityManager::entities;
registry EntityManager::entityRegistry;
vector<string> EntityManager::layers;


//-----------------ENTITY-----------------------

//adds a script || pass as pointer
void Entity::AddScript(void* script, const std::string& name)
{
	EntityManager::AddScript(this->name, script, name);
}

//removes a Script
void Entity::RemoveScript(const string& name)
{
	EntityManager::RemoveScript(this->name, name);
}

//gets a Script
void* Entity::GetScript(const string& name)
{
	return EntityManager::GetScript(this->name, name);
}

//checks if it has a Script
bool Entity::HasScript(const string& name)
{
	return EntityManager::HasScript(this->name, name);
}

//-------------ENTITY MANAGER---------------

//create entity
Entity& EntityManager::Create(const char* name, bool isIndependent)
{
	if (IsEntity(name))
	{
		//Logger::LogErrorAlways("Entity", (string)name + " is already a name of a entity.");

		//appends numbers to the name
		string n = name;
		unsigned long entityCount = 0;
		while (IsEntity(n))
		{
			entityCount++;
			n = name + to_string(entityCount);
			if (!IsEntity(n))
				break;
		}

		entity e = entityRegistry.create();
		entities.emplace_back(n, e, isIndependent);
		return entities[entities.size() - 1];
	}

	entity e = entityRegistry.create();
	entities.emplace_back(name, e, isIndependent);
	return entities[entities.size() - 1];
}

//create entity
Entity& EntityManager::Create(const string& name, bool isIndependent)
{
	if (IsEntity(name))
	{
		//Logger::LogErrorAlways("Entity", name + " is already a name of a entity.");

		//appends numbers to the name
		string n = name;
		unsigned long entityCount = 0;
		while (IsEntity(n))
		{
			n += to_string(entityCount);
			if (!IsEntity(n))
				break;
		}

		entity e = entityRegistry.create();
		entities.emplace_back(n, e, isIndependent);
		return entities[entities.size() - 1];
	}

	entity e = entityRegistry.create();
	entities.emplace_back(name, e, isIndependent);
	return entities[entities.size() - 1];
}

//destroy entity
void EntityManager::Destroy(std::string& name)
{
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		if (entities[i].name == name)
		{
			entityRegistry.destroy(entities[i].entityHandle);
			vector<Entity>::iterator it = entities.begin() + i;
			entities.erase(it);
			return;
		}
	}

	Logger::LogErrorAlways("Entity", name + " is not a entity.");
	//printf("%s is not a entity\n", name.c_str());
}

//destroy entity
void EntityManager::Destroy(entt::entity& entity)
{
	if (entityRegistry.valid(entity))
	{
		for (unsigned int i = 0; i < entities.size(); i++)
		{
			if (entities[i].entityHandle == entity)
			{
				entityRegistry.destroy(entities[i].entityHandle);
				vector<Entity>::iterator it = entities.begin() + i;
				entities.erase(it);
				return;
			}
		}
	}
}

//gets a entity
Entity* EntityManager::GetEntity(const string& name)
{
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		if (entities[i].name == name)
			return &entities[i];
	}

	//printf("%s is not a entity\n", name.c_str());
	Logger::LogErrorAlways("Entity", name + " is not a entity.");
	return nullptr;
}

//return if a entity has the name already
bool EntityManager::IsEntity(const string& name)
{
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		if (entities[i].name == name)
			return true;
	}

	//printf("%s is not a entity\n", name.c_str());
	return false;
}

//destroys all entities || except scene independent ones
void EntityManager::DestroyAllEntities()
{
	if (entities.size() < 1)
		return;

	vector<Entity>::iterator it;

	for (unsigned int i = 0; i < entities.size(); i++)
	{
		if (!entities[i].sceneIndependent)
		{
			entityRegistry.destroy(entities[i].entityHandle);
			it = entities.begin() + i;
			entities.erase(it);
		}
	}
}

//destroys all entities including scene independent ones
void EntityManager::DestroyAllEntitiesIndependent()
{
	if (entities.size() < 1)
		return;

	entities.clear();
	entityRegistry.clear();
}

//adds a layer
void EntityManager::AddLayer(const string& name)
{
	if (IsLayer(name))
	{
		//printf("%s is already a layer name.\n", name.c_str());
		Logger::LogErrorAlways("Layer", name + " is already a layer.");
		return;
	}

	layers.emplace_back(name);
}

//removes a layer
void EntityManager::RemoveLayer(const string& name)
{
	if (!IsLayer(name))
	{
		//printf("%s is not a layer name.\n", name.c_str());
		Logger::LogErrorAlways("Layer", name + " is not a layer.");
		return;
	}

	for (unsigned int i = 0; i < layers.size(); i++)
	{
		if (layers[i] == name)
		{
			vector<string>::iterator it = layers.begin() + i;
			layers.erase(it);
		}
	}
}

//gets all entities by layer
vector<Entity*> EntityManager::GetAllEntitiesByLayer(const string& layer)
{
	vector<Entity*> e;

	if (entities.size() < 1)
		return e;

	for (unsigned int i = 0; i < entities.size(); i++)
	{
		if (entities[i].layer == layer)
			e.emplace_back(&entities[i]);
	}

	return e;
}

//returns if a layer already exists
bool EntityManager::IsLayer(const string& name)
{
	if (layers.size() < 1)
		return false;

	for (unsigned int i = 0; i < layers.size(); i++)
	{
		if (layers[i] == name)
			return true;
	}

	return false;
}

//adds a Script to the entity
void EntityManager::AddScript(const string& entityName, void* script, const string name)
{
	if (HasScript(entityName, name))
	{
		Logger::LogErrorAlways("Script", entityName + " already has a Script instance named " + name + '.');
		return;
	}

	Entity* e = GetEntity(entityName);
	e->scripts.script = script;
	e->scripts.name = name;
}

//removes a Script
void EntityManager::RemoveScript(const string& entityName, const string name)
{
	if (!HasScript(entityName, name))
	{
		Logger::LogErrorAlways("Script", entityName + " does not have a Script instance named " + name + '.');
		return;
	}

	Entity* e = GetEntity(entityName);
	e->scripts.~Script();
}

//gets a Script
void* EntityManager::GetScript(const string& entityName, const string name)
{
	if (!HasScript(entityName, name))
	{
		Logger::LogErrorAlways("Script", entityName + " does not have a Script instance named " + name + '.');
		return nullptr;
	}

	Entity* e = GetEntity(entityName);
	return e->scripts.script;
}

//checks if a entity has a Script
bool EntityManager::HasScript(const string& entityName, const string name)
{
	Entity* e = GetEntity(entityName);
	
	if (!e->scripts.script)
		return false;

	if (e->scripts.name == name)
		return true;

	return false;
}