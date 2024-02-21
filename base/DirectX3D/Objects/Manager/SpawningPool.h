#pragma once

class SpawningPool
{
public:
	SpawningPool(ModelAnimatorInstancing* monsterInstancing, Vector3 centerPos, float spawnRange = 100.0f, float spawnTime = 3.0f, UINT SIZE = 10);
	~SpawningPool();

	void Update();
	void Render();
	void GUIRender();

	void Spawn();

private:
	ModelAnimatorInstancing* monsterInstancing;
	vector<Monster*> monsters;

	UINT SIZE;
	float spawnRange;
	float spawnTime;
	float time;
	Vector3 centerPos;
};
