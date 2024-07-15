#pragma once

//defines a component interface

#include <BTDSTD/Maps/IDRegistery.hpp>

namespace Smok::ECS::Interface
{
	//defines a IComponent
	struct ICompoenent
	{
		uint64 entityID = 0; //the ID associated with the Entity who owns this Component
		uint64 compNameID = 0; //the ID associated with the name of the Component that implements this interface
	};
}