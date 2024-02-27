#include "Framework.h"
#include "RenderTargetScene.h"

RenderTargetScene::RenderTargetScene()
{
    //model = new ModelAnimator("Fox");
    //model->ReadClip("Idle");
    //model->UpdateWorld();

    model = new Model("Human");
    model->UpdateWorld();

    renderTarget = new RenderTarget();
    depthStencil = new DepthStencil();

    quad = new Quad(Vector2(500, 500)); // �� �׸� �ϳ� �����
    //quad = new Sphere(200);
    quad->Pos() = { CENTER_X, CENTER_Y };
    quad->GetMaterial()->SetShader(L"Effect/Bloom.hlsl"); // ��� : "��½��" Ȥ�� �� ���� ȿ��
                                                          // ���⼭�� �� �� �� ���� �κ��� ����
    quad->GetMaterial()->SetDiffuseMap(Texture::Add(L"Rendered_Sight", renderTarget->GetSRV()));
                        // �ؽ�ó Ŭ������ �׸� ���� ���, �ۿ��� ���� ������� �׸� �����͸� ��������
    quad->UpdateWorld(); //����, ���� �� ��� ������Ʈ

    valueBuffer = new FloatValueBuffer(); //�Ҽ� ���� ����
    valueBuffer->Get()[0] = 1; //�⺻�� 1 �ֱ�
    valueBuffer->Get()[1] = 1; //���� ����
}

RenderTargetScene::~RenderTargetScene()
{
    delete model;
    delete renderTarget;
    delete depthStencil;
    delete quad;
    delete valueBuffer;
}

void RenderTargetScene::Update()
{
    model->UpdateWorld();
}

void RenderTargetScene::PreRender()
{
    // ���� ���� ���� ���� (���� Ÿ��)

    renderTarget->Set(depthStencil); //�� ���� (=Ŭ������ �̸� ������) ���� ���ٽǷ� RTV����

    //RTV�� ������ ������ �� �׸���
    model->Render();
}

void RenderTargetScene::Render()
{
    //���� ������ �ʿ��ϴٸ� ���⼭
    model->Render();
}

void RenderTargetScene::PostRender()
{
    valueBuffer->SetPS(10); // ��� ���̴��� ���� ������ ���԰�(���ǰ����� Ȱ�� ������) �ְ� Ȱ��ȭ
    quad->Render(); //���带 ����

    // ���� Ÿ�ٿ����� ������ �Ϻ� ������ �ؽ�ó�� ����
    // �ؽ�ó�� ���忡 ��Ƽ����� ����
    // �ٽ� �� ���带 �ۿ��� ���� -> ����ڴ� ���带 ���� ���� �� �� �ְ� �ȴ�
}

void RenderTargetScene::GUIRender()
{
    ImGui::SliderFloat("Threshold", &valueBuffer->Get()[0], 0, 1);
                      //threshold : �Ӱ���. Ư�� �����̳� ó���� �Ͼ�� ���� �ּ�(Ȥ�� �ִ�) ����
                      //            ���ӿ����� �ַ� ����, Ư���� �������� �÷��̾� ���� ����� �Ǻ��� �� ���

    ImGui::SliderFloat("Value", &valueBuffer->Get()[1], 0, 10);
                      //�� �Ӱ����� �̹� ���� �������� �� ������ ������ : ��� ���̴��� �� ���� ����

}
