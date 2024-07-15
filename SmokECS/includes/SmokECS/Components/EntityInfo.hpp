#pragma once

//defines a component describing the name, tag, and other description data for a Entity

#include <SmokECS/Interfaces/IComponent.hpp>

#include <BTDSTD/IO/YAML.hpp>

#include <string>

namespace Smok::ECS::Component
{
	struct EntityInfo : public Interface::ICompoenent
	{
		std::string entityName = "Entity 0"; //the entity name
		//the entity tag
	};

	//converts this Component into YAML data
	inline void EntityInfo_ConvertToYAML(YAML::Emitter& emitter, EntityInfo* component)
	{
		emitter << YAML::Key << "EntityInfoComp" << YAML::Value << YAML::BeginMap;

		emitter << YAML::Key << "entityName" << YAML::DoubleQuoted << component->entityName;

		emitter << YAML::EndMap;
	}

	//converts YAML data to this Component
	inline void EntityInfo_ConvertFromYAML(EntityInfo* component, YAML::Node& data)
	{
		auto comp = data["EntityInfoComp"];
		if (comp)
		{
			component->entityName = comp["entityName"].as<std::string>();
		}
	}
}