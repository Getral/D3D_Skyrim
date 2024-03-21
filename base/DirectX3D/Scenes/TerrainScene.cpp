#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	TerrainManager::Get();

	FOR(objectName.size())
		for (int j = 0; j < objectPos[i].size(); j++)
			ObjectManager::Get()->Create(objectPos[i][j], objectRot[i][j], objectName[i]);

	skyBox = new SkyBox(L"Textures/Landscape/BlueSky.dds");
}

TerrainScene::~TerrainScene()
{
	delete skyBox;
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
	skyBox->Render();
	TerrainManager::Get()->Render();
}

void TerrainScene::PostRender()
{
	
}

void TerrainScene::GUIRender()
{
	TerrainManager::Get()->GUIRender();
}
