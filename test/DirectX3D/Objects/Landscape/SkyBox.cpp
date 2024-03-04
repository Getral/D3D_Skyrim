#include "Framework.h"

SkyBox::SkyBox(wstring file)
{
    //�ؽ�ó�� ���̴� ����
    skyMap = Texture::Add(file);
    //material->SetShader(L"Basic/Texture.hlsl"); //�⺻
    material->SetShader(L"Landscape/Skybox.hlsl"); //���� ���̴�

    FOR(2)
    {
        rasterizerState[i] = new RasterizerState();
        depthStencilState[i] = new DepthStencilState();
    }
    rasterizerState[1]->FrontCounterClockwise(true); // �����Ϳ��� "��" = ���
                                                     // = ����� ��� ������ ġ�ڴ�
    depthStencilState[1]->DepthEnable(false);        // ȭ�� �켱���� ���� =
                                    //"�̰ź��� �տ� �ִ� �׸��� ������ �տ� �ִ� �ɷ� ģ��"

    // -> �ȿ��� �ؽ�ó�� ���̰�, ����� ������ �ϴ��� ������ �������� ���
}

SkyBox::~SkyBox()
{
    FOR(2)
        delete rasterizerState[i];

    FOR(2)
        delete depthStencilState[i];
}

void SkyBox::Render()
{
    skyMap->PSSet(10); // �̹����μ� ������ ���� (���̴����� 10�� ������ ������ ������ ������,
                       //                       10���� ���� �켱������ ������ ���� ����ȴ�)

    // ��ī�̹ڽ��� �ɼ��� ����� ���¸� ȣ��
    rasterizerState[1]->SetState();
    depthStencilState[1]->SetState();

    Sphere::Render(); // ��ü�μ� �ڽ��� ����

    //���� ����
    rasterizerState[0]->SetState();
    depthStencilState[0]->SetState();

}
