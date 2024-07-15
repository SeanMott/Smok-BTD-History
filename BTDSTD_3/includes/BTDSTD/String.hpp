#pragma once

//defines a string for BTDSTD

#include <BTDSTD/Types.hpp>

#include <string>
#include <vector>

namespace BTD::String
{
	//splits a string into a array by a char
	inline std::vector<std::string> SplitStrByChar(const std::string& strToSplit, const char c)
	{
		std::vector<std::string> strs; strs.reserve(2);

		std::string word = "";
		for (uint32 i = 0; i < strToSplit.size(); ++i)
		{
			//splits by char
			if (strToSplit[i] == c)
			{
				strs.emplace_back(word);
				word = "";
			}
			//adds data
			else
				word += strToSplit[i];
		}

		//adds the last word
		strs.emplace_back(word);

		return strs;
	}

	//replaces all instances of a word in a string || does NOT change the str you pass in
	inline std::string ReplaceAll_Copy(std::string str, const std::string& from, const std::string& to)
	{
		size_t start_pos = 0;
		
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) //gets all instances
		{
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
		}

		return str;
	}

	//replaces all instances of a word in a string || DOES CHANGE the str passed in
	inline void ReplaceAll(std::string& str, const std::string& from, const std::string& to)
	{
		size_t start_pos = 0;

		while ((start_pos = str.find(from, start_pos)) != std::string::npos) //gets all instances
		{
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
		}
	}

	//gets all instances of a word in a string || returns true if found, false if none
	/*
	inline bool GetAllInstancesOfWord(const std::string& str, const std::string& word, 
	std::vector<size_t>& locationOffsets)
	{
		
	}
	*/

	//prints a array of strings
	inline void PrintStrArray(const std::vector<std::string>& strs)
	{
		std::string printStr = "[ ";

		const size_t count = strs.size();
		const size_t lastIndex = count - 1;
		for (uint32 i = 0; i < count; ++i)
		{
			if (i > 0 || i < lastIndex)
				printStr += strs[i] + ", ";
			else
				printStr += strs[i];
		}

		printf("%s ]\n", printStr.c_str());
	}
}