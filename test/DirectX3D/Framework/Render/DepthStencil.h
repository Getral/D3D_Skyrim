#pragma once
class DepthStencil
{
    // ���� ���ٽ� Ŭ���� : ���� ���ٽ� ������Ʈ�� �����Ǵ� �ɼ��� ���� ����ؼ�
    //                     ���̿� ���� �̹��� ���� / ��ֹ��� ���� �̹��� ���� ȿ����
    //                     ������ ���Ƿ� ������ ���� Ŭ����

public:
    DepthStencil(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT, bool isStencil = false);
    ~DepthStencil();

    void Clear(); //��������

    //�ڷ��� ȣ�� ���� �Լ�
    ID3D11DepthStencilView*& GetDSV() { return dsv; }
    ID3D11ShaderResourceView*& GetSRV() { return srv; }

private:
    // ������ ����
    void CreateDSVTexture();
    void CreateDSV();
    void CreateSRV();

private:
    UINT width;
    UINT height;
    bool isStencil;

    ID3D11Texture2D* dsvTexture;
    ID3D11DepthStencilView* dsv;
    ID3D11ShaderResourceView* srv; // <- ���̴� ���ҽ� ���� ��� : DX���� ���̴��� �ؽ�ó�� �����ϱ� ���� ����
};

