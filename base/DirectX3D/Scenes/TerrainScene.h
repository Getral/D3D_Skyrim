#pragma once

class TerrainScene : public Scene
{
private:
	UINT terrainSize = 10;

	vector<string> objectName =
	{
		"rock_large1", "rock_large2", "rock_large3", "rock_large4", "rock_large5",
		"rock_medium1", "rock_medium2", "rock_medium3", "rock_medium4",
		"rock_small1", "rock_small2"
	};

	vector<vector<Vector3>> objectPos =
	{
		{ Vector3(178, 12, 200), Vector3(200, 0, 200), Vector3(210, 15, 230), Vector3(300, 3, 225), Vector3(300, 5, 175),
			Vector3(300, 1, 310), Vector3(257, 0.1, 357) }, // rock_large1
		{ Vector3(300, 0, 200), Vector3(270, 0, 228.5), Vector3(227.5, 0, 263), Vector3(213, 0, 345), Vector3(227.3, 0, 329.5),
			Vector3(200, 0, 100), Vector3(288.9, 0.5, 154.3), Vector3(168.8, 0.5, 163.6) }, // rock_large2
		{ Vector3(188, 0, 125.5), Vector3(246, 0, 203), Vector3(278, -1, 189.5), Vector3(277.8, 6.5, 205.3), Vector3(307.5, 1, 208),
			Vector3(303.6, 1.5, 215.2), Vector3(296.6, -0.3, 246.4), Vector3(256.7, -0.5, 240.5), Vector3(273.7, -0.5, 307.9) }, // rock_large3
		{ Vector3(284.5, 0, 196.5), Vector3(307.5, 184), Vector3(296.8, 0, 235.7), Vector3(220.9, -2.4, 256.4), Vector3(172.3, 25.3, 241.7),
			Vector3(178.9, 7.5, 282.3), Vector3(193.3, 7.5, 336.1), Vector3(229.9, -0.7, 342.2), Vector3(265.6, -0.7, 344.3) }, // rock_large4
		{ Vector3(183, 0, 50), Vector3(202, 0, 112.4), Vector3(180.6, 0, 150), Vector3(234.2, 0, 206.4), Vector3(206.9, 0, 206.4),
			Vector3(307.7, 0, 181.8), Vector3(299.3, 0, 161.3), Vector3(300.3, 6.4, 211.7), Vector3(307.2, 1.1, 232.4), Vector3(298.9, -0.7, 297.4),
			Vector3(288.4, -2.7, 297.5), Vector3(282.6, -2.7, 303.1), Vector3(294.8, 4.6, 309.1), Vector3(208.2, -0.4, 309.1), Vector3(182.8, 11.6, 209.5),
			Vector3(179.4, 24.9, 243.1), Vector3(179.4, 24.9, 234.8), Vector3(153.1, 46, 231.9), Vector3(122.8, 46, 199.1), Vector3(152.9, 46, 258), 
			Vector3(151.6, 20.8, 298.2), Vector3(185, 6.7, 332), Vector3(165.7, 6.7, 185.7) }, // rock_large5
		{ Vector3(0, 0, 0) }, // rock_medium1
		{ Vector3(0, 0, 0) }, // rock_medium2
		{ Vector3(0, 0, 0) }, // rock_medium3
		{ Vector3(0, 0, 0) }, // rock_medium4
		{ Vector3(0, 0, 0) }, // rock_small1
		{ Vector3(0, 0, 0) } // rock_small2
	};

	vector<vector<float>> objectRot =
	{
		{ 0, 0, 0, 0, 0, 0, 0 }, // rock_large1
		{ 0, 0, 0, 0, 0, 0, 0, 0 }, // rock_large2
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // rock_large3
		{ 0, 0, 0, -87, -52, 53, 53, -53, 158 }, // rock_large4
		{ 0, -62, -175, 50, 87, 19, -12, 134, 170, -148, -62, -62, -1, 55, 28, -75, 82, 19, 26,
			147, 147, 60, 39 }, // rock_large5
		{ 0 }, // rock_medium1
		{ 0 }, // rock_medium2
		{ 0 }, // rock_medium3
		{ 0 }, // rock_medium4
		{ 0 }, // rock_small1
		{ 0 } // rock_small2
	};

public:
	TerrainScene();
	~TerrainScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

private:
	Model* testModel;

	Model* tree01;
	Model* tree02;
	//Terrain* terrain;
};

