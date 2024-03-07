#include "Framework.h"

EnemySpawn::EnemySpawn(ModelAnimatorInstancing* modelAnimatorInstancing, Enemy* enemy, vector<Vector3> enemySpawnPos)
	: instancing(modelAnimatorInstancing), spawnPos(enemySpawnPos)
{
	FOR(spawnPos.size())
	{
		Transform* transform = instancing->Add();
		transform->Scale() *= 0.001f;
		Enemy* tmp = new Enemy(enemy->GetName(), i, instancing, transform, spawnPos[i], 50000);
		tmp->SetStatus(enemy->GetStatus());
		tmp->GetCollier()->Scale() *= 1000.0f;
		enemies.push_back(tmp);
	}
}

EnemySpawn::~EnemySpawn()
{
	delete instancing;
	for (Enemy* enemy : enemies)
		delete enemy;
}

void EnemySpawn::Update()
{
	instancing->Update();

	for (Enemy* enemy : enemies)
		enemy->Update();

	for (Enemy* enemy : enemies)
	{
		if (playerData->GetCollier()->IsCollision(enemy->GetTrackCollider()))
		{
			enemy->SetTarget(playerData);
		}
		else
		{
			enemy->SetTarget(nullptr);
		}
	}
}

void EnemySpawn::Render()
{
	instancing->Render();
	for (Enemy* enemy : enemies) enemy->Render();
}

void EnemySpawn::GUIRender()
{
	instancing->GUIRender();
	for (Enemy* enemy : enemies) enemy->GUIRender();
}

void EnemySpawn::Spawn()
{
	for (Enemy* enemy : enemies)
		enemy->Spawn();
}
