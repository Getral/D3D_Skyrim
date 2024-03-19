#include "Framework.h"
#include "TerrainManager.h"

TerrainManager::TerrainManager()
{
	wstring heightMap = L"Textures/HeightMaps/Tamriel/TamrielBeta_10_2016_01-001.png";
	//wstring heightMap = L"Textures/HeightMaps/TestMap.png";
	terrain = new Terrain(L"Textures/Landscape/tamriel.4.0.0.dds", heightMap);

	float size = 16.0f;
	terrain->Scale() *= size;
	terrain->Pos().SetX(-terrain->GetSize().x * size * 0.5f);
	terrain->Pos().SetZ(-terrain->GetSize().y * size * 0.5f);
	terrain->Pos().y -= 600.0f;
	terrain->UpdateWorld();
}

TerrainManager::~TerrainManager()
{
	delete terrain;
}

void TerrainManager::Update()
{
	playerData->Pos().y += -gravity * DELTA;
	if (terrain->ComputePicking(playerData->Pos(), playerData))
		playerData->Pos().y += (gravity + 2) * DELTA;

	if (playerData->Pos().y <= 0.0f)
		playerData->Pos().y = 200.0f;
}

void TerrainManager::Render()
{
	terrain->Render();
}

void TerrainManager::GUIRender()
{
	ImGui::Text("Test : %d", test);
}
