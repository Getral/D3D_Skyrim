#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(L"Textures/Landscape/tundra02.dds");
	terrain->SetSize(Vector2(100, 100));
	terrain->Pos() = { -terrain->GetSize().x / 2, 0, -terrain->GetSize().y / 2 };
	terrain->UpdateWorld();
	//for (int i = 0; i < terrainSize; i++)
	//{
	//	vector<Terrain*> tmp;
	//	for (int j = 0; j < terrainSize; j++)
	//	{
	//		tmp.push_back(new Terrain(L"Textures/Landscape/tundra02.dds"));
	//	}
	//	terrain.push_back(tmp);
	//}
	//
	//for (int i = 0; i < terrainSize; i++)
	//{
	//	for (int j = 0; j < terrainSize; j++)
	//	{
	//		terrain[i][j]->Pos() = { -terrain[i][j]->GetSize().x * (terrainSize / 2 - i), 0,
	//			-terrain[i][j]->GetSize().y * (terrainSize / 2 - j)};
	//		terrain[i][j]->UpdateWorld();
	//	}
	//}
}

TerrainScene::~TerrainScene()
{
	//for (vector<Terrain*> terrains : terrain)
	//	for (Terrain* t : terrains)
	//		delete t;
	delete terrain;
}

void TerrainScene::Update()
{
}

void TerrainScene::PreRender()
{
}

void TerrainScene::Render()
{
	//for (vector<Terrain*> terrains : terrain)
	//	for (Terrain* t : terrains)
	//		t->Render();
	terrain->Render();
}

void TerrainScene::PostRender()
{
}

void TerrainScene::GUIRender()
{
}
