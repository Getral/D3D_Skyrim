#pragma once

class MonsterScene : public Scene
{
public:
	MonsterScene();
	~MonsterScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

private:
	Terrain* terrain;
	ModelAnimator* alduin;
};

