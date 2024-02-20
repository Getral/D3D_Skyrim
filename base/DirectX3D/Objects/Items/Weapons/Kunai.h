#pragma once
class Kunai
{
    //����ü �ϳ��� �Ѱ��ϴ� Ŭ����

private:
    //������ �ʿ��� �ֿ� ������ (������)
    float LIFE_SPAN = 5; // life span = ���� �ֱ�, Ȥ�� ���� ���� �Ⱓ
                         // ���α׷��ֿ����� �ӽ÷� ������ ��ü�� �ڵ� ����
                         // Ȥ�� ��Ȱ��ȭ�ϱ���� �ɸ��� �ð��� ���Ѵ�

public:
    //ȣ��� �Լ�
    Kunai(Transform* transform); //�ν��Ͻ��� ������ Ʈ������ �Ű� ����
    ~Kunai();

    void Update();
    void Render();

    void Throw(Vector3 pos, Vector3 dir);

    SphereCollider* GetCollider() { return collider; }
    Transform* GetTransform() { return transform; }
private:
    //��� �Լ�

private:
    //��� ����

    Transform* transform;
    SphereCollider* collider;

    float speed = 1000;
    float time = 0; //������ �ð�

    Vector3 direction;
};

