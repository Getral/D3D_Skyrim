#pragma once

class EnemySpawnManager
{
public:
	EnemySpawnManager(ModelAnimatorInstancing* modelAnimatorInstancing, Enemy* enemy, vector<Vector3> enemySpawnPos);
	~EnemySpawnManager();

	void Update();
	void Render();
	void GUIRender();

	void Spawn();

private:
	ModelAnimatorInstancing* instancing;
	vector<Enemy*> enemies;
	vector<Vector3> spawnPos;
};
