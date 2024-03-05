#pragma once

class EnemySpawn
{
public:
	EnemySpawn(ModelAnimatorInstancing* modelAnimatorInstancing, Enemy* enemy, vector<Vector3> enemySpawnPos);
	~EnemySpawn();

	void Update();
	void Render();
	void GUIRender();

	void SetPlayerData(Player* player);

	vector<Enemy*>& GetEnemies() { return enemies; }
	void Spawn();

private:
	Player* playerData;

	ModelAnimatorInstancing* instancing;
	vector<Enemy*> enemies;
	vector<Vector3> spawnPos;
};
