#include "Framework.h"

Wolf::Wolf(string name, UINT index, ModelAnimatorInstancing* modelAnimatorInstancing, Transform* transform, Vector3 spawnPos, float trackRange)
	: Enemy(name, index, modelAnimatorInstancing, transform, spawnPos, trackRange)
{
	colliders.push_back(new CapsuleCollider(25.0f));

	SetCollidersParent();
}

Wolf::~Wolf()
{

}

void Wolf::Update()
{
	Enemy::Update();

	if (playerData->GetCollier()->IsCollision(attackCollider))
	{
		SetState(ATTACK);
	}
	else if (playerData->GetCollier()->IsCollision(trackCollider))
	{
		SetState(RUN);
		SetTarget(playerData);
	}
	else
	{
		SetState(IDLE);
		SetTarget(nullptr);
	}

	SetColliderByNode();
}

void Wolf::Render()
{
	Enemy::Render();
}

void Wolf::GUIRender()
{
	Enemy::GUIRender();
	ImGui::SliderInt("Node", (int*)&node, 1, 100);
}

void Wolf::SetState(State state)
{
}

void Wolf::Track()
{
	if (curState == ATTACK) return;
	if (curState == HIT) return;
	if (target)
	{
		velocity = target->GlobalPos() - transform->GlobalPos();
		transform->Pos() += velocity.GetNormalized() * this->status.speed * DELTA;
		transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI;
	}
}

void Wolf::Attack()
{
}

void Wolf::SetColliderByNode()
{
	colliderTransforms[0]->SetWorld(instancing->GetTransformByNode(index, node));
}
