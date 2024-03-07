#include "Framework.h"

SamplerState::SamplerState()
{
    // ���÷� ������Ʈ : DX�� �׷��� ��� ���� ������ ������Ʈ�� �ϳ�(�׸��� �⺻)
    // ������ �ؽ�ó�� ��� �ɼ��� �����Ѵ�
    // ����� �⺻������ ���� �� : �ִ� �״�� ���ڴٴ� �ǵ� + �ʿ��ϸ� ���⼭ �����Ѵٴ� ��

    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; // �Ÿ��� ���� �ؽ�ó ��� ���(���͸�) : �⺻���� ���� ���ø�
    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;    // �ؽ�ó ��巹�� ��� : �⺻�� �� �޽���, �� �ؽ�ó�� �θ���
    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;;
    desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desc.MinLOD = 0;
    desc.MaxLOD = D3D11_FLOAT32_MAX;
    //LOD(Level Of Detail) : ī�޶��� �Ÿ��� ���� ����Ƽ�� �ٸ��� �ϴ� ��   

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
