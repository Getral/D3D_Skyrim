#pragma once
class alduin : public ModelAnimator
{ 
private:
	enum State
	{
		IDLE,
		TAKEOFF,
		HOVER,
		HOVER_HIT,
		WALK,
		RUN,
		RUN_L,
		RUN_R,
		ATTACK_F, //물기, (공중) 접근
		ATTACK_L, //날개 휘두르기 왼쪽
		ATTACK_R, //날개 휘두르기 오른쪽
		ATTACK_B, // 꼬리 휘두르기
		INHALE,
		BREATH, //inhale -> exhale_breath
		FIREBALL, //inhale -> exhale_fireball
		PAIN, // pain,pain2  랜덤 재생
		PAIN2,
		DEATH
	};

public:

	alduin();
	~alduin();

	void Update();
	void Render();
	void GUIRender();

	void SetTarget(Player* target);

private:

	void SetAnimation();
	void SetState(State state);
	void Move();

	void beginAttack();
	void Inhale();
	void FireBallAttack();
	void BreathAttack();


	void EndTakeoff();
	void EndHit();
	void EndAttack();

	void Patterns();

	State curState = IDLE;
	CapsuleCollider* alduinCollider2;

	CapsuleCollider* HeadCollider;
	CapsuleCollider* LWingCollider;
	CapsuleCollider* RWingCollider;
	CapsuleCollider* BodyCollider;
	CapsuleCollider* RLegCollider;
	CapsuleCollider* LLegCollider;

	CapsuleCollider* TailCollider;

	CapsuleCollider* collider_F;
	CapsuleCollider* collider_R;
	CapsuleCollider* collider_L;
	CapsuleCollider* collider_B;
	Transform* transform;
	Player* target;

	UINT nodeIndex = 0;

	float moveSpeed = 500;
	float rotSpeed = 0.5;
	float deceleration = 5; //감속

	Vector3 velocity;

	vector<map<float, Event>> totalEvent;
	vector<map<float, Event>::iterator> eventIters;

	float maxHp = 3000.0f;
	float curHp = 3000.0f;


};

