#include "Framework.h"
#include "ShadowScene.h"

ShadowScene::ShadowScene()
{
    forest = new Model("Forest");
    forest->Scale() *= 5;
    forest->UpdateWorld();

    //human = new Model("Human");
    human = new ModelAnimator("Human");
    human->ReadClip("Idle", 1);
    human->UpdateWorld();

    shadow = new Shadow();

    // ���� �˾ƺ��� Ȱ��� : �� ȣ�� Ȥ�� ����� (<-�� ��� ���)

    light = Environment::Get()->GetLight(0); // �⺻���� ������ �� ��������
    //light = Environment::Get()->AddLight(); //���ο� ���� ���� ��ȯ�ޱ�

    light->type = 1;               //���� ���� (�� ������ ���Ŀ�)
    light->pos = { 0, 50, -500 }; //���� ��ġ
    light->range = 3000;           //���� ���� (���� ������ ��� ����)

    light->direction = { 0, -1, 1 }; //���� ���� (���簪 : �տ���, �񽺵���, �Ʒ���)
    light->color = { 1, 1, 1, 1 };   //������ �� (���簪 : ���)
    
    light->length;  //���� ����      (���� �������� ����....�� �� ����)

    // ���� ��� ��/���� �ʴ� ���� ����ų ���, ���� �������� �Ʒ� ������ ���� ����ϸ� �ȴ�
    light->inner;   //���� ���� ���� (���� ���ߵǾ� ���̴� ����...�� ����)
    light->outer;   //���� �ܰ� ���� (���� ������� ��ġ�� ����...�� ����)
}

ShadowScene::~ShadowScene()
{
    delete forest;
    delete human;
    delete shadow;
}

void ShadowScene::Update()
{
    if (KEY_DOWN('1')) light->type = 0; // ���⼺ ���� (directional light) :
                                        // ����, ũ��, ���� ���� ��� �����ϰ� ���⸸ ����.
                                        // ���� �� ��� ��ü�� �� ���� �����ϰ� �޴´�
                                        // ���� ��� 3D ���α׷��ֿ��� ���� ���� ��������
                                        // ���� �⺻�̶� ���� ū �߿䵵�� ���� �ʴ´�
                                        // ���Ƿ� ġ�� - �޺�

    if (KEY_DOWN('2')) light->type = 1; // ���� ���� (�� ����, point light) : 
                                        // Ư�� ���� �߽����� ���� ���� ������ ������
                                        // �߽ɿ� �������� ������� ���¿� ������ ������ ����
                                        // ���� ��, ��ο� ���� ������ �� �־� ���ӿ��� ���� ����

    if (KEY_DOWN('3')) light->type = 2; // ���� ����, ���� ����, ����Ʈ����Ʈ (spot light)
                                        // Ư�� ������ �������� ���� ����� ������ ������
                                        // �ش� ���⿡ ������, �߽ɿ� �������� �������
                                        // ������ �ٸ� ���� ���� ���� ���� �ʴ´�
                                        // ���ӿ��� ���� ���̴� ���� �� �ϳ�

    if (KEY_DOWN('4')) light->type = 3; // ĸ�� ���� (capsule light) :
                                        // �� ������ ��������� ���� �߽��� 2������ ��
                                        // �� ���� �� �߽ɿ� �̸��� �Ÿ��� �տ� ���� ��Ⱑ �޶�����
                                        // �� �߽��� ���� ���, �� �߽��� �� ����� �� �������� ������
                                        // �ش� �������� �־������� ��ο�����
                                        // ���Ƿ� ġ�� �߱��� ���� ������ �ܼ�ȭ�� �Ϳ� ������ �� ������
                                        // ���̵� ���� ������ ��ȿ�����̶� ���ӿ����� �� ���� �ʴ´�

    // * �� �����ӿ�ũ���� ������, ���� �߿��� (Ư�� ���ӿ� ��) Ȱ��Ǵ� ������ �ϳ� �� �ִ�
    // ���� ���� (area light) : �� ��ü�� �������� ��� ��/���� ����
    //                         -> ���� ��ü�� ������ ��⸦ �����µ� ������ ���ұ��� �� �� ����
    //                         -> ��ο� ������ ����, �ǿܷ� ���� �ⱸ Ȥ�� â��, Ȥ�� ��ο� ���� �����

    forest->UpdateWorld();
    //human->UpdateWorld();
    human->Update();
}

void ShadowScene::PreRender()
{
    //�׸����� ���� Ÿ�� ����(�� �غ�)
    shadow->SetRenderTarget();

    //�ΰ����� ���� ���̴��� ���� (���ǿ� ���� ���̴� ��ȭ...���� ���� ���� �Լ�)
    human->SetShader(L"Light/DepthMap.hlsl");

    //���ǿ� ���� �ȼ��� �ٲ� �ΰ��� ����...�ؼ� �ؽ�ó�� �غ�
    human->Render();
}

void ShadowScene::Render()
{
    //�� �Լ����� ������� �ؽ�ó�� �׸��ڿ��� ���� ������� ����
    shadow->SetRender();

    //�׸��ڸ� �ޱ� ���� ���̴� ����
    forest->SetShader(L"Light/Shadow.hlsl");
    human->SetShader(L"Light/Shadow.hlsl");

    //���̴��� ���õ� ���� �ΰ��� ��¥ ȣ��
    forest->Render();
    human->Render();
}

void ShadowScene::PostRender()
{
    //shadow->PostRender(); // ���� ��¿�
}

void ShadowScene::GUIRender()
{
    shadow->GUIRender(); // ����� ���ۿ�
}
