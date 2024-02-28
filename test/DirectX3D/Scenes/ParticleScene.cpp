#include "Framework.h"
#include "ParticleScene.h"

ParticleScene::ParticleScene()
{
    collider = new SphereCollider(30); // �׽�Ʈ�� �浹ü

    //particle = new Spark(L"Textures/Effect/star.png", true);
    //particle = new Rain(); //�� ����
    //particle = new Sprite(L"Textures/Effect/explosion.png", 10, 10, 5, 3);
    //particle = new Sprite(L"Textures/Effect/fire_8x2.png", 5, 25, 8, 2, false);

    // ��ƼŬ�� �����̰�, ������ �ƴ� ���� ����� �ʿ��� ��
    //particle->Play(Vector3()); //�������� ���� ����Ʈ ����

    //---------------------------------------

    // ���� ��ƼŬ ���
    //particle = new ParticleSystem(L"Textures/Effect/explosion.png");
                                        // �׸����� �����
    particle = new ParticleSystem("TextData/Particles/Star.fx");
                                        // ������ ������ ������ �о �����
}

ParticleScene::~ParticleScene()
{
    delete particle;
    delete collider;
}

void ParticleScene::Update()
{
    if (KEY_DOWN(VK_LBUTTON)) //��Ŭ��
    {
        Ray ray = CAM->ScreenPointToRay(mousePos);
        Contact contact;

        if (collider->IsRayCollision(ray, &contact)) //���콺 Ŀ���� ��ü�� ������
        {
            particle->Play(contact.hitPoint); //�ű⼭ ��ƼŬ ���
        }
    }
    particle->Update();
}

void ParticleScene::PreRender()
{
}

void ParticleScene::Render()
{
    particle->Render();
    collider->Render();
}

void ParticleScene::PostRender()
{
}

void ParticleScene::GUIRender()
{
    particle->GUIRender();
}
