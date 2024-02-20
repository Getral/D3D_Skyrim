#include "Framework.h"

Reflection::Reflection(Transform* target)
    : target(target)
{
    renderTarget = new RenderTarget(2048, 2048);
    depthStencil = new DepthStencil(2048, 2048, true); // ���ٽ� ���� ���

    camera = new Camera();

    quad = new Quad(Vector2(200, 200));
    quad->Pos() = { 100, 100, 0 };
    Texture* texture = Texture::Add(L"Reflection", renderTarget->GetSRV());
    quad->GetMaterial()->SetDiffuseMap(texture);
    quad->UpdateWorld();

    // �����
    FOR(2) rasterizerState[i] = new RasterizerState();
    rasterizerState[1]->CullMode(D3D11_CULL_NONE); // ���⿡ ���� �ؽ�ó �ø� ����
}

Reflection::~Reflection()
{
    delete renderTarget;
    delete depthStencil;

    FOR(2) delete rasterizerState[i];

    delete camera;
    delete quad;
}

void Reflection::Update()
{
    //Ŭ���� �� ī�޶��� ��ġ�� ���� �� �þ߿� ��ġ��Ű��
    camera->Pos() = CAM->Pos();
    camera->Rot() = CAM->Rot();

    //�� �þ߸� ����� Ŭ���� �� ī�޶� �ݻ� ��Ȳ�� ���߾ ���� ����, ��ġ�� ������
    //->�ݻ� ����� �߿� ����

    // * ���� ��Ȳ : �� �ݻ縦 ��ǥ�� �ϰ� �����Ƿ�, ���� ���� �� �ְ�,
    //   ���� ������ �ݻ��� �������� ��´ٰ� ����

    camera->Rot().x *= -1; // ���Ʒ� ������
    camera->Pos().y = target->Pos().y * 2.0f - camera->Pos().y;
                     // target : ���� ��� = �ݻ������� ��ü
                     // target - cam = ī�޶󿡼� �ݻ������� �Ÿ�
                     // -> ���� �ǹ� : �ݻ�� �þ�(ī�޶�)�� ���麸�� �� �Ʒ��� ��ó��
                     //    or ���� ������ �� �� ���ʿ��� ��ġ����(*2)

    // �þ߰��� ��ġ�� ������ ī�޶� �þ߸� ������Ʈ
    camera->UpdateWorld();
}

void Reflection::SetReflection()
{
    renderTarget->Set(depthStencil);
    camera->SetView(); // ��ġ�� ������ ���缭 �þ� ��� (���� �߰� ī�޶�� �� �ʿ�)
}

void Reflection::SetRender()
{
    camera->GetViewBuffer()->SetVS(10);
    DC->PSSetShaderResources(10, 1, &renderTarget->GetSRV());
}

void Reflection::PostRender()
{
    // ī�޶� ���� ����Ÿ����, ���̴� �����͸� �����ͼ� ���� �ؽ�ó��, ��ü�� ���
    quad->Render();
}

void Reflection::GUIRender()
{
    quad->GUIRender();
    camera->GUIRender();
}
