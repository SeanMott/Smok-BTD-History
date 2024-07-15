#pragma once

//defines various matrixs

#include <BTDSTD/CompilerFunctions.hpp>

namespace BTD::Math::Mat
{
	//defines a matatrix functions and structs
	struct Mat4
	{
		float data[16];

		//gets the x position
		//gets the y position
		//gets the z position

		//sets the position in the matrix
		//gets the position from the matrix

		//gets the w rotation
		//gets the x rotation
		//gets the y rotation
		//gets the z rotation

		//sets the rotation in the matrix
		//gets the rotation from the matrix

		//gets the x scale
		//gets the y scale
		//gets the z scale

		//sets the scale in the matrix
		//gets the scale from the matrix
	};

	//returns a identity matrix
	//BTD_Compiler_ForceInline Mat4 Mat4Identity()
	//{
	//	Mat4 matrix;
	//	memset(&matrix, 0, sizeof(float) * 16);
	//	matrix.data[0] = 1.0f;
	//	matrix.data[5] = 1.0f;
	//	matrix.data[10] = 1.0f;
	//	matrix.data[15] = 1.0f;
	//	return matrix;
	//}

	//tranlates a matrix

	//rotates a matrix

	//scales a matrix

	//calculates a model matrix

}