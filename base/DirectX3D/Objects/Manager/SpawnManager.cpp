#include "Framework.h"

SpawnManager::SpawnManager()
{
	monsterName.push_back("Bear");


	FOR(MONSTER_SIZE)
	{
		monsterInstancing.push_back(new ModelAnimatorInstancing("Bear"));
		for (int j = 0; j < clipNameTable[i].size(); j++)
			monsterInstancing[i]->ReadClip(clipNameTable[i][j]);

		enemies.push_back(new Enemy(monsterName[i], i, monsterInstancing[i]));
		enemies[i]->SetStatus(statusTable[i]);

		EnemySpawn* tmp = new EnemySpawn(monsterInstancing[i], enemies[i], posTable[i]);
		tmp->Spawn();
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
		msm->SetPlayerData(playerData);
}
