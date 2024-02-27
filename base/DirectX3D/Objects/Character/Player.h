#pragma once

class Player : public ModelAnimator
{
public:
	struct Status
	{
		float curHp = 100;
		float maxHp = 100;
		float atk = 10;
		float speed = 10;
	};

private:
	enum ACTION
	{
		IDLE, /*JUMP, HIT_LIGHT, HIT_HEAVY,*/ //HIT_BLOCK,
		WALK_F, WALK_FL, WALK_FR, WALK_B, WALK_BL, WALK_BR, WALK_L, WALK_R,
		RUN_F, RUN_FL, RUN_FR, RUN_B, RUN_BL, RUN_BR, RUN_L, RUN_R,
		CIDLE, CMOVE_F, CMOVE_FL, CMOVE_FR, CMOVE_B, CMOVE_BL, CMOVE_BR, CMOVE_L, CMOVE_R,
		ATTACK_RIGHT, ATTACK_LEFT, ATTACK_HEAVY,
		BLOCK
	};

public:

	Player();
	~Player();

	void Update();
	void Render();
	void PostRender();
	void GUIRender();

	Transform* GetTransform() { return transform; }
	Status GetStatus() { return status; }
	CapsuleCollider* GetCollier() { return collider; }

private:
	void Control();
	void Move();
	void Rotate();
	void Attack();
	void SetAnimation();

	void SetAction(ACTION action);

	void Attack1hm();
	void Attack2hm();
	void Attackh2h();

	void EndAttack();

protected:
	Transform* transform;

	Status status;

	CapsuleCollider* collider;

	ACTION action;

	ACTION curAction = IDLE;

	float moveSpeed = 0;
	float runSpeed = 0;
	float coruchSpeed = 0;
	float rotSpeed = 1;
	float deceleration = 0;

	Vector3 velocity;

	float jumpVelocity = 0;
	float jumpForce = 0.5f;
	float gravityMult = 0.5f;
	bool isJump = false;

	bool isTorch = false; // 나중에 횃불 추가하면 사용할 bool값
};

