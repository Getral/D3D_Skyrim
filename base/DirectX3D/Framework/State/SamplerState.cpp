#include "Framework.h"

SamplerState::SamplerState()
{
    // 샘플러 스테이트 : DX의 그래픽 출력 절차 단위인 스테이트의 하나(그리고 기본)
    // 정점과 텍스처의 출력 옵션을 설정한다
    // 현재는 기본값으로 설정 중 : 있는 그대로 쓰겠다는 의도 + 필요하면 여기서 수정한다는 뜻

    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; // 거리에 따른 텍스처 출력 방식(필터링) : 기본값은 선형 샘플링
    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;    // 텍스처 어드레스 방식 : 기본은 한 메쉬에, 한 텍스처를 두르기
    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;;
    desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desc.MinLOD = 0;
    desc.MaxLOD = D3D11_FLOAT32_MAX;
    //LOD(Level Of Detail) : 카메라의 거리에 따라서 퀄리티를 다르게 하는 것   

    Changed();
}

SamplerState::~SamplerState()
{
    state->Release();
}

void SamplerState::SetState(UINT slot)
{
    DC->PSSetSamplers(slot, 1, &state);
}

void SamplerState::Filter(D3D11_FILTER value)
{
    desc.Filter = value;

    Changed();
}

void SamplerState::Changed()
{
    if (state != nullptr)
        state->Release();

    DEVICE->CreateSamplerState(&desc, &state);
}
