#include "Framework.h"

Kunai::Kunai(Transform* transform) : transform(transform)
{
    transform->Scale() = { 2, 2, 2 }; // ũ�� �⺻���� 1
                                      // ���߿� ũ�Ⱑ �ٲ��� �ϸ� �ͼ� �����ϰ�

    collider = new SphereCollider();
    collider->SetParent(transform);

    collider->Scale() = { 2, 2, 2 }; //ũ�� �⺻���� 1.0
    collider->Pos() = {};            //��ġ �⺻�� : �θ� ��ġ
}

Kunai::~Kunai()
{
    delete collider;
}

void Kunai::Update()
{
    //��Ȱ��ȭ �߿��� �� ������
    if (!transform->Active()) return;

    time += DELTA; // �ð� ����� ���� ������ ����

    if (time > LIFE_SPAN)
        transform->SetActive(false);

    transform->Pos() += direction * speed * DELTA;

    collider->UpdateWorld();
}

void Kunai::Render()
{
    collider->Render();
}

void Kunai::Throw(Vector3 pos, Vector3 dir)
{
    //Ȱ��ȭ
    transform->SetActive(true);

    transform->Pos() = pos;
    direction = dir;

    //���⿡ �°� ��(=Ʈ������) ȸ�� ����
    transform->Rot().y = atan2(dir.x, dir.z) - XM_PIDIV2; //���� ���� + �� ���鿡 ���� ����
                                                          //���� ���� 90�� ���ư� �־���
    //transform->Rot().y = atan2(dir.x, dir.z) - XMConvertToRadians(90);
    //                                           �� ������ ȣ���� �ٲ��ִ� �Լ�

    time = 0; //����ð� ����
}
