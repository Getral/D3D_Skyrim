#include "Framework.h"
#include "RenderTarget.h"

RenderTarget::RenderTarget(UINT width, UINT height, DXGI_FORMAT format)
    : width(width), height(height), format(format)
{
    CreateRTVTexture();
    CreateRTV();
    CreateSRV();
}

RenderTarget::~RenderTarget()
{
    rtvTexture->Release();
    rtv->Release();
    srv->Release();
}

void RenderTarget::Set(DepthStencil* depthStencil, Float4 clearColor)
{
    DC->OMSetRenderTargets(1, &rtv, depthStencil->GetDSV());
        //OMSetRenderTargets : DX에서 제공하는, 레더 타겟 생성 함수
        //                     매개변수는 각각 생성할 렌더 타겟(별도 출력) 개수,
        //                     렌터 타겟 생성 결과 위치, 추가 참조 데이터

    DC->ClearRenderTargetView(rtv, (float*)&clearColor); //렌더타겟 출력정보 초기화

    Environment::Get()->Set(); // 출력절차(싱글턴) 호출 후, 출력 기능 호출로 바뀐 데이터를 다시 적용
    Environment::Get()->SetViewport(width, height); //받은 크기대로 뷰포트 다시 정해주기
}

void RenderTarget::CreateRTVTexture()
{
    D3D11_TEXTURE2D_DESC desc = {};

    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1; //샘플링 숫자 = 기본값 1.
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;

    DEVICE->CreateTexture2D(&desc, nullptr, &rtvTexture);
            //어떤 자료에서, 어떤 자료를 추가 참조해서, 어디에 결과를 만들 것인가
}

void RenderTarget::CreateRTV()
{
    D3D11_RENDER_TARGET_VIEW_DESC desc = {};
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //출력을 옮기려는 과정이라, 위 함수와 비슷한 값이면 OK
    desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

    DEVICE->CreateRenderTargetView(rtvTexture, &desc, &rtv);
        //위에서 만든 텍스처를 기반으로 지금 만든 구조체를 추가로 참조해서, rtv 변수에 결과를 만든다
}

void RenderTarget::CreateSRV()
{
    D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    desc.Texture2D.MipLevels = 1;

    DEVICE->CreateShaderResourceView(rtvTexture, &desc, &srv);
}
