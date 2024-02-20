#include "Framework.h"

HullShader::HullShader(wstring file)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
    // ������ �ɼ� ���� : 1. Dx3D���� ���ҽ��� ���� �� ���� ������ �ؼ��϶�� �Ǿ� ������ �״�� ������
    //                   2. ����׷� ������ �Ǿ� �־ ��Ų ��� �ϱ�

    D3DCompileFromFile(file.c_str(),            // �������� ���̴� �ڵ�
        nullptr,                                // �߰� �ɼ� �ڵ�
        D3D_COMPILE_STANDARD_FILE_INCLUDE,      // �������� �� �߰��� ����(����)�� DX ����
        "HS",                                   // ������(���̴� �ڵ� ���忡���� main�Լ� ����� ��)
        "hs_5_0",                               // ����� ���̴�(������ ����)
        flags,                                  // ������ �ÿ� ������ ������ �ɼ�
        0,                                      // �߰� ������ �ɼ��� �ִٸ� ���⼭
        &blob,                                  // ��� ������ : ���� ���̴��� ����ó�� ���� ��ġ�� ���� ���� �̵�� �����͸� ��Ī
        nullptr                                 // �߰��� ����� ó���ϴٰ� ������ ���� ��� ��ó�� �ൿ ����
    );

    DEVICE->CreateHullShader(blob->GetBufferPointer(), //��� ���� �־���(������) ������ �޸� ������
        blob->GetBufferSize(),                         //����� ó���ϱ� ���� ���� ũ��
        nullptr,                                       //�߰��� ������ ���̴� �ɼ�
        &shader);                                      //���̴� ������
}

HullShader::~HullShader()
{
    shader->Release();
}

void HullShader::Set()
{
    //�����ġ���� �ҷ����� ���̴��� (�ɼ� �״��) ����
    DC->HSSetShader(shader, nullptr, 0); // shader�� ���� �ɼǴ��, �߰� �ɼ��� ����
                                         // -> �ܺο��� �ҷ������ shader�� ����
                                         // �ٸ� �ɼǵ� �̸� �غ��� ��, �Ű�������
                                         // nullptr, nullptr, 0���� ���� ��
}
