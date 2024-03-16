#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	for (int i = 0; i < height; i++)
	{
		vector<Terrain*> tmp;
		for (int j = 0; j < width; j++)
		{
			wstring index = L"";
			if (j + i * 32 + 1 < 10)
				index = L"00";
			else if (j + i * 32 + 1 < 100)
				index = L"0";
			index += to_wstring(j + i * 32 + 1);
			wstring file = L"Textures/HeightMaps/Tamriel/TamrielBeta_10_2016_01-" + index + L".png";
			tmp.push_back(new Terrain(L"Textures/Landscape/tamriel.4.0.0.dds", file));
		}
		terrain.push_back(tmp);
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			terrain[i][j]->Pos().SetX(-(terrain[i][j]->GetSize().x * (width / 2 - j)) + terrain[i][j]->GetSize().x * 0.5f);
			terrain[i][j]->Pos().SetY(-100);
			terrain[i][j]->Pos().SetZ(-(terrain[i][j]->GetSize().y * (height / 2 - i)) + terrain[i][j]->GetSize().y * 0.5f);
			terrain[i][j]->UpdateWorld();
		}
	}
}

TerrainScene::~TerrainScene()
{
	for (vector<Terrain*> terrains : terrain)
		for (Terrain* t : terrains)
			delete t;
}

void TerrainScene::Update()
{
	for (vector<Terrain*> terrains : terrain)
		for (Terrain* t : terrains)
			t->UpdateWorld();
}

void TerrainScene::PreRender()
{
}

void TerrainScene::Render()
{
	for (vector<Terrain*> terrains : terrain)
		for (Terrain* t : terrains)
			t->Render();
}

void TerrainScene::PostRender()
{
}

void TerrainScene::GUIRender()
{
}
