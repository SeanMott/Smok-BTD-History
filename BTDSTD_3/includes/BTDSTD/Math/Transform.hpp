#pragma once

//defines a transform, matrix, and quaterion

#include <BTDSTD/Math/Vectors.hpp>

#include <BTDSTD/Math/Quaterion.hpp>


#include <glm/gtx/transform.hpp>
#include <glm/gtx/dual_quaternion.hpp>

namespace BTD::Math::Trans
{
	//defines a transform
	struct Transform
	{
		FVec3 position = { 0.0f, 0.0f, 0.0f }, scale = { 1.0f, 1.0f, 1.0f };
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

		glm::mat4 modelMatrix = glm::mat4(1.0f);

		bool isDirty = true;

		//returns a default transform
		static inline Transform Default() 
		{
			Transform t;
			t.position = { 0.0f, 0.0f, 0.0f };
			t.rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
			t.scale = { 1.0f, 1.0f, 1.0f };
			return t;
		}

		//calculates the model matrix || will create it regardless and reset the dirty flag
		inline glm::mat4 CalModelMatrix_Force()
		{
			modelMatrix = glm::mat4(1.0f);

			modelMatrix = glm::translate(glm::mat4(1.0f), BTD_Util_Typepun(position, glm::vec3));// *
				//glm::scale(glm::mat4(1.0f), BTD_Util_Typepun(scale, glm::vec3));

			isDirty = false;

			return modelMatrix;
		}

		//calculates the model matrix || will just return the pre-existing if it's not dirty
		inline glm::mat4 CalModelMatrix()
		{
			if (isDirty)
				return CalModelMatrix_Force();

			return modelMatrix;
		}

		//sets position || this way is reccomanded over changing the values directly so the dirty flag is set
		inline void SetPosition(const BTD::Math::FVec3& _position)
		{
			position = _position;
			isDirty = true;
		}

		//sets position || this way is reccomanded over changing the values directly so the dirty flag is set
		inline void SetPosition(const float xPos, const float yPos, const float zPos)
		{
			position = { xPos, yPos, zPos };
			isDirty = true;
		}

		//sets scale || this way is reccomanded over changing the values directly so the dirty flag is set
		inline void SetScale(const BTD::Math::FVec3& _scale)
		{
			scale = _scale;
			isDirty = true;
		}

		//sets scale || this way is reccomanded over changing the values directly so the dirty flag is set
		inline void SetScale(const float xSize, const float ySize, const float zSize)
		{
			scale = { xSize, ySize, zSize };
			isDirty = true;
		}

		//translates the transform

		//rotatets the transform

		//scales the transform

		//returns the world origin
		static BTD_Compiler_ForceInline FVec3 WorldOrigin() { return FVec3::Zero(); }

		//returns the local forward of the transform
		BTD_Compiler_ForceInline FVec3 LocalForward()
		{
			return FVec3(glm::eulerAngles(glm::rotate(rotation, 0.01f, FVec3::WorldForward().GLM())));
		}
		//returns the local backward of the transform
		BTD_Compiler_ForceInline FVec3 LocalBackward()
		{
			return FVec3(glm::eulerAngles(glm::rotate(rotation, 0.01f, FVec3::WorldBackward().GLM())));
		}

		//calculates the left direction vector
		BTD_Compiler_ForceInline FVec3 LocalLeft()
		{
			return FVec3(glm::eulerAngles(glm::rotate(rotation, 0.01f, FVec3::WorldLeft().GLM())));
		}

		//calculates the right direction vector
		BTD_Compiler_ForceInline FVec3 LocalRight()
		{
			return FVec3(glm::eulerAngles(glm::rotate(rotation, 0.01f, FVec3::WorldRight().GLM())));
		}

		//calculates the up direction vector
		BTD_Compiler_ForceInline FVec3 LocalUp()
		{
			return FVec3(glm::eulerAngles(glm::rotate(rotation, 0.01f, FVec3::WorldUp().GLM())));
		}

		//calculates the down direction vector
		BTD_Compiler_ForceInline FVec3 LocalDown()
		{
			return FVec3(glm::eulerAngles(glm::rotate(rotation, 0.01f, FVec3::WorldDown().GLM())));
		}
	};
}