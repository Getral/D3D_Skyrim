#include "Framework.h"
#include "MonsterScene.h"
#include "PlayerScene.h"

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
}

void MonsterScene::Update()
{
	SpawnManager::Get()->Update();
}

void MonsterScene::PreRender()
{
}

void MonsterScene::Render()
{
	terrain->Render();
	SpawnManager::Get()->Render();
}

void MonsterScene::PostRender()
{
}

void MonsterScene::GUIRender()
{
	SpawnManager::Get()->GUIRender();
}
