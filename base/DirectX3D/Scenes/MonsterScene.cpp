#include "Framework.h"
#include "MonsterScene.h"
#include "PlayerScene.h"

MonsterScene::MonsterScene()
{
	SpawnManager::Get();
}

MonsterScene::~MonsterScene()
{
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
	SpawnManager::Get()->Render();
}

void MonsterScene::PostRender()
{
}

void MonsterScene::GUIRender()
{
	//SpawnManager::Get()->GUIRender();
}
