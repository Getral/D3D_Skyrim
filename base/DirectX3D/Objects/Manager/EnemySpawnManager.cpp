#include "Framework.h"

EnemySpawnManager::EnemySpawnManager(ModelAnimatorInstancing* modelAnimatorInstancing, Enemy* enemy, vector<Vector3> enemySpawnPos)
	: instancing(modelAnimatorInstancing), spawnPos(enemySpawnPos)
{
	FOR(spawnPos.size())
	{
		Transform* transform = instancing->Add();
		transform->Scale() *= 0.001f;
		Enemy* tmp = new Enemy(enemy->GetName(), transform, spawnPos[i]);
		tmp->SetStatus(enemy->GetStatus());
		enemies.push_back(tmp);
	}
}

EnemySpawnManager::~EnemySpawnManager()
{
	delete instancing;
	for (Enemy* enemy : enemies)
		delete enemy;
}

void EnemySpawnManager::Update()
{
	instancing->Update();

	for (Enemy* enemy : enemies)
		enemy->Update();
}

void EnemySpawnManager::Render()
{
	instancing->Render();
	for (Enemy* enemy : enemies) enemy->Render();
}

void EnemySpawnManager::GUIRender()
{
	instancing->GUIRender();
	for (Enemy* enemy : enemies) enemy->GUIRender();
}

void EnemySpawnManager::Spawn()
{
	for (Enemy* enemy : enemies)
		enemy->Spawn();
}
