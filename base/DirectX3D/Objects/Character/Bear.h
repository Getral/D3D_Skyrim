#pragma once

class Bear : public Enemy
{
private:
	enum State
	{
		IDLE,
		RUN,
		ATTACK,
		ATTACK2,
		ATTACK3,
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
	Bear(string name, UINT index = 0, ModelAnimatorInstancing* modelAnimatorInstancing = new ModelAnimatorInstancing(""),
		Transform* transform = new Transform(), Vector3 spawnPos = { 0, 0, 0 }, float trackRange = 1000.0f);
	~Bear();

	virtual void Update();
	virtual void Render();
	virtual void GUIRender();

	void SetState(State state);

private:
	virtual void Track();
	void Attack();

	virtual void SetColliderByNode();
private:
	State curState = IDLE;

	bool isAttacked = false;
};

