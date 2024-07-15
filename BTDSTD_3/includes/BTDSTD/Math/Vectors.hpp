#pragma once

//defines various vectors

#include <BTDSTD/CompilerFunctions.hpp>
#include <BTDSTD/Types.hpp>

#include <glm/glm.hpp>

namespace BTD::Math
{
	//defines a vector 2
	struct I32Vec2
	{
		int32 x = 0, y = 0;
	};

	//defines a vector 2
	struct UI32Vec2
	{
		uint32 x = 0, y = 0;
	};

	//defines a vector 2
	struct FVec2
	{
		float x = 0.0f, y = 0.0f;

		//returns a zero vector
		static BTD_Compiler_ForceInline FVec2 Zero() { return { 0.0f, 0.0f }; }
	};

	//defines a vector 2
	struct DVec2
	{
		double x = 0.0f, y = 0.0f;
	};

	//defines a vector 3
	struct UI32Vec3
	{
		uint32 x = 0, y = 0, z = 0;
	};

	//defines a vector 3
	struct FVec3
	{
		float x = 0.0f, y = 0.0f, z = 0.0f;

		FVec3() = default;

		FVec3(const float _x, const float _y, const float _z)
			:x(_x), y(_y), z(_z) {}

		//turns a glm vec3 to Fvec3
		FVec3(const glm::vec3 data)
			:x(data.x), y(data.y), z(data.z) {}

		//converts it to the GLM
		inline glm::vec3 GLM() const { return BTD_Util_Typepun(*this, glm::vec3); }

		//returns a zero vector (0, 0, 0)
		static BTD_Compiler_ForceInline FVec3 Zero() { return { 0.0f, 0.0f, 0.0f }; }
		//returns a one vector (1, 1, 1)
		static BTD_Compiler_ForceInline FVec3 One() { return { 1.0f, 1.0f, 1.0f }; }

		//returns the world forward vector (0, 0, -1)
		static BTD_Compiler_ForceInline FVec3 WorldForward() { return { 0.0f, 0.0f, -1.0f }; }
		//returns the world backward vector (0, 0, 1)
		static BTD_Compiler_ForceInline FVec3 WorldBackward() { return { 0.0f, 0.0f, 1.0f }; }

		//returns the world up vector (0, 1, 0)
		static BTD_Compiler_ForceInline FVec3 WorldUp() { return { 0.0f, 1.0f, 0.0f }; }
		//returns the world down vector (0, -1, 0)
		static BTD_Compiler_ForceInline FVec3 WorldDown() { return { 0.0f, -1.0f, 0.0f }; }

		//returns the world left vector (-1, 0, 0)
		static BTD_Compiler_ForceInline FVec3 WorldLeft() { return { -1.0f, 0.0f, 0.0f }; }
		//returns the world right vector (1, 0, 0)
		static BTD_Compiler_ForceInline FVec3 WorldRight() { return { 1.0f, 0.0f, 0.0f }; }

		FVec3 operator+(const FVec3& data)
		{
			return { x + data.x, y + data.y, z + data.z };
		}

		FVec3 operator-(const FVec3& data)
		{
			return { x - data.x, y - data.y, z - data.z };
		}

		FVec3 operator*(const FVec3& data)
		{
			return { x * data.x, y * data.y, z * data.z };
		}

		FVec3 operator+(const float& data)
		{
			return { x + data, y + data, z + data };
		}

		FVec3 operator*(const float& data)
		{
			return { x * data, y * data, z * data };
		}
	};

	//defines a vector 3
	struct DVec3
	{
		double x = 0.0f, y = 0.0f, z = 0.0f;

		//converts it to the GLM
		inline glm::vec3 GLM() const { return BTD_Util_Typepun(*this, glm::vec3); }
	};
}