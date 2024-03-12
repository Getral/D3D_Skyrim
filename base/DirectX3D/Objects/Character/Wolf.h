#pragma once



class Wolf : public Enemy
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
		
	};

public:
	Wolf(string name, UINT index = 0, ModelAnimatorInstancing* modelAnimatorInstancing = new ModelAnimatorInstancing(""),
		Transform* transform = new Transform(), Vector3 spawnPos = { 0, 0, 0 }, float trackRange = 1000.0f);
	~Wolf();

	virtual void Update();
	virtual void Render();
	virtual void GUIRender();

	void SetState(State state);

private:
	void Attack();

	void SetEvent(int clip, Event event, float timeRatio);
	void ExecuteEvent();

	virtual void Track();
	virtual void SetColliderByNode();
private:
	State curState;

	UINT node = 1;
};

