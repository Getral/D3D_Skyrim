#pragma once

class SpawnManager : public Singleton<SpawnManager>
{
private:
	enum MonsterName
	{
		BEAR,
		WOLF
	};

	vector<vector<string>> clipNameTable =
	{
		{ "bear_idle", "bear_run_forward", "bear_attack", "bear_hit"}
	};

	vector<vector<Vector3>> posTable =
	{
		{ Vector3(50, 0, 50), Vector3(-20, 0, 30), Vector3(-10, 0, -20) }
	};

	vector<Character::Status> statusTable =
	{
		Character::Status(100, 1000, 1000, 50, 10)
	};

	UINT MONSTER_SIZE = 1;

public:
	SpawnManager();
	~SpawnManager();

	void Update();
	void Render();
	void GUIRender();

	void SetPlayerData(Player* player);

	ModelAnimatorInstancing* GetMonsterInstancingWithIndex(int index) { return monsterInstancing[index]; }
	Enemy* GetEnemyWithIndex(int index) { return enemies[index]; }

	vector<ModelAnimatorInstancing*> &GetMonsterInstancing() { return monsterInstancing; }
	vector<Enemy*> &GetEnemies() { return enemies; }

private:
	Player* playerData;

	vector<string> monsterName;
	vector<ModelAnimatorInstancing*> monsterInstancing;
	vector<Enemy*> enemies;
	
	vector<EnemySpawn*> monsterSpawnManager;

};

