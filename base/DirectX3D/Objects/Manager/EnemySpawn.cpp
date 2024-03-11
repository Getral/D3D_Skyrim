#include "Framework.h"

EnemySpawn::EnemySpawn(ModelAnimatorInstancing* modelAnimatorInstancing, Enemy* enemy, vector<Vector3> enemySpawnPos)
	: instancing(modelAnimatorInstancing), spawnPos(enemySpawnPos)
{
	FOR(spawnPos.size())
	{
		Transform* transform = instancing->Add();
		transform->Scale() *= 0.001f;
		transform->UpdateWorld();
		Enemy* tmp;
		if (enemy->GetName() == "Bear")
			tmp = new Bear(enemy->GetName(), i, instancing, transform, spawnPos[i], 50000);
		else if (enemy->GetName() == "Wolf")
			tmp = new Wolf(enemy->GetName(), i, instancing, transform, spawnPos[i], 50000);
		else
			tmp = new Enemy(enemy->GetName(), i, instancing, transform, spawnPos[i], 50000);
		tmp->SetStatus(enemy->GetStatus());
		tmp->GetCollider()->Scale() *= 1000.0f;
		tmp->SetPlayerData(playerData);
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

void EnemySpawn::SetPlayerData(Player* player)
{
	playerData = player;
	for (Enemy* enemy : enemies) enemy->SetPlayerData(player);
	Spawn();
}

void EnemySpawn::Spawn()
{
	for (Enemy* enemy : enemies)
		enemy->Spawn();
}
