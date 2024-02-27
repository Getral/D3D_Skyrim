#include "Framework.h"

Player::Player()
	: ModelAnimator("male_dragonbone")
{
	ReadClip("idle");
	//ReadClip("male_idle");
	//ReadClip("male_idle");
	//ReadClip("male_idle");
	//ReadClip("male_block_hit");
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
	ReadClip("male_crouch_forward");
	ReadClip("male_crouch_forward_l");
	ReadClip("male_crouch_forward_r");
	ReadClip("male_crouch_backward");
	ReadClip("male_crouch_backward_l");
	ReadClip("male_crouch_backward_r");
	ReadClip("male_crouch_left");
	ReadClip("male_crouch_right");
	ReadClip("attack_right");
	ReadClip("attack_left");
	ReadClip("attack_power");
	ReadClip("male_block");

	collider = new CapsuleCollider();
	collider->SetParent(transform);

	action = (ACTION)frameBuffer->Get().cur.clip;



}

Player::~Player()
{
	delete transform;
	delete collider;
}

void Player::Update()
{
	Control();
	SetAnimation();

	ModelAnimator::Update();

	collider->UpdateWorld();
}

void Player::Render()
{
	ModelAnimator::Render();
	collider->Render();
}

void Player::PostRender()
{
}

void Player::GUIRender()
{
}

void Player::Control()
{
	Rotate();
	Move();
	Attack();
}

void Player::Move()
{
	if (curAction == ATTACK_RIGHT || curAction == ATTACK_LEFT || curAction == ATTACK_HEAVY)
		return;

	bool isMoveZ = false;
	bool isMoveX = false;

	if (KEY_PRESS(VK_SHIFT)) //달리기
	{
		if (KEY_PRESS('W'))
		{
			velocity.z += DELTA;
			isMoveZ = true;
		}
		if (KEY_PRESS('S'))
		{
			velocity.z -= DELTA;
			isMoveZ = true;
		}
		if (KEY_PRESS('A'))
		{
			velocity.x -= DELTA;
			isMoveX = true;
		}
		if (KEY_PRESS('D'))
		{
			velocity.x += DELTA;
			isMoveX = true;
		}
	}
	
	else if (KEY_PRESS(VK_CONTROL)) //앉아서 이동
	{
		if (KEY_PRESS('W'))
		{
			velocity.z += DELTA * 0.5f;
			isMoveZ = true;
		}
		if (KEY_PRESS('S'))
		{
			velocity.z -= DELTA * 0.5f;
			isMoveZ = true;
		}
		if (KEY_PRESS('A'))
		{
			velocity.x -= DELTA * 0.5f;
			isMoveX = true;
		}
		if (KEY_PRESS('D'))
		{
			velocity.x += DELTA * 0.5f;
			isMoveX = true;
		}
	}
	
	else //걷기
	{
		if (KEY_PRESS('W'))
		{
			velocity.z += DELTA * 0.7f;
			isMoveZ = true;
		}
		if (KEY_PRESS('S'))
		{
			velocity.z -= DELTA * 0.7f;
			isMoveZ = true;
		}
		if (KEY_PRESS('A'))
		{
			velocity.x -= DELTA * 0.7f;
			isMoveX = true;
		}
		if (KEY_PRESS('D'))
		{
			velocity.x += DELTA * 0.7f;
			isMoveX = true;
		}
	}
	

	//방향을 구하고 정규화
	if (velocity.Length() > 1) velocity.Normalize();

	if (!isMoveZ)
		velocity.z = Lerp(velocity.z, 0, deceleration * DELTA);

	if (!isMoveX)
		velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);

	Matrix rotY = XMMatrixRotationY(Rot().y);

	Vector3 direction = XMVector3TransformCoord(velocity, rotY);

	Pos() += direction * moveSpeed * DELTA * -1;
}

void Player::Rotate()
{
}

void Player::Attack()
{
}

void Player::SetAnimation()
{
	if (curAction == ATTACK_RIGHT || curAction == ATTACK_LEFT || curAction == ATTACK_HEAVY)
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

	else if (velocity.z < -0.1f && velocity.x == 0)
	{
		if (KEY_PRESS(VK_SHIFT)) SetAction(RUN_B);
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_B);
		else SetAction(WALK_B);
	}

	else if (velocity.x < -0.1f && velocity.z == 0)
	{
		if (KEY_PRESS(VK_SHIFT)) SetAction(RUN_L);
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_L);
		else SetAction(WALK_L);
	}

	else if (velocity.x > 0.1f && velocity.z == 0)
	{
		if (KEY_PRESS(VK_SHIFT)) SetAction(RUN_R);
		else if (KEY_PRESS(VK_CONTROL)) SetAction(CMOVE_R);
		else SetAction(WALK_R);
	}			
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
