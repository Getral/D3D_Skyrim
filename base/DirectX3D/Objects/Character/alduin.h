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
		FORWARD,
		BACKWARD,
		BLEED,
		APROACH,
		FLIGHT_FOR,
		ATTACK_F, //물기, (공중) 접근
		ATTACK_L, //날개 휘두르기 왼쪽
		ATTACK_R, //날개 휘두르기 오른쪽
		ATTACK_B, // 꼬리 휘두르기
		INHALE,
		BREATH, //inhale -> exhale_breath
		FIREBALL, //inhale -> exhale_fireball
		PAIN, // pain,pain2  랜덤 재생
		PAIN2,
		LANDING,
		LANDING_SOFT,
		LANDING_HARD,
		LAND,
		LAND_VERTICAL,
		DIVE,
		DEATH,
		TURN_L,
		TURN_R
	};

public:

	alduin();
	~alduin();

	void Update();
	void Render();
	void GUIRender();

	void SetTarget(Player* target);
	float GetHP() { return curHp; }

private:

	//void SetAnimation();
	void SetState(State state);
	void Move();

	void Inhale();
	void FireBallAttack();
	void BreathAttack();

	void Attacking();
	void beginTakeoff();
	void EndTakeoff();
	void beginAproach();
	void EndAction();

	void Dying();
	void Dead();

	void Patterns();
	void PatternFire();
	void PatternsAir();

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
	BoxCollider* breathCollider;
	SphereCollider* fBallCollider;

	Transform* transform;
	Transform* FireAttackTransform;
	Player* target;
	Vector3* tempRot;

	UINT nodeIndex = 0;

	float moveSpeed = 15.0f;
	float rotSpeed = 0.25;
	float altitude = 0.0f;
	float deceleration = 5; //감속
	float CoolingTime = 0;
	float fireBallDir = 0.0f;

	bool isAscending = false;
	bool isDescending = false;
	bool isAttacking = false;
	bool isFireAttack = false;


	Vector3 velocity;

	vector<map<float, Event>> totalEvent;
	vector<map<float, Event>::iterator> eventIters;

	float maxHp = 3000.0f;
	float curHp = 3000.0f;


};

