#include "Framework.h"

Player::Player()
	: ModelAnimator("male_dragonbone")
{
	ModelAnimator::Scale() *= 0.001;

	ReadClip("male_1hm_idle");
	ReadClip("male_jump");
	ReadClip("male_1hm_stagger");
	ReadClip("male_1hm_stagger_medium");
	ReadClip("male_1hm_stagger_large");
	ReadClip("male_1hm_stagger_largest");
	ReadClip("male_1hm_block_hit_shield");
	ReadClip("male_1hm_walk_forward");
	ReadClip("male_1hm_walk_forward_l");
	ReadClip("male_1hm_walk_forward_r");
	ReadClip("male_1hm_walk_backward");
	ReadClip("male_1hm_walk_backward_l");
	ReadClip("male_1hm_walk_backward_r");
	ReadClip("male_1hm_walk_left");
	ReadClip("male_1hm_walk_right");
	ReadClip("male_1hm_run_forward");
	ReadClip("male_1hm_run_forward_l");
	ReadClip("male_1hm_run_forward_r");
	ReadClip("male_1hm_run_backward");
	ReadClip("male_1hm_run_backward_l");
	ReadClip("male_1hm_run_backward_r");
	ReadClip("male_1hm_run_left");
	ReadClip("male_1hm_run_right");
	ReadClip("male_crouch_idle");
	ReadClip("male_crouch_walk_forward");
	ReadClip("male_crouch_walk_forward_l");
	ReadClip("male_crouch_walk_forward_r");
	ReadClip("male_crouch_walk_backward");
	ReadClip("male_crouch_walk_backward_l");
	ReadClip("male_crouch_walk_backward_r");
	ReadClip("male_crouch_walk_left");
	ReadClip("male_crouch_walk_right");
	ReadClip("male_1hm_sneak_attack_right");
	ReadClip("male_1hm_sneak_attack_left");
	ReadClip("male_1hm_sneak_attack_power");
	ReadClip("male_1hm_attack_right");
	ReadClip("male_1hm_attack_left");
	ReadClip("male_1hm_attack_power");
	ReadClip("male_1hm_block_shield");
	ReadClip("male_1hm_block_bash_intro_shield");
	ReadClip("male_1hm_block_bash_shield");
	ReadClip("male_1hm_walk_forward_attack");
	ReadClip("male_1hm_walk_backward_attack");
	ReadClip("male_1hm_walk_left_attack");
	ReadClip("male_1hm_walk_right_attack");
	ReadClip("male_1hm_run_forward_attack");
	ReadClip("male_1hm_run_backward_attack");
	ReadClip("male_1hm_run_left_attack");
	ReadClip("male_1hm_run_right_attack");
	ReadClip("male_2hm_idle");
	ReadClip("male_2hm_block_idle");
	ReadClip("male_2hm_attack_left");
	ReadClip("male_2hm_attack_right");
	ReadClip("male_2hm_attack_power");
	ReadClip("male_2hm_stagger");
	ReadClip("male_2hm_stagger_medium");
	ReadClip("male_2hm_stagger_large");
	ReadClip("male_2hm_stagger_largest");
	ReadClip("male_2hm_block_hit");
	ReadClip("male_2hm_walk_forward");
	ReadClip("male_2hm_walk_forward_l");
	ReadClip("male_2hm_walk_forward_r");
	ReadClip("male_2hm_walk_backward");
	ReadClip("male_2hm_walk_backward_l");
	ReadClip("male_2hm_walk_backward_r");
	ReadClip("male_2hm_walk_left");
	ReadClip("male_2hm_walk_right");
	ReadClip("male_2hm_run_forward");
	ReadClip("male_2hm_run_forward_l");
	ReadClip("male_2hm_run_forward_r");
	ReadClip("male_2hm_run_backward");
	ReadClip("male_2hm_run_backward_l");
	ReadClip("male_2hm_run_backward_r");
	ReadClip("male_2hm_run_left");
	ReadClip("male_2hm_run_right");
	ReadClip("male_2hm_walk_forward_attack");
	ReadClip("male_2hm_walk_backward_attack");
	ReadClip("male_2hm_walk_left_attack");
	ReadClip("male_2hm_walk_right_attack");
	ReadClip("male_2hm_run_forward_attack");
	ReadClip("male_2hm_run_backward_attack");
	ReadClip("male_2hm_run_left_attack");
	ReadClip("male_2hm_run_right_attack");
	ReadClip("male_bow_idle");
	ReadClip("male_bow_draw_intro");
	ReadClip("male_bow_draw_idle");
	ReadClip("male_bow_release");
	ReadClip("male_bow_walk_forward");
	ReadClip("male_bow_walk_forward_l");
	ReadClip("male_bow_walk_forward_r");
	ReadClip("male_bow_walk_backward");
	ReadClip("male_bow_walk_backward_l");
	ReadClip("male_bow_walk_backward_r");
	ReadClip("male_bow_walk_left");
	ReadClip("male_bow_walk_right");
	ReadClip("male_bow_run_forward");
	ReadClip("male_bow_run_forward_l");
	ReadClip("male_bow_run_forward_r");
	ReadClip("male_bow_run_backward");
	ReadClip("male_bow_run_backward_l");
	ReadClip("male_bow_run_backward_r");
	ReadClip("male_bow_run_left");
	ReadClip("male_bow_run_right");
	ReadClip("male_bowdrawn_walk_forward");
	ReadClip("male_bowdrawn_walk_forward_l");
	ReadClip("male_bowdrawn_walk_forward_r");
	ReadClip("male_bowdrawn_walk_backward");
	ReadClip("male_bowdrawn_walk_backward_l");
	ReadClip("male_bowdrawn_walk_backward_r");
	ReadClip("male_bowdrawn_walk_left");
	ReadClip("male_bowdrawn_walk_right");
	//ReadClip("male_death");

	//ModelAnimator::Rot().y = XM_PI;

	collider = new CapsuleCollider(3, 5);
	collider->Scale() *= 1000;
	collider->Pos().y = 6000;
	collider->SetParent(this);

	SpawnManager::Get()->SetPlayerData(this);

	action = (ACTION)frameBuffer->Get().cur.clip;

	//dragonbonehelmet = new Dragonbonehelmet();
	//dragonbonehelmet->Load();
	//head = new Transform();
	//dragonbonehelmet->SetParent(head);
	//dragonbonecuirassplate = new Dragonbonecuirassplate();
	//dragonbonecuirassplate->Load();
	//armor = new IronArmor();
	//armor->Load();
	//body = new Transform();
	//armor->SetParent(body);
	//dragonbonegauntlets = new Dragonbonegauntlets();
	//dragonbonegauntlets->Load();
	//hands = new Transform();
	//dragonbonegauntlets->SetParent(hands);
	//dragonboneboots = new Dragonboneboots();
	//dragonboneboots->Load();
	//foot = new Transform();
	//dragonboneboots->SetParent(foot);
	//dragonboneshield = new Dragonboneshield();
	//dragonboneshield->Load();
	//leftHand = new Transform();
	//dragonboneshield->SetParent(leftHand);

	bladeSword = new BladeSword();
	bladeSword->Load();

	rightHand = new Transform();
	bladeSword->SetParent(rightHand);

	shield = new Shield();
	shield->Load();

	leftHand = new Transform();
	shield->SetParent(leftHand);

	GetClip(OHM_ATK_R)->SetEvent(bind(&Player::WeaponCollider, this), 0.1f);
	GetClip(OHM_ATK_L)->SetEvent(bind(&Player::WeaponCollider, this), 0.1f);
	GetClip(OHM_ATK_P)->SetEvent(bind(&Player::WeaponCollider, this), 0.1f);
	GetClip(OHM_ATK_R)->SetEvent(bind(&Player::EndAttack, this), 0.7f);
	GetClip(OHM_ATK_L)->SetEvent(bind(&Player::EndAttack, this), 0.7f);
	GetClip(OHM_ATK_P)->SetEvent(bind(&Player::EndAttack, this), 0.7f);
	GetClip(OHM_HIT_LIGHT)->SetEvent(bind(&Player::EndHit, this), 0.7f);
	GetClip(OHM_HIT_MEDIUM)->SetEvent(bind(&Player::EndHit, this), 0.7f);
	GetClip(OHM_HIT_LARGE)->SetEvent(bind(&Player::EndHit, this), 0.8f);
	GetClip(OHM_HIT_BLOCK)->SetEvent(bind(&Player::EndBlockHit, this), 0.5f);
	
	GetClip(OHM_HIT_LIGHT)->SetEvent(bind(&Player::SetInvincible, this), 0.0f);
	GetClip(OHM_HIT_MEDIUM)->SetEvent(bind(&Player::SetInvincible, this), 0.0f);
	GetClip(OHM_HIT_LARGE)->SetEvent(bind(&Player::SetInvincible, this), 0.0f);
	GetClip(OHM_HIT_BLOCK)->SetEvent(bind(&Player::SetInvincible, this), 0.0f);
}

Player::~Player()
{
	delete bladeSword;
	delete shield;
	//delete armor;
	//delete dragonboneboots;
	//delete dragonbonecuirassplate;
	//delete dragonbonegauntlets;
	//delete dragonbonehelmet;
	//delete dragonboneshield;
	delete collider;
	delete rightHand;
	delete leftHand;
	//delete head;
	//delete body;
	//delete foot;
	//delete hands;
}

void Player::Update()
{
	Control();
	GetHit();
	SetAnimation();

	ModelAnimator::Update();

	collider->UpdateWorld();
	rightHand->SetWorld(GetTransformByNode(79));
	bladeSword->Update();
	leftHand->SetWorld(GetTransformByNode(119));
	shield->Update();	

	if (isInvincible)
	{
		invincibleCount += DELTA;
		if (invincibleCount > 2.0f) EndInvincible();
	}

	//body->SetWorld(GetTransformByNode(nodeIndex1));
	//armor->Update();
	//leftHand->SetWorld(GetTransformByNode(119));
	//dragonboneshield->Update();
	//head->SetWorld(GetTransformByNode(nodeIndex1));
	//dragonbonehelmet->Update();
	//body->SetWorld(GetTransformByNode(nodeIndex2));
	//dragonbonecuirassplate->Update();
	//foot->SetWorld(GetTransformByNode(nodeIndex3));
	//dragonboneboots->Update();
	//hands->SetWorld(GetTransformByNode(nodeIndex4));
	//dragonbonegauntlets->Update();

	if (KEY_PRESS('H'))
		this->status.curstamina -= 10 * DELTA;
}

void Player::Render()
{
	ModelAnimator::Render();
	collider->Render();
	bladeSword->Render();
	shield->Render();
	//armor->Render();
	//dragonboneboots->Render();
	//dragonbonecuirassplate->Render();
	//dragonbonegauntlets->Render();
	//dragonbonehelmet->Render();
	//dragonboneshield->Render();

}

void Player::PostRender()
{
}

void Player::GUIRender()
{
	bladeSword->GUIRender();
	collider->GUIRender();
	ModelAnimator::GUIRender();
	ImGui::SliderInt("nodeIndex1", (int*)&nodeIndex1, 1, 200);
	ImGui::SliderInt("nodeIndex2", (int*)&nodeIndex2, 1, 200);
}

void Player::Control()
{
	Rotate();
	Move();
	Attack();
	Block();
}

void Player::Move()
{
	if (curAction == OHM_ATK_R || curAction == OHM_ATK_L || curAction == OHM_ATK_P)
		return;
	if (isBlock) return;
	if (isHit) return;
	if (!KEY_PRESS('W') && !KEY_PRESS('S') && !KEY_PRESS('A') && !KEY_PRESS('D')) velocity.z = 0.0f, velocity.x = 0.0f;

	bool isMoveZ = false;
	bool isMoveX = false;

	if (KEY_PRESS(VK_SHIFT)) //달리기
	{
		if (KEY_PRESS('W'))
		{
			velocity.z += DELTA * status.speed * 1.0f;
			isMoveZ = true;
		}
		if (KEY_UP('W'))
		{
			velocity.z = 0.0f;
		}
		if (KEY_PRESS('S'))
		{
			velocity.z -= DELTA * status.speed * 1.0f;
			isMoveZ = true;
		}
		if (KEY_UP('S'))
		{
			velocity.z = 0.0f;
		}
		if (KEY_PRESS('A'))
		{
			velocity.x -= DELTA * status.speed * 1.0f;
			isMoveX = true;
		}
		if (KEY_UP('A'))
		{
			velocity.x = 0.0f;
		}
		if (KEY_PRESS('D'))
		{
			velocity.x += DELTA * status.speed * 1.0f;
			isMoveX = true;
		}
		if (KEY_UP('D'))
		{
			velocity.x = 0.0f;
		}
	}

	else if (KEY_PRESS(VK_CONTROL)) //앉아서 이동
	{
		if (KEY_PRESS('W'))
		{
			velocity.z += DELTA * status.speed * 0.5f;
			isMoveZ = true;
		}
		if (KEY_UP('W'))
		{
			velocity.z = 0.0f;
		}
		if (KEY_PRESS('S'))
		{
			velocity.z -= DELTA * status.speed * 0.5f;
			isMoveZ = true;
		}
		if (KEY_UP('S'))
		{
			velocity.z = 0.0f;
		}
		if (KEY_PRESS('A'))
		{
			velocity.x -= DELTA * status.speed * 0.5f;
			isMoveX = true;
		}
		if (KEY_UP('A'))
		{
			velocity.x = 0.0f;
		}
		if (KEY_PRESS('D'))
		{
			velocity.x += DELTA * status.speed * 0.5f;
			isMoveX = true;
		}
		if (KEY_UP('D'))
		{
			velocity.x = 0.0f;
		}
	}

	else //걷기
	{
		if (KEY_PRESS('W'))
		{
			velocity.z += DELTA * status.speed * 0.7f;
			isMoveZ = true;
		}
		if (KEY_UP('W'))
		{
			velocity.z = 0.0f;
		}
		if (KEY_PRESS('S'))
		{
			velocity.z -= DELTA * status.speed * 0.7f;
			isMoveZ = true;
		}
		if (KEY_UP('S'))
		{
			velocity.z = 0.0f;
		}
		if (KEY_PRESS('A'))
		{
			velocity.x -= DELTA * status.speed * 0.7f;
			isMoveX = true;
		}
		if (KEY_UP('A'))
		{
			velocity.x = 0.0f;
		}
		if (KEY_PRESS('D'))
		{
			velocity.x += DELTA * status.speed * 0.7f;
			isMoveX = true;
		}
		if (KEY_UP('D'))
		{
			velocity.x = 0.0f;
		}
	}
		

	//방향을 구하고 정규화
	if (KEY_PRESS(VK_SHIFT))
	{
		if (velocity.Length() > status.speed * 1.0f) velocity = velocity.GetNormalized() * 5.0f;
	}
	else if (KEY_PRESS(VK_CONTROL))
	{
		if (velocity.Length() > status.speed * 0.5f) velocity = velocity.GetNormalized() * 2.5f;
	}
	else
	{
		if (velocity.Length() > status.speed * 0.7f) velocity = velocity.GetNormalized() * 3.5f;
	}

	if (!isMoveZ)
		velocity.z = Lerp(velocity.z, 0, deceleration * DELTA);

	if (!isMoveX)
		velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);

	Matrix rotY = XMMatrixRotationY(Rot().y);

	Vector3 direction = XMVector3TransformCoord(velocity, rotY);

	if (KEY_PRESS(VK_SHIFT))
	{
		Pos() += direction * status.speed * 1.0f * DELTA * -1;
	}
	else if (KEY_PRESS(VK_CONTROL))
	{
		Pos() += direction * status.speed * 0.5f * DELTA * -1;
	}
	else
	{
		Pos() += direction * status.speed * 0.7f * DELTA * -1;
	}
}

void Player::Jump()
{
}

void Player::Rotate()
{
	if (KEY_PRESS('Q'))
	{
		Rot().y -= DELTA * rotSpeed;
	}

	if (KEY_PRESS('E'))
	{
		Rot().y += DELTA * rotSpeed;
	}

}

void Player::Attack()
{
	if (curAction == OHM_ATK_R || curAction == OHM_ATK_L || curAction == OHM_ATK_P) return;
	if (isHit) return;

	if (KEY_PRESS(VK_LBUTTON))
	{
		attackCharge += DELTA;
	}
	if (KEY_UP(VK_LBUTTON))
	{
		if (attackCharge > 1.0f)
		{
			SetAction(OHM_ATK_P);
		}
		else
		{
			if (!isCombo)
			{
				SetAction(OHM_ATK_R);
				isCombo = true;
			}
			else
			{
				SetAction(OHM_ATK_L);
				isCombo = false;
			}
		}
		attackCharge = 0.0f;
	}
}

void Player::Block()
{
	if (curAction == OHM_ATK_R || curAction == OHM_ATK_L || curAction == OHM_ATK_P) return;
	if (isHit) return;

	if (KEY_DOWN(VK_RBUTTON))
	{
		SetAction(OHM_BLOCK);
		isBlock = true;
	}

	if (KEY_UP(VK_RBUTTON))
	{
		EndBlock();
	}
}

void Player::GetHit()
{
	if (isInvincible) return;

	if (isBlock)
	{
		if (KEY_DOWN('Z'))
		{
			SetAction(OHM_HIT_BLOCK);
			isHit = true;
		}
		if (KEY_DOWN('X'))
		{
			SetAction(OHM_HIT_BLOCK);
			isHit = true;
		}
		if (KEY_DOWN('C'))
		{
			SetAction(OHM_HIT_BLOCK);
			isHit = true;
		}
	}
	else
	{
		if (KEY_DOWN('Z'))
		{
			SetAction(OHM_HIT_LIGHT);
			isHit = true;
		}
		if (KEY_DOWN('X'))
		{
			SetAction(OHM_HIT_MEDIUM);
			isHit = true;
		}
		if (KEY_DOWN('C'))
		{
			SetAction(OHM_HIT_LARGE);
			isHit = true;
		}
	}
}

void Player::SetAnimation()
{
	if (curAction == OHM_ATK_R || curAction == OHM_ATK_L || curAction == OHM_ATK_P
		|| curAction == OHM_BLOCK || curAction == OHM_HIT_LIGHT || curAction == OHM_HIT_MEDIUM ||
		curAction == OHM_HIT_LARGE || curAction == OHM_HIT_BLOCK)
		return;


	if (velocity.z < -0.1f && velocity.x < -0.1f)
	{
		if (KEY_PRESS(VK_SHIFT)) SetAction(OHM_RUN_FL);
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_FL);
		else SetAction(OHM_WALK_FL);
	}

	else if (velocity.z > 0.1f && velocity.x > 0.1f)
	{
		if (KEY_PRESS(VK_SHIFT)) SetAction(OHM_RUN_FR);
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_FR);
		else SetAction(OHM_WALK_FR);
	}

	else if (velocity.z < -0.1f && velocity.x < -0.1f)
	{
		if (KEY_PRESS(VK_SHIFT)) SetAction(OHM_RUN_BL);
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_BL);
		else SetAction(OHM_WALK_BL);
	}

	else if (velocity.z < -0.1f && velocity.x > 0.1f)
	{
		if (KEY_PRESS(VK_SHIFT)) SetAction(OHM_RUN_BR);
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_BR);
		else SetAction(OHM_WALK_BR);
	}

	else if (velocity.z > 0.1f)
	{
		if (KEY_PRESS(VK_SHIFT)) SetAction(OHM_RUN_F);
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_F);
		else SetAction(OHM_WALK_F);
	}

	else if (velocity.z < -0.1f)
	{
		if (KEY_PRESS(VK_SHIFT)) SetAction(OHM_RUN_B);
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_B);
		else SetAction(OHM_WALK_B);
	}

	else if (velocity.x < -0.1f)
	{
		if (KEY_PRESS(VK_SHIFT)) SetAction(OHM_RUN_L);
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_L);
		else SetAction(OHM_WALK_L);
	}

	else if (velocity.x > 0.1f)
	{
		if (KEY_PRESS(VK_SHIFT)) SetAction(OHM_RUN_R);
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_R);
		else SetAction(OHM_WALK_R);
	}
	else if (KEY_PRESS(VK_CONTROL)) SetAction(CIDLE);

	else SetAction(OHM_IDLE);
}

void Player::SetAction(ACTION action)
{
	if (action == curAction) return;

	curAction = action;
	PlayClip((int)action);
}

void Player::WeaponCollider()
{
	if (!bladeSword->GetIsWeapon())
	{
		bladeSword->SetIsCollider(true);
	}
}

void Player::EndAttack()
{
	if (bladeSword->GetIsWeapon())
	{
	bladeSword->SetIsCollider(false);
	}
	SetAction(OHM_IDLE);
}

void Player::EndBlock()
{
	SetAction(OHM_IDLE);
	isBlock = false;
}

void Player::EndHit()
{
	SetAction(OHM_IDLE);
	isHit = false;
}

void Player::EndBlockHit()
{
	SetAction(OHM_BLOCK);
	isHit = false;
}

void Player::SetInvincible()
{
	isInvincible = true;	
}

void Player::EndInvincible()
{
	isInvincible = false;
	invincibleCount = 0.0f;
}
