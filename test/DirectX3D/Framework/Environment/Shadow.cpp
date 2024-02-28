#include "Framework.h"
#include "Shadow.h"

Shadow::Shadow(UINT width, UINT height)
    : width(width), height(height)
{
    //���� Ÿ��, ���� ���ٽ�, ���� ����
    renderTarget = new RenderTarget(width, height);
    depthStencil = new DepthStencil(width, height);
    viewBuffer = new ViewBuffer();
    projectionBuffer = new MatrixBuffer();

    //(�׽�Ʈ��) ���� ����
    quad = new Quad(Vector2(200, 200));
    quad->Pos() = { 100, 100, 0 };
    quad->UpdateWorld();

    //�ؽ�ó ���� (�� �׽�Ʈ������ ���� ���忡�� �ֱ�)
    Texture* texture = Texture::Add(L"Shadow", renderTarget->GetSRV());
    quad->GetMaterial()->SetDiffuseMap(texture);
}

Shadow::~Shadow()
{
    delete renderTarget;
    delete depthStencil;
    delete viewBuffer;
    delete projectionBuffer;
    delete quad;
}

void Shadow::SetRenderTarget()
{
    renderTarget->Set(depthStencil); // ���� Ÿ�� ���� (�׽�Ʈ�������� ������������ �ߴ� ��)
    SetViewProjection(); //����Ʈ, ��İ��� ���� ������ ���⼭ ȣ��
}

void Shadow::SetRender()
{
    viewBuffer->SetVS(11);
    projectionBuffer->SetVS(12);
                // DX������ ���̴��� �׷��� ���길�� �ƴ϶� �߰� �ڵ� ���࿡�� Ȱ���� �� �ִ�...(��ǻƮ ���̴��� Ȯ��)
                // �׸��� �׷��� ������ ������ �Ѿ�� �Ǹ� ���̴��� ������ �켱���� �ܿ�, �߰� ���ǽ��� ���� �Ҵ翡�� ����
                // -> �� �Ű������� ���� �ٸ��� �ִ� ������ ���̴��� ���̳�, ��Ÿ �Լ� ������ �ٲ� ���� �ִ�
                // -> ���⼭ ���� �Ű������� ����� ��ǻ��� ������ ������� �ٲ��ִ� ��. (���� ������ ����)

    DC->PSSetShaderResources(10, 1, &renderTarget->GetSRV());
                //10�� ���Ժ���, 1�� ����ŭ��, GetSRV���� ������ ��� �غ�

    //������� ����Ǹ� �ؽ�ó�� �غ�
}

void Shadow::PostRender()
{
    //�� �Լ����� �غ�� �ؽ�ó....�� ���� ����....�� �׽�Ʈ������ ���
    quad->Render();
}

void Shadow::GUIRender()
{
    ImGui::SliderFloat("Scale", &scale, 1, 10); //"ũ��" ����
}

void Shadow::SetViewProjection()
{
    // ���� Ŭ������ �Ẹ�� (DX + �����ӿ�ũ ����)
    LightBuffer::Light* light = Environment::Get()->GetLight(0);
    //LightBuffer : �� ��� ����� ���۷� �ٲ� Ŭ����
    //Light(�����ӿ�ũ) : �� ���� ���� �ִ� ���� �� ������ (���� �����ʹ� DX�� ���̴��� �л�)
    //GetLight() : ����������� ������ ���� ȣ���ϱ�. 0�� �⺻���� ������ ���

    //->���� �����͸� �����ͷ� �޾Ҵ�

    //�̾ ����Ʈ�� ����� ��� ���ϱ�
    Matrix view = XMMatrixLookAtLH(Vector3(light->pos), Vector3(), Vector3(0, 1, 0));
                //XMMatrixLookAtLH : DX�� ����� Ȱ���ؼ� ��� ������ ���ϴ� �Լ�
                //                   LH�� ���� ��ǥ��. LookAt�� �Ű������� ����->���� ������ �ؼ�
                // ���� ������ �Ű������� ���� ��������, ��������, ������ ������(��)�� ������ ���´�

    Matrix projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, 1, 0.1f, 1000);
                //XMMatrixPerspectiveFovLH : DX�� ����� Ȱ���ؼ� ������� ������ ���ϴ� �Լ�
                //                          LH�� ������ǥ��, Perspective�� ������ ����ȴ�.
                //                     ���� �Ű����� ������ "ȸ������� 360��, �¿���� 1:1,
                //                    ���� ������ ���� ����� Z��ǥ�� 0.1, ���� �� ��ǥ�� 1000

    //���� ����
    viewBuffer->Set(view, XMMatrixInverse(nullptr, view)); // XMMatrixInverse : ����� �����(��� ������)
                                                           // �� ������ ���� ��� �����͸� GPU���� ���� ����
                                                           // �Ű������� ���� "�߰� �ɼ��� �ִ°�?
                                                           // �׸��� ������ �����ΰ�? (=view)"
    projectionBuffer->Set(projection);

    //���۸� ���̴��� �ѱ�� (=GPU��� �� ��� ���)
    viewBuffer->SetVS(1);
    projectionBuffer->SetVS(2);
}
