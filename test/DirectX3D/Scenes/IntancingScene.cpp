#include "Framework.h"
#include "IntancingScene.h"

IntancingScene::IntancingScene()
{
    
    // �� (���� ����) ����
    models = new ModelAnimatorInstancing("Naruto");
    statics = new ModelInstancing("Kunai");

    // �ִϸ����� ���� �б�
    models->ReadClip("Idle");    
    models->ReadClip("Punching");
    models->ReadClip("Throw");

    // ��ġ (�ִϸ�����)
    for (float z = 0; z < HEIGHT; ++z)
    {
        for (float x = 0; x < WIDTH; ++x)
        {
            Transform* transform = models->Add();
            transform->Pos() = { x, 0, z };
            transform->Scale() *= 0.01f;
        }
    }

    // ��ġ (���� ��)
    for (float z = 0; z < SIZE; ++z)
    {
        for (float x = 1; x <= SIZE; ++x)
        {
            Transform* transform = statics->Add();
            transform->Pos() = { -x, 0, z };
        }
    }
}

IntancingScene::~IntancingScene()
{
    delete models;
    delete statics;
}

void IntancingScene::Update()
{
    models->Update();
    statics->Update();
}

void IntancingScene::PreRender()
{
}

void IntancingScene::Render()
{
    models->Render();
    statics->Render();
}

void IntancingScene::PostRender()
{
}

void IntancingScene::GUIRender()
{
    ImGui::SliderInt("ID", &instanceID, 0, 100);
    ImGui::SliderInt("Clip", &clip, 0, 2);

    if (ImGui::Button("Play"))
    {
        models->PlayClip(instanceID, clip);
    }
    models->GUIRender();// �� �� UI ���� ����
    statics->GUIRender();
}
