#include "Framework.h"

Dragonboneshield::Dragonboneshield() : Model("dragonboneshield")
{
	SetTag("dragonboneshield");
}

Dragonboneshield::~Dragonboneshield()
{
}

void Dragonboneshield::Update()
{
	UpdateWorld();
}

void Dragonboneshield::Render()
{
	Model::Render();
}

void Dragonboneshield::GUIRender()
{
	Model::GUIRender();
}
