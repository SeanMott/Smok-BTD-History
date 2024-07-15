#pragma once

//defines a registery that maps a ID to a string

#include <BTDSTD/Types.hpp>
#include <BTDSTD/Logger.hpp>

#include <vector>
#include <string>

namespace BTD::Map
{
	//defines a registery that maps a ID to a string
	class IDStringRegistery
	{
		//vars
	private:

		std::vector<uint64> usedIDs; //the used IDs
		std::vector<std::string> usedStrs; //the used strings

		std::vector<uint64> freeIDs; //the freeded IDs

		uint64 nextID = 0; //the next ID

		//methods
	public:

		//registers space in the registery
		inline void ReserveSpace(const uint32& space)
		{
			usedIDs.reserve(space); usedStrs.reserve(space); freeIDs.reserve(space);
		}

		//is the ID in use
		inline bool IDIsInUse(const uint64& ID)
		{
			for (uint32 i = 0; i < usedIDs.size(); ++i)
			{
				if (usedIDs[i] == ID)
					return true;
			}

			return false;
		}

		//checks if a name is registered
		inline bool NameIsRegistered(const std::string& str)
		{
			const char* s = str.c_str();
			for (uint32 i = 0; i < usedStrs.size(); ++i)
			{
				if (!strcmp(s, usedStrs[i].c_str()))
					return true;
			}

			return false;
		}

		//checks if a name is registered
		inline bool NameIsRegistered(const std::string& str, uint32& arrayIndex)
		{
			const char* s = str.c_str();
			for (uint32 i = 0; i < usedStrs.size(); ++i)
			{
				if (!strcmp(s, usedStrs[i].c_str()))
				{
					arrayIndex = i;
					return true;
				}
			}

			return false;
		}

		//generates a new ID and binda a name to it || returns 0 if failed
		inline uint64 RegisterName(const std::string& str)
		{
			uint64 ID = 0;

			//checks if the name already exsts
			uint32 nameIndex = 0;
			if (NameIsRegistered(str, nameIndex))
			{
				BTD::Util::Logger::LogWarningToConsole("BTD STD", "ID String Registery", "RegisterName",
					std::string("\"" + str + "\" is already a registerd name ID pair. We will be returning the ID associated with this string.").c_str());
				return usedIDs[nameIndex];
			}

			//checks for free ID
			if (freeIDs.size() > 0)
			{
				ID = freeIDs[0];
				freeIDs.erase(freeIDs.begin());
			}

			//if no ID was found
			if (!ID)
			{
				//if no more IDs can be used
				if (nextID + 1 >= UINT32_MAX)
				{
					BTD::Util::Logger::LogErrorToConsole("BTD STD", "ID String Registery", "RegisterName",
						std::string("\"" + str + "\" can not be used to register with a ID. No more IDs can be generated, remove some.").c_str());
					return 0;
				}

				//generates a new ID
				nextID++;
				ID = nextID;
			}

			//binds name to ID
			usedIDs.emplace_back(ID);
			usedStrs.emplace_back(str);

			return ID;
		}

		//frees a ID by name

		//frees a ID by ID

		//gets a ID by name
		inline uint64 GetIDByName(const std::string& name)
		{
			uint32 arrayIndex = 0;
			if (NameIsRegistered(name, arrayIndex))
				return usedIDs[arrayIndex];
		}

		//gets a name by ID
		inline std::string GetNameByID(const uint64& ID)
		{
			for (uint32 i = 0; i < usedIDs.size(); ++i)
			{
				if (ID == usedIDs[i])
					return usedStrs[i];
			}

			return "";
		}

		//frees all IDs
		inline void Clear()
		{
			size_t amount = freeIDs.size(); freeIDs.clear(); freeIDs.reserve(amount);
			amount = usedIDs.size(); usedIDs.clear(); usedIDs.reserve(amount);
			amount = usedStrs.size(); usedStrs.clear(); usedStrs.reserve(amount);
		}
	};
}