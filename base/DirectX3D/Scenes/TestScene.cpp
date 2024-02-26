#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	terrain = new Terrain();
	terrain->Pos() = { -terrain->GetSize().x / 2, 0, -terrain->GetSize().y / 2 };
	terrain->UpdateWorld();

	monsterInstancing = new ModelAnimatorInstancing("alduin");
	monsterInstancing->Scale() *= 0.001f;
	monsterInstancing->ReadClip("alduin_bite");

	vector<Vector3> poses1;
	poses1.push_back(Vector3(50, 0, 50));
	spawnPoses.push_back(poses1);

	Enemy* monster = new Enemy("alduin");
	monster->SetStatus(100, 1000, 1000, 50, 10);
	
	monsterSpawnManager = new EnemySpawnManager(monsterInstancing, monster, spawnPoses[0]);
	monsterSpawnManager->Spawn();
}

TestScene::~TestScene()
{
	delete terrain;
	delete monsterInstancing;
	delete alduin;
	delete monsterSpawnManager;
}

void TestScene::Update()
{
	monsterSpawnManager->Update();
	//alduin->Update();
}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	terrain->Render();
	monsterSpawnManager->Render();
	//alduin->Render();
}

void TestScene::PostRender()
{
}

void TestScene::GUIRender()
{
	monsterSpawnManager->GUIRender();
	//alduin->GUIRender();
}
