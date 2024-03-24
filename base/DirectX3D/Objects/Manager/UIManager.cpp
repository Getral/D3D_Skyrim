#include "Framework.h"

UIManager::UIManager()
{
	compass = new Quad(L"Textures/UI/Compass.png");
	compass->Pos() = { CENTER_X, WIN_HEIGHT * 0.95, 0 };
	compass->Scale() *= 0.1f;
	compass->UpdateWorld();

#pragma region compass_dir_quad
	compass_dir.push_back(new Quad(L"Textures/UI/Compass_N.png"));
	compass_dir.back()->SetParent(compass);
	compass_dir.back()->Scale() *= 10;

	compass_dir.push_back(new Quad(L"Textures/UI/Compass_S.png"));
	compass_dir.back()->SetParent(compass);
	compass_dir.back()->Scale() *= 15;

	compass_dir.push_back(new Quad(L"Textures/UI/Compass_W.png"));
	compass_dir.back()->SetParent(compass);
	compass_dir.back()->Scale() *= 15;

	compass_dir.push_back(new Quad(L"Textures/UI/Compass_E.png"));
	compass_dir.back()->SetParent(compass);
	compass_dir.back()->Scale() *= 15;
#pragma endregion

#pragma region enemy_dirquad
	monsterCount = SpawnManager::Get()->GetMonsterCount();

	FOR(monsterCount)
	{
		enemies_dir.push_back(new Quad(L"Textures/UI/enemy_dir.png"));
		enemies_dir.back()->SetParent(compass);
		enemies_dir.back()->Scale() *= 0.4f;
		final_angles.push_back(0.0f);
	}
	boss_dir = new Quad(L"Textures/UI/enemy_dir.png");
	boss_dir->SetParent(compass);
	boss_dir->Scale() *= 0.4f;
	final_angles.push_back(0.0f);

	bossQuest_dir = new Quad(L"Textures/UI/Quest.png");
	bossQuest_dir->SetParent(compass);


#pragma endregion

#pragma region status_bar
	HP_bar_background = new Quad(L"Textures/UI/status_bar.png");
	HP_bar_background->Pos() = { CENTER_X,WIN_HEIGHT * 0.05,0 };
	HP_bar_background->Scale() *= 0.1f;
	HP_bar_background->Scale().x *= 1.5f;
	HP_bar_background->UpdateWorld();

	HP_bar = new Quad(L"Textures/UI/hp_bar.png");
	HP_bar->SetParent(HP_bar_background);
	HP_bar->Scale() *= 5.0f;
	HP_bar->Scale().x *= 2.3f;

	maxHpBar = HP_bar->Scale().x;

	SP_bar_background = new Quad(L"Textures/UI/status_bar.png");
	SP_bar_background->Pos() = { WIN_WIDTH * 0.85, WIN_HEIGHT * 0.05,0 };
	SP_bar_background->Scale() *= 0.1f;
	SP_bar_background->Scale().x *= 1.5f;
	SP_bar_background->UpdateWorld();

	SP_bar = new ProgressBar(
		L"Textures/UI/sp_bar.png",
		L"Textures/UI/none.png",
		true
	);
	SP_bar->Pos() = { WIN_WIDTH * 0.85, WIN_HEIGHT * 0.05,0 };
	SP_bar->Scale() *= 0.7f;
	SP_bar->Scale().x *= 2.0f;
#pragma endregion

#pragma region enemy_status_bar
	enemy_HP_bar_background = new Quad(L"Textures/UI/enemyHP_background.png");
	enemy_HP_bar_background->Pos() = { CENTER_X,WIN_HEIGHT * 0.925f,0 };
	enemy_HP_bar_background->Scale().y *= 1.2f;
	enemy_HP_bar_background->UpdateWorld();

	enemy_HP_bar = new ProgressBar(
		L"Textures/UI/enemyHP_bar.png",
		L"Textures/UI/none.png",
		false,
		true
	);

	enemy_HP_bar->SetParent(enemy_HP_bar_background);

	enemyName_bear = new Quad(L"Textures/UI/enemyName_Bear.png");
	enemyName_bear->Pos() = { CENTER_X,WIN_HEIGHT * 0.9f,0 };
	enemyName_bear->Scale() *= 0.1f;
	enemyName_bear->UpdateWorld();

	enemyName_wolf = new Quad(L"Textures/UI/enemyName_Wolf.png");
	enemyName_wolf->Pos() = { CENTER_X,WIN_HEIGHT * 0.9f,0 };
	enemyName_wolf->Scale() *= 0.1f;
	enemyName_wolf->UpdateWorld();

	enemyName_alduin = new Quad(L"Textures/UI/enemyName_Alduin.png");
	enemyName_alduin->Pos() = { CENTER_X,WIN_HEIGHT * 0.9f,0 };
	enemyName_alduin->Scale() *= 0.1f;
	enemyName_alduin->UpdateWorld();
#pragma endregion

	invenUI = new InvenUI();

	itemstatus = new ItemStatus();

	intro_title = new Quad(L"Textures/UI/Intro/Logo.jpg");
	intro_title->Pos() = { WIN_WIDTH * 0.25f, WIN_HEIGHT * 0.6f };
	intro_title->Scale() *= 0.5f;

	intro_backGround = new Quad(L"Textures/UI/Intro/Background.jpg");
	intro_backGround->Pos() = { CENTER_X, CENTER_Y };

	outtro_backGround = new Quad(L"Textures/UI/Intro/Background.jpg");
	outtro_backGround->Pos() = { CENTER_X, CENTER_Y };

	journal_frame = new Quad(L"Textures/UI/journal_frame.png");
	journal_frame->GetMaterial()->SetShader(L"UI/EditAlpha.hlsl");
	journal_frame->Pos() = { CENTER_X, CENTER_Y };
	journal_frame->Scale() *= 0.1f;

	journal_frame_bar = new Quad(L"Textures/UI/journal_bar.png");
	journal_frame_bar->Pos() = { CENTER_X - 200.0f, CENTER_Y - 25.0f };
	journal_frame_bar->Scale() *= 0.1f;

	journal_frame_bar2 = new Quad(L"Textures/UI/journal_bar2.png");
	journal_frame_bar2->Pos() = { CENTER_X + 150.0f, CENTER_Y - 50.0f };
	journal_frame_bar2->Scale() *= 0.1f;

	journal_quest_select_icon = new Quad(L"Textures/UI/journal_arrow.png");
	journal_quest_select_icon->Pos() = { CENTER_X - 230.0f, CENTER_Y - 30.0f };
	journal_quest_select_icon->Scale() *= 0.1f;

	journal_quest_bar = new Quad(L"Textures/UI/quest_bar.png");
	journal_quest_bar->Pos() = { CENTER_X + 150.0f, CENTER_Y + 180.0f };
	journal_quest_bar->Scale() *= 0.1f;

	quest_icon_finished = new Quad(L"Textures/UI/quest_finished.png");
	quest_icon_finished->Pos() = { CENTER_X - 100.0f, CENTER_Y - 80.0f };
	quest_icon_finished->Scale() *= 0.1f;

	quest_icon_unfinished = new Quad(L"Textures/UI/quest_unfinished.png");
	quest_icon_unfinished->Pos() = { CENTER_X - 100.0f, CENTER_Y - 80.0f };
	quest_icon_unfinished->Scale() *= 0.1f;
}

UIManager::~UIManager()
{
	delete compass;
	for (Quad* dir : compass_dir)
		delete dir;
	delete boss_dir;

	delete HP_bar_background;
	delete HP_bar;

	delete SP_bar_background;
	delete SP_bar;

	delete intro_title;
	delete intro_backGround;

	delete outtro_backGround;

	delete journal_frame;
}

void UIManager::Update(Player* player, vector<EnemySpawn*> enemies, alduin* alduin)
{
	// 나침반 동서남북
#pragma region compass_dir
	tmp_N = XMConvertToDegrees(player->Rot().y);
	tmp_S = tmp_N + 180;
	tmp_W = tmp_N + 90;
	tmp_E = tmp_N - 90;

	dirX_tmp[0] = tmp_N;
	dirX_tmp[1] = tmp_S;
	dirX_tmp[2] = tmp_W;
	dirX_tmp[3] = tmp_E;

	FOR(4)
	{
		while (dirX_tmp[i] < -180)
			dirX_tmp[i] += 360;
		while (dirX_tmp[i] > 180)
			dirX_tmp[i] -= 360;
	}

	FOR(4)
	{
		compass_dir[i]->Pos().x = -dirX_tmp[i] * compass->GetSize().x / 140;
	}

	for (Quad* dir : compass_dir)
		dir->UpdateWorld();
#pragma endregion

#pragma region enemy_dir

	TargetCompassEnemy(player, enemies, alduin);

	FOR(monsterCount)
	{
		enemies_dir[i]->Pos().x = final_angles[i] * compass->GetSize().x / 140;
		enemies_dir[i]->UpdateWorld();
	}

	boss_dir->Pos().x = final_angles.back() * compass->GetSize().x / 140;
	boss_dir->UpdateWorld();

	bossQuest_dir->Pos().x = boss_dir->Pos().x;
	bossQuest_dir->UpdateWorld();


	int tmp = 0;
	for (int i = 0; i < enemies.size(); i++)
	{
		for (int j = 0; j < enemies[i]->GetEnemies().size(); j++)
		{
			if (enemies[i]->GetEnemies()[j]->GetTransform()->Active() && enemies[i]->GetEnemies()[j]->IsBattle() && alduin->GetIsSleeping() == true)
			{
				enemies_dir[tmp]->SetActive(true);
			}
			else
				enemies_dir[tmp]->SetActive(false);
			tmp++;
		}
	}

#pragma endregion

#pragma region player_hp
	HP_ratio = player->GetStatus().curHp / player->GetStatus().maxHp;
	HP_bar->Scale().x = maxHpBar * HP_ratio;
	HP_bar->UpdateWorld();

	SP_bar->SetAmount(player->GetStatus().curstamina / player->GetStatus().maxstamina);
	SP_bar->UpdateWorld();
#pragma endregion
	timer += 1 * DELTA;
	//if (timer > 3)
	{
		GetClosestEnemy(player, enemies);
		timer = 0;
	}

	if(alduin->GetIsSleeping() == false)
		enemy_HP_bar->SetAmount(alduin->GetHP() / alduin->GetMaxHP());

	else
		enemy_HP_bar->SetAmount(curEnemy->GetStatus().curHp / curEnemy->GetStatus().maxHp);

	enemy_HP_bar->UpdateWorld();

	aldu_isSleeping = alduin->GetIsSleeping(); // Render조건에 사용
	if (isInven)
		invenUI->Update(player);
	if (KEY_DOWN('I'))
		isInven = !isInven;

	if (isIntro)
	{
		intro_title->UpdateWorld();
		intro_backGround->UpdateWorld();

		if ((mousePos.x < WIN_WIDTH * 0.9f && mousePos.x > WIN_WIDTH * 0.8f) &&
			(mousePos.y < WIN_HEIGHT * 0.275f && mousePos.y > WIN_HEIGHT * 0.225f))
		{
			isHoverPlay = true;
			isHoverExit = false;
		}
		else if ((mousePos.x < WIN_WIDTH * 0.9f && mousePos.x > WIN_WIDTH * 0.8f) &&
			(mousePos.y < WIN_HEIGHT * 0.2f && mousePos.y > WIN_HEIGHT * 0.15f))
		{
			isHoverPlay = false;
			isHoverExit = true;
		}
		else
		{
			isHoverPlay = false;
			isHoverExit = false;
		}

		if (isHoverPlay && KEY_DOWN(VK_LBUTTON))
			isIntro = false;
		if (isHoverExit && KEY_DOWN(VK_LBUTTON))
			exit(0);
	}

	if (isOuttro)
	{
		outtro_backGround->UpdateWorld();
		if (KEY_DOWN(VK_LBUTTON))
			exit(0);
	}

	if (KEY_DOWN('J'))
		isOpenQuest = !isOpenQuest;

	if (isOpenQuest)
	{
		journal_frame->UpdateWorld();
		journal_frame_bar->UpdateWorld();
		if (isQuest)
		{
			journal_quest_select_icon->UpdateWorld();
			journal_quest_bar->UpdateWorld();
			journal_frame_bar2->UpdateWorld();
			if (!isQuestFinished)
				quest_icon_unfinished->UpdateWorld();
			else
				quest_icon_finished->UpdateWorld();
		}
	}

	if (questTextTime > 0.0f)
		questTextTime -= DELTA;
}

void UIManager::Render()
{
}

void UIManager::PostRender()
{
	compass->Render();
	FOR(4)
	{
		if (compass_dir[i]->Pos().x >= -60 * compass->GetSize().x / 140 && compass_dir[i]->Pos().x <= +60 * compass->GetSize().x / 140)
			compass_dir[i]->Render();
	}

	FOR(monsterCount)
	{
		if (enemies_dir[i]->Pos().x >= -60 * compass->GetSize().x / 140 && enemies_dir[i]->Pos().x <= +60 * compass->GetSize().x / 140)
			enemies_dir[i]->Render();
	}


	if (boss_dir->Pos().x >= -60 * compass->GetSize().x / 140 && boss_dir->Pos().x <= +60 * compass->GetSize().x / 140)
	{
	    if (isQuest)
	        bossQuest_dir->Render();
	    else
	        boss_dir->Render();
	}

	HP_bar_background->Render();
	HP_bar->Render();

	SP_bar_background->Render();
	SP_bar->Render();

	if (curEnemy->IsBattle() == true || aldu_isSleeping == false)
	{
		enemy_HP_bar_background->Render();
		enemy_HP_bar->Render();
	}
	



	if (aldu_isSleeping == false)
	{

		enemyName_alduin->Render();
	}
	else
	{
		if (curEnemy->IsBattle() == true)
		{
			if (curEnemy->GetName() == "Bear")
				enemyName_bear->Render();
			else if (curEnemy->GetName() == "Wolf")
				enemyName_wolf->Render();
		}
		
	}
	

	if (isInven)
		invenUI->Render();

	if (isIntro)
	{
		intro_backGround->Render();
		intro_title->Render();
		Font::Get()->SetStyle("Futura_big");
		if (isHoverPlay)
		{
			Font::Get()->SetStyle("Futura_more_big");
			Font::Get()->SetColor("White");
			Font::Get()->RenderText("PLAY", { WIN_WIDTH * 0.8f, WIN_HEIGHT * 0.25f });
			Font::Get()->SetStyle("Futura_big");
			Font::Get()->SetColor("Gray");
			Font::Get()->RenderText("EXIT", { WIN_WIDTH * 0.8f, WIN_HEIGHT * 0.175f });
		}
		else if (isHoverExit)
		{
			Font::Get()->SetStyle("Futura_big");
			Font::Get()->RenderText("PLAY", { WIN_WIDTH * 0.8f, WIN_HEIGHT * 0.25f });
			Font::Get()->SetStyle("Futura_more_big");
			Font::Get()->SetColor("White");
			Font::Get()->RenderText("EXIT", { WIN_WIDTH * 0.8f, WIN_HEIGHT * 0.175f });
			Font::Get()->SetColor("Gray");
		}
		else
		{
			Font::Get()->RenderText("PLAY", { WIN_WIDTH * 0.8f, WIN_HEIGHT * 0.25f });
			Font::Get()->RenderText("EXIT", { WIN_WIDTH * 0.8f, WIN_HEIGHT * 0.175f });
		}
		Font::Get()->SetStyle("Futura");
	}

	if (isOuttro)
	{
		outtro_backGround->Render();
		Font::Get()->SetStyle("Futura_outtro");
		Font::Get()->RenderText("THANK YOU!", { CENTER_X - 375.0f, CENTER_Y + 100.0f });
		Font::Get()->SetStyle("Futura");
	}

	if (isOpenQuest)
	{
		journal_frame->Render();
		journal_frame_bar->Render();
		Font::Get()->RenderText("퀘스트", { CENTER_X - 30.0f, CENTER_Y + 260.0f });
		if (isQuest)
		{
			journal_quest_select_icon->Render();
			journal_quest_bar->Render();
			journal_frame_bar2->Render();
			Font::Get()->RenderText("알두인 사냥", { CENTER_X - 350.0f, CENTER_Y - 25.0f });
			Font::Get()->RenderText("알두인 사냥", { CENTER_X + 90.0f, CENTER_Y + 185.0f });
			Font::Get()->RenderText("드래곤본의 목표는 모든 드래곤을 잡아야 하는 것이다. 이제 마지막 남은 드래곤은 알두인이다. 알두인을 잡아라!", 
				{ CENTER_X - 150.0f, CENTER_Y + 60.0f }, { 500.0f, 200.0f });
			Font::Get()->RenderText("목록", { CENTER_X + 125.0f, CENTER_Y - 45.0f });
			Font::Get()->RenderText("알두인 사냥하기", { CENTER_X - 75.0f, CENTER_Y - 75.0f });
			if (!isQuestFinished)
				quest_icon_unfinished->Render();
			else
				quest_icon_finished->Render();
		}
	}

	if (questTextTime > 0.0f)
	{
		if (!isQuestFinished)
		{
			Font::Get()->SetStyle("Futura_big");
			Font::Get()->RenderText("시 작 :  알 두 인  사 냥", { CENTER_X - 120.0f, WIN_HEIGHT * 0.85f });
			Font::Get()->SetStyle("Futura");
		}
		else
		{
			Font::Get()->SetStyle("Futura_big");
			Font::Get()->RenderText("퀘 스 트 완 료 :  알 두 인  사 냥", { CENTER_X - 180.0f, WIN_HEIGHT * 0.85f });
			Font::Get()->SetStyle("Futura");
		}
	}
}

void UIManager::GUIRender()
{
	//ImGui::Text("enemy_angle : %f", final_angle);
	ImGui::Text("enemy_angle : %f", final_angles[monsterCount]);

	//ImGui::Text("enemy_angle : %f", final_angles[1]);
	//
	ImGui::Text("enemy_pos0 : %f", enemies_dir[0]->Pos().x);
	Vector3 dist = Vector3(1, 2, 3) - Vector3(4, 5, 6);
	ImGui::Text("enemy_pos0 : %f", dist.Length());
	ImGui::Text("bool : %d", curEnemy->IsBattle());
	//ImGui::Text("enemy_angle : %f", enemies_dir[1]->Pos().x);

	//ImGui::Text("weight : %d", itemstatus->GetArmor("armor1")->GetStatus().weight);
	//ImGui::Text("weight : %d", itemstatus->GetItem("armor1").weight);


	//invenUI->GUIRender();
}

void UIManager::TargetCompassEnemy(Player* player, vector<EnemySpawn*> enemies, alduin* alduin)
{
	int tmp = 0;
	for (int i = 0; i < enemies.size(); i++)
	{
		for (int j = 0; j < enemies[i]->GetEnemies().size(); j++)
		{
			Vector3 temp = player->Forward();
			Vector3 temp2 = player->GlobalPos() - enemies[i]->GetEnemies()[j]->GetTransform()->GlobalPos();

			float temp_value = sqrt(temp.x * temp.x + temp.y * temp.y + temp.z * temp.z);
			float temp2_value = sqrt(temp2.x * temp2.x + temp2.y * temp2.y + temp2.z * temp2.z);

			float cal_dot = Dot(temp, temp2);

			float angle = acos(cal_dot / (temp_value * temp2_value));

			if (Cross(temp, temp2).y > 0)
			{
				final_angles[tmp] = XMConvertToDegrees(angle);
			}
			else
			{
				final_angles[tmp] = -XMConvertToDegrees(angle);
			}
			tmp++;
		}
	}
	Vector3 temp = player->Forward();
	Vector3 temp2 = player->GlobalPos() - alduin->GlobalPos();

	float temp_value = sqrt(temp.x * temp.x + temp.y * temp.y + temp.z * temp.z);
	float temp2_value = sqrt(temp2.x * temp2.x + temp2.y * temp2.y + temp2.z * temp2.z);

	float cal_dot = Dot(temp, temp2);

	float angle = acos(cal_dot / (temp_value * temp2_value));

	if (Cross(temp, temp2).y > 0)
	{
		final_angles[tmp] = XMConvertToDegrees(angle);
	}
	else
	{
		final_angles[tmp] = -XMConvertToDegrees(angle);
	}
}

void UIManager::GetClosestEnemy(Player* player, vector<EnemySpawn*> enemies)
{
	FOR(monsterCount)
		distances.push_back(100.0f);

	int tmp = 0;
	int closestEnemyIndex = -1;
	float min_dist = 100000000.0f;
	for (int i = 0; i < enemies.size(); i++)
	{
		for (int j = 0; j < enemies[i]->GetEnemies().size(); j++)
		{
			Vector3 dist = player->GlobalPos() - enemies[i]->GetEnemies()[j]->GetTransform()->GlobalPos();
			distances[tmp] = dist.Length();

			if (distances[tmp] < min_dist)
			{
				min_dist = distances[tmp];
				closestEnemyIndex = tmp;
			}

			tmp++;
		}
	}

	
	
	int enemyIndexInGroup = closestEnemyIndex % enemies[0]->GetEnemies().size();
	int enemyGroupIndex = closestEnemyIndex / enemies[0]->GetEnemies().size();
	Character* closestEnemy = enemies[enemyGroupIndex]->GetEnemies()[enemyIndexInGroup];
	curEnemy = closestEnemy;
	
	
}

void UIManager::StartOuttro()
{
	isOuttro = true;
}

void UIManager::StartQuest()
{
	isQuest = true;
	questTextTime = 2.0f;
}

void UIManager::EndQuest()
{
	isQuestFinished = true;
	questTextTime = 2.0f;
}
