#include "Framework.h"
#include "HumanScene.h"

HumanScene::HumanScene()
{
    human = new Human();
}

HumanScene::~HumanScene()
{
    delete human;
}

void HumanScene::Update()
{
    human->Update();
}

void HumanScene::PreRender()
{
}

void HumanScene::Render()
{
    human->Render();
}

void HumanScene::PostRender()
{
}

void HumanScene::GUIRender()
{
}
