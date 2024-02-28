#include "Framework.h"
#include "DijkstraScene.h"

DijkstraScene::DijkstraScene()
{
	dijkstra = new Dijkstra();
	//terrain = new Terrain();
	terrain = new TerrainEditor();
	fox = new FoxD();

	fox->SetTerrain(terrain);
	fox->SetDijkstra(dijkstra);

	dijkstra->SetTerrain(terrain);
}

DijkstraScene::~DijkstraScene()
{
	delete dijkstra;
	delete terrain;
	delete fox;
}

void DijkstraScene::Update()
{
	dijkstra->Update();
	fox->Update();
}

void DijkstraScene::PreRender()
{
}

void DijkstraScene::Render()
{

	dijkstra->Render();
	terrain->Render();
	fox->Render();
}

void DijkstraScene::PostRender()
{
}

void DijkstraScene::GUIRender()
{
}
