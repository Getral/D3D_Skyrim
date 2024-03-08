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
		BLEED,
		APROACH,
		FLIGHT_FOR,
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
	float GetHP() { return curHp; }

private:

	void SetAnimation();
	void SetState(State state);
	void Move();

	void beginAttack();
	void Inhale();
	void FireBallAttack();
	void BreathAttack();

	void beginTakeoff();
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
	Vector3* tempRot;

	UINT nodeIndex = 0;

	float moveSpeed = 500;
	float rotSpeed = 0.25;
	float altitude = 0.0f;
	float deceleration = 5; //����

	bool isAscending = false;

	Vector3 velocity;

	vector<map<float, Event>> totalEvent;
	vector<map<float, Event>::iterator> eventIters;

	float maxHp = 3000.0f;
	float curHp = 3000.0f;


};

