#pragma once

class TerrainScene : public Scene
{
private:
	UINT terrainSize = 10;

public:
	TerrainScene();
	~TerrainScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

private:
	UINT width = 1;
	UINT height = 1;

	Player* player;

	float testPos;

	vector<vector<Terrain*>> terrain;
	//Terrain* terrain;
};

