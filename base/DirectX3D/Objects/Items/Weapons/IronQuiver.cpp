#include "Framework.h"

IronQuiver::IronQuiver() : Model("IronQuiver")
{
	SetTag("IronQuiver");
	Pos().x += -2.0f;
	Pos().y += 0;
	Pos().z += 1.5f;

	Rot().x += 0;
	Rot().y += 0;
	Rot().z += XM_PI;

	Scale().x *= 1.0f;
	Scale().y *= 1.0f;
	Scale().z *= 1.0f;

}

IronQuiver::~IronQuiver()
{
}

void IronQuiver::Update()
{
	UpdateWorld();
}

void IronQuiver::Render()
{
	Model::Render();
}

void IronQuiver::GUIRender()
{
	Model::GUIRender();
}
