#pragma once



class Wolf : public Enemy
{
private:
	enum State
	{
		IDLE,
		COMBATIDLE,
		WALK,
		HOWLING,
		RUN,
		ATTACK,
	};

	enum Collider
	{
		HEAD
	};

public:
	Wolf(string name, UINT index = 0, ModelAnimatorInstancing* modelAnimatorInstancing = new ModelAnimatorInstancing(""),
		Transform* transform = new Transform(), Vector3 spawnPos = { 0, 0, 0 });
	~Wolf();

	virtual void Update();
	virtual void Render();
	virtual void GUIRender();

	void SetState(State state);

private:
	void SetRandIdleRot();

	void Behavior();
	void Walk();
	void Attack();

	void StartIdle();

	void EndHowling();

	void StartRun();

	void StartAttack();
	void EndAttack();

	void SetEvent(int clip, Event event, float timeRatio);
	void ExecuteEvent();

	virtual void Track();
	virtual void SetColliderByNode();
private:
	State curState;

	UINT node = 1;

	Vector3 randPos;
	Vector3 tmpPos;

	float idleTime = 0.0f;
	float attackDelay = 0.0f;
	float rotSpeed = 10.0f;

	bool isTracking = false;
};

