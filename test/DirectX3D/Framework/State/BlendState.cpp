#include "Framework.h"

BlendState::BlendState()
{    
    // ���� ������Ʈ : �̹����� ��ϵǾ��ų�, �ܺο��� ���� ������ ȭ�Ҹ� Ż����Ű�ų� (���� ������)
    //                  ���� ��ġ�� �ִ� �̹����� ȭ�Ҹ� ��ġ�ų� (������ ó��)
    //                  �̹����� �ٸ� ������ �Űܼ� �����ϴ� ���� ���
    //                  = WinAPI�� �־��� AlphaBlendBlt�� ����ϴ� ����� ���� ����

    desc.RenderTarget[0].BlendEnable = false;                       // ���� ��� Ȱ��ȭ
    desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;          // ���带 �ϱ� ���� �ر׸�(����)
    desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;     // ���� �Ŀ� ����� �̹��� ���� (�⺻�� : ���� �����Ϳ� ��ġ��)
    desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;              // ���� ��� (�⺻�� : ������)
    
    desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;     // ���� ���� (������ ����)
    desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;// �ɼ� ������ �� 3���� ����
    desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;         // 
    
    desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // ������ �̹����� ��ĥ �� ���� ����
                                                                               // �⺻�� : �տ� �ִ� �̹����� ������ �켱 (�� ����)
    // D3D11_COLOR_WRITE_ENABLE_NONE : RenderTargetWriteMask �ɼ� �������� ���� ���ٱ� �ʿ���� ȣ�� ������ �� ��° ������
    //                                 ���� � �͵� �̹����� ������ ���� (= �ڿ� �ִ� �׸��� ������ �� ����)

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
