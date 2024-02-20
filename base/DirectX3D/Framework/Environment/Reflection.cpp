#include "Framework.h"

Reflection::Reflection(Transform* target)
    : target(target)
{
    renderTarget = new RenderTarget(2048, 2048);
    depthStencil = new DepthStencil(2048, 2048, true); // 스텐실 상태 사용

    camera = new Camera();

    quad = new Quad(Vector2(200, 200));
    quad->Pos() = { 100, 100, 0 };
    Texture* texture = Texture::Add(L"Reflection", renderTarget->GetSRV());
    quad->GetMaterial()->SetDiffuseMap(texture);
    quad->UpdateWorld();

    // 보험용
    FOR(2) rasterizerState[i] = new RasterizerState();
    rasterizerState[1]->CullMode(D3D11_CULL_NONE); // 방향에 의한 텍스처 컬링 없음
}

Reflection::~Reflection()
{
    delete renderTarget;
    delete depthStencil;

    FOR(2) delete rasterizerState[i];

    delete camera;
    delete quad;
}

void Reflection::Update()
{
    //클래스 내 카메라의 위치를 지금 내 시야와 일치시키기
    camera->Pos() = CAM->Pos();
    camera->Rot() = CAM->Rot();

    //내 시야를 따라온 클래스 내 카메라를 반사 상황에 맞추어서 보는 방향, 위치를 재조정
    //->반사 계산의 중요 과정

    // * 샘플 상황 : 물 반사를 목표로 하고 있으므로, 땅에 물이 고여 있고,
    //   따라서 수면을 반사의 기준으로 삼는다고 가정

    camera->Rot().x *= -1; // 위아래 뒤집기
    camera->Pos().y = target->Pos().y * 2.0f - camera->Pos().y;
                     // target : 연산 대상 = 반사현상의 주체
                     // target - cam = 카메라에서 반사면까지의 거리
                     // -> 식의 의미 : 반사용 시야(카메라)를 수면보다 더 아래인 것처럼
                     //    or 지금 나보다 좀 더 위쪽에서 비치도록(*2)

    // 시야각과 위치가 조정된 카메라 시야를 업데이트
    camera->UpdateWorld();
}

void Reflection::SetReflection()
{
    renderTarget->Set(depthStencil);
    camera->SetView(); // 위치와 각도에 맞춰서 시야 담기 (수동 추가 카메라라서 더 필요)
}

void Reflection::SetRender()
{
    camera->GetViewBuffer()->SetVS(10);
    DC->PSSetShaderResources(10, 1, &renderTarget->GetSRV());
}

void Reflection::PostRender()
{
    // 카메라가 잡은 렌더타겟의, 셰이더 데이터를 가져와서 만든 텍스처의, 실체를 출력
    quad->Render();
}

void Reflection::GUIRender()
{
    quad->GUIRender();
    camera->GUIRender();
}
