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
	ModelAnimator* alduin;
	SpawningPool* spawningPool;
};

