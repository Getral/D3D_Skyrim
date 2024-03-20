#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	TerrainManager::Get();

	testModel = new Model("rock_large3");
	testModel->Scale() *= 0.05f;

	FOR(objectName.size())
		for (int j = 0; j < objectPos[i].size(); j++)
			ObjectManager::Get()->Create(objectPos[i][j], objectName[i]);
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
