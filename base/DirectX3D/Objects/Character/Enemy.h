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

public:
	Enemy(string name, UINT index = 0, ModelAnimatorInstancing* modelAnimatorInstancing = new ModelAnimatorInstancing(""),
		Transform* transform = new Transform(), Vector3 spawnPos = { 0, 0, 0 }, float trackRange = 1000.0f);
	~Enemy();

	void Update();
	void Render();
	void GUIRender();

	void SetTarget(Transform* target) { this->target = target; }
	void SetState(State state);

	SphereCollider* GetTrackCollider() { return trackCollider; }

private:
	void Track();

private:
	ModelAnimatorInstancing* instancing;

	float trackTime = 0.0f;
	float trackRange = 0.0f;
	float speed = 10.0f;

	UINT index;
	State curState = IDLE;

	SphereCollider* trackCollider;

	Transform* target;
	Vector3 velocity;
};

