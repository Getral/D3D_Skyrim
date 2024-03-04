#pragma once

class Enemy : public Character
{
private:
	enum State
	{
		IDLE,
		RUN,
		ATTACK,
		HIT,
	};

	enum Collider
	{
		HIP,
		KNEE_L,
		HEEL_L,
		SOLE_L,
		TOES_L,
		THIGH_L,
		KNEE_R,
		HEEL_R,
		SOLE_R,
		TOES_R,
		THIGH_R,
		BELLY,
		TORSO,
		CHEST,
		NECK,
		SHOULDER_L,
		ELBOW_L,
		WRIST_L,
		HAND_L,
		FINGERS_L,
		SHOULDER_R,
		ELBOW_R,
		WRIST_R,
		HAND_R,
		FINGERS_R,
		HEAD,
	};

public:
	Enemy(string name, UINT index = 0, ModelAnimatorInstancing* modelAnimatorInstancing = new ModelAnimatorInstancing(""),
		Transform* transform = new Transform(), Vector3 spawnPos = { 0, 0, 0 }, float trackRange = 1000.0f);
	~Enemy();

	void Update();
	void Render();
	void GUIRender();

	void SetTarget(Transform* target) { if(this->target != target) this->target = target; }
	void SetState(State state);

	SphereCollider* GetTrackCollider() { return trackCollider; }

private:
	void Track();
	void SetColliderByNode();

private:
	ModelAnimatorInstancing* instancing;

	float trackTime = 0.0f;
	float trackRange = 0.0f;
	float speed = 10.0f;

	UINT index;
	UINT node;
	State curState = IDLE;

	SphereCollider* trackCollider;
	vector<CapsuleCollider*> colliders;

	Transform* target;
	Vector3 velocity;
};

