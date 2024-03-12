#pragma once

class SpawnManager : public Singleton<SpawnManager>
{
private:
	enum MonsterName
	{
		BEAR,
		WOLF
	};

	vector<string> monsterName = {
		"Bear", "Wolf"
	};

	vector<vector<string>> clipNameTable =
	{
		{ "bear_idle", "bear_run_forward", "bear_attack", "bear_attack2", "bear_attack3", "bear_hit"},
		{ "wolf_idle", "wolf_run_forward", "wolf_attack"}
	};

	vector<vector<Vector3>> posTable =
	{
		{ Vector3(50, 0, 50), Vector3(-20, 0, 30), Vector3(-10, 0, -20) },
		{ Vector3(10, 0, -20), Vector3(-100, 0, 50), Vector3(75, 0, 80) }
	};

	vector<Character::Status> statusTable =
	{
		Character::Status(15, 300, 200, 20, 25),
		Character::Status(10, 150, 100, 10, 15)
	};

	UINT MONSTER_SIZE = 2;
	UINT MONSTER_COUNT_ACTIVATED = 0;
	UINT MONSTER_COUNT = 0;

public:
	SpawnManager();
	~SpawnManager();

	void Update();
	void Render();
	void GUIRender();

	void SetPlayerData(Player* player);

	ModelAnimatorInstancing* GetMonsterInstancingWithIndex(int index) { return monsterInstancing[index]; }
	Enemy* GetEnemyWithIndex(int index) { return enemies[index]; }
	vector<EnemySpawn*> GetMonsterSpawnManager() { return monsterSpawnManager; }
	EnemySpawn* GetMonsterSpawnManagerWithIndex(int index) { return monsterSpawnManager[index]; }

	vector<ModelAnimatorInstancing*> &GetMonsterInstancing() { return monsterInstancing; }
	vector<Enemy*> &GetEnemies() { return enemies; }

	UINT GetActivatedMonsterCount();
	UINT GetMonsterCount();

private:
	Player* playerData;

	vector<ModelAnimatorInstancing*> monsterInstancing;
	vector<Enemy*> enemies;
	
	vector<EnemySpawn*> monsterSpawnManager;

};

