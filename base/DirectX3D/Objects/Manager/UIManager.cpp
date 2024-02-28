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

    enemy_dir = new Quad(L"Textures/UI/enemy_dir.png");
    enemy_dir->SetParent(compass);
    enemy_dir->Scale() *= 0.5f;
}

UIManager::~UIManager()
{
    delete compass;
    for (Quad* dir : compass_dir)
        delete dir;
}

void UIManager::Update(Naruto* naruto, Model* enemy)
{
    // 나침반 동서남북
#pragma region compass_dir
    tmp_N = XMConvertToDegrees(naruto->Rot().y);
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
        compass_dir[i]->Pos().x = dirX_tmp[i] * compass->GetSize().x / 140;
    }

    for (Quad* dir : compass_dir)
        dir->UpdateWorld();
#pragma endregion
    // 나침반 적 표시
#pragma region enemy_dir
    TargetCompassEnemy(naruto, enemy);

    enemy_dir->Pos().x = final_angle * compass->GetSize().x / 140;

    enemy_dir->UpdateWorld();
#pragma endregion
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
    if (enemy_dir->Pos().x >= -60 * compass->GetSize().x / 140 && enemy_dir->Pos().x <= +60 * compass->GetSize().x / 140)
        enemy_dir->Render();
}

void UIManager::GUIRender()
{
    ImGui::Text("enemy_angle : %f", final_angle);
}

float UIManager::TargetCompassEnemy(Naruto* naruto, Model* model)
{   
    Vector3 temp = -naruto->Forward();
    Vector3 temp2 = model->GlobalPos() - naruto->GlobalPos();

    float temp_value = sqrt(temp.x * temp.x + temp.y * temp.y + temp.z * temp.z);
    float temp2_value = sqrt(temp2.x * temp2.x + temp2.y * temp2.y + temp2.z * temp2.z);

    cal_dot = Dot(temp, temp2);

    angle = acos(cal_dot / (temp_value * temp2_value));

    // player기준으로 왼쪽 오른쪽 판단
    if (Cross(temp, temp2).y > 0)
    {
        final_angle = XMConvertToDegrees(angle);
    }
    else
    {
        final_angle = -XMConvertToDegrees(angle);
    }

    return final_angle;
}
