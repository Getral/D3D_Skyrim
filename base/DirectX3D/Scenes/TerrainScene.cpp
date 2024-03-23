#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	TerrainManager::Get();

	FOR(objectName.size())
		for (int j = 0; j < objectPos[i].size(); j++)
			ObjectManager::Get()->Create(objectPos[i][j], objectRot[i][j], objectName[i]);


	ObjectManager::Get()->Create({ 243,0,300 }, 125, "farmhouse");
	ObjectManager::Get()->Create({ 260,0,300 }, 26, "farmhouse2");

	ObjectManager::Get()->Create({ 350,0,200 }, 0, "chest_armor_iron");

	for (int i = 290; i <= 400; i += 10)
		ObjectManager::Get()->Create({ (float)i,0,400 }, 0, "rock_large4");
	
	for (int i = 400; i >= 0; i -= 10)
		ObjectManager::Get()->Create({ 400,0,(float)i }, 0, "rock_large4");
	
	for (int i = 400; i >= 200; i -= 10)
		ObjectManager::Get()->Create({ (float)i,0,0 }, 0, "rock_large4");
	

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
