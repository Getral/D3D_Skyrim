#include "Framework.h"
#include "SpawnManager.h"

SpawnManager::SpawnManager()
{
	MONSTER_SIZE = (UINT)monsterName.size();
	FOR(MONSTER_SIZE)
	{
		monsterInstancing.push_back(new ModelAnimatorInstancing(monsterName[i]));
		for (int j = 0; j < clipNameTable[i].size(); j++)
			monsterInstancing[i]->ReadClip(clipNameTable[i][j]);

		if (monsterName[i] == "Bear")
			enemies.push_back(new Bear(monsterName[i], i, monsterInstancing[i]));
		else if (monsterName[i] == "Wolf")
			enemies.push_back(new Wolf(monsterName[i], i, monsterInstancing[i]));
		enemies[i]->SetStatus(statusTable[i]);

		EnemySpawn* tmp = new EnemySpawn(monsterInstancing[i], enemies[i], posTable[i]);
		monsterSpawnManager.push_back(tmp);
	}
}

SpawnManager::~SpawnManager()
{
	for (ModelAnimatorInstancing* mi : monsterInstancing)
		delete mi;
	for (EnemySpawn* msm : monsterSpawnManager)
		delete msm;
}

void SpawnManager::Update()
{
	for (ModelAnimatorInstancing* mi : monsterInstancing)
		mi->Update();
	for (EnemySpawn* msm : monsterSpawnManager)
		msm->Update();
}

void SpawnManager::Render()
{
	for (ModelAnimatorInstancing* mi : monsterInstancing)
		mi->Render();
	for (EnemySpawn* msm : monsterSpawnManager)
		msm->Render();
}

void SpawnManager::GUIRender()
{
	for (ModelAnimatorInstancing* mi : monsterInstancing)
		mi->GUIRender();
	for (EnemySpawn* msm : monsterSpawnManager)
		msm->GUIRender();
}

void SpawnManager::SetPlayerData(Player* player)
{
	playerData = player;
	for (EnemySpawn* msm : monsterSpawnManager)
	{
		msm->SetPlayerData(playerData);
	}
}

UINT SpawnManager::GetActivatedMonsterCount()
{
	MONSTER_COUNT_ACTIVATED = 0;
	for (int i = 0; i < monsterSpawnManager.size(); i++)
	{
		for (int j = 0; j < monsterSpawnManager[i]->GetEnemies().size(); j++)
		{
			if (monsterSpawnManager[i]->GetEnemies()[j]->GetTransform()->Active())
			{
				MONSTER_COUNT_ACTIVATED++;
			}
		}
	}
	return MONSTER_COUNT_ACTIVATED;
}

UINT SpawnManager::GetMonsterCount()
{
	MONSTER_COUNT = 0;
	for (int i = 0; i < monsterSpawnManager.size(); i++)
	{
		for (int j = 0; j < monsterSpawnManager[i]->GetEnemies().size(); j++)
		{
			MONSTER_COUNT++;
		}
	}
	return MONSTER_COUNT;
}
