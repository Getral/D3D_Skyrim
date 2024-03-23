#pragma once

class TerrainScene : public Scene
{
private:
	UINT terrainSize = 10;

	vector<string> objectName =
	{
		"rock_large1", "rock_large2", "rock_large3", "rock_large4", "rock_large5",
		"rock_medium1", "rock_medium2", "rock_medium3", "rock_medium4", "tree", "chest"
	};

	vector<vector<Vector3>> objectPos =
	{
		{ Vector3(178, 12, 200), Vector3(200, 0, 200), Vector3(210, 15, 230), Vector3(300, 3, 225), Vector3(300, 5, 175),
			Vector3(300, 1, 310), Vector3(257, 0.1, 357) }, // rock_large1
		{ Vector3(300, 0, 200), Vector3(270, 0, 228.5), Vector3(227.5, 0, 263), Vector3(213, 0, 345), Vector3(227.3, 0, 329.5),
			Vector3(200, 0, 100), Vector3(288.9, 0.5, 154.3), Vector3(168.8, 0.5, 163.6) }, // rock_large2
		{ Vector3(188, 0, 125.5), Vector3(246, 0, 203), Vector3(278, -1, 189.5), Vector3(277.8, 6.5, 205.3), Vector3(307.5, 1, 208),
			Vector3(303.6, 1.5, 215.2), Vector3(296.6, -0.3, 246.4), Vector3(256.7, -0.5, 240.5), Vector3(273.7, -0.5, 307.9) }, // rock_large3
		{ Vector3(284.5, 0, 196.5), Vector3(307.5, 0, 184), Vector3(296.8, 0, 235.7), Vector3(220.9, -2.4, 256.4), Vector3(172.3, 25.3, 241.7),
			Vector3(178.9, 7.5, 282.3), Vector3(193.3, 7.5, 336.1), Vector3(229.9, -0.7, 342.2), Vector3(265.6, -0.7, 344.3), 
			Vector3(286,0,270), Vector3(278,0,263), Vector3(270,0,257), Vector3(262,0,257), Vector3(254,0,258), Vector3(247,0,258), Vector3(238,0,258),
			Vector3(232,0,258), Vector3(225,0,258), Vector3(225,0,272), Vector3(225,0,285), Vector3(225,0,296), Vector3(225,0,308), Vector3(225,0,318),
			Vector3(231,0,318), Vector3(241,0,318), Vector3(253,0,318), Vector3(259,0,315), Vector3(264,0,312), Vector3(270,0,313), Vector3(275,0,313),
			Vector3(282,0,313), Vector3(286,0,305), Vector3(291,0,303)}, // rock_large4
		{ Vector3(183, 0, 50), Vector3(202, 0, 112.4), Vector3(180.6, 0, 150), Vector3(234.2, 0, 206.4), Vector3(206.9, 0, 206.4),
			Vector3(307.7, 0, 181.8), Vector3(299.3, 0, 161.3), Vector3(300.3, 6.4, 211.7), Vector3(307.2, 1.1, 232.4), Vector3(298.9, -0.7, 297.4),
			Vector3(288.4, -2.7, 297.5), Vector3(282.6, -2.7, 303.1), Vector3(294.8, 4.6, 309.1), Vector3(208.2, -0.4, 309.1), Vector3(182.8, 11.6, 209.5),
			Vector3(179.4, 24.9, 243.1), Vector3(179.4, 24.9, 234.8), Vector3(153.1, 46, 231.9), Vector3(122.8, 46, 199.1), Vector3(152.9, 46, 258), 
			Vector3(151.6, 20.8, 298.2), Vector3(185, 6.7, 332), Vector3(165.7, 6.7, 185.7) }, // rock_large5
		{ Vector3(182.6, 0, 156.5), Vector3(167.4, 5.9, 170.7), Vector3(179.5, 1.5, 170.7), Vector3(227.3, -1.2, 179.5), Vector3(233.7, -1.2, 184.8),
			Vector3(224.7, 5, 188), Vector3(225.3, 6.4, 202.9), Vector3(205.5, 6.4, 202.9), Vector3(192, 5.7, 200.5), Vector3(190.7, 9, 204.3),
			Vector3(264.1, 4.5, 214.7), Vector3(248.6, 9.7, 224.8), Vector3(261.2, 4.4, 221.5), Vector3(292.3, 15.5, 214.8), Vector3(292.6, 18, 200.7),
			Vector3(300.4, 13, 184.4), Vector3(291.9, 11.1, 171.1), Vector3(296.1, 7.8, 165.2), Vector3(289.7, 7.3, 161.2), Vector3(303, 9, 200),
			Vector3(312.7, 0.9, 190.1), Vector3(307.7, 2.9, 243.2), Vector3(314.2, -1, 310.5), Vector3(295.8, -1, 325.1), Vector3(275.3, 0.1, 373.7)}, // rock_medium1
		{ Vector3(304.6, 0, 169.7), Vector3(314.1, 0, 196.1), Vector3(303.8, 5.4, 239.6), Vector3(286.5, 4.7, 223.3), Vector3(256.6, 2.5, 209),
			Vector3(236, 0.6, 197.8), Vector3(182.5, 0.6, 175), Vector3(169.8, 4, 180.6), Vector3(197.1, 0.5, 117.5), Vector3(182.1, 2.4, 134.9),
			Vector3(176.3, 1.3, 128.3), Vector3(159.1, -0.5, 159.7), Vector3(189.3, -0.5, 75.7), Vector3(172.6, -0.6, 55), Vector3(100.8, 30, 162.9),
			Vector3(129.6, 22.8, 133.7) }, // rock_medium2
		{ Vector3(220.4, 0, 182), Vector3(209.3, 0, 190.6), Vector3(191.5, 0, 149.2), Vector3(197.4, 0, 136.5), Vector3(229.5, 0, 183.4),
			Vector3(234.1, 0, 190.4), Vector3(226.3, 5.7, 214.7), Vector3(196.8, 5.7, 206.9), Vector3(172.3, 2.1, 177.3), Vector3(305, 6.8, 187),
			Vector3(301.7, 8.3, 233.3), Vector3(294.1, -2.4, 294.9), Vector3(289, 4.3, 302.6), Vector3(273.7, 4.3, 314.8), Vector3(249.9, 0.7, 325.2),
			Vector3(216.7, 0.7, 288.3), Vector3(188.5, 24.5, 234.6), Vector3(176.6, 18.9, 210.1), Vector3(179.1, -0.7, 65.9), Vector3(191.1, -0.7, 30.7),
			Vector3(210.9, -1.5, 78.1) }, // rock_medium3
		{ Vector3(200.2, 0, 146.6), Vector3(188.1, 3.1, 136.4), Vector3(205, 2, 107.9), Vector3(216.1, 2.3, 88.7), Vector3(206.9, -1, 182),
			Vector3(134.2, 32.1, 193.5), Vector3(159, 31.6, 220.2) }, // rock_medium4
		{ Vector3(157, 18, 146), Vector3(159, 16, 113), Vector3(179, 9, 102), Vector3(162, 12, 184), Vector3(189, 10, 199),Vector3(214, 12, 199),
			Vector3(233, 9, 217),Vector3(262, 6, 198), Vector3(292, 12, 164), Vector3(297, 17, 210), Vector3(299, 15, 231), Vector3(292, 6, 262), Vector3(239, 0, 305),
			Vector3(148, 7, 163), Vector3(168, 8, 129),Vector3(217, 2, 91),Vector3(141, 18, 175),Vector3(180, 6, 181),Vector3(228, 6, 204),Vector3(246, 11, 226),
			Vector3(271, 0, 254),Vector3(290, 10, 308),Vector3(262, 10, 324),Vector3(208, 4, 285),Vector3(204, 12, 262),Vector3(215, 14, 241),Vector3(206, 6, 327),Vector3(168, 33, 265)}, //Tree
		{ Vector3(350, 0, 150) }
	};

	vector<vector<float>> objectRot =
	{
		{ 0, 0, 0, 0, 0, 0, 0 }, // rock_large1
		{ 0, 0, 0, 0, 0, 0, 0, 0 }, // rock_large2
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // rock_large3
		{ 0, 0, 0, -87, -52, 53, 53, -53, 158, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // rock_large4
		{ 0, -62, -175, 50, 87, 19, -12, 134, 170, -148, -62, -62, -1, 55, 28, -75, 82, 19, 26,
			147, 147, 60, 39 }, // rock_large5
		{ 0, 46, -46, 46, -72, 38, -109, -136, -158, -17, -118, 27, -63, -42, -94, -61, -69, -52,
			85, -80, -60, -103, -78, -148, -15 }, // rock_medium1
		{ -32, 12, -39, -84, -35, -99, 39, 44, -35, 25, 116, 116, 89, -37, 72, 98 }, // rock_medium2
		{ -175, 169, -25, 79, 105, 61, 115, 115, 65, 107, 78, 160, 180, 123, -160, 68, 167, 93, 98,
			60, 109 }, // rock_medium3
		{ 104, 35, -2, -121, -174, -119, -67 }, // rock_medium4
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		  0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0 }
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
	Model* tree01;
	Model* tree02;

	SkyBox* skyBox;
	//Terrain* terrain;
};

