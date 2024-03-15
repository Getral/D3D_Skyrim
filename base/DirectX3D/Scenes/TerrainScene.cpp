#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	for (int i = 0; i < height; i++)
	{
		vector<Terrain*> tmp;
		for (int j = 0; j < width; i++)
		{
			wstring file = L"Textures/HeightMaps/Tamriel/TamrielBeta_10_2016_01_" + to_wstring(/*j + i * 16 + */1) + L".gif";
			tmp.push_back(new Terrain(L"Textures/Landscape/tamriel.4.0.0.dds", file));
			tmp[j]->Pos() = { -(tmp[j]->GetSize().x * (50 - j)) + tmp[j]->GetSize().x * 0.5f , 0,
				-(tmp[j]->GetSize().y * (50 - j)) + tmp[j]->GetSize().y * 0.5f };
		}
		terrain.push_back(tmp);
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
