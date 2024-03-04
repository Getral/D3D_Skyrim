#include "Framework.h"

Player::Player()
	: ModelAnimator("male_dragonbone")
{
	ModelAnimator::Scale() *= 0.001;
	
	ReadClip("male_idle");
	ReadClip("male_jump");
	ReadClip("male_stagger");
	ReadClip("male_stagger_medium");
	ReadClip("male_stagger_large");
	ReadClip("male_block_hit_shield");
	ReadClip("male_walk_forward");
	ReadClip("male_walk_forward_l");
	ReadClip("male_walk_forward_r");
	ReadClip("male_walk_backward");
	ReadClip("male_walk_backward_l");
	ReadClip("male_walk_backward_r");
	ReadClip("male_walk_left");
	ReadClip("male_walk_right");
	ReadClip("male_run_forward");
	ReadClip("male_run_forward_l");
	ReadClip("male_run_forward_r");
	ReadClip("male_run_backward");
	ReadClip("male_run_backward_l");
	ReadClip("male_run_backward_r");
	ReadClip("male_run_left");
	ReadClip("male_run_right");
	ReadClip("male_crouch_idle");
	ReadClip("male_crouch_walk_forward");
	ReadClip("male_crouch_walk_forward_l");
	ReadClip("male_crouch_walk_forward_r");
	ReadClip("male_crouch_walk_backward");
	ReadClip("male_crouch_walk_backward_l");
	ReadClip("male_crouch_walk_backward_r");
	ReadClip("male_crouch_walk_left");
	ReadClip("male_crouch_walk_right");
	ReadClip("male_attack_right");
	ReadClip("male_attack_left");
	ReadClip("male_attack_power");
	ReadClip("male_block_shield");
	ReadClip("male_block_bash_intro_shield");
	ReadClip("male_block_bash_shield");
	
	ModelAnimator::Rot().y = XM_PI;

	collider = new CapsuleCollider(3, 5);
	collider->Scale() *= 1000;
	collider->Pos().y = 6000;
	collider->SetParent(this);
	
	action = (ACTION)frameBuffer->Get().cur.clip;

	bladeSword = new BladeSword();
	bladeSword->Load();

	rightHand = new Transform();
	bladeSword->SetParent(rightHand);

	shield = new Shield();
	shield->Load();

	leftHand = new Transform();
	shield->SetParent(leftHand);

	GetClip(ATTACK_RIGHT)->SetEvent(bind(&Player::EndAttack, this), 0.7f);
	GetClip(ATTACK_LEFT)->SetEvent(bind(&Player::EndAttack, this), 0.7f);
	GetClip(ATTACK_HEAVY)->SetEvent(bind(&Player::EndAttack, this), 0.7f);
	GetClip(HIT_LIGHT)->SetEvent(bind(&Player::EndHit, this), 0.7f);
	GetClip(HIT_MEDIUM)->SetEvent(bind(&Player::EndHit, this), 0.7f);
	GetClip(HIT_HEAVY)->SetEvent(bind(&Player::EndHit, this), 0.8f);
	GetClip(HIT_BLOCK)->SetEvent(bind(&Player::EndBlockHit, this), 0.5f);
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
	rightHand->SetWorld(GetTransformByNode(79));
	bladeSword->Update();
	leftHand->SetWorld(GetTransformByNode(119));
	shield->Update();
}

void Player::Render()
{
	ModelAnimator::Render();
	collider->Render();
	bladeSword->Render();
	shield->Render();
	
}

void Player::PostRender()
{
}

void Player::GUIRender()
{
	bladeSword->GUIRender();
	collider->GUIRender();
	ModelAnimator::GUIRender();
	ImGui::SliderInt("nodeIndex", (int*)&nodeIndex, 1, 500);
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
	if (curAction == ATTACK_RIGHT || curAction == ATTACK_LEFT || curAction == ATTACK_HEAVY)
		return;
	if (isBlock) return;
	if (isHit) return;

	bool isMoveZ = false;
	bool isMoveX = false;

	if (KEY_PRESS(VK_SHIFT)) //달리기
	{
		if (KEY_PRESS('W'))
		{
			velocity.z += DELTA * status.speed * 1.0f;
			isMoveZ = true;
		}
		if (KEY_PRESS('S'))
		{
			velocity.z -= DELTA * status.speed * 1.0f;
			isMoveZ = true;
		}
		if (KEY_PRESS('A'))
		{
			velocity.x -= DELTA * status.speed * 1.0f;
			isMoveX = true;
		}
		if (KEY_PRESS('D'))
		{
			velocity.x += DELTA * status.speed * 1.0f;
			isMoveX = true;
		}
	}
	
	else if (KEY_PRESS(VK_CONTROL)) //앉아서 이동
	{
		if (KEY_PRESS('W'))
		{
			velocity.z += DELTA * status.speed * 0.5f;
			isMoveZ = true;
		}
		if (KEY_PRESS('S'))
		{
			velocity.z -= DELTA * status.speed * 0.5f;
			isMoveZ = true;
		}
		if (KEY_PRESS('A'))
		{
			velocity.x -= DELTA * status.speed * 0.5f;
			isMoveX = true;
		}
		if (KEY_PRESS('D'))
		{
			velocity.x += DELTA * status.speed * 0.5f;
			isMoveX = true;
		}
	}
	
	else //걷기
	{
		if (KEY_PRESS('W'))
		{
			velocity.z += DELTA * status.speed * 0.7f;
			isMoveZ = true;
		}
		if (KEY_PRESS('S'))
		{
			velocity.z -= DELTA * status.speed * 0.7f;
			isMoveZ = true;
		}
		if (KEY_PRESS('A'))
		{
			velocity.x -= DELTA * status.speed * 0.7f;
			isMoveX = true;
		}
		if (KEY_PRESS('D'))
		{
			velocity.x += DELTA * status.speed * 0.7f;
			isMoveX = true;
		}
	}
	

	//방향을 구하고 정규화
	if (KEY_PRESS(VK_SHIFT))
	{
		if (velocity.Length() > status.speed * 1.0f) velocity.Normalize();
	}
	else if (KEY_PRESS(VK_CONTROL))
	{
		if (velocity.Length() > status.speed * 0.5f) velocity.Normalize();
	}
	else
	{
		if (velocity.Length() > status.speed * 0.7f) velocity.Normalize();
	}

	if (!isMoveZ)
		velocity.z = Lerp(velocity.z, 0, deceleration * DELTA * status.speed);

	if (!isMoveX)
		velocity.x = Lerp(velocity.x, 0, deceleration * DELTA * status.speed);

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
}

void Player::Attack()
{
	if (curAction == ATTACK_RIGHT || curAction == ATTACK_LEFT || curAction == ATTACK_HEAVY) return;
	if (isHit) return;
	
	//if (KEY_PRESS(VK_LBUTTON)) 
	//if (KEY_DOWN(VK_LBUTTON)) SetAction(ATTACK_RIGHT);
	//if (KEY_DOWN(VK_LBUTTON)) SetAction(ATTACK_LEFT);
	if (KEY_DOWN(VK_LBUTTON)) SetAction(ATTACK_HEAVY);

}

void Player::Block()
{
	if (curAction == ATTACK_RIGHT || curAction == ATTACK_LEFT || curAction == ATTACK_HEAVY) return;
	if (isHit) return;

	if (KEY_DOWN(VK_RBUTTON))
	{
		SetAction(BLOCK);
		isBlock = true;
	}

	if (KEY_UP(VK_RBUTTON))
	{
		EndBlock();
	}
}

void Player::GetHit()
{
	if (isBlock)
	{
		if (KEY_DOWN('Z'))
		{
			SetAction(HIT_BLOCK);
			isHit = true;
		}
		if (KEY_DOWN('X'))
		{
			SetAction(HIT_BLOCK);
			isHit = true;
		}
		if (KEY_DOWN('C'))
		{
			SetAction(HIT_BLOCK);
			isHit = true;
		}
	}	
	else
	{
		if (KEY_DOWN('Z'))
		{
			SetAction(HIT_LIGHT);
			isHit = true;
		}
		if (KEY_DOWN('X'))
		{
			SetAction(HIT_MEDIUM);
			isHit = true;
		}
		if (KEY_DOWN('C'))
		{
			SetAction(HIT_HEAVY);
			isHit = true;
		}
	}	
}

void Player::SetAnimation()
{
	if (curAction == ATTACK_RIGHT || curAction == ATTACK_LEFT || curAction == ATTACK_HEAVY 
		|| curAction == BLOCK || curAction == HIT_LIGHT || curAction == HIT_MEDIUM ||
		curAction == HIT_HEAVY || curAction == HIT_BLOCK)
		return;


	if (velocity.z < -0.1f && velocity.x < -0.1f)
	{
		if (KEY_PRESS(VK_SHIFT)) SetAction(RUN_FL);
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_FL);
		else SetAction(WALK_FL);
	}

	else if (velocity.z > 0.1f && velocity.x > 0.1f)
	{
		if (KEY_PRESS(VK_SHIFT)) SetAction(RUN_FR);
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_FR);
		else SetAction(WALK_FR);
	}

	else if (velocity.z < -0.1f && velocity.x < -0.1f)
	{
		if (KEY_PRESS(VK_SHIFT)) SetAction(RUN_BL);
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_BL);
		else SetAction(WALK_BL);
	}

	else if (velocity.z < -0.1f && velocity.x > 0.1f)
	{
		if (KEY_PRESS(VK_SHIFT)) SetAction(RUN_BR);
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_BR);
		else SetAction(WALK_BR);
	}

	else if (velocity.z > 0.1f)
	{
		if (KEY_PRESS(VK_SHIFT)) SetAction(RUN_F);
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_F);
		else SetAction(WALK_F);
	}

	else if (velocity.z < -0.1f)
	{
		if (KEY_PRESS(VK_SHIFT)) SetAction(RUN_B);
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_B);
		else SetAction(WALK_B);
	}

	else if (velocity.x < -0.1f)
	{
		if (KEY_PRESS(VK_SHIFT)) SetAction(RUN_L);
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_L);
		else SetAction(WALK_L);
	}

	else if (velocity.x > 0.1f)
	{
		if (KEY_PRESS(VK_SHIFT)) SetAction(RUN_R);
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_R);
		else SetAction(WALK_R);
	}
	else if (KEY_PRESS(VK_CONTROL)) SetAction(CIDLE);

	else SetAction(IDLE);
}

void Player::SetAction(ACTION action)
{
	if (action == curAction) return;

	curAction = action;
	PlayClip((int)action);
}

void Player::Attack1hm()
{
}

void Player::Attack2hm()
{
}

void Player::Attackh2h()
{
}

void Player::EndAttack()
{
	SetAction(IDLE);
}

void Player::EndBlock()
{
	SetAction(IDLE);
	isBlock = false;
}

void Player::EndHit()
{
	SetAction(IDLE);
	isHit = false;
}

void Player::EndBlockHit()
{
	SetAction(BLOCK);
	isHit = false;
}
