#include "Framework.h"
#include "RenderTargetScene.h"

RenderTargetScene::RenderTargetScene()
{
    //model = new ModelAnimator("Fox");
    //model->ReadClip("Idle");
    //model->UpdateWorld();

    model = new Model("Human");
    model->UpdateWorld();

    renderTarget = new RenderTarget();
    depthStencil = new DepthStencil();

    quad = new Quad(Vector2(500, 500)); // 흰 그림 하나 만들기
    //quad = new Sphere(200);
    quad->Pos() = { CENTER_X, CENTER_Y };
    quad->GetMaterial()->SetShader(L"Effect/Bloom.hlsl"); // 블룸 : "번쩍임" 혹은 빛 번짐 효과
                                                          // 여기서는 그 중 색 강조 부분을 구현
    quad->GetMaterial()->SetDiffuseMap(Texture::Add(L"Rendered_Sight", renderTarget->GetSRV()));
                        // 텍스처 클래스에 그림 파일 대신, 앱에서 현재 만들어진 그림 데이터를 가져오기
    quad->UpdateWorld(); //생성, 설정 후 결과 업데이트

    valueBuffer = new FloatValueBuffer(); //소수 계산용 버퍼
    valueBuffer->Get()[0] = 1; //기본값 1 주기
    valueBuffer->Get()[1] = 1; //위와 같음
}

RenderTargetScene::~RenderTargetScene()
{
    delete model;
    delete renderTarget;
    delete depthStencil;
    delete quad;
    delete valueBuffer;
}

void RenderTargetScene::Update()
{
    model->UpdateWorld();
}

void RenderTargetScene::PreRender()
{
    // 렌더 전에 세팅 수행 (렌더 타겟)

    renderTarget->Set(depthStencil); //씬 내의 (=클래스로 미리 설정된) 깊이 스텐실로 RTV생성

    //RTV로 설정된 영역에 모델 그리기
    model->Render();
}

void RenderTargetScene::Render()
{
    //월드 렌더가 필요하다면 여기서
    model->Render();
}

void RenderTargetScene::PostRender()
{
    valueBuffer->SetPS(10); // 블룸 셰이더에 먼저 설정된 슬롯값(조건값으로 활용 가능한) 주고 활성화
    quad->Render(); //쿼드를 렌더

    // 렌더 타겟에서는 월드의 일부 정보를 텍스처에 렌더
    // 텍스처는 쿼드에 매티리얼로 설정
    // 다시 그 쿼드를 앱에서 렌더 -> 사용자는 쿼드를 통해 모델을 볼 수 있게 된다
}

void RenderTargetScene::GUIRender()
{
    ImGui::SliderFloat("Threshold", &valueBuffer->Get()[0], 0, 1);
                      //threshold : 임계점. 특정 연산이나 처리가 일어나기 위한 최소(혹은 최대) 조건
                      //            게임에서는 주로 방어력, 특정한 구간에서 플레이어 진행 요건을 판별할 때 사용

    ImGui::SliderFloat("Value", &valueBuffer->Get()[1], 0, 10);
                      //위 임계점을 이번 씬에 적용했을 때 연산할 보정값 : 블룸 셰이더의 색 변조 정도

}
