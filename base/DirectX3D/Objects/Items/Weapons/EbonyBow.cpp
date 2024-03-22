#include "Framework.h"

EbonyBow::EbonyBow() : ModelAnimator("EbonyBow")
{
	SetTag("EbonyBow");

	Pos().x += 0.0f;
	Pos().y += -9.5;
	Pos().z += 0.0f;

	Rot().x += 0;
	Rot().y += 0;
	Rot().z += XM_PI;

	Scale().x *= 0.01f;
	Scale().y *= 0.01f;
	Scale().z *= 0.01f;

	collider = new BoxCollider();
	collider->Pos().x += 21.0f;
	collider->Pos().y += 0.0;
	collider->Pos().z += 0.0f;

	collider->Rot().x += 0.0f;
	collider->Rot().y += 0.0f;
	collider->Rot().z += 0.0f;

	collider->Scale().x *= 22.7f;
	collider->Scale().y *= 116.0f;
	collider->Scale().z *= 1.0f;


	collider->SetTag("EbonyBowCollider");
	collider->SetParent(this);
	collider->Load();



	ReadClip("ebony_bow_idle");
	ReadClip("ebony_bow_draw");
	ReadClip("ebony_bow_draw_idle");
	ReadClip("ebony_bow_release");

	SetState(IDLE);

}

EbonyBow::~EbonyBow()
{
	delete collider;
}

void EbonyBow::Update()
{
	UpdateWorld();
	//ColliderManager(isWeapon);
	collider->UpdateWorld();
}

void EbonyBow::Render()
{
	ModelAnimator::Render();
	collider->Render();
}

void EbonyBow::GUIRender()
{
	ModelAnimator::GUIRender();
	collider->GUIRender();
}

void EbonyBow::SetState(EbonyBowAction action)
{
	if (curState == action) return;

	curState = action;
	this->PlayClip((int)action);
}

//void EbonyBow::ColliderManager(bool isWeaponColl)
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
