#pragma once

class Player : public ModelAnimator
{
public:
	struct Status
	{
		float curHp = 100;
		float maxHp = 100;
		float curstamina = 100;
		float maxstamina = 100;
		float atk = 10;
		float def = 10;
		float speed = 5;
	};

	enum ACTION
	{
		IDLE, JUMP, HIT_LIGHT, HIT_MEDIUM, HIT_HEAVY, HIT_BLOCK,
		WALK_F, WALK_FL, WALK_FR, WALK_B, WALK_BL, WALK_BR, WALK_L, WALK_R,
		RUN_F, RUN_FL, RUN_FR, RUN_B, RUN_BL, RUN_BR, RUN_L, RUN_R,
		CIDLE, CMOVE_F, CMOVE_FL, CMOVE_FR, CMOVE_B, CMOVE_BL, CMOVE_BR, CMOVE_L, CMOVE_R,
		ATTACK_RIGHT, ATTACK_LEFT, ATTACK_HEAVY,
		BLOCK, PARRY_START, PARRY
	};

public:

	Player();
	~Player();

	void Update();
	void Render();
	void PostRender();
	void GUIRender();

	Status& GetStatus() { return status; }
	CapsuleCollider* GetCollier() { return collider; }
	BladeSword* GetSword() { return bladeSword; }
	bool GetIsHit() { return isHit; }
	ACTION GetAction() { return curAction; }


	void SetAction(ACTION action);
	void SetIsHit(bool value) { isHit = value; }

private:
	void Control();
	void Move();
	void Jump();
	void Rotate();
	void Attack();
	void Block();
	void GetHit();

	void SetAnimation();

	void WeaponCollider();
	void EndAttack();
	void EndBlock();
	void EndHit();
	void EndBlockHit();
	void SetInvincible();
	void EndInvincible();

protected:

	BladeSword* bladeSword;
	Shield* shield;

	//Dragonboneboots* dragonboneboots;
	//Dragonbonecuirassplate* dragonbonecuirassplate;
	//Dragonbonegauntlets* dragonbonegauntlets;
	//Dragonbonehelmet* dragonbonehelmet;
	//Dragonboneshield* dragonboneshield;
	//IronArmor* armor;

	Transform* rightHand;
	Transform* leftHand;
	//Transform* head;
	//Transform* body;
	//Transform* foot;
	//Transform* hands;


	Status status;

	CapsuleCollider* collider;

	ACTION action;

	ACTION curAction = IDLE;

	float rotSpeed = 1;
	float deceleration = 10;

	UINT nodeIndex1 = 1;
	UINT nodeIndex2 = 1;

	Vector3 velocity;

	float jumpVelocity = 0;
	float jumpForce = 0.5f;
	float gravityMult = 0.5f;
	float attackCharge = 0.0f;
	float invincibleCount = 0.0f; // 무적시간 재는 변수

	bool isInvincible = false; //무적인가?
	bool isJump = false;
	bool isBlock = false;
	bool isHit = false;
	bool isCombo = false;

	bool isTorch = false; // 나중에 횃불 추가하면 사용할 bool값
};

