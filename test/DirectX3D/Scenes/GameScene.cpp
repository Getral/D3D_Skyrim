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

    //// 로봇의 외형(만) 생성
    //robotInstancing = new ModelAnimatorInstancing("Robot");
    //robotInstancing->ReadClip("StandUp");
    //robotInstancing->ReadClip("Walk");
    //robotInstancing->ReadClip("Run");
    //robotInstancing->ReadClip("Hit");
    //robotInstancing->ReadClip("Dying");
    //
    ////로봇 실제 데이터 생성
    //Transform* t = robotInstancing->Add(); // 모델을 출력하기 위한 트랜스폼을 인스턴싱에서 추가
    //robot = new Robot(t, robotInstancing, 0); //실제 로봇에 출력용 트랜스폼과 인덱스 주기
    ////->이로써 로봇은 실제 데이터(로봇 클래스)와, 외형(모델)과, 이 둘을 이어줄 트랜스폼(t)을 다 갖는다

    //robot->SetTarget(naruto);

    KunaiManager::Get(); // 아무것도 안 하는 의미없는 코드지만,
                         // 이 코드가 수행되면서 싱글턴이 생성된다는 것이 의의
    
    RobotManager::Get()->SetTarget(naruto); //싱글턴 생성 후, 표적 설정까지

    UIManager::Get();

    CAM->SetTarget(naruto); //팔로우캠 + 추적대상 설정
    CAM->TargetOptionLoad("Naruto"); // 나루토에 맞춘 카메라 위치 설정 로드 (있으면 로드 없으면 그대로)
    CAM->LookAtTarget(); // 팔로우캠 + 추적 대상 있음 + 그 추적 대상을 락온으로 추적 (이 경우는 나루토)

    FOR(2)
        blendState[i] = new BlendState();
    blendState[1]->AlphaToCoverage(true); // 알파 혹은 지정된 배경색을 외부 픽셀과 결합할 것인가


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

    blendState[1]->SetState(); // 상태 설정하기
    //background->Render();      // 알파 적용된 상태에서 배경만 출력하기
    blendState[0]->SetState(); // 상태 복원하기

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
