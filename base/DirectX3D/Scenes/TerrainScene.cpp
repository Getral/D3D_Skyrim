#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	TerrainManager::Get();

	ObjectManager::Get()->Create({178, 12, 200}, "rock_large1");
}

TerrainScene::~TerrainScene()
{

}

void TerrainScene::Update()
{
	TerrainManager::Get()->Update();
}

void TerrainScene::PreRender()
{
}

void TerrainScene::Render()
{
	TerrainManager::Get()->Render();
}

void TerrainScene::PostRender()
{
}

void TerrainScene::GUIRender()
{
	TerrainManager::Get()->GUIRender();
}
