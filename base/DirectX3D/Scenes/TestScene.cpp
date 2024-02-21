#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	terrain = new Terrain();
	terrain->Pos() = { -terrain->GetSize().x / 2, 0, -terrain->GetSize().y / 2 };
	terrain->UpdateWorld();

	spawningPool = new SpawningPool(Vector3(0, 0, 0));
}

TestScene::~TestScene()
{
	delete terrain;
	delete monsterInstancing;
	delete spawningPool;
}

void TestScene::Update()
{
	spawningPool->Update();
}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	terrain->Render();
	spawningPool->Render();
}

void TestScene::PostRender()
{
}

void TestScene::GUIRender()
{
	spawningPool->GUIRender();
}
