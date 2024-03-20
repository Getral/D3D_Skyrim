#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	TerrainManager::Get();

	testModel = new Model("rock_large1");
	testModel->Scale() *= 0.05f;

	ObjectManager::Get()->Create({ 178, 12, 200 }, "rock_large1");
	//ObjectManager::Get()->Create({ 200, 12, 200 }, "rock_large1");
}

TerrainScene::~TerrainScene()
{

}

void TerrainScene::Update()
{
	TerrainManager::Get()->Update();
	testModel->UpdateWorld();
}

void TerrainScene::PreRender()
{
}

void TerrainScene::Render()
{
	TerrainManager::Get()->Render();
	testModel->Render();
}

void TerrainScene::PostRender()
{
}

void TerrainScene::GUIRender()
{
	TerrainManager::Get()->GUIRender();
	testModel->GUIRender();
}
