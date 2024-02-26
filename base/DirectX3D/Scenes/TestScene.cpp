#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	terrain = new Terrain();
	terrain->Pos() = { -terrain->GetSize().x / 2, 0, -terrain->GetSize().y / 2 };
	terrain->UpdateWorld();

	monsterName.push_back("Bear");
	
	clipName[BEAR] = { "bear_idle", "bear_attack", "bear_hit" };

	FOR(monsterName.size())
	{
		monsterInstancing.push_back(new ModelAnimatorInstancing("Bear"));
		for (int j = 0; j < clipName[i].size(); j++)
			monsterInstancing[i]->ReadClip(clipName[i][j]);
	}

	vector<Vector3> poses1;
	poses1.push_back(Vector3(50, 0, 50));
	spawnPoses.push_back(poses1);

	enemies.push_back(new Enemy("bear"));
	enemies[0]->SetStatus(100, 1000, 1000, 50, 10);
	
	FOR(2)
	{
		monsterSpawnManager.push_back(new EnemySpawnManager(monsterInstancing[i], enemies[i], spawnPoses[i]));
		monsterSpawnManager[i]->Spawn();
	}
}

TestScene::~TestScene()
{
	delete terrain;
	delete alduin;
	for (ModelAnimatorInstancing* mi : monsterInstancing)
		delete mi;
	for (EnemySpawnManager* msm : monsterSpawnManager)
		delete msm;
}

void TestScene::Update()
{
	for (EnemySpawnManager* msm : monsterSpawnManager)
		msm->Update();
	//alduin->Update();
}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	terrain->Render();
	for (EnemySpawnManager* msm : monsterSpawnManager)
		msm->Render();
	//alduin->Render();
}

void TestScene::PostRender()
{
}

void TestScene::GUIRender()
{
	for (EnemySpawnManager* msm : monsterSpawnManager)
		msm->GUIRender();
	//alduin->GUIRender();
}
