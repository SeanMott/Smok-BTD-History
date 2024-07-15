#pragma once

//defines a file IO operations

#include <BTDSTD/Logger.hpp>
#include <BTDSTD/Types.hpp>

#include <vector>
#include <stdio.h>

namespace BTD::IO
{
	//defines a file operation
	enum class FileOP
	{
		TextRead_OpenExisting = 0,
		TextWrite_OpenCreateStart,
		TextWrite_OpenCreateApp,
		TextBoth_OpenCreate,
		TextBoth_OpenCreateNuke,
		TextBoth_OpenCreateApp,
		BinaryRead_OpenExisting,
		BinaryWrite_OpenCreateStart,
		BinaryWrite_OpenCreateApp,
		BinaryBoth_OpenCreate,
		BinaryBoth_OpenCreateNuke,
		BinaryBoth_OpenCreateApp,

		Count
	};

	//converts a file operation enum to a native string flag
	inline static const char* ConvertToNative(const FileOP op)
	{
		switch (op)
		{
		case FileOP::TextRead_OpenExisting:
			return "r";
		case FileOP::TextWrite_OpenCreateStart:
			return "w";
		case FileOP::TextWrite_OpenCreateApp:
			return "a";
		case FileOP::TextBoth_OpenCreate:
			return "r+";
		case FileOP::TextBoth_OpenCreateNuke:
			return "w+";
		case FileOP::TextBoth_OpenCreateApp:
			return "a+";
		case FileOP::BinaryRead_OpenExisting:
			return "rb";
		case FileOP::BinaryWrite_OpenCreateStart:
			return "wb";
		case FileOP::BinaryWrite_OpenCreateApp:
			return "ab";
		case FileOP::BinaryBoth_OpenCreate:
			return "rb+";
		case FileOP::BinaryBoth_OpenCreateNuke:
			return "r+b";
		case FileOP::BinaryBoth_OpenCreateApp:
			return "wb+";
		default:
			Util::Logger::LogErrorToConsole("BTD STD", "File", "ConvertToNative", "The flag give was not valid for file reading or writing!");
			return "";
		}
	}

	//defines a file
	struct File
	{
		FILE* file = nullptr;

		bool isOpen = false;

		std::string path = "";

		//opens a file
		inline bool Open(const char* _path, FileOP OP = FileOP::TextWrite_OpenCreateStart)
		{
			//if it's already open
			if (isOpen)
			{
				Util::Logger::LogWarningToConsole("BTD STD", "File", "Open", "File was already open, it will be closed then open with the new path");
				Close();
			}

			file = fopen(_path, ConvertToNative(OP));
			if (!file)
			{
				Util::Logger::LogErrorToConsole("BTD STD", "File", "Open",
					(std::string("Failed to open file at: ") + std::string(path)).c_str());
				return false;
			}
			path = _path;
			isOpen = true;

			return true;
		}

		//closes a file
		inline void Close()
		{
			fclose(file);
			isOpen = false;
		}

		//gets the length of the entire file
		inline size_t GetFileLength() const
		{
			if (!isOpen)
			{
				Util::Logger::LogErrorToConsole("BTD STD", "File", "GetFileLength", "File is not open, can not get length");
				return 0;
			}

			fseek(file, 0, SEEK_END);
			size_t length = ftell(file);
			fseek(file, 0, SEEK_SET);
			return length;
		}

		//writes all text to the file
		inline bool WriteText(const std::string& text)
		{
			if (!isOpen)
			{
				Util::Logger::LogErrorToConsole("BTD STD", "File", "Write", "File is not open, can't write text");
				return false;
			}

			fwrite(text.c_str(), sizeof(char), text.size(), file);
			return true;
		}

		//reads the whole file's text
		inline bool ReadAllText(std::string& text)
		{
			if (!isOpen)
			{
				Util::Logger::LogErrorToConsole("BTD STD", "File", "ReadAllText", "File is not open, there is no text to read");
				return false;
			}

			fseek(file, 0, SEEK_END);
			long length = ftell(file);
			fseek(file, 0, SEEK_SET);
			char* _text = (char*)calloc(length, sizeof(char));
			if (_text)
				fread(_text, 1, length, file);
			text = _text;

			return true;
		}

		//reads a SPRV shader byte file into a buffer || buffer will be allocated inside the function
		inline bool ReadSPRVByteCode(std::vector<uint32>& byteCode)
		{
			if (!isOpen)
			{
				Util::Logger::LogErrorToConsole("BTD STD", "File", "ReadSPRVByteCode", "File is not open, there is no byte code to import");
				return false;
			}

			// find what the size of the file is by looking up the location of the cursor
			// because the cursor is at the end, it gives the size directly in bytes
			size_t fileSize = GetFileLength();

			// spirv expects the buffer to be on uint32, so make sure to reserve a int
			// vector big enough for the entire file
			byteCode.resize(fileSize / sizeof(uint32_t));

			// put file cursor at beginning
			fseek(file, 0, SEEK_SET);

			// load the entire file into the buffer
			fread((char*)byteCode.data(), 1, fileSize, file);

			return true;
		}
	};
}