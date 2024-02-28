#include "Framework.h"
#include "ShadowScene.h"

ShadowScene::ShadowScene()
{
    forest = new Model("Forest");
    forest->Scale() *= 5;
    forest->UpdateWorld();

    //human = new Model("Human");
    human = new ModelAnimator("Human");
    human->ReadClip("Idle", 1);
    human->UpdateWorld();

    shadow = new Shadow();

    // 같이 알아보는 활용법 : 빛 호출 혹은 만들기 (<-빛 사용 방법)

    light = Environment::Get()->GetLight(0); // 기본으로 설정된 빛 가져오기
    //light = Environment::Get()->AddLight(); //새로운 빛을 만들어서 반환받기

    light->type = 1;               //광원 종류 (상세 설명은 이후에)
    light->pos = { 0, 50, -500 }; //광원 위치
    light->range = 3000;           //조명 범위 (빛이 실제로 닿는 범위)

    light->direction = { 0, -1, 1 }; //조명 방향 (현재값 : 앞에서, 비스듬히, 아래로)
    light->color = { 1, 1, 1, 1 };   //조명의 색 (현재값 : 흰색)
    
    light->length;  //광선 길이      (빛이 강해지는 범위....잘 안 쓴다)

    // 빛이 닿는 곳/닿지 않는 곳을 대비시킬 경우, 초점 광원에서 아래 변수를 같이 고려하면 된다
    light->inner;   //조명 집중 범위 (빛이 집중되어 쏘이는 범위...의 비중)
    light->outer;   //조명 외곽 범위 (빛이 흩어져서 비치는 범위...의 비중)
}

ShadowScene::~ShadowScene()
{
    delete forest;
    delete human;
    delete shadow;
}

void ShadowScene::Update()
{
    if (KEY_DOWN('1')) light->type = 0; // 방향성 광원 (directional light) :
                                        // 형태, 크기, 범위 등은 모두 무시하고 방향만 존재.
                                        // 월드 내 모든 물체가 이 빛을 동등하게 받는다
                                        // 거의 모든 3D 프로그래밍에서 가장 많이 쓰이지만
                                        // 워낙 기본이라서 별로 큰 중요도를 갖진 않는다
                                        // 현실로 치면 - 햇빛

    if (KEY_DOWN('2')) light->type = 1; // 영역 광원 (점 광원, point light) : 
                                        // 특정 점을 중심으로 빛이 퍼져 나가고 있으며
                                        // 중심에 가까울수록 밝아지는 형태와 범위를 가지는 광원
                                        // 밝은 곳, 어두운 곳을 구분할 수 있어 게임에서 흔히 쓴다

    if (KEY_DOWN('3')) light->type = 2; // 집중 광원, 초점 광원, 스포트라이트 (spot light)
                                        // 특정 방향을 초점으로 빛이 쏘아져 나가고 있으며
                                        // 해당 방향에 있으면, 중심에 가까울수록 밝아진다
                                        // 방향이 다를 때는 빛을 거의 받지 않는다
                                        // 게임에서 흔히 쓰이는 광원 중 하나

    if (KEY_DOWN('4')) light->type = 3; // 캡슐 광원 (capsule light) :
                                        // 점 광원과 비슷하지만 빛의 중심이 2군데인 빛
                                        // 각 점은 두 중심에 이르는 거리의 합에 따라 밝기가 달라진다
                                        // 두 중심이 가장 밝고, 두 중심의 맨 가운데가 그 다음으로 밝으며
                                        // 해당 영역에서 멀어질수록 어두워진다
                                        // 현실로 치면 야광봉 같은 물건을 단순화한 것에 비유할 수 있지만
                                        // 아이디어에 비해 연산이 비효율적이라서 게임에서는 잘 쓰지 않는다

    // * 이 프레임워크에는 없지만, 광원 중에서 (특히 게임에 잘) 활용되는 광원이 하나 더 있다
    // 면적 광원 (area light) : 면 전체를 광원으로 삼는 점/초점 광원
    //                         -> 면적 전체가 동등한 밝기를 가지는데 광원의 역할까지 할 때 쓴다
    //                         -> 어두운 곳에서 보는, 실외로 가는 출구 혹은 창문, 혹은 어두운 곳의 모니터

    forest->UpdateWorld();
    //human->UpdateWorld();
    human->Update();
}

void ShadowScene::PreRender()
{
    //그림자의 렌더 타겟 지정(및 준비)
    shadow->SetRenderTarget();

    //인간한테 뎁스 셰이더를 적용 (조건에 따른 셰이더 변화...등을 가진 조건 함수)
    human->SetShader(L"Light/DepthMap.hlsl");

    //조건에 따라 픽셀이 바뀐 인간을 렌더...해서 텍스처를 준비
    human->Render();
}

void ShadowScene::Render()
{
    //위 함수에서 만들어진 텍스처를 그림자에서 렌더 대상으로 세팅
    shadow->SetRender();

    //그림자를 받기 위한 셰이더 세팅
    forest->SetShader(L"Light/Shadow.hlsl");
    human->SetShader(L"Light/Shadow.hlsl");

    //셰이더가 세팅된 배경과 인간을 진짜 호출
    forest->Render();
    human->Render();
}

void ShadowScene::PostRender()
{
    //shadow->PostRender(); // 쿼드 출력용
}

void ShadowScene::GUIRender()
{
    shadow->GUIRender(); // 디버그 조작용
}
