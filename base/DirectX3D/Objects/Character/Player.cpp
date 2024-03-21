#include "Framework.h"

Player::Player()
	: ModelAnimator("male_dragonbone")
{
	ClientToScreen(hWnd, &clientCenterPos);
	SetCursorPos(clientCenterPos.x, clientCenterPos.y);

	ModelAnimator::Scale() *= 0.0001f;

	Pos().x = 200.0f;
	Pos().y = 500.0f;
	Pos().z = 200.0f;

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
	ReadClip("male_1hm_equip");
	ReadClip("male_1hm_unequip");
	ReadClip("male_2hm_equip");
	ReadClip("male_2hm_unequip");
	ReadClip("male_bow_equip");
	ReadClip("male_bow_unequip");
	//ReadClip("male_death");

	collider = new CapsuleCollider(2, 6);
	collider->Scale() *= 1000;
	collider->Pos().y = 5000;
	collider->Pos().z = -600;
	collider->SetParent(this);

	CAM->Rot().x = 0;

	SpawnManager::Get()->SetPlayerData(this);
	TerrainManager::Get()->SetPlayerData(this);

	action = (ACTION)frameBuffer->Get().cur.clip;

	bladeSword = new BladeSword();
	bladeSword->Load();

	rightHand = new Transform();
	bladeSword->SetParent(rightHand);

	shield = new Shield();
	shield->Load();

	leftHand = new Transform();
	shield->SetParent(leftHand);

	headCollider = new CapsuleCollider(10);

	head = new Transform();
	headCollider->SetParent(head);

	GetClip(OHM_ATK_R)->SetEvent(bind(&Player::WeaponCollider, this), 0.1f);
	GetClip(OHM_ATK_L)->SetEvent(bind(&Player::WeaponCollider, this), 0.1f);
	GetClip(OHM_ATK_P)->SetEvent(bind(&Player::WeaponCollider, this), 0.1f);
	GetClip(OHM_ATK_R)->SetEvent(bind(&Player::EndAttack, this), 0.7f);
	GetClip(OHM_ATK_L)->SetEvent(bind(&Player::EndAttack, this), 0.7f);
	GetClip(OHM_ATK_P)->SetEvent(bind(&Player::EndAttack, this), 0.7f);

	GetClip(OHM_WALK_FW_ATK)->SetEvent(bind(&Player::WeaponCollider, this), 0.1f);
	GetClip(OHM_WALK_BW_ATK)->SetEvent(bind(&Player::WeaponCollider, this), 0.1f);
	GetClip(OHM_WALK_L_ATK)->SetEvent(bind(&Player::WeaponCollider, this), 0.1f);
	GetClip(OHM_WALK_R_ATK)->SetEvent(bind(&Player::WeaponCollider, this), 0.1f);
	GetClip(OHM_RUN_FW_ATK)->SetEvent(bind(&Player::WeaponCollider, this), 0.1f);
	GetClip(OHM_RUN_BW_ATK)->SetEvent(bind(&Player::WeaponCollider, this), 0.1f);
	GetClip(OHM_RUN_L_ATK)->SetEvent(bind(&Player::WeaponCollider, this), 0.1f);
	GetClip(OHM_RUN_R_ATK)->SetEvent(bind(&Player::WeaponCollider, this), 0.1f);
	GetClip(OHM_CATK_R)->SetEvent(bind(&Player::WeaponCollider, this), 0.1f);
	GetClip(OHM_CATK_L)->SetEvent(bind(&Player::WeaponCollider, this), 0.1f);
	GetClip(OHM_CATK_P)->SetEvent(bind(&Player::WeaponCollider, this), 0.1f);

	GetClip(OHM_WALK_FW_ATK)->SetEvent(bind(&Player::EndAttack, this), 0.7f);
	GetClip(OHM_WALK_BW_ATK)->SetEvent(bind(&Player::EndAttack, this), 0.7f);
	GetClip(OHM_WALK_L_ATK)->SetEvent(bind(&Player::EndAttack, this), 0.7f);
	GetClip(OHM_WALK_R_ATK)->SetEvent(bind(&Player::EndAttack, this), 0.7f);
	GetClip(OHM_RUN_FW_ATK)->SetEvent(bind(&Player::EndAttack, this), 0.7f);
	GetClip(OHM_RUN_BW_ATK)->SetEvent(bind(&Player::EndAttack, this), 0.7f);
	GetClip(OHM_RUN_L_ATK)->SetEvent(bind(&Player::EndAttack, this), 0.7f);
	GetClip(OHM_RUN_R_ATK)->SetEvent(bind(&Player::EndAttack, this), 0.7f);
	GetClip(OHM_CATK_R)->SetEvent(bind(&Player::EndAttack, this), 0.7f);
	GetClip(OHM_CATK_L)->SetEvent(bind(&Player::EndAttack, this), 0.7f);
	GetClip(OHM_CATK_P)->SetEvent(bind(&Player::EndAttack, this), 0.7f);

	GetClip(THM_ATK_R)->SetEvent(bind(&Player::WeaponCollider, this), 0.2f);
	GetClip(THM_ATK_L)->SetEvent(bind(&Player::WeaponCollider, this), 0.2f);
	GetClip(THM_ATK_P)->SetEvent(bind(&Player::WeaponCollider, this), 0.2f);
	GetClip(THM_ATK_R)->SetEvent(bind(&Player::EndAttack, this), 0.8f);
	GetClip(THM_ATK_L)->SetEvent(bind(&Player::EndAttack, this), 0.8f);
	GetClip(THM_ATK_P)->SetEvent(bind(&Player::EndAttack, this), 0.8f);

	GetClip(THM_WALK_FW_ATK)->SetEvent(bind(&Player::WeaponCollider, this), 0.2f);
	GetClip(THM_WALK_BW_ATK)->SetEvent(bind(&Player::WeaponCollider, this), 0.2f);
	GetClip(THM_WALK_L_ATK)->SetEvent(bind(&Player::WeaponCollider, this),  0.2f);
	GetClip(THM_WALK_R_ATK)->SetEvent(bind(&Player::WeaponCollider, this),  0.2f);
	GetClip(THM_RUN_FW_ATK)->SetEvent(bind(&Player::WeaponCollider, this),  0.2f);
	GetClip(THM_RUN_BW_ATK)->SetEvent(bind(&Player::WeaponCollider, this),  0.2f);
	GetClip(THM_RUN_L_ATK)->SetEvent(bind(&Player::WeaponCollider, this),   0.2f);
	GetClip(THM_RUN_R_ATK)->SetEvent(bind(&Player::WeaponCollider, this),   0.2f);

	GetClip(THM_WALK_FW_ATK)->SetEvent(bind(&Player::EndAttack, this), 0.8f);
	GetClip(THM_WALK_BW_ATK)->SetEvent(bind(&Player::EndAttack, this), 0.8f);
	GetClip(THM_WALK_R_ATK)->SetEvent(bind(&Player::EndAttack, this), 0.8f);
	GetClip(THM_WALK_L_ATK)->SetEvent(bind(&Player::EndAttack, this), 0.8f);
	GetClip(THM_RUN_FW_ATK)->SetEvent(bind(&Player::EndAttack, this), 0.8f);
	GetClip(THM_RUN_BW_ATK)->SetEvent(bind(&Player::EndAttack, this), 0.8f);
	GetClip(THM_RUN_L_ATK)->SetEvent(bind(&Player::EndAttack, this), 0.8f);
	GetClip(THM_RUN_R_ATK)->SetEvent(bind(&Player::EndAttack, this), 0.8f);

	GetClip(OHM_HIT_LIGHT)->SetEvent(bind(&Player::EndHit, this), 0.7f);
	GetClip(OHM_HIT_MEDIUM)->SetEvent(bind(&Player::EndHit, this), 0.7f);
	GetClip(OHM_HIT_LARGE)->SetEvent(bind(&Player::EndHit, this), 0.8f);
	GetClip(OHM_HIT_LARGEST)->SetEvent(bind(&Player::EndHit, this), 0.9f);
	GetClip(OHM_HIT_BLOCK)->SetEvent(bind(&Player::EndBlockHit, this), 0.5f);
	
	GetClip(OHM_HIT_LIGHT)->SetEvent(bind(&Player::SetInvincible, this), 0.0f);
	GetClip(OHM_HIT_MEDIUM)->SetEvent(bind(&Player::SetInvincible, this), 0.0f);
	GetClip(OHM_HIT_LARGE)->SetEvent(bind(&Player::SetInvincible, this), 0.0f);
	GetClip(OHM_HIT_LARGEST)->SetEvent(bind(&Player::SetInvincible, this), 0.0f);
	GetClip(OHM_HIT_BLOCK)->SetEvent(bind(&Player::SetInvincible, this), 0.0f);

	GetClip(THM_HIT_LIGHT)->SetEvent(bind(&Player::EndHit, this), 0.7f);
	GetClip(THM_HIT_MEDIUM)->SetEvent(bind(&Player::EndHit, this), 0.7f);
	GetClip(THM_HIT_LARGE)->SetEvent(bind(&Player::EndHit, this), 0.8f);
	GetClip(THM_HIT_LARGEST)->SetEvent(bind(&Player::EndHit, this), 0.9f);
	GetClip(THM_HIT_BLOCK)->SetEvent(bind(&Player::EndBlockHit, this), 0.5f);
	
	GetClip(THM_HIT_LIGHT)->SetEvent(bind(&Player::SetInvincible, this), 0.0f);
	GetClip(THM_HIT_MEDIUM)->SetEvent(bind(&Player::SetInvincible, this), 0.0f);
	GetClip(THM_HIT_LARGE)->SetEvent(bind(&Player::SetInvincible, this), 0.0f);
	GetClip(THM_HIT_LARGEST)->SetEvent(bind(&Player::SetInvincible, this), 0.0f);
	GetClip(THM_HIT_BLOCK)->SetEvent(bind(&Player::SetInvincible, this), 0.0f);

	GetClip(BOW_DRAW_INTRO)->SetEvent(bind(&Player::SetBowDrawn, this), 0.7f);
	GetClip(BOW_RELEASE)->SetEvent(bind(&Player::ShootArrow, this), 0.1f);
	GetClip(BOW_RELEASE)->SetEvent(bind(&Player::EndBowDrawn, this), 0.5f);

	GetClip(OHM_EQUIP)->SetEvent(bind(&Player::Set1hmIdle, this), 0.7f);
	GetClip(THM_EQUIP)->SetEvent(bind(&Player::Set2hmIdle, this), 0.7f);
	GetClip(BOW_EQUIP)->SetEvent(bind(&Player::SetbowIdle, this), 0.7f);

	prevMousePos = mousePos;
}

Player::~Player()
{
	delete bladeSword;
	delete shield;
	delete collider;
	delete rightHand;
	delete leftHand;
}

void Player::Update()
{
	Control();
	GetHit();
	SetAnimation();

	ModelAnimator::Update();

	collider->UpdateWorld();
	rightHand->SetWorld(GetTransformByNode(82));
	bladeSword->Update();
	leftHand->SetWorld(GetTransformByNode(119));
	shield->Update();	

	headCollider->UpdateWorld();
	head->SetWorld(GetTransformByNode(48));


	if (isInvincible)
	{
		invincibleCount += DELTA;
		if (invincibleCount > 1.0f) EndInvincible();
	}

	if (KEY_PRESS('H'))
		this->status.curstamina -= 10 * DELTA;
}

void Player::Render()
{
	ModelAnimator::Render();
	collider->Render();
	bladeSword->Render();
	//shield->Render();

	headCollider->Render();
}

void Player::PostRender()
{
}

void Player::GUIRender()
{
	bladeSword->GUIRender();
	collider->GUIRender();
	ModelAnimator::GUIRender();
	ImGui::Text("Win_width : %d", clientCenterPos.x);
	ImGui::Text("Win_height : %d", clientCenterPos.y);
	ImGui::SliderInt("nodeIndex1", (int*)&nodeIndex1, 1, 200);
	ImGui::SliderInt("nodeIndex2", (int*)&nodeIndex2, 1, 200);
}

void Player::Control()
{
	Rotate();
	Jump();
	Move();
	Attack();
	Block();
	WeaponChange();
}

void Player::Move()
{
	if (curAction == OHM_ATK_R || curAction == OHM_ATK_L || curAction == OHM_ATK_P ||
		curAction == THM_ATK_R || curAction == THM_ATK_L || curAction == THM_ATK_P ||
		curAction == OHM_CATK_R || curAction == OHM_CATK_L || curAction == OHM_CATK_P ||
		curAction == BOW_DRAW_INTRO || curAction == BOW_RELEASE)
		return;
	if (curAction == OHM_EQUIP || curAction == OHM_UNEQUIP || curAction == THM_EQUIP ||
		curAction == THM_UNEQUIP || curAction == BOW_EQUIP || curAction == BOW_UNEQUIP)
		return;
	if (isBlock) return;
	//if (isHit) return;
	if (!KEY_PRESS('W') && !KEY_PRESS('S') && !KEY_PRESS('A') && !KEY_PRESS('D')) velocity.z = 0.0f, velocity.x = 0.0f;

	bool isMoveZ = false;
	bool isMoveX = false;

	if (KEY_PRESS(VK_SHIFT) && !isbowdrawn) //달리기
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

	else if (KEY_PRESS(VK_CONTROL) && !isbowdrawn) //앉아서 이동
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
	if (KEY_PRESS(VK_SHIFT) && !isbowdrawn)
	{
		if (velocity.Length() > status.speed * 1.0f) velocity = velocity.GetNormalized() * 5.0f;
	}
	else if (KEY_PRESS(VK_CONTROL) && !isbowdrawn)
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

	if (KEY_PRESS(VK_SHIFT) && !isbowdrawn)
	{
		Pos() += direction * status.speed * 1.0f * DELTA * -1;
	}
	else if (KEY_PRESS(VK_CONTROL) && !isbowdrawn)
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
	if (isJump)
	{
		Pos().y += gravity * DELTA;
	}

	if (isJump) return;

	if (KEY_DOWN(VK_SPACE))
	{
		isJump = true;
	}
}

void Player::Rotate()
{
	//Vector3 delta = mousePos - Vector3(clientCenterPos.x, clientCenterPos.y);
	//SetCursorPos(clientCenterPos.x, clientCenterPos.y);		

	Vector3 delta = mousePos - prevMousePos; // 가장 최근 마우스 위치에서 현재까지 움직인 마우스의 변화량 구하기
	prevMousePos = mousePos;

	Rot().y += delta.x * rotSpeed * DELTA; // 캐릭터 좌우회전 (추적 중이라 카메라도 따라갈 것)
	//Rot().x -= delta.y * rotSpeed * DELTA; // 카메라 상하회전

	CAM->Rot().x -= delta.y * rotSpeed * DELTA;
	//Rot().y = CAM->Rot().y;
	//Rot().x = CAM->Rot().x;


	if (KEY_DOWN(VK_MBUTTON))
	{
		CAM->Rot().x = 0;
	}


	//if (KEY_PRESS('Q'))
	//{
	//	Rot().y -= DELTA * rotSpeed;
	//}

	//if (KEY_PRESS('E'))
	//{
	//	Rot().y += DELTA * rotSpeed;
	//}

}

void Player::Attack()
{
	if (curAction == OHM_ATK_R || curAction == OHM_ATK_L || curAction == OHM_ATK_P || 
		curAction == THM_ATK_R || curAction == THM_ATK_L || curAction == THM_ATK_P || 
		curAction == OHM_WALK_FW_ATK || curAction == OHM_WALK_BW_ATK || curAction == OHM_WALK_L_ATK ||
		curAction == OHM_WALK_R_ATK || curAction == OHM_RUN_FW_ATK || curAction == OHM_RUN_BW_ATK ||
		curAction == OHM_RUN_L_ATK || curAction == OHM_RUN_R_ATK || curAction == OHM_CATK_R ||
		curAction == OHM_CATK_L || curAction == OHM_CATK_P || curAction == THM_WALK_FW_ATK ||
		curAction == THM_WALK_BW_ATK || curAction == THM_WALK_L_ATK || curAction == THM_WALK_R_ATK ||
		curAction == THM_RUN_FW_ATK || curAction == THM_RUN_BW_ATK || curAction == THM_RUN_L_ATK ||
		curAction == THM_RUN_R_ATK || curAction == BOW_RELEASE) return;
	if (curAction == OHM_EQUIP || curAction == OHM_UNEQUIP || curAction == THM_EQUIP ||
		curAction == THM_UNEQUIP || curAction == BOW_EQUIP || curAction == BOW_UNEQUIP)
		return;
	if (isBlock) return;
	if (isHit) return;

	if (is1hm)
	{
		if (velocity.z < -0.1f && velocity.x < -0.1f || 
			velocity.z > 0.1f && velocity.x > 0.1f || velocity.z > 0.1f && !KEY_PRESS(VK_CONTROL))
		{
			if (KEY_PRESS(VK_SHIFT))
			{
				if (KEY_PRESS(VK_LBUTTON))
				{
					attackCharge += DELTA;
				}
				if (KEY_UP(VK_LBUTTON))
				{
					SetAction(OHM_RUN_FW_ATK);
					attackCharge = 0.0f;
				}
			}
			else 
			{
				if (KEY_PRESS(VK_LBUTTON))
				{
					attackCharge += DELTA;
				}
				if (KEY_UP(VK_LBUTTON))
				{
					SetAction(OHM_WALK_FW_ATK);
					attackCharge = 0.0f;
				}
			}
		}

		else if (velocity.z < -0.1f && velocity.x < -0.1f || 
			velocity.z < -0.1f && velocity.x > 0.1f || velocity.z < -0.1f && !KEY_PRESS(VK_CONTROL))
		{
			if (KEY_PRESS(VK_SHIFT))
			{
				if (KEY_PRESS(VK_LBUTTON))
				{
					attackCharge += DELTA;
				}
				if (KEY_UP(VK_LBUTTON))
				{
					SetAction(OHM_RUN_BW_ATK);
					attackCharge = 0.0f;
				}
			}
			else
			{
				if (KEY_PRESS(VK_LBUTTON))
				{
					attackCharge += DELTA;
				}
				if (KEY_UP(VK_LBUTTON))
				{
					SetAction(OHM_WALK_BW_ATK);
					attackCharge = 0.0f;
				}
			}
		}
		else if (velocity.x < -0.1f && !KEY_PRESS(VK_CONTROL))
		{
			if (KEY_PRESS(VK_SHIFT))
			{
				if (KEY_PRESS(VK_LBUTTON))
				{
					attackCharge += DELTA;
				}
				if (KEY_UP(VK_LBUTTON))
				{
					SetAction(OHM_RUN_L_ATK);
					attackCharge = 0.0f;
				}
			}
			else
			{
				if (KEY_PRESS(VK_LBUTTON))
				{
					attackCharge += DELTA;
				}
				if (KEY_UP(VK_LBUTTON))
				{
					SetAction(OHM_WALK_L_ATK);
					attackCharge = 0.0f;
				}
			}
		}
		else if (velocity.x > 0.1f && !KEY_PRESS(VK_CONTROL))
		{
			if (KEY_PRESS(VK_SHIFT))
			{
				if (KEY_PRESS(VK_LBUTTON))
				{
					attackCharge += DELTA;
				}
				if (KEY_UP(VK_LBUTTON))
				{
					SetAction(OHM_RUN_R_ATK);
					attackCharge = 0.0f;
				}
			}
			else 
			{
				if (KEY_PRESS(VK_LBUTTON))
				{
					attackCharge += DELTA;
				}
				if (KEY_UP(VK_LBUTTON))
				{
					SetAction(OHM_WALK_R_ATK);
					attackCharge = 0.0f;
				}
			}
		}

		else if (KEY_PRESS(VK_CONTROL)) return;

		else 
		{
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
	}

	if (is2hm)
	{
		if (velocity.z < -0.1f && velocity.x < -0.1f ||
			velocity.z > 0.1f && velocity.x > 0.1f || velocity.z > 0.1f && !KEY_PRESS(VK_CONTROL))
		{
			if (KEY_PRESS(VK_SHIFT))
			{
				if (KEY_PRESS(VK_LBUTTON))
				{
					attackCharge += DELTA;
				}
				if (KEY_UP(VK_LBUTTON))
				{
					SetAction(THM_RUN_FW_ATK);
					attackCharge = 0.0f;
				}
			}
			else
			{
				if (KEY_PRESS(VK_LBUTTON))
				{
					attackCharge += DELTA;
				}
				if (KEY_UP(VK_LBUTTON))
				{
					SetAction(THM_WALK_FW_ATK);
					attackCharge = 0.0f;
				}
			}
		}

		else if (velocity.z < -0.1f && velocity.x < -0.1f ||
			velocity.z < -0.1f && velocity.x > 0.1f || velocity.z < -0.1f && !KEY_PRESS(VK_CONTROL))
		{
			if (KEY_PRESS(VK_SHIFT))
			{
				if (KEY_PRESS(VK_LBUTTON))
				{
					attackCharge += DELTA;
				}
				if (KEY_UP(VK_LBUTTON))
				{
					SetAction(THM_RUN_BW_ATK);
					attackCharge = 0.0f;
				}
			}
			else
			{
				if (KEY_PRESS(VK_LBUTTON))
				{
					attackCharge += DELTA;
				}
				if (KEY_UP(VK_LBUTTON))
				{
					SetAction(THM_WALK_BW_ATK);
					attackCharge = 0.0f;
				}
			}
		}
		else if (velocity.x < -0.1f && !KEY_PRESS(VK_CONTROL))
		{
			if (KEY_PRESS(VK_SHIFT))
			{
				if (KEY_PRESS(VK_LBUTTON))
				{
					attackCharge += DELTA;
				}
				if (KEY_UP(VK_LBUTTON))
				{
					SetAction(THM_RUN_L_ATK);
					attackCharge = 0.0f;
				}
			}
			else
			{
				if (KEY_PRESS(VK_LBUTTON))
				{
					attackCharge += DELTA;
				}
				if (KEY_UP(VK_LBUTTON))
				{
					SetAction(THM_WALK_L_ATK);
					attackCharge = 0.0f;
				}
			}
		}
		else if (velocity.x > 0.1f && !KEY_PRESS(VK_CONTROL))
		{
			if (KEY_PRESS(VK_SHIFT))
			{
				if (KEY_PRESS(VK_LBUTTON))
				{
					attackCharge += DELTA;
				}
				if (KEY_UP(VK_LBUTTON))
				{
					SetAction(THM_RUN_R_ATK);
					attackCharge = 0.0f;
				}
			}
			else
			{
				if (KEY_PRESS(VK_LBUTTON))
				{
					attackCharge += DELTA;
				}
				if (KEY_UP(VK_LBUTTON))
				{
					SetAction(THM_WALK_R_ATK);
					attackCharge = 0.0f;
				}
			}
		}

		else
		{
			if (KEY_PRESS(VK_LBUTTON))
			{
				attackCharge += DELTA;
			}
			if (KEY_UP(VK_LBUTTON))
			{
				if (attackCharge > 1.0f)
				{
					SetAction(THM_ATK_P);
				}
				else
				{
					if (!isCombo)
					{
						SetAction(THM_ATK_R);
						isCombo = true;
					}
					else
					{
						SetAction(THM_ATK_L);
						isCombo = false;
					}
				}
				attackCharge = 0.0f;
			}
		}
	}

	if (isbow)
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			SetAction(BOW_DRAW_INTRO);
		}
		if (KEY_PRESS(VK_LBUTTON))
		{
			attackCharge += DELTA;
			if (attackCharge > 1.0f)
			{
				isbowdrawn = true;
			}
		}
		if (KEY_UP(VK_LBUTTON))
		{
			if (attackCharge > 1.0f)
			{
				SetAction(BOW_RELEASE);
			}
			else
			{
				SetAction(BOW_IDLE);
			}
			isbowdrawn = false;
			attackCharge = 0.0f;
		}
	}

	
}

void Player::Block()
{
	if (curAction == OHM_ATK_R || curAction == OHM_ATK_L || curAction == OHM_ATK_P) return;
	if (isbow) return;
	if (isHit) return;

	if (is1hm)
	{
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

	if (is2hm)
	{
		if (KEY_DOWN(VK_RBUTTON))
		{
			SetAction(THM_BLOCK);
			isBlock = true;
		}

		if (KEY_UP(VK_RBUTTON))
		{
			EndBlock();
		}
	}

}

void Player::GetHit()
{
	if (!isHit) return;
	if (isInvincible) return;
	if (isbow) return;

	if (is1hm)
	{
		if (isBlock)
		{			
				SetAction(OHM_HIT_BLOCK);
		}
		else
		{
				SetAction(OHM_HIT_LIGHT);
		}
	}

	if (is2hm)
	{
		if (isBlock)
		{
				SetAction(THM_HIT_BLOCK);
		}
		else
		{
				SetAction(THM_HIT_LIGHT);
		}
	}
	
}

void Player::WeaponChange()
{
	if (curAction != OHM_IDLE && curAction != THM_IDLE && curAction != BOW_IDLE) return;
	if (curAction == OHM_EQUIP || curAction == OHM_UNEQUIP || curAction == THM_EQUIP ||
		curAction == THM_UNEQUIP || curAction == BOW_EQUIP || curAction == BOW_UNEQUIP)
		return;
	if (KEY_PRESS(VK_CONTROL)) return;

	if (is1hm)
	{
		if (KEY_DOWN('2'))
		{
			GetClip(OHM_UNEQUIP)->SetEvent(bind(&Player::Change2hm, this), 0.7f, true);
			is1hm = false;
			is2hm = true;
			SetAction(OHM_UNEQUIP);
		}
		if (KEY_DOWN('3'))
		{
			GetClip(OHM_UNEQUIP)->SetEvent(bind(&Player::Changebow, this), 0.7f, true);
			is1hm = false;
			isbow = true;
			SetAction(OHM_UNEQUIP);
		}
	}
	
	if (is2hm)
	{
		if (KEY_DOWN('1'))
		{
			GetClip(THM_UNEQUIP)->SetEvent(bind(&Player::Change1hm, this), 0.7f, true);
			is2hm = false;
			is1hm = true;
			SetAction(THM_UNEQUIP);
		}
		if (KEY_DOWN('3'))
		{
			GetClip(THM_UNEQUIP)->SetEvent(bind(&Player::Changebow, this), 0.7f, true);
			is2hm = false;
			isbow = true;
			SetAction(THM_UNEQUIP);
		}
	}
	
	if (isbow)
	{
		if (KEY_DOWN('1'))
		{
			GetClip(BOW_UNEQUIP)->SetEvent(bind(&Player::Change1hm, this), 0.7f, true);
			isbow = false;
			is1hm = true;
			SetAction(BOW_UNEQUIP);
		}
		if (KEY_DOWN('2'))
		{
			GetClip(BOW_UNEQUIP)->SetEvent(bind(&Player::Change2hm, this), 0.7f, true);
			isbow = false;
			is2hm = true;
			SetAction(BOW_UNEQUIP);
		}
	}

}

void Player::SetAnimation()
{
	if (curAction == OHM_ATK_R || curAction == OHM_ATK_L || curAction == OHM_ATK_P ||
		curAction == OHM_BLOCK || curAction == OHM_HIT_LIGHT || curAction == OHM_HIT_MEDIUM ||
		curAction == OHM_HIT_LARGE || curAction == OHM_HIT_LARGEST || curAction == OHM_HIT_BLOCK || 
		curAction == THM_ATK_R || curAction == THM_ATK_L || curAction == THM_ATK_P ||
		curAction == THM_BLOCK || curAction == THM_HIT_LIGHT || curAction == THM_HIT_MEDIUM ||
		curAction == THM_HIT_LARGE || curAction == THM_HIT_LARGEST || curAction == THM_HIT_BLOCK||
		curAction == OHM_WALK_FW_ATK || curAction == OHM_WALK_BW_ATK || curAction == OHM_WALK_L_ATK ||
		curAction == OHM_WALK_R_ATK || curAction == OHM_RUN_FW_ATK || curAction == OHM_RUN_BW_ATK ||
		curAction == OHM_RUN_L_ATK || curAction == OHM_RUN_R_ATK || curAction == THM_WALK_FW_ATK ||
		curAction == OHM_CATK_R || curAction == OHM_CATK_L || curAction == OHM_CATK_P ||
		curAction == THM_WALK_BW_ATK || curAction == THM_WALK_L_ATK || curAction == THM_WALK_R_ATK||
		curAction == THM_RUN_FW_ATK || curAction == THM_RUN_BW_ATK || curAction == THM_RUN_L_ATK ||
		curAction == THM_RUN_R_ATK || curAction == BOW_DRAW_INTRO || curAction == BOW_RELEASE)
		return;
	if (curAction == OHM_EQUIP || curAction == OHM_UNEQUIP || curAction == THM_EQUIP ||
		curAction == THM_UNEQUIP || curAction == BOW_EQUIP || curAction == BOW_UNEQUIP)
		return;

	if (is1hm)
	{
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

	if (is2hm)
	{
		if (velocity.z < -0.1f && velocity.x < -0.1f)
		{
			if (KEY_PRESS(VK_SHIFT)) SetAction(THM_RUN_FL);
			else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_FL);
			else SetAction(THM_WALK_FL);
		}

		else if (velocity.z > 0.1f && velocity.x > 0.1f)
		{
			if (KEY_PRESS(VK_SHIFT)) SetAction(THM_RUN_FR);
			else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_FR);
			else SetAction(THM_WALK_FR);
		}

		else if (velocity.z < -0.1f && velocity.x < -0.1f)
		{
			if (KEY_PRESS(VK_SHIFT)) SetAction(THM_RUN_BL);
			else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_BL);
			else SetAction(THM_WALK_BL);
		}

		else if (velocity.z < -0.1f && velocity.x > 0.1f)
		{
			if (KEY_PRESS(VK_SHIFT)) SetAction(THM_RUN_BR);
			else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_BR);
			else SetAction(THM_WALK_BR);
		}

		else if (velocity.z > 0.1f)
		{
			if (KEY_PRESS(VK_SHIFT)) SetAction(THM_RUN_F);
			else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_F);
			else SetAction(THM_WALK_F);
		}

		else if (velocity.z < -0.1f)
		{
			if (KEY_PRESS(VK_SHIFT)) SetAction(THM_RUN_B);
			else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_B);
			else SetAction(THM_WALK_B);
		}

		else if (velocity.x < -0.1f)
		{
			if (KEY_PRESS(VK_SHIFT)) SetAction(THM_RUN_L);
			else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_L);
			else SetAction(THM_WALK_L);
		}

		else if (velocity.x > 0.1f)
		{
			if (KEY_PRESS(VK_SHIFT)) SetAction(THM_RUN_R);
			else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_R);
			else SetAction(THM_WALK_R);
		}
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CIDLE);

		else SetAction(THM_IDLE);
	}

	if (isbow && !isbowdrawn)
	{
		if (velocity.z < -0.1f && velocity.x < -0.1f)
		{
			if (KEY_PRESS(VK_SHIFT)) SetAction(BOW_RUN_FL);
			else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_FL);
			else SetAction(BOW_WALK_FL);
		}

		else if (velocity.z > 0.1f && velocity.x > 0.1f)
		{
			if (KEY_PRESS(VK_SHIFT)) SetAction(BOW_RUN_FR);
			else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_FR);
			else SetAction(BOW_WALK_FR);
		}

		else if (velocity.z < -0.1f && velocity.x < -0.1f)
		{
			if (KEY_PRESS(VK_SHIFT)) SetAction(BOW_RUN_BL);
			else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_BL);
			else SetAction(BOW_WALK_BL);
		}

		else if (velocity.z < -0.1f && velocity.x > 0.1f)
		{
			if (KEY_PRESS(VK_SHIFT)) SetAction(BOW_RUN_BR);
			else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_BR);
			else SetAction(BOW_WALK_BR);
		}

		else if (velocity.z > 0.1f)
		{
			if (KEY_PRESS(VK_SHIFT)) SetAction(BOW_RUN_F);
			else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_F);
			else SetAction(BOW_WALK_F);
		}

		else if (velocity.z < -0.1f)
		{
			if (KEY_PRESS(VK_SHIFT)) SetAction(BOW_RUN_B);
			else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_B);
			else SetAction(BOW_WALK_B);
		}

		else if (velocity.x < -0.1f)
		{
			if (KEY_PRESS(VK_SHIFT)) SetAction(BOW_RUN_L);
			else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_L);
			else SetAction(BOW_WALK_L);
		}

		else if (velocity.x > 0.1f)
		{
			if (KEY_PRESS(VK_SHIFT)) SetAction(BOW_RUN_R);
			else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_R);
			else SetAction(BOW_WALK_R);
		}

		else if (KEY_PRESS(VK_CONTROL)) SetAction(CIDLE);


		else SetAction(BOW_IDLE);
	}

	if (isbow && isbowdrawn)
	{
		if (velocity.z < -0.1f && velocity.x < -0.1f)
		{
			SetAction(BOW_DRAWN_WALK_FL);
		}

		else if (velocity.z > 0.1f && velocity.x > 0.1f)
		{
			SetAction(BOW_DRAWN_WALK_FR);
		}

		else if (velocity.z < -0.1f && velocity.x < -0.1f)
		{
			SetAction(BOW_DRAWN_WALK_BL);
		}

		else if (velocity.z < -0.1f && velocity.x > 0.1f)
		{
			SetAction(BOW_DRAWN_WALK_BR);
		}

		else if (velocity.z > 0.1f)
		{
			SetAction(BOW_DRAWN_WALK_F);
		}

		else if (velocity.z < -0.1f)
		{
			SetAction(BOW_DRAWN_WALK_B);
		}

		else if (velocity.x < -0.1f)
		{
			SetAction(BOW_DRAWN_WALK_L);
		}

		else if (velocity.x > 0.1f)
		{
			SetAction(BOW_DRAWN_WALK_R);
		}
		else SetAction(BOW_DRAW_IDLE);
	}

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
	if (is1hm)
	{
		SetAction(OHM_IDLE);
	}
	if (is2hm)
	{
		SetAction(THM_IDLE);
	} 
}

void Player::EndBlock()
{
	if (is1hm)
	{
		SetAction(OHM_IDLE);
	}
	if (is2hm)
	{
		SetAction(THM_IDLE);
	}
	isBlock = false;
}

void Player::EndHit()
{
	if (is1hm)
	{
		SetAction(OHM_IDLE);
	}
	if (is2hm)
	{
		SetAction(THM_IDLE);
	}
	isHit = false;
}

void Player::EndBlockHit()
{
	if (is1hm)
	{
		SetAction(OHM_BLOCK);
	}
	if (is2hm)
	{
		SetAction(THM_BLOCK);
	}
	isHit = false;
}

void Player::SetBowDrawn()
{	
	SetAction(BOW_DRAW_IDLE);
}

void Player::ShootArrow()
{


}

void Player::EndBowDrawn()
{
	SetAction(BOW_IDLE);
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

void Player::Change1hm()
{
	SetAction(OHM_EQUIP);
}

void Player::Change2hm()
{
	SetAction(THM_EQUIP);
}

void Player::Changebow()
{
	SetAction(BOW_EQUIP);
}

void Player::Set1hmIdle()
{
	SetAction(OHM_IDLE);
}

void Player::Set2hmIdle()
{
	SetAction(THM_IDLE);
}

void Player::SetbowIdle()
{
	SetAction(BOW_IDLE);
}



void Player::DoNothing()
{
	return;
}
