#pragma once

class Enemy : public Character
{
public:
	Enemy(string name, UINT index = 0, ModelAnimatorInstancing* modelAnimatorInstancing = new ModelAnimatorInstancing(""),
		Transform* transform = new Transform(), Vector3 spawnPos = { 0, 0, 0 }, float trackRange = 1000.0f);
	~Enemy();

	virtual void Update();
	virtual void Render();
	virtual void GUIRender();

	void SetTarget(Transform* target) { if(this->target != target) this->target = target; }
	void SetPlayerData(Player* player) { if (this->playerData != player) playerData = player; }

	SphereCollider* GetTrackCollider() { return trackCollider; }
	SphereCollider* GetAttackCollider() { return attackCollider; }
	vector<CapsuleCollider*> GetColliders() { return colliders; }

protected:
	virtual void Track();

	virtual void SetCollidersParent();

protected:
	ModelAnimatorInstancing* instancing;

	float trackTime = 0.0f;
	float hitDelay = 0.0f;
	float trackRange = 0.0f;
	float attackRange = 0.0f;

	UINT index;
	UINT node;

	SphereCollider* trackCollider;
	SphereCollider* attackCollider;
	vector<CapsuleCollider*> colliders;
	vector<Transform*> colliderTransforms;

	Transform* target;
	Vector3 velocity;

	Player* playerData;
};

