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
		ATTACK_F, //����, (����) ����
		ATTACK_L, //���� �ֵθ��� ����
		ATTACK_R, //���� �ֵθ��� ������
		ATTACK_B, // ���� �ֵθ���
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
	float deceleration = 5; //����

	Vector3 velocity;
	Vector3 targetPos;

	float maxHp = 3000.0f;
	float curHp = 3000.0f;


};

