#include "Framework.h"

RasterizerState::RasterizerState()
{
    // �����Ͷ����� ������Ʈ : ����ȭ�� �ؽ�ó(2D �̹���)�� �ȼ��� ��ȯ�ؼ� ����ϴ� ����
    //                       �ؽ�ó ǥ�� + 3D ���� ����Ϳ��� ���� ���� �׸����� ��ȯ�Ѵ�
    //                       �⺻������ ���� �����Ǿ� �ְ�, �ʿ��ϸ� �ٸ� ������ �߰��� �ҷ���
    //                       �ٸ� �ɼ��� �ֱ⵵ �Ѵ�

    desc.CullMode = D3D11_CULL_BACK;  // ��� ���� ���� (�ø� ���) : �⺻���� �޸� ������
    desc.FillMode = D3D11_FILL_SOLID; // �ؽ�ó ��� ���� (��� ȭ�Ҹ� ä�� ���ΰ�) : �⺻=�� �׸���
    //desc.FrontCounterClockwise      // ���� �ؽ�ó�� �ݽð� �����ΰ�? : 
                                      // -> ���� ������ �� ������ �ð� ����/�ݽð� �������� ����� ��
                                      //    ��� ���� ������ ������ ���ΰ��� ���Ѵ�. �⺻���� false

    // * �ؽ�ó ���� ������ ������ ���� ���� �����,
    //   ����� ���ο����� ȸ����, ������ ���� �������� �� ȸ���� ��� �ٸ� ���
    //   = �ϳ��� A �����̶�� �ٸ� �͵� A �����̴�....��� ���� ����

    Changed();
}

RasterizerState::~RasterizerState()
{
    state->Release();
}

void RasterizerState::SetState()
{
    DC->RSSetState(state);
}

void RasterizerState::FillMode(D3D11_FILL_MODE value)
{
    desc.FillMode = value;

    Changed();
}

void RasterizerState::CullMode(D3D11_CULL_MODE value)
{
    desc.CullMode = value;

    Changed();
}

void RasterizerState::FrontCounterClockwise(bool value)
{
    desc.FrontCounterClockwise = value;

    Changed();
}

void RasterizerState::Changed()
{
    if (state != nullptr)
        state->Release();

    DEVICE->CreateRasterizerState(&desc, &state);
}
