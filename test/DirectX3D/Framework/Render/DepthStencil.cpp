#include "Framework.h"
#include "DepthStencil.h"

DepthStencil::DepthStencil(UINT width, UINT height, bool isStencil)
    : width(width), height(height), isStencil(isStencil)
{
    // �� Ŭ������ ���� ���ٽ� ���� ������ ������,
    // �ϴ��� �̸� ������ ��� ����
    CreateDSVTexture(); //���� �������� ���� �״�� ����
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
    //->�켱���� ���� ����, �⺻���� 1, ���ٽ� ����
}

void DepthStencil::CreateDSVTexture()
{
    // ���� ���ٽ� ���¸� �غ��ϰ�, �ش� ȭ���� ���� �ؽ�óó�� �ٹ̱�

    D3D11_TEXTURE2D_DESC depthDesc = {}; //�⺻������ �ϴ� ����
    //���� ������ �ɼ� ����
    depthDesc.Width = width;
    depthDesc.Height = height;
    depthDesc.MipLevels = 1; // �Ӹ� �Ⱦ�
    depthDesc.ArraySize = 1; //���� �ؽ�ó �Ⱦ�
    depthDesc.Format = isStencil ? DXGI_FORMAT_R24G8_TYPELESS : DXGI_FORMAT_R32_TYPELESS;
                    //���ٽ��̸� 1����Ʈ�� ���ٽ� �����Ϳ� ���, ������ ��� �̹����� ���
    depthDesc.Usage = D3D11_USAGE_DEFAULT;
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
            //BindFlag : �߰� �ɼ�, ���� ���� ���ٽ�, ���̴� ���ҽ� �ɼ��� �����ϴ� ������ ����

    DEVICE->CreateTexture2D(&depthDesc, nullptr, &dsvTexture);
    //CreateTexture2D : ������ ������ ȭ���� 2D �ؽ�ó�� ����� DX �Լ�
    //         �Ű������� "� �����͸� ��������, � �����Ϳ� �Բ�, � ������� ������ ���ΰ�"
}

void DepthStencil::CreateDSV()
{
    //�ؽ�ó �����͸� ������� �� �׸��� ����(ó���ϱ�) ���� �غ� ����
    D3D11_DEPTH_STENCIL_VIEW_DESC depthViewDesc = {};

    depthViewDesc.Format = isStencil ? DXGI_FORMAT_D24_UNORM_S8_UINT : DXGI_FORMAT_D32_FLOAT;
                        // ���ٽ��� ������ 1����Ʈ �뷮�� ������ �����ְ� �ƴϸ� 4����Ʈ �Ҽ�
    depthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D; //�̹��� ����(ó��) ���

    DEVICE->CreateDepthStencilView(dsvTexture, &depthViewDesc, &dsv);
    //CreateDepthStencilView : ���� ���ٽ� ���°� ����� ȭ��� �����͸� ����� DX �Լ�
    //       �Ű������� "� ������, � �����Ϳ� �Բ�, � ������� ������ ���ΰ�"
}

void DepthStencil::CreateSRV()
{
    // ���̴��� �ؽ�ó�� �����ϱ� ���� ����Ʈ ����
    D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
    desc.Format = isStencil ? DXGI_FORMAT_R24_UNORM_X8_TYPELESS : DXGI_FORMAT_R32_FLOAT;
    // ���ٽ��̸� ���� ���ٽǿ� ���� �κ��� ����� ����
    desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    // � �̹����μ� ����� ���ΰ� 
    desc.Texture2D.MipLevels = 1; //�Ӹ� ����

    DEVICE->CreateShaderResourceView(dsvTexture, &desc, &srv);
    //-> �̰����� ���̴��� �׸��� ����ϱ� ���� �غ� ��
}
