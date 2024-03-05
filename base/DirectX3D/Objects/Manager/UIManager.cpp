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
    FOR(SpawnManager::Get()->GetMonsterSpawnManager().size())
    {
        enemies_dir.push_back(new Quad(L"Textures/UI/enemy_dir.png"));
        enemies_dir.back()->SetParent(compass);
        enemies_dir.back()->Scale() *= 0.5f;
        final_angles.push_back(0.0f);
    }

    
    //enemy_dir = new Quad(L"Textures/UI/enemy_dir.png");
    //enemy_dir->SetParent(compass);
    //enemy_dir->Scale() *= 0.5f;
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
}

UIManager::~UIManager()
{
    delete compass;
    for (Quad* dir : compass_dir)
        delete dir;
    delete enemy_dir;

    delete HP_bar_background;
    delete HP_bar;

    delete SP_bar_background;
    delete SP_bar;
}

void UIManager::Update(Player* player, vector<EnemySpawn*> enemies)
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
    for (int i = 0; i < enemies.size(); i++)
    {
        for (int j = 0; j < enemies[i]->GetEnemies().size(); j++)
        {
            TargetCompassEnemy(player, enemies[i]->GetEnemies()[j]);

            enemies_dir[i]->Pos().x = final_angles[i] * compass->GetSize().x / 140;

            enemies_dir[i]->UpdateWorld();
        }
    }

    
#pragma endregion
    HP_ratio = player->GetStatus().curHp / player->GetStatus().maxHp;
    HP_bar->Scale().x = maxHpBar * HP_ratio;
    HP_bar->UpdateWorld();

    SP_bar->SetAmount(player->GetStatus().curstamina / player->GetStatus().maxstamina);
    SP_bar->UpdateWorld();


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

    for (int i = 0; i < SpawnManager::Get()->GetMonsterSpawnManager().size(); i++)
    {
        if (enemies_dir[i]->Pos().x >= -60 * compass->GetSize().x / 140 && enemies_dir[i]->Pos().x <= +60 * compass->GetSize().x / 140)
            enemies_dir[i]->Render();
    }


    

    HP_bar_background->Render();
    HP_bar->Render();

    SP_bar_background->Render();
    SP_bar->Render();
}

void UIManager::GUIRender()
{
    ImGui::Text("enemy_angle : %f", final_angle);
    ImGui::Text("enemy_angle : %f", final_angle);
    ImGui::Text("enemy_angle : %f", final_angle);
}

void UIManager::TargetCompassEnemy(Player* player, Enemy* enemy)
{
    Vector3 temp = player->Forward();
    Vector3 temp2 = player->GlobalPos() - enemy->GetTransform()->GlobalPos();

    float temp_value = sqrt(temp.x * temp.x + temp.y * temp.y + temp.z * temp.z);
    float temp2_value = sqrt(temp2.x * temp2.x + temp2.y * temp2.y + temp2.z * temp2.z);

    cal_dot = Dot(temp, temp2);

    angle = acos(cal_dot / (temp_value * temp2_value));

    if (Cross(temp, temp2).y > 0)
    {
        final_angle = XMConvertToDegrees(angle);
    }
    else
    {
        final_angle = -XMConvertToDegrees(angle);
    }

    final_angles.push_back(final_angle);
}
