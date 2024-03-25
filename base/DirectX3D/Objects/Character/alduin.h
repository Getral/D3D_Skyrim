#pragma once

#define MAX_GROUND_ATK 60

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
		HIT,
		DEATH,
		TURN_L,
		TURN_R,
		SLEEP,
		WAKEUP
	};
public:

	alduin();
	~alduin();

	void Update();
	void Render();
	void GUIRender();

	void SetTarget(Player_Dragon* target);
	void SetTarget2(Player* target);
	float GetHP() { return curHp; }
	float GetMaxHP() { return maxHp; }
	Transform* GetTransform() { return transform; }
	
	bool GetIsSleeping() { return isSleeping; }
	bool& SetIsColliderRend() { return isColliderRend; }
private:

	//void SetAnimation();
	void SetState(State state, float Scale = 1.0f);
	void Move();

	void Inhale();
	void InhaleStart();
	void BreathAttack();

	void Attacking();
	void Attacking2();
	void beginTakeoff();
	void EndTakeoff();
	void beginAproach();
	void EndAction();
	void EndLanding();
	void HitDelayEnd();

	void SleepWake();
	void WakeUp();
	

	void hit();
	void Dying();
	void Dead();

	void Patterns();
	void PatternFire();
	void PatternsAir();



	State curState = IDLE;
	CapsuleCollider* alduinCollider2;

	CapsuleCollider* HeadCollider;
	CapsuleCollider* BodyCollider;
	CapsuleCollider* TailCollider;

	CapsuleCollider* collider_F;
	CapsuleCollider* collider_R;
	CapsuleCollider* collider_L;
	CapsuleCollider* collider_B;

	CapsuleCollider* Acollider_F;
	CapsuleCollider* Acollider_R;
	CapsuleCollider* Acollider_L;
	CapsuleCollider* Acollider_B;
	BoxCollider* breathCollider;
	BoxCollider* ApproachCollider;

	SphereCollider* WakeUpCollider;

	Transform* transform;
	Transform* FireAttackTransform;
	Player_Dragon* target;
	Player* target2;
	Vector3 tempPos;
	Vector3 tempRot;
	ParticleSystem* DeathParticle;
	ParticleSystem* BreathParticle;

	UINT nodeIndex = 0;


	float moveSpeed = 15.0f;
	float rotSpeed = 0.25;
	float altitude = 0.0f;
	float deceleration = 5; //감속
	float CoolingTime = 1.0f;
	float HitDelay = 0.0f;
	float HitDelay2 = 0.7f;
	float breathDelay = 0.0f;

	bool isAscending = false;
	bool isDescending = false;
	bool isAttacking = false;
	bool isFireAttack = false;
	bool isMoving = false;
	bool isSleeping = true;
	bool isColliderRend = false;


	Vector3 velocity;

	vector<map<float, Event>> totalEvent;
	vector<map<float, Event>::iterator> eventIters;

	float maxHp = 500.0f;
	float curHp = 500.0f;

	


};

