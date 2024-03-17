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
		ATTACK2,
		ATTACK3,
		ATTACK4,
		HIT,
		DEATH
	};

	enum Collider
	{
		HIP,
		BELLY,
		TORSO,
		THIGH_FL,
		LEG_FL,
		FOOT_FL,
		THIGH_FR,
		LEG_FR,
		FOOT_FR,
		CHEST,
		NECK,
		HEAD,
		MOUTH,
		THIGH_BL,
		LEG_BL,
		FOOT_BL,
		THIGH_BR,
		LEG_BR,
		FOOT_BR,
		TAIL1,
		TAIL2,
		TAIL3
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

	void Death();

	void Behavior();
	void Walk();

	void StartIdle();

	void EndHowling();

	void StartRun();

	void StartAttack();
	void StartAttackTrigger();
	void EndAttackTrigger();
	void EndAttack();

	void EndCombatIdle();

	void StartHit();
	void EndHit();

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
	bool isHit = false;
	bool attackTrigger = false;

	int atkType = 0;
};

