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
	bool IsIntro() { return isIntro; }

	void TargetCompassEnemy(Player* player, vector<EnemySpawn*> enemies, alduin* alduin);

	void GetClosestEnemy(Player* player, vector<EnemySpawn*> enemies);
	//float GetEnemyDegree() { return final_angle; }

	void StartOuttro();

private:
	Quad* compass;
	vector<Quad*> compass_dir;
	vector<Quad*> enemies_dir;

	Quad* boss_dir;
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
	Quad* enemyName_wolf;
	Quad* enemyName_alduin;

	float tmp_N;
	float tmp_S;
	float tmp_W;
	float tmp_E;

	float dirX_tmp[4];

	vector<float> final_angles;
	vector<float> distances;

	Character* curEnemy;

	int monsterCount = 0;

	bool isQuest = true;
	
	InvenUI* invenUI;
	bool isInven = false;

	ItemStatus* itemstatus;

	int timer = 0;

	bool aldu_isSleeping = true;
	
	Quad* intro_title;
	Quad* intro_backGround;
	bool isIntro = true;
	bool isHoverPlay = false;
	bool isHoverExit = false;

	Quad* outtro_backGround;
	bool isOuttro = false;
};

