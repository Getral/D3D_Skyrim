#pragma once

class PlayerScene : public Scene
{

public:
	PlayerScene();
	~PlayerScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

private:
	Terrain* terrain;
	Player* player;

};

