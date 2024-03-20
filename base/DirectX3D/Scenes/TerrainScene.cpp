#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	/*for (int i = 0; i < height; i++)
	{
		vector<Terrain*> tmp;
		for (int j = 1; j <= width; j++)
		{
			wstring index = L"";
			if (j + i * 16 < 10)
				index = L"00";
			else if (j + i * 16 < 100)
				index = L"0";
			index += to_wstring(j + i * 16);
			wstring file = L"Textures/HeightMaps/Tamriel/TamrielBeta_10_2016_01-" + index + L".png";
			tmp.push_back(new Terrain(L"Textures/Landscape/tamriel.4.0.0.dds", file));
		}
		terrain.push_back(tmp);
	}

	player = SpawnManager::Get()->GetPlayerData();

	float size = 16.0f;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			terrain[i][j]->Scale() *= size;
			terrain[i][j]->Pos().SetX(terrain[i][j]->GetSize().x * size * 0.5f);
			terrain[i][j]->Pos().SetY(-3200);
			terrain[i][j]->Pos().SetZ(terrain[i][j]->GetSize().y * size * 0.5f);
			terrain[i][j]->Rot().y = XM_PI;
			terrain[i][j]->UpdateWorld();
		}
	}*/
	//tree01 = new Model("tree_winter");


	//for (int i = 0; i < height; i++)
	//{
	//	vector<Terrain*> tmp;
	//	for (int j = 1; j <= width; j++)
	//	{
	//		wstring index = L"";
	//		if (j + i * 16 < 10)
	//			index = L"00";
	//		else if (j + i * 16 < 100)
	//			index = L"0";
	//		index += to_wstring(j + i * 16);
	//		wstring file = L"Textures/HeightMaps/Tamriel/TamrielBeta_10_2016_01-" + index + L".png";
	//		tmp.push_back(new Terrain(L"Textures/Landscape/tamriel.4.0.0.dds", file));
	//	}
	//	terrain.push_back(tmp);
	//}

	//for (int i = 0; i < height; i++)
	//{
	//	for (int j = 0; j < width; j++)
	//	{
	//		terrain[i][j]->Pos().SetX(-(terrain[i][j]->GetSize().x * (width / 2 - j)) + terrain[i][j]->GetSize().x * 0.5f);
	//		terrain[i][j]->Pos().SetY(-200);
	//		terrain[i][j]->Pos().SetZ(-(terrain[i][j]->GetSize().y * (height / 2 - i)) + terrain[i][j]->GetSize().y * 0.5f);
	//		terrain[i][j]->UpdateWorld();
	//	}
	//}
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
	//tree01->Render();
	//for (vector<Terrain*> terrains : terrain)
	//	for (Terrain* t : terrains)
	//		t->Render();
	TerrainManager::Get()->Render();
}

void TerrainScene::PostRender()
{
}

void TerrainScene::GUIRender()
{
	TerrainManager::Get()->GUIRender();
}
