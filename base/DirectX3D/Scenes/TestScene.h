#pragma once

class TestScene : public Scene
{
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
	ModelAnimatorInstancing* monsterInstancing;
	vector<Enemy*> enemies;
	vector<vector<Vector3>> spawnPoses;
	EnemySpawnManager* monsterSpawnManager;
	ModelAnimator* alduin;
};

