#pragma once
class RenderTarget
{
    // ���� Ÿ�� : �������� �ִ� ��ǻ�� ���α׷��ֿ���, ���� ����� ���� ������ ����/ǥ�� ��ǥ��
    //            �ٸ� ���ð���(����Ʈ, ī�޶�)�� ��ǥ�� �����ϴ� �Ͱ� �� ������� ���� �̹����� ��Ī

    // ������ ���ϸ�, ���� �ٸ� ���� �׸���

public:
    RenderTarget(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT,
        DXGI_FORMAT format = DXGI_FORMAT_R32G32B32A32_FLOAT);
    ~RenderTarget();

    //����Ÿ�� ���� (���� ���ٽ� ��� �ʿ�, �⺻ ������ ���)
    void Set(DepthStencil* depthStencil, Float4 clearColor = Float4(1, 1, 1, 1));

    ID3D11ShaderResourceView*& GetSRV() { return srv; }
    ID3D11RenderTargetView*& GetRTV() { return rtv; } //DX�� ����Ÿ�� ��� �⺻ ����

private:
    void CreateRTVTexture();
    void CreateRTV();
    void CreateSRV();

private:
    UINT width;
    UINT height;
    DXGI_FORMAT format; // �̹��� ����(�������)

    ID3D11Texture2D* rtvTexture;
    ID3D11RenderTargetView* rtv;
    ID3D11ShaderResourceView* srv;

};

