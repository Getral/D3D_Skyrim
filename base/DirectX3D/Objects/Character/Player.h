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
		float speed = 5;
	};

	enum ACTION
	{
		OHM_IDLE, JUMP, OHM_HIT_LIGHT, OHM_HIT_MEDIUM, OHM_HIT_LARGE, OHM_HIT_LARGEST, OHM_HIT_BLOCK,
		OHM_WALK_F, OHM_WALK_FL, OHM_WALK_FR, OHM_WALK_B, OHM_WALK_BL, OHM_WALK_BR, OHM_WALK_L, OHM_WALK_R,
		OHM_RUN_F, OHM_RUN_FL, OHM_RUN_FR, OHM_RUN_B, OHM_RUN_BL, OHM_RUN_BR, OHM_RUN_L, OHM_RUN_R,
		CIDLE, CMOVE_F, CMOVE_FL, CMOVE_FR, CMOVE_B, CMOVE_BL, CMOVE_BR, CMOVE_L, CMOVE_R,
		OHM_ATK_R, OHM_ATK_L, OHM_ATK_P,
		OHM_BLOCK, OHM_PARRY_START, OHM_PARRY, 
		OHM_RUN_BW_ATK, OHM_RUN_FW_ATK, OHM_RUN_L_ATK, OHM_RUN_R_ATK,

		THM_IDLE, THM_ATK_L
	};

public:

	Player();
	~Player();

	void Update();
	void Render();
	void PostRender();
	void GUIRender();

	Status GetStatus() { return status; }
	CapsuleCollider* GetCollier() { return collider; }
	bool GetIsHit() { return isHit; }


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

	ACTION curAction = OHM_IDLE;

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
	bool is1hm = false;
	bool is2hm = true;
	bool isbow = false;


	bool isTorch = false; // 나중에 횃불 추가하면 사용할 bool값
};

