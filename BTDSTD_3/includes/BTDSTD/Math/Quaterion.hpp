#pragma once

//defines a quaterion

#include <BTDSTD/Math/Vectors.hpp>

//#include <math.h>

//#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc\matrix_transform.hpp>

//#include <glm/gtc\matrix_transform.hpp>
//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx\quaternion.hpp>

//#include <glm/glm.hpp>
//#include <glm/gtx/transform.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/quaternion.hpp>
//#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

//defines quaterion functions and structs
namespace BTD::Math::Quat
{
	////defines a quaterion
	//struct Quaterion
	//{
	//	//the full quaterion
	//	glm::quat quaterion = glm::quat_identity<float, glm::packed_highp>(); //the quaterion version of the rotation data

	//	Quaterion() {}
	//	//Quaterion(const float w, const float x, const float y, const float z)
	//	//{
	//	//	quaterion.w = w; quaterion.x = x; quaterion.y = y; quaterion.z = z;
	//	//}
	//	Quaterion(const glm::quat& _quaterion)
	//	{
	//		quaterion = _quaterion;
	//	}
	//	Quaterion(const BTD::Math::FVec3 vec)
	//	{
	//		quaterion = glm::quat(vec.GLM());
	//	}

	//	//returns a identity quaterion
	//	static BTD_Compiler_ForceInline Quaterion Identity() { return glm::quat_identity<float, glm::packed_highp>(); }

		//returns the eular angels of this quaterion
		//inline FVec3 Eular() { return FVec3(glm::eulerAngles(quaterion)); }
		//returns the eular angels of this quaterion
		//inline FVec3 Eular() const { return FVec3(glm::eulerAngles(quaterion)); }

		//sets the rotation
		//inline void SetRotation(const float x_pitch, const float y_yaw, const float z_roll)
		//{
		//	glm::quat pitch = glm::angleAxis(glm::radians(x_pitch), BTD::Math::FVec3::WorldLeft().GLM());
		//	glm::quat yaw = glm::angleAxis(glm::radians(y_yaw), BTD::Math::FVec3::WorldUp().GLM());
		//	glm::quat roll = glm::angleAxis(glm::radians(z_roll), BTD::Math::FVec3::WorldForward().GLM());
		//
		//	quaterion = pitch * yaw * roll;
		//	quaterion = glm::normalize(quaterion);
		//}

		//rotates on the X axis
		//inline void RotateX(const float xRot)
		//{
		//	quaterion = glm::normalize(glm::angleAxis(glm::radians(xRot), BTD::Math::FVec3::WorldLeft().GLM())) * quaterion;
		//}

		//rotates on the Y axis
		//inline void RotateY(const float yRot)
		//{
		//	quaterion = glm::normalize(glm::angleAxis(glm::radians(yRot), BTD::Math::FVec3::WorldUp().GLM())) * quaterion;
		//}

		//rotates on the Z axis
		//inline void RotateZ(const float zRot)
		//{
		//	quaterion = glm::normalize(glm::angleAxis(glm::radians(zRot), BTD::Math::FVec3::WorldForward().GLM())) * quaterion;
		//}

		//rotates on all 3 axis
		//inline void Rotate(const float x_pitch, const float y_yaw, const float z_roll)
		//{
		//	glm::quat pitch = glm::angleAxis(glm::radians(x_pitch), BTD::Math::FVec3::WorldLeft().GLM());
		//	glm::quat yaw = glm::angleAxis(glm::radians(y_yaw), BTD::Math::FVec3::WorldUp().GLM());
		//	glm::quat roll = glm::angleAxis(glm::radians(z_roll), BTD::Math::FVec3::WorldForward().GLM());
		//
		//	quaterion = glm::normalize((pitch * yaw * roll)) * quaterion;
		//}

		//FVec3 operator+(const FVec2& other)
		//{
		//	return { x + other.x, y + other.y, z };
		//}
		//
		//FVec3 operator+(const FVec3& other)
		//{
		//	return { x + other.x, y + other.y, z + other.z };
		//}

		//Quaterion operator*(const Quaterion& other) const
		//{
		//	Quaterion q;
		//	q.quaterion.w = quaterion.w * other.quaterion.w;
		//	q.quaterion.x = quaterion.x * other.quaterion.x;
		//	q.quaterion.y = quaterion.y * other.quaterion.y;
		//	q.quaterion.z = quaterion.z * other.quaterion.z;
		//
		//	return q;
		//}
		//Quaterion operator*(const Quaterion& other)
		//{
		//	Quaterion q;
		//	q.quaterion.w = quaterion.w * other.quaterion.w;
		//	q.quaterion.x = quaterion.x * other.quaterion.x;
		//	q.quaterion.y = quaterion.y * other.quaterion.y;
		//	q.quaterion.z = quaterion.z * other.quaterion.z;
		//
		//	return q;
		//}
		//Quaterion operator*(const float other)
		//{
		//	Quaterion q; q.quaterion* other;
		//
		//	return q;
		//}

		//FVec3 operator+=(const FVec3& other)
		//{
		//	return { x += other.x, y += other.y, z += other.z };
		//}
		//FVec3 operator*=(const FVec3& other)
		//{
		//	return { x *= other.x, y *= other.y, z *= other.z };
		//}
		//
		//FVec3 operator+(const float& other)
		//{
		//	return { x + other, y + other, z + other };
		//}
		//
		//FVec3 operator-(const float& other)
		//{
		//	return { x - other, y - other, z - other };
		//}
		//
		//FVec3 operator*(const float& other)
		//{
		//	return { x * other, y * other, z * other };
		//}
		//
		//FVec3 operator*(const float& other) const
		//{
		//	return { x * other, y * other, z * other };
		//}
		//
		//FVec3 operator*=(const float& other)
		//{
		//	return { x *= other, y *= other, z *= other };
		//}
		//
		//FVec3 operator-(const FVec3& other)
		//{
		//	return { x - other.x, y - other.y, z - other.z };
		//}

		//Quaterion operator=(const Quaterion& other)
		//{
		//	quaterion = other.quaterion;
		//	return *this;
		//}
	//};

	//calculates a look rotation, expects look direction to be normalized
	//BTD_Compiler_ForceInline Quaterion LookRotation(const BTD::Math::FVec3& lookDir, const BTD::Math::FVec3 upDir = BTD::Math::FVec3::WorldUp())
	//{
	//	return glm::quatLookAt(lookDir.GLM(), upDir.GLM());
	//}
}
