#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	terrain = new Terrain();
	terrain->Pos() = { -terrain->GetSize().x / 2, 0, -terrain->GetSize().y / 2 };
	terrain->UpdateWorld();

	SpawnManager::Get();
}

TestScene::~TestScene()
{
	delete terrain;
	delete alduin;
}

void TestScene::Update()
{
	SpawnManager::Get()->Update();
	//alduin->Update();
}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	terrain->Render();
	SpawnManager::Get()->Render();
	//alduin->Render();
}

void TestScene::PostRender()
{
}

void TestScene::GUIRender()
{
	SpawnManager::Get()->GUIRender();
	//alduin->GUIRender();
}
