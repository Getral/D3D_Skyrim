#include "Framework.h"
#include "DepthStencil.h"

DepthStencil::DepthStencil(UINT width, UINT height, bool isStencil)
    : width(width), height(height), isStencil(isStencil)
{
    // 이 클래스가 뎁스 스텐실 설정 역할을 하지만,
    // 일단은 미리 정해진 대로 설정
    CreateDSVTexture(); //별도 자유설정 없이 그대로 생성
    CreateDSV();
    CreateSRV();
}

DepthStencil::~DepthStencil()
{
    dsvTexture->Release();
    dsv->Release();
    srv->Release();
}

void DepthStencil::Clear()
{
    DC->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1, 0);
    //->우선순위 설정 해제, 기본순위 1, 스텐실 없음
}

void DepthStencil::CreateDSVTexture()
{
    // 뎁스 스텐실 상태를 준비하고, 해당 화면을 따로 텍스처처럼 꾸미기

    D3D11_TEXTURE2D_DESC depthDesc = {}; //기본값으로 일단 만듬
    //만든 다음에 옵션 설정
    depthDesc.Width = width;
    depthDesc.Height = height;
    depthDesc.MipLevels = 1; // 밉맵 안씀
    depthDesc.ArraySize = 1; //별도 텍스처 안씀
    depthDesc.Format = isStencil ? DXGI_FORMAT_R24G8_TYPELESS : DXGI_FORMAT_R32_TYPELESS;
                    //스텐실이면 1바이트를 스텐실 데이터에 사용, 없으면 모두 이미지로 사용
    depthDesc.Usage = D3D11_USAGE_DEFAULT;
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
            //BindFlag : 추가 옵션, 현재 뎁스 스텐실, 셰이더 리소스 옵션을 적용하는 것으로 설정

    DEVICE->CreateTexture2D(&depthDesc, nullptr, &dsvTexture);
    //CreateTexture2D : 지정된 영역의 화면을 2D 텍스처로 만드는 DX 함수
    //         매개변수는 "어떤 데이터를 기준으로, 어떤 데이터와 함께, 어떤 결과물에 저장할 것인가"
}

void DepthStencil::CreateDSV()
{
    //텍스처 데이터를 기반으로 이 그림을 보기(처리하기) 위한 준비 절차
    D3D11_DEPTH_STENCIL_VIEW_DESC depthViewDesc = {};

    depthViewDesc.Format = isStencil ? DXGI_FORMAT_D24_UNORM_S8_UINT : DXGI_FORMAT_D32_FLOAT;
                        // 스텐실이 있으면 1바이트 용량은 정수로 떼어주고 아니면 4바이트 소수
    depthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D; //이미지 인지(처리) 방식

    DEVICE->CreateDepthStencilView(dsvTexture, &depthViewDesc, &dsv);
    //CreateDepthStencilView : 깊이 스텐실 상태가 적용된 화면용 데이터를 만드는 DX 함수
    //       매개변수는 "어떤 원본을, 어떤 데이터와 함께, 어떤 결과물에 저장할 것인가"
}

void DepthStencil::CreateSRV()
{
    // 셰이더가 텍스처에 접근하기 위한 뷰포트 절차
    D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
    desc.Format = isStencil ? DXGI_FORMAT_R24_UNORM_X8_TYPELESS : DXGI_FORMAT_R32_FLOAT;
    // 스텐실이면 이제 스텐실에 가린 부분은 출력이 없음
    desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    // 어떤 이미지로서 출력할 것인가 
    desc.Texture2D.MipLevels = 1; //밉맵 수준

    DEVICE->CreateShaderResourceView(dsvTexture, &desc, &srv);
    //-> 이것으로 셰이더가 그림을 출력하기 위한 준비 끝
}
