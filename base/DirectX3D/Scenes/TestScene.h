#pragma once

class TestScene : public Scene
{
private:
	enum MonsterName {
		BEAR,
		WOLF
	};

public:
	TestScene();
	~TestScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

private:
	Terrain* terrain;
	vector<string> monsterName;
	vector<vector<string>> clipName;
	vector<ModelAnimatorInstancing*> monsterInstancing;
	vector<Enemy*> enemies;
	vector<vector<Vector3>> spawnPoses;
	vector<EnemySpawnManager*> monsterSpawnManager;
	ModelAnimator* alduin;
};

