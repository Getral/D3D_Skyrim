#include "Framework.h"

Enemy::Enemy(string name, UINT index, ModelAnimatorInstancing* modelAnimatorInstancing, Transform* transform, Vector3 spawnPos, float trackRange)
	: Character(transform, name, spawnPos), index(index), instancing(modelAnimatorInstancing), trackRange(trackRange)
{
	trackCollider = new SphereCollider();
	trackCollider->Scale() *= trackRange;
	trackCollider->SetParent(transform);

	torsoCollider = new CapsuleCollider(20.0f, 60.0f);
	headCollider = new CapsuleCollider(25.0f);
	headCollider->SetWorld(instancing->GetTransformByNode(index, 91));
}

Enemy::~Enemy()
{
	delete trackCollider;
	delete torsoCollider;
	delete headCollider;
}

void Enemy::Update()
{
	Character::Update();
	trackCollider->UpdateWorld();
	torsoCollider->UpdateWorld();
	headCollider->UpdateWorld();

	torsoCollider->SetWorld(instancing->GetTransformByNode(index, node));

	if (target)
	{
		SetState(RUN);
		velocity = target->GlobalPos() - transform->GlobalPos();
	}

	Track();
}

void Enemy::Render()
{
	//Character::Render();
	//trackCollider->Render();
	torsoCollider->Render();
	headCollider->Render();
}

void Enemy::GUIRender()
{
	Character::GUIRender();
	ImGui::SliderInt("Node Number : %d", (int*)&node, 1, 130);
}

void Enemy::SetState(State state)
{
	if (state == curState) return;

	curState = state;
	instancing->PlayClip(index, (int)state, 0.5f);
}

void Enemy::Track()
{
	if (target)
	{
		transform->Pos() += velocity.GetNormalized() * speed * DELTA;
		transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI;
	}
	else
	{
		SetState(IDLE);
	}
}
