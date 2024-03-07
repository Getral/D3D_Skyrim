#include "Framework.h"
#include "IronArmor.h"

IronArmor::IronArmor() : Model("armor")
{
	SetTag("armor");
}

IronArmor::~IronArmor()
{
}

void IronArmor::Update()
{
	UpdateWorld();
}

void IronArmor::Render()
{
	Model::Render();
}

void IronArmor::GUIRender()
{
	Model::GUIRender();
}
