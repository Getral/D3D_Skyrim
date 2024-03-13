#pragma once

class Bear : public Enemy
{
private:
	enum State
	{
		SLEEP,
		STARTSLEEP,
		WAKEUP,
		IDLE,
		COMBATIDLE,
		RUN,
		ATTACK,
		ATTACK2,
		ATTACK3,
		ATTACK4,
		HIT,
		HEADSHAKE,
		DEATH
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
		Transform* transform = new Transform(), Vector3 spawnPos = { 0, 0, 0 });
	~Bear();

	virtual void Update();
	virtual void Render();
	virtual void GUIRender();

	void SetState(State state);

private:
	void SetEvent();
	void Behavior();

	void StartStartSleep();
	void EndStartSleep();

	void StartWakeUp();
	void EndWakeUp();

	void StartRun();
	void EndRun();

	void StartAttack();
	void EndAttack();

	void StartHit();
	void EndHit();

	void EndHeadShake();

	void SetEvent(int clip, Event event, float timeRatio);
	void ExecuteEvent();

	virtual void Track();
	virtual void SetColliderByNode();

private:
	float rotSpeed = 4.0f;
	float attackDelay = 0.0f;
	bool isHit = false;
	bool isSleep = true;
	bool isWakeUp = false;

	State curState;
	UINT attackState = 0;
};
