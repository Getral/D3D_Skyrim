#pragma once
class alduin : public ModelAnimator
{ 
private:
	enum State
	{
		IDLE,
		TAKEOFF,
		HOVER,
		WALK,
		RUN,
		RUN_L,
		RUN_R,
		ATTACK_F, //물기, (공중) 접근
		ATTACK_L, //날개 휘두르기 왼쪽
		ATTACK_R, //날개 휘두르기 오른쪽
		ATTACK_B, // 꼬리 휘두르기
		BREATH, //inhale -> exhale_breath
		FIREBALL, //inhale -> exhale_fireball
		PAIN, // pain,pain2  랜덤 재생
		DEATH
	};

public:

	alduin();
	~alduin();

	void Update();
	void Render();
	void GUIRender();

	void SetTarget(Transform* target);


private:

	void SetAnimation();
	void SetState(State state);
	void Pattern1();
	void Pattern2();

	State curState = IDLE;
	CapsuleCollider* alduinCollider;
	Transform transform;
	Transform* target;

	float moveSpeed = 500;
	float rotSpeed = 1;
	float deceleration = 5; //감속

	Vector3 velocity;
	Vector3 targetPos;

	float maxHp = 3000.0f;
	float curHp = 3000.0f;


};

