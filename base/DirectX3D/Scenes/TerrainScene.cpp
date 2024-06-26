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

	ObjectManager::Get()->Create({ 260	,0	,275	}, -XM_PIDIV4, "chest_potion");
	ObjectManager::Get()->Create({ 257.5,0	,272.5	}, -XM_PIDIV4 / 2, "chest_weapon_ebony");
	ObjectManager::Get()->Create({ 255	,0	,270	}, 0, "chest_weapon_iron");
	ObjectManager::Get()->Create({ 252.5,0	,272.5	}, XM_PIDIV4 / 2, "chest_armor_dragon");
	ObjectManager::Get()->Create({ 250	,0	,275	}, XM_PIDIV4, "chest_armor_iron");

	ObjectManager::Get()->Create({ 240, 0, 280 }, 0, "sign");

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
