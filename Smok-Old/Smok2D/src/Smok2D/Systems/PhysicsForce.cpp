#include "PhysicsForce.h"

#include <Core\Events\EngineEvents.h>
#include <Renderer\Display.h>

#include <Core\ECS\EntityManager.h>
#include <Core\ECS\Components\Transform.h>
#include <Smok2D\Components\Rigidbody.h>

void PhysicsForce::Init()
{
	ECSSystemEvent::AddMethod(&PhysicsForce::ApplyForce);
}

void PhysicsForce::Shutdown()
{
	//remove from event
}

void PhysicsForce::ApplyForce()
{
	auto entities = EntityManager::GetReg().view<Rigidbody, Transform>();

	if (entities.size() < 1)
		return;

	for (auto entity : entities)
	{
		auto& rigid = entities.get<Rigidbody>(entity);
		if (!rigid.isActive)
			continue;
		
		auto& trans = entities.get<Transform>(entity);

		if (rigid.forceDir == ForceDirection::None)
			return;

		if (rigid.forceDir == ForceDirection::Up)
			trans.position.y += rigid.force * DisplayI.GetDeltaTime();// * 2);

	}
}
