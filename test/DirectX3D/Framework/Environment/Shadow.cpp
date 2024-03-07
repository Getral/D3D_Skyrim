#include "Framework.h"
#include "Shadow.h"

Shadow::Shadow(UINT width, UINT height)
    : width(width), height(height)
{
    //렌더 타겟, 뎁스 스텐실, 버퍼 생성
    renderTarget = new RenderTarget(width, height);
    depthStencil = new DepthStencil(width, height);
    viewBuffer = new ViewBuffer();
    projectionBuffer = new MatrixBuffer();

    //(테스트용) 쿼드 생성
    quad = new Quad(Vector2(200, 200));
    quad->Pos() = { 100, 100, 0 };
    quad->UpdateWorld();

    //텍스처 생성 (및 테스트용으로 만든 쿼드에도 넣기)
    Texture* texture = Texture::Add(L"Shadow", renderTarget->GetSRV());
    quad->GetMaterial()->SetDiffuseMap(texture);
}

Shadow::~Shadow()
{
    delete renderTarget;
    delete depthStencil;
    delete viewBuffer;
    delete projectionBuffer;
    delete quad;
}

void Shadow::SetRenderTarget()
{
    renderTarget->Set(depthStencil); // 렌더 타겟 설정 (테스트씬에서는 프리렌더에서 했던 것)
    SetViewProjection(); //뷰포트, 행렬공간 투사 과정을 여기서 호출
}

void Shadow::SetRender()
{
    viewBuffer->SetVS(11);
    projectionBuffer->SetVS(12);
                // DX에서는 셰이더를 그래픽 연산만이 아니라 추가 코드 수행에도 활용할 수 있다...(컴퓨트 셰이더로 확인)
                // 그리고 그래픽 연산의 범위를 넘어서게 되면 셰이더의 슬롯은 우선순위 외에, 추가 조건식의 변수 할당에도 쓴다
                // -> 위 매개변수를 각각 다르게 주는 것으로 셰이더의 색이나, 기타 함수 내용을 바꿀 수도 있다
                // -> 여기서 쓰인 매개변수의 결과는 디퓨즈맵 연산을 흑백으로 바꿔주는 것. (파일 설정에 의함)

    DC->PSSetShaderResources(10, 1, &renderTarget->GetSRV());
                //10번 슬롯부터, 1개 층만큼을, GetSRV에서 가져와 출력 준비

    //여기까지 진행되면 텍스처가 준비
}

void Shadow::PostRender()
{
    //위 함수에서 준비된 텍스처....를 입힌 쿼드....를 테스트용으로 출력
    quad->Render();
}

void Shadow::GUIRender()
{
    ImGui::SliderFloat("Scale", &scale, 1, 10); //"크기" 설정
}

void Shadow::SetViewProjection()
{
    // 광원 클래스를 써보기 (DX + 프레임워크 설정)
    LightBuffer::Light* light = Environment::Get()->GetLight(0);
    //LightBuffer : 빛 계산 기능을 버퍼로 바꾼 클래스
    //Light(프레임워크) : 빛 버퍼 내에 있는 실제 빛 데이터 (세부 데이터는 DX와 셰이더에 분산)
    //GetLight() : 출력절차에서 생성된 광원 호출하기. 0은 기본으로 생성된 결과

    //->광원 데이터를 포인터로 받았다

    //이어서 뷰포트와 투사될 행렬 구하기
    Matrix view = XMMatrixLookAtLH(Vector3(light->pos), Vector3(), Vector3(0, 1, 0));
                //XMMatrixLookAtLH : DX의 기능을 활용해서 행렬 공간을 구하는 함수
                //                   LH는 기준 좌표계. LookAt은 매개변수를 원점->초점 순으로 해석
                // 따라서 현재의 매개변수에 의해 광원에서, 원점으로, 위쪽이 기준축(위)인 공간이 나온다

    Matrix projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, 1, 0.1f, 1000);
                //XMMatrixPerspectiveFovLH : DX의 기능을 활용해서 원근행렬 공간을 구하는 함수
                //                          LH는 기준좌표계, Perspective라서 원근이 적용된다.
                //                     현재 매개변수 설정은 "회전허용은 360도, 좌우대비는 1:1,
                //                    인지 가능한 가장 가까운 Z좌표는 0.1, 가장 먼 좌표는 1000

    //버퍼 세팅
    viewBuffer->Set(view, XMMatrixInverse(nullptr, view)); // XMMatrixInverse : 역행렬 만들기(행렬 뒤집기)
                                                           // 이 과정을 통해 행렬 데이터를 GPU에서 연산 가능
                                                           // 매개변수는 각각 "추가 옵션이 있는가?
                                                           // 그리고 원본은 무엇인가? (=view)"
    projectionBuffer->Set(projection);

    //버퍼를 셰이더에 넘기기 (=GPU계산 후 출력 대기)
    viewBuffer->SetVS(1);
    projectionBuffer->SetVS(2);
}
