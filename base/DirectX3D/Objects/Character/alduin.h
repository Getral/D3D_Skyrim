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
		ATTACK_F, //����, (����) ����
		ATTACK_L, //���� �ֵθ��� ����
		ATTACK_R, //���� �ֵθ��� ������
		ATTACK_B, // ���� �ֵθ���
		INHALE,
		BREATH, //inhale -> exhale_breath
		FIREBALL, //inhale -> exhale_fireball
		PAIN, // pain,pain2  ���� ���
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
	float deceleration = 5; //����

	Vector3 velocity;

	vector<map<float, Event>> totalEvent;
	vector<map<float, Event>::iterator> eventIters;

	float maxHp = 3000.0f;
	float curHp = 3000.0f;


};

