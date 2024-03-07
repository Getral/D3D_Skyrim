#include "Framework.h"

Dragonbonehelmet::Dragonbonehelmet() : Model("dragonbonehelmet")
{
	SetTag("dragonbonehelmet");
}

Dragonbonehelmet::~Dragonbonehelmet()
{
}

void Dragonbonehelmet::Update()
{
	UpdateWorld();
}

void Dragonbonehelmet::Render()
{
	Model::Render();
}

void Dragonbonehelmet::GUIRender()
{
	Model::GUIRender();
}
