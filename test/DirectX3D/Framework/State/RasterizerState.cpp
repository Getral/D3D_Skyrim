#include "Framework.h"

RasterizerState::RasterizerState()
{
    // 래스터라이저 스테이트 : 정점화된 텍스처(2D 이미지)를 픽셀로 변환해서 출력하는 절차
    //                       텍스처 표현 + 3D 모델을 모니터에서 보기 위한 그림으로 변환한다
    //                       기본적으로 먼저 설정되어 있고, 필요하면 다른 곳에서 추가로 불러서
    //                       다른 옵션을 주기도 한다

    desc.CullMode = D3D11_CULL_BACK;  // 출력 선별 기준 (컬링 모드) : 기본값은 뒷면 버리기
    desc.FillMode = D3D11_FILL_SOLID; // 텍스처 출력 기준 (어떻게 화소를 채울 것인가) : 기본=다 그리기
    //desc.FrontCounterClockwise      // 전면 텍스처가 반시계 방향인가? : 
                                      // -> 면을 구성한 세 정점이 시계 방향/반시계 방향으로 진행될 때
                                      //    어느 쪽을 앞으로 간주할 것인가를 정한다. 기본값은 false

    // * 텍스처 구성 기준을 가르는 정점 진행 방향과,
    //   축평면 내부에서의 회전과, 임의의 축을 기준으로 한 회전은 모두 다른 대상
    //   = 하나가 A 방향이라고 다른 것도 A 방향이다....라는 법은 없다

    Changed();
}

RasterizerState::~RasterizerState()
{
    state->Release();
}

void RasterizerState::SetState()
{
    DC->RSSetState(state);
}

void RasterizerState::FillMode(D3D11_FILL_MODE value)
{
    desc.FillMode = value;

    Changed();
}

void RasterizerState::CullMode(D3D11_CULL_MODE value)
{
    desc.CullMode = value;

    Changed();
}

void RasterizerState::FrontCounterClockwise(bool value)
{
    desc.FrontCounterClockwise = value;

    Changed();
}

void RasterizerState::Changed()
{
    if (state != nullptr)
        state->Release();

    DEVICE->CreateRasterizerState(&desc, &state);
}
