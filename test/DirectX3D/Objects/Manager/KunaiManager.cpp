#include "Framework.h"
#include "KunaiManager.h"

KunaiManager::KunaiManager()
{
    kunaiInstancing = new ModelInstancing("Kunai");

    kunaies.reserve(SIZE);
    FOR(SIZE)
    {
        Transform* transform = kunaiInstancing->Add();
        transform->SetActive(false);
        Kunai* kunai = new Kunai(transform);
        kunaies.push_back(kunai);
    }
}

KunaiManager::~KunaiManager()
{
    //���� �����
    for (Kunai* kunai : kunaies)
        delete kunai;

    //�𵨵� �����
    delete kunaiInstancing;
}

void KunaiManager::Update()
{
    kunaiInstancing->Update(); //�� ������Ʈ
    for (Kunai* kunai : kunaies) kunai->Update(); //�����͵� ������Ʈ
}

void KunaiManager::Render()
{
    kunaiInstancing->Render(); //�� Render
    for (Kunai* kunai : kunaies) kunai->Render(); //�����͵� Render
                    //���� ȣ��� ����Render�� ������ �ʿ䰡 ����(�������� �浹ü ������)
}

void KunaiManager::Throw(Vector3 pos, Vector3 dir)
{
    for (Kunai* kunai : kunaies)
    {
        //���� �� ���� ������ ó������ �Ǻ��ؼ� �ϳ��� ������ �ٷ� ����
        if (!kunai->GetTransform()->Active())
        {
            kunai->Throw(pos, dir);
            return;
        }
    }
}

bool KunaiManager::IsCollision(Collider* collider)
{
    for (Kunai* kunai : kunaies)
    {
        if (kunai->GetCollider()->IsCollision(collider))
        {
            //�Ѿ��� �¾��� ��, "�Ѿ���" ������ �ڵ带 �߰�

            //���� �ڵ� : �浹 �� ������� �ϱ�
            kunai->GetTransform()->SetActive(false); // <-�� ���� ������ ����ź�� �ȴ�
            return true;
        }
    }

    return false;
}
