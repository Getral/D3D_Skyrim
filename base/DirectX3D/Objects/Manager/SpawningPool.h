#pragma once

class SpawningPool
{
public:
	SpawningPool(ModelAnimatorInstancing* monsterInstancing, Vector3 centerPos, UINT SIZE = 10, float spawnRange = 100.0f, float spawnTime = 3.0f );
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
