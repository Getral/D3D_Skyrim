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
	void SetEvent(int clip, Event event, float timeRatio);
	void Move();


	void FireAttack();

	void EndTakeoff();
	void EndHit();
	void EndAttack();
	void EndBreath();

	void Patterns();



	State curState = IDLE;
	CapsuleCollider* alduinCollider;
	SphereCollider* collider_F;
	SphereCollider* collider_R;
	SphereCollider* collider_L;
	SphereCollider* collider_B;
	Transform* transform;
	Player* target;

	float moveSpeed = 500;
	float rotSpeed = 0.5;
	float deceleration = 5; //����

	Vector3 velocity;
	Vector3 targetPos;

	vector<map<float, Event>> totalEvent;
	vector<map<float, Event>::iterator> eventIters;

	float maxHp = 3000.0f;
	float curHp = 3000.0f;




};

