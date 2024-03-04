#include "Framework.h"
#include "IntancingScene.h"

IntancingScene::IntancingScene()
{
    
    // 모델 (최초 구현) 생성
    models = new ModelAnimatorInstancing("Naruto");
    statics = new ModelInstancing("Kunai");

    // 애니메이터 동작 읽기
    models->ReadClip("Idle");    
    models->ReadClip("Punching");
    models->ReadClip("Throw");

    // 배치 (애니메이터)
    for (float z = 0; z < HEIGHT; ++z)
    {
        for (float x = 0; x < WIDTH; ++x)
        {
            Transform* transform = models->Add();
            transform->Pos() = { x, 0, z };
            transform->Scale() *= 0.01f;
        }
    }

    // 배치 (정적 모델)
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
    models->GUIRender();// 각 모델 UI 렌더 따로
    statics->GUIRender();
}
