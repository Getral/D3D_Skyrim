#include "Framework.h"

BlendState::BlendState()
{    
    // 블렌드 스테이트 : 이미지에 등록되었거나, 외부에서 직접 설정한 화소를 탈락시키거나 (배경색 날리기)
    //                  같은 위치에 있는 이미지와 화소를 합치거나 (반투명 처리)
    //                  이미지를 다른 곳으로 옮겨서 투사하는 절차 담당
    //                  = WinAPI에 있었던 AlphaBlendBlt와 담당하는 기능이 거의 같다

    desc.RenderTarget[0].BlendEnable = false;                       // 블렌드 기능 활성화
    desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;          // 블렌드를 하기 위한 밑그림(원본)
    desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;     // 블렌드 후에 도출될 이미지 설정 (기본값 : 원래 데이터에 합치기)
    desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;              // 블렌드 방식 (기본값 : 덮어씌우기)
    
    desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;     // 알파 블렌드 (반투명 블렌드)
    desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;// 옵션 내용은 위 3종과 동일
    desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;         // 
    
    desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // 불투명 이미지가 겹칠 때 투과 여부
                                                                               // 기본값 : 앞에 있는 이미지가 무조건 우선 (다 가림)
    // D3D11_COLOR_WRITE_ENABLE_NONE : RenderTargetWriteMask 옵션 설정에서 별도 접근권 필요없이 호출 가능한 두 번째 선택지
    //                                 뜻은 어떤 것도 이미지를 가리지 않음 (= 뒤에 있는 그림이 무조건 다 보임)

    Changed();
}

BlendState::~BlendState()
{
    state->Release();
}

void BlendState::SetState()
{
    float blendFactor[4] = {};
    DC->OMSetBlendState(state, blendFactor, 0xffffffff);
}

void BlendState::Alpha(bool value)
{
    desc.RenderTarget[0].BlendEnable = value;
    desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

    Changed();
}

void BlendState::Additive()
{
    desc.RenderTarget[0].BlendEnable = true;
    desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
    desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

    Changed();
}

void BlendState::AlphaToCoverage(bool value)
{
    desc.AlphaToCoverageEnable = value;

    Changed();
}

void BlendState::Changed()
{
    if (state != nullptr)
        state->Release();

    DEVICE->CreateBlendState(&desc, &state);
}
