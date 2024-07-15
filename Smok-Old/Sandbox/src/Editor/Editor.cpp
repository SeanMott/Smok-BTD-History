#ifndef SMOK_DIST

#include "Editor.h"

#include <Core\Events\EngineEvents.h>
#include <Core\Events\ScriptEvents.h>
#include <Core\Events\InputEvents.h>
#include <Core\AssetManager.h>
#include <Core\Input.h>

#include <Renderer\Display.h>

#include <Core\ECS\EntityManager.h>
#include <Core\ECS\Components\Transform.h>

#ifdef Smok2D_Link
#include <Smok2D\Components\OrthographicCamera.h>
#include <Smok2D\Components\Sprite.h>
#endif

#ifdef Smok3D_Link
#endif

#include "Scenes\SceneManager.h"

#include <imgui.h>

using namespace std; using namespace glm;

Entity Editor::selectedEntity("Entity");
Transform* Editor::selectedTrans = nullptr;
//static string selectedTexture = "";

Entity* Editor::editorCam = nullptr;
//Transform* Editor::editorTrans = nullptr;

float Editor::moveSpeed = 5.0f;

static bool useEditorCam = false;

void Editor::Init()
{
	//makes Editor Cam
	EntityManager::Create("editorCam");
	editorCam = EntityManager::GetEntity("editorCam");
	editorCam->AddComponent<Transform>(vec3(DisplayI.GetScreenWidth() / 2, DisplayI.GetScreenHeight() / 2, 0.0f));
	editorCam->AddComponent<OrthographicCamera>((float)DisplayI.GetScreenWidth(), (float)DisplayI.GetScreenHeight(), false);
	editorCam->layer = "Editor";

	//makes Editor arrows

	ECSGUIRenderEvent::AddMethod(&Editor::Draw);
	KeyPressEvent::AddMethod(&Editor::CamSwitch);
	ScriptUpdateEvent::AddMethod(&Editor::CamCon);
}

void Editor::Shutdown()
{
	//remove from events
}

void Editor::Draw()
{
	//Scene List
	ImGui::Begin("Scene List");
	
	if (ImGui::Button("Save"))
		SceneManager::SaveScene();
	if (ImGui::Button("Reload"))
		SceneManager::Reload();

	ImGui::End();

	//camera
	ImGui::Begin("Current Camera");
	ImGui::Text("Current Camera: %s", (useEditorCam == true ? "Editor" : "Scene"));
	ImGui::End();

	//Entity Hierarchy
	ImGui::Begin("Entity Hierarchy");
	vector<Entity> entities = EntityManager::GetAllEntities();
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		if (entities[i].layer == "Editor")
			continue;

		if (ImGui::Button(entities[i].name.c_str()))
		{
			selectedEntity = entities[i];
			if (selectedEntity.HasComponent<Transform>())
			{
				selectedTrans = selectedEntity.GetComponent<Transform>();
				if (editorCam->HasComponent<Transform>())
					editorCam->GetComponent<Transform>()->position = vec3(selectedTrans->position.x / 2, selectedTrans->position.y / 2, 0.0f);
			}
			else
				selectedTrans = nullptr;
		}
	}
	ImGui::End();

	//Selected Entity Inspecter
	ImGui::Begin("Inspecter");

	//Entity name and layer
	ImGui::Text("Name: %s\nLayer:%s", selectedEntity.name.c_str(), selectedEntity.layer.c_str());

	if (!EntityManager::GetReg().valid(selectedEntity.entityHandle))
	{
		ImGui::End();
		return;
	}

	//Transform Component || make theses changeable
	if (selectedTrans)
		ImGui::Text("Transform:\nX: %f, Y: %f, Z: %f\nX: %f, Y: %f, Z: %f\nX: %f, Y: %f, Z: %f",
			selectedTrans->position.x, selectedTrans->position.y, selectedTrans->position.z,
			selectedTrans->rotation.x, selectedTrans->rotation.y, selectedTrans->rotation.z,
			selectedTrans->scale.x, selectedTrans->scale.y, selectedTrans->scale.z
		);

#ifdef Smok2D_Link
	//Sprite Component || make theses changeable
	if (selectedEntity.HasComponent<Sprite>())
	{
		Sprite* sprite = selectedEntity.GetComponent<Sprite>();
		ImGui::Text("Sprite:\nTexture: %s, Slot: %u\nShader: %s\nColor:\n\tR: %f, G: %f, B: %f, A: %f\nLayer: %u\nIs Active: %s",
			sprite->texture.c_str(), sprite->textureSlot, sprite->shader.c_str(),
			sprite->color.r, sprite->color.g, sprite->color.b, 1.0f,
			sprite->layer, (sprite->isActive == true ? "Yes" : "No"));
	}

	//Orthographic Camera Component || make theses changeable
	if (selectedEntity.HasComponent<OrthographicCamera>())
	{
		OrthographicCamera* cam = selectedEntity.GetComponent<OrthographicCamera>();
		ImGui::Text("Orthographic Camera:\nView:\n\tX: %f, Y: %f\nIs Active: %s",
			cam->viewLength, cam->viewHeight, (cam->isActive == true ? "Yes" : "No"));
	}

	//Rigidbody Component || make theses changeable
#endif

#ifdef Smok3D_link
	//Mesh Component || make theses changeable

	//Perspective Camera Component || make theses changeable

	//Rigidbody Component || make theses changeable
#endif

	ImGui::End();
}

void Editor::CamSwitch(int key, bool isRepeat)
{
	//switchs to editor and scene cams
	if (key == SMOK_KEY_E)
	{
		auto c = EntityManager::GetReg().view<OrthographicCamera>();

		for (auto cam : c)
		{
			auto& camera = c.get<OrthographicCamera>(cam);
			camera.isActive = !camera.isActive;
		}

		if (c.size() > 1)
			useEditorCam = !useEditorCam;
	}
}

void Editor::CamCon(float deltaTime)
{
	if (!editorCam->HasComponent<Transform>())
		return;

	Transform* trans = EntityManager::GetComponent<Transform>("editorCam");
	if (!trans)
		return;

	//moves editor camera
	if (Input::GetKey(SMOK_KEY_W))
		trans->position -= vec3(0.0f, moveSpeed, 0.0f);
	else if (Input::GetKey(SMOK_KEY_S))
		trans->position += vec3(0.0f, moveSpeed, 0.0f);
	else if (Input::GetKey(SMOK_KEY_A))
		trans->position -= vec3(moveSpeed, 0.0f, 0.0f);
	else if (Input::GetKey(SMOK_KEY_D))
		trans->position += vec3(moveSpeed, 0.0f, 0.0f);

	//moves selected object
	if (!selectedTrans)
		return;

	//selected move
	if (Input::GetKey(SMOK_KEY_UP))
		selectedTrans->position -= vec3(0.0f, moveSpeed, 0.0f);
	else if (Input::GetKey(SMOK_KEY_DOWN))
		selectedTrans->position += vec3(0.0f, moveSpeed, 0.0f);
	else if (Input::GetKey(SMOK_KEY_LEFT))
		selectedTrans->position -= vec3(moveSpeed, 0.0f, 0.0f);
	else if (Input::GetKey(SMOK_KEY_RIGHT))
		selectedTrans->position += vec3(moveSpeed, 0.0f, 0.0f);
}

#endif
