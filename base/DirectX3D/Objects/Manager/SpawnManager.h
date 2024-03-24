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
		{ "bear_sleep", "bear_startsleep", "bear_wakeup","bear_idle", "bear_combatidle","bear_run_forward", "bear_attack", "bear_attack2",
			"bear_attack3", "bear_attack_standing", "bear_hit", "bear_headshake", "bear_death" },
		{ "wolf_idle", "wolf_combatidle", "wolf_walk", "wolf_howling" ,"wolf_run_forward", "wolf_attack", "wolf_attack2", "wolf_attack3",
			"wolf_attack4", "wolf_hit", "wolf_death"}
	};

	vector<vector<Vector3>> posTable =
	{
		{ Vector3(290, 0, 365)/*, Vector3(180, 10, 200), Vector3(-100, 2000, -200) */},
		{ Vector3(350, 0, 250)}
	};

	vector<Character::Status> statusTable =
	{
		Character::Status(15, 100, 200, 20, 2.5),
		Character::Status(10, 80, 100, 10, 3.5)
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
	Player* GetPlayerData() { return playerData; }

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

