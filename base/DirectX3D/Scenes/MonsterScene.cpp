#include "Framework.h"
#include "MonsterScene.h"

MonsterScene::MonsterScene()
{
	terrain = new Terrain();
	terrain->Pos() = { -terrain->GetSize().x / 2, 0, -terrain->GetSize().y / 2 };
	terrain->UpdateWorld();

	SpawnManager::Get();
}

MonsterScene::~MonsterScene()
{
	delete terrain;
	delete alduin;
}

void MonsterScene::Update()
{
	SpawnManager::Get()->Update();
	//alduin->Update();
}

void MonsterScene::PreRender()
{
}

void MonsterScene::Render()
{
	terrain->Render();
	SpawnManager::Get()->Render();
	//alduin->Render();
}

void MonsterScene::PostRender()
{
}

void MonsterScene::GUIRender()
{
	SpawnManager::Get()->GUIRender();
	//alduin->GUIRender();
}
