#include "Framework.h"

DepthStencilState::DepthStencilState()
{
    // 뎁스(깊이), 스텐실 스테이트 : 이미지의 우선순위(Z축 좌표 혹은 강제출력순위) 설정 및 (뎁스)
    //                             이미지를 가려서 못 보이게 하는 조건 여부와 세부 설정(스텐실)
    //                             -> 이 둘을 합쳐 이미지의 선별적 출력을 담당하는 스테이트

    desc.DepthEnable = true;                            //깊이 사용여부
    desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;   //깊이에 의한 우선순위 적용 : ALL = 전부 적용함
    desc.DepthFunc = D3D11_COMPARISON_LESS;             //깊이 판단 기준 : (카메라와의 거리에서) Z축 값이 낮은 순서대로 = 가까운 놈이 무조건 다 보인다

    desc.StencilEnable = true;      //스텐실 사용여부
    desc.StencilReadMask = 0xff;    //스텐실을 적용해서 이미지를 읽을 때, 가리게 될 마스크의 데이터값
    desc.StencilWriteMask = 0xff;   //출력할 때, 가리게 될 마스크의 데이터값

    // 뎁스 스텐실은 여기서 옵션을 일일이 수정하기보다
    // 필요할 때 따로 클래스를 만들거나, 아니면 스텐실을 적용한 마스크의 역할을 할
    // 다른 개체를 만들어 호출하는 경우가 더 많다
    
    // * 특히 뎁스 스텐실의 특성(선별)을 살리면 -> 이 스테이트를 통해서도 (블렌드 이상으로)
    //   이미지의 원본과 출력 장소를 분리시킬 수 있다

    desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;       //스텐실 계산 방식 (잘 안 씀)
    desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;  
    desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    Changed();
}

DepthStencilState::~DepthStencilState()
{
    state->Release();
}

void DepthStencilState::SetState()
{
    DC->OMSetDepthStencilState(state, 1);
}

void DepthStencilState::DepthEnable(bool value)
{
    desc.DepthEnable = value;

    Changed();
}

void DepthStencilState::DepthWriteMask(D3D11_DEPTH_WRITE_MASK value)
{
    desc.DepthWriteMask = value;

    Changed();
}

void DepthStencilState::Changed()
{
    if (state != nullptr)
        state->Release();

    DEVICE->CreateDepthStencilState(&desc, &state);
}
