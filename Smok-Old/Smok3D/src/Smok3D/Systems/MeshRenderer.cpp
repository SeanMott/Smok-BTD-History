#include <smpch.h>
#include "MeshRenderer.h"

#include <Core\ECS\EntityManager.h>
#include <Core\ECS\Components\Transform.h>
//#include <Core\ECS\Components\Camera.h>
#include <Smok3D\Components\Mesh.h>

#include <gtc/matrix_transform.hpp>

using namespace glm;

/*
//renders the meshs
void MeshRenderer::RenderMesh()
{
	mat4 PV = mat4(1.0f); //Projection * View

	mat4 projection = mat4(1.0f);
	mat4 view = mat4(1.0f);

	//get array of all entities with both a mesh and transform component
	auto entities = EntityManager::GetReg().view<Transform, Mesh>();
	
	//get all cameras and store the first one
	auto cameras = EntityManager::GetReg().view<Transform, Transform>();

	for (auto camera : cameras)
	{
		//Camera& cam = EntityManager::GetReg().get<Camera>(camera);
		//if (!cam.isActive)
			//continue;

		Transform& trans = EntityManager::GetReg().get<Transform>(camera);
		cam.projection = perspective(glm::radians(cam.FOV), cam.aspectRatio, cam.nearClipField, cam.farClipField);
		projection = cam.projection;
		cam.view = lookAt(trans.position, trans.front, trans.up);
		view = cam.view;
		PV = projection * view;
	}

	//iterate through them all meshs
	for (auto entity : entities)
	{
		Mesh& mesh = EntityManager::GetReg().get<Mesh>(entity);
		if (!mesh.isActive)
			continue;

		Transform& trans = EntityManager::GetReg().get<Transform>(entity);

		//if not equal to last vertex buffer rebind
		if (lastVertexBuffer != mesh.vertexBuffer)
		{
			mesh.vertexBuffer->Bind();
			lastVertexBuffer = mesh.vertexBuffer;
		}

		//if not equal to last index buffer rebind
		if (lastIndexBuffer != mesh.indexBuffer)
		{
			mesh.indexBuffer->Bind();
			lastIndexBuffer = mesh.indexBuffer;
		}

		//if not equal to last shader rebind
		if (lastShader != mesh.shader)
		{
			mesh.shader->Bind();
			lastShader = mesh.shader;
		}

		//if not equal to last texture rebind
		if (lastTexture != mesh.texture)
		{
			mesh.texture->Bind(mesh.textureSlot);
			lastTexture = mesh.texture;
		}

		mat4 PVM = mat4(1.0f); //projection * view * model

		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::mat4(1.0f);
		Transform t = EntityManager::GetReg().get<Transform>(EntityManager::GetEntity("Box")->entity);
		model = glm::translate(model, t.position);
		float angle = 20.0f;
		model = glm::rotate(model, glm::radians(angle), t.rotation); //glm::vec3(1.0f, 0.3f, 0.5f));
		PVM = PV * model;

		lastShader->SetMatrix4("PVM", PVM);

		//draw call and get vertex buffer size
		if (!lastIndexBuffer)
			glDrawArrays(GL_TRIANGLES, 0, lastVertexBuffer->GetSize());
		else
			glDrawElements(GL_TRIANGLES, lastIndexBuffer->GetCount(), GL_UNSIGNED_INT, 0);
	}

	/*
	----Note----
	add batch rendering later
	----Note----

	----Note----
	submit meshs then render all at once
	----Note----

	*/
/*
}
*/