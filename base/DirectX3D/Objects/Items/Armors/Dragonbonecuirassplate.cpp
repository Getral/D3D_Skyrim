#include "Framework.h"

Dragonbonecuirassplate::Dragonbonecuirassplate() : Model("dragonbonecuirassplate")
{
	SetTag("dragonbonecuirassplate");
}

Dragonbonecuirassplate::~Dragonbonecuirassplate()
{
}

void Dragonbonecuirassplate::Update()
{
	UpdateWorld();
}

void Dragonbonecuirassplate::Render()
{
	Model::Render();
}

void Dragonbonecuirassplate::GUIRender()
{
	Model::GUIRender();
}
