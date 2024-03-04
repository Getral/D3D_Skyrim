#pragma once
class RenderTarget
{
    // 렌더 타겟 : 렌더링이 있는 컴퓨터 프로그래밍에서, 렌더 대상이 가진 본래의 공간/표적 좌표를
    //            다른 투시공간(뷰포트, 카메라)의 좌표에 이전하는 것과 그 결과물로 나온 이미지를 지칭

    // 간단히 말하면, 모델을 다른 곳에 그리기

public:
    RenderTarget(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT,
        DXGI_FORMAT format = DXGI_FORMAT_R32G32B32A32_FLOAT);
    ~RenderTarget();

    //렌더타겟 세팅 (뎁스 스텐실 기능 필요, 기본 배경색은 흰색)
    void Set(DepthStencil* depthStencil, Float4 clearColor = Float4(1, 1, 1, 1));

    ID3D11ShaderResourceView*& GetSRV() { return srv; }
    ID3D11RenderTargetView*& GetRTV() { return rtv; } //DX는 렌더타겟 기능 기본 제공

private:
    void CreateRTVTexture();
    void CreateRTV();
    void CreateSRV();

private:
    UINT width;
    UINT height;
    DXGI_FORMAT format; // 이미지 포맷(출력유형)

    ID3D11Texture2D* rtvTexture;
    ID3D11RenderTargetView* rtv;
    ID3D11ShaderResourceView* srv;

};

