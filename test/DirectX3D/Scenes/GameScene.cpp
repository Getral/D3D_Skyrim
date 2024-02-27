#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
    background = new Model("Forest");
    background->SetShader(L"Basic/Texture.hlsl");
    background->Scale() *= 10.0f;
    background->UpdateWorld();

    naruto = new Naruto();

    model_N = new Model("Kunai");
    model_N->Pos() = { 0,0,-1000 };
    model_N->Rot() = { 0,+XM_PI/2,0};
    model_N->Scale() *= 1000;
    model_N->UpdateWorld();

    model_S = new Model("Kunai");
    model_S->Pos() = { 0,0,+1000 };
    model_S->Rot() = { 0,-XM_PI/2,0};
    model_S->Scale() *= 1000;
    model_S->UpdateWorld();

    model_E = new Model("Kunai");
    model_E->Pos() = { 1000,0,0 };
    model_E->Rot() = { 0,0,0 };
    model_E->Scale() *= 1000;
    model_E->UpdateWorld();

    model_W = new Model("Kunai");
    model_W->Pos() = { -1000,0,0 };
    model_W->Rot() = { 0,+XM_PI,0};
    model_W->Scale() *= 1000;
    model_W->UpdateWorld();

    fox = new Model("Fox");
    fox->Pos() = { -100,0,-100 };
    fox->UpdateWorld();

    //// �κ��� ����(��) ����
    //robotInstancing = new ModelAnimatorInstancing("Robot");
    //robotInstancing->ReadClip("StandUp");
    //robotInstancing->ReadClip("Walk");
    //robotInstancing->ReadClip("Run");
    //robotInstancing->ReadClip("Hit");
    //robotInstancing->ReadClip("Dying");
    //
    ////�κ� ���� ������ ����
    //Transform* t = robotInstancing->Add(); // ���� ����ϱ� ���� Ʈ�������� �ν��Ͻ̿��� �߰�
    //robot = new Robot(t, robotInstancing, 0); //���� �κ��� ��¿� Ʈ�������� �ε��� �ֱ�
    ////->�̷ν� �κ��� ���� ������(�κ� Ŭ����)��, ����(��)��, �� ���� �̾��� Ʈ������(t)�� �� ���´�

    //robot->SetTarget(naruto);

    KunaiManager::Get(); // �ƹ��͵� �� �ϴ� �ǹ̾��� �ڵ�����,
                         // �� �ڵ尡 ����Ǹ鼭 �̱����� �����ȴٴ� ���� ����
    
    RobotManager::Get()->SetTarget(naruto); //�̱��� ���� ��, ǥ�� ��������

    UIManager::Get();

    CAM->SetTarget(naruto); //�ȷο�ķ + ������� ����
    CAM->TargetOptionLoad("Naruto"); // �����信 ���� ī�޶� ��ġ ���� �ε� (������ �ε� ������ �״��)
    CAM->LookAtTarget(); // �ȷο�ķ + ���� ��� ���� + �� ���� ����� �������� ���� (�� ���� ������)

    FOR(2)
        blendState[i] = new BlendState();
    blendState[1]->AlphaToCoverage(true); // ���� Ȥ�� ������ ������ �ܺ� �ȼ��� ������ ���ΰ�


    skyBox = new SkyBox(L"Textures/Landscape/BlueSky.dds");
}

GameScene::~GameScene()
{
    delete naruto;
    delete background;
    delete skyBox;

    FOR(2)
        delete blendState[i];

    KunaiManager::Get()->Delete();
    RobotManager::Get()->Delete();
}

void GameScene::Update()
{
    naruto->Update();
    //robotInstancing->Update();
    //robot->Update();

    KunaiManager::Get()->Update();
    UIManager::Get()->Update(naruto, fox);
    //RobotManager::Get()->Update();
    //model->UpdateWorld();
    fox->UpdateWorld();
}

void GameScene::PreRender()
{
}

void GameScene::Render()
{
    //skyBox->Render();

    blendState[1]->SetState(); // ���� �����ϱ�
    //background->Render();      // ���� ����� ���¿��� ��游 ����ϱ�
    blendState[0]->SetState(); // ���� �����ϱ�

    naruto->Render();
    //robotInstancing->Render();
    //robot->Render();

    KunaiManager::Get()->Render();
    //RobotManager::Get()->Render();

    model_N->Render();
    model_S->Render();
    model_E->Render();
    model_W->Render();

    UIManager::Get()->Render();

    fox->Render();
}

void GameScene::PostRender()
{
    naruto->PostRender();
    RobotManager::Get()->PostRender();
    UIManager::Get()->PostRender();
}

void GameScene::GUIRender()
{
    skyBox->GUIRender();
    naruto->GUIRender();
    UIManager::Get()->GUIRender();

    //ImGui::Text("naruto_forward x : %f", naruto->Forward().x);
    //ImGui::Text("naruto_forward y : %f", naruto->Forward().y);
    //ImGui::Text("naruto_forward z : %f", naruto->Forward().z);
    //
    //ImGui::Text("naruto_pos x : %f", naruto->GlobalPos().x);
    //ImGui::Text("naruto_pos y : %f", naruto->GlobalPos().y);
    //ImGui::Text("naruto_pos z : %f", naruto->GlobalPos().z);
    //
    //ImGui::Text("fox_pos x : %f", fox->GlobalPos().x);
    //ImGui::Text("fox_pos y : %f", fox->GlobalPos().y);
    //ImGui::Text("fox_pos z : %f", fox->GlobalPos().z);
}
