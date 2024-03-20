#pragma once
class UIManager : public Singleton<UIManager>
{
public:
	UIManager();
	~UIManager();

	void Update(Player* player, vector<EnemySpawn*> enemies, alduin* alduin);
	void Render();
	void PostRender();
	void GUIRender();

	
	InvenUI* GetInvenUI() { return invenUI; }

	void TargetCompassEnemy(Player* player, vector<EnemySpawn*> enemies, alduin* alduin);

	//float GetEnemyDegree() { return final_angle; }

private:
	Quad* compass;
	vector<Quad*> compass_dir;
	vector<Quad*> enemies_dir;

	Quad* enemy_dir;
	Quad* bossQuest_dir;

	Quad* HP_bar_background;
	Quad* HP_bar;
	float maxHpBar;
	float HP_ratio;

	Quad* SP_bar_background;
	ProgressBar* SP_bar;

	Quad* enemy_HP_bar_background;
	ProgressBar* enemy_HP_bar;

	Quad* enemyName_bear;

	float tmp_N;
	float tmp_S;
	float tmp_W;
	float tmp_E;

	float dirX_tmp[4];

	vector<float> final_angles;

	int monsterCount = 0;

	bool isQuest = true;
	
	InvenUI* invenUI;
	bool isInven = false;

	ItemStatus* itemstatus;
};

