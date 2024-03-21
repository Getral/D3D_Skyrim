#include "Framework.h"

IronBow::IronBow() : ModelAnimator("IronBow")
{
	SetTag("IronBow");

	Pos().x += -0.5;
	Pos().y += 0;
	Pos().z += 0;

	Rot().x += XM_PI/2;
	Rot().y += XM_PI;
	Rot().z += 0;

	Scale().x *= 0.01f;
	Scale().y *= 0.01f;
	Scale().z *= 0.01f;

	collider = new BoxCollider();
	collider->Pos().x += -5.3f;
	collider->Pos().y += 0.0;
	collider->Pos().z += 0.0f;

	collider->Rot().x += 0.0f;
	collider->Rot().y += 0.0f;
	collider->Rot().z += 0.0f;

	collider->Scale().x *= 20.1f;
	collider->Scale().y *= 116.0f;
	collider->Scale().z *= 1.0f;


	collider->SetTag("IronBowCollider");
	collider->SetParent(this);
	collider->Load();



	this->ReadClip("iron_bow_idle");
	this->ReadClip("iron_bow_draw");
	this->ReadClip("iron_bow_draw_idle");
	this->ReadClip("iron_bow_draw_release");

	SetState(IDLE);
}     

IronBow::~IronBow()
{
	delete collider;
}

void IronBow::Update()
{
	UpdateWorld();
	//ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void IronBow::Render()
{
	ModelAnimator::Render();
	collider->Render();
}

void IronBow::GUIRender()
{
	ModelAnimator::GUIRender();
	collider->GUIRender();

}

void IronBow::SetState(IronBowAction action)
{
	if (curState == action) return;

	curState = action;
	this->PlayClip((int)action);
}

//void IronBow::ColliderManager(bool isWeaponColl)
//{
//	if (isWeaponColl)
//	{
//		collider->SetActive(true);
//	}
//	else
//	{
//		collider->SetActive(false);
//	}
//
//}
