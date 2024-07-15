//defines a Script || allows Unity and Unreal like scripts to be used along with Systems and Components

/*
Scripts are simaler to Unreal, Unity, or Godot style scripts. They are not stored as Componets but can be accessed bu Systems.
Scripts can have methods linked to Script specific events.
Theses require a Script method prototype to have a certain return and paramater(s).
The name and paramater names can be what ever you like.

Script events are as followed:

--Start and End are called once and only if the Script is instanced on a Entity

void Start() || gets called when the scene loads
void End() || gets called when the scene ends

--theses are called every update frame

void Update(float deltaTime) || passes the delta time every frame
void FixedUpdate(float fixedUpdate) || passes a fixed delta time every frame, defaults to 60.0f

--Theses are triggered only if a Physics system is enabled.
--Requires the Entity with the Script to have a Collider must match dimention type, does not require a Rigidbody

void OnTriggerEnter(const std::string other, const std::string self) || only triggers in Smok3D when the Entity enters a 3D trigger collider
void OnTriggerExit(const std::string other, const std::string self) || only triggers in Smok3D when the Entity exits a 3D trigger collider
void OnColliderEnter(const std::string other, const std::string self) || only triggers in Smok3D when the Entity enters a 3D nontrigger collider
void OnColliderExit(const std::string other, const std::string self) || only triggers in Smok3D when the Entity exits a 3D nontrigger collider

void OnTriggerEnter(const std::string other, const std::string self) || only triggers in Smok2D when the Entity enters a 2D trigger collider
void OnTriggerExit(const std::string other, const std::string self) || only triggers in Smok2D when the Entity exits a 2D trigger collider
void OnColliderEnter(const std::string other, const std::string self) || only triggers in Smok2D when the Entity enters a 2D nontrigger collider
void OnColliderExit(const std::string other, const std::string self) || only triggers in Smok2D when the Entity exits a 2D nontrigger collider

--called when the Entity is destroyed and has this Script instanced

void Destroy() || when the Entity is destroyed

--when the Script instance is enabled or disabled

void OnEnable() || when the Entity Script is enabled is not called at Start
void Disable() || when the Entity Script is disabled

*/

#ifndef Script_h
#define Script_h

#include <string>

struct Script
{
	void* script = nullptr; //pointer to the class instance
	std::string filePath, name; //place where the script header is stored, name of the script can be custome
	bool isActive = true;

	/*Deconstructor
	~Script()
	{
		if (script)
			delete script;

		filePath = ""; name = "";
	}*/
};

#endif