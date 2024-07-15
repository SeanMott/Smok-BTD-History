#pragma once

//defines a 3D camera

#include <BTDSTD/Math/Transform.hpp>

namespace BTD::Math
{
	//defines a camera
	struct Camera
	{
		bool boundToWindowSize = true; //this camera will resize it's render aspect to the window

		float FOV = 70.0f; //the radius
		FVec2 far_near_clip = { 0.01f, 100.0f };
		FVec2 screenRenderSize = { 800.0f, 600.0f };

		Trans::Transform transform;

		//the internal Projection and View
		glm::mat4 projection = glm::mat4(1.0f), view = glm::mat4(1.0f);

		bool isDirty = false; //is this camera dirty

		//calculates the Projection of this camera
		inline glm::mat4 CalProjection()
		{
			isDirty = true;

			projection = glm::perspective(glm::radians(FOV), screenRenderSize.x / screenRenderSize.y,
				far_near_clip.y, far_near_clip.x);

			// invert the Y direction on projection matrix so that we are more similar
			// to opengl and gltf axis
			projection[1][1] *= -1;

			return projection;
		}

		//calculates the view of the camera
		inline glm::mat4 CalView()
		{
			isDirty = true;

			view = glm::inverse(glm::translate(transform.position.GLM()));

			return view;
		}
	};
}