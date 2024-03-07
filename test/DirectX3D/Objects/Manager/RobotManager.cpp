#include "Framework.h"

RobotManager::RobotManager()
{
    //����� ����
    robotInstancing = new ModelAnimatorInstancing("Robot");
    robotInstancing->ReadClip("StandUp"); //�κ��� ���¿� ���� �ε��� ���� ���߱�
    robotInstancing->ReadClip("Walk");
    robotInstancing->ReadClip("Run");
    robotInstancing->ReadClip("Hit");
    robotInstancing->ReadClip("Dying");

    //�ν��Ͻ� ���ο��� �� Ʈ�������� ���� ��,
    //�κ��� ����� Ʈ�������� ��ġ��Ű��
    FOR(SIZE)
    {
        Transform* transform = robotInstancing->Add(); // Ʈ�������� �߰��ϰ�, ��ȯ���� �ޱ�
        transform->SetActive(false); //�޾ƿ� Ʈ������(=������� �� �κ�)�� Ȱ��ȭ ����
        Robot* robot = new Robot(transform, robotInstancing, i);
                                        //�κ� �����͸� ����� Ʈ������, ��, �ε��� �ֱ�
        robots.push_back(robot); //�κ��� �����͸� ���Ϳ� �߰�
    }

    //�κ� ��(����), Ʈ������(SIZE��ŭ) Ʈ������ ��ġ���� ������ ��¥ �κ� ������(SIZE��ŭ)
    //->���� ��� �غ�ȴ�
}

RobotManager::~RobotManager()
{
    delete robotInstancing;

    for (Robot* robot : robots)
        delete robot;
}

void RobotManager::Update()
{
    //���ο� �Լ� ��������

    // 1. �浹 ���� ����
    Collision();

    // 2. (��)���� ����
    time += DELTA; //����ð� ����

    if (time >= SPAWN_TIME) //��� �ð��� �������ݿ� �����ϸ�
    {
        time -= SPAWN_TIME;
        Spawn(); //����(����)
    }

    //���� �Լ� �� -> �� ������Ʈ
    robotInstancing->Update();

    for (Robot* robot : robots)
        robot->Update(); //�κ��� ������Ʈ
}

void RobotManager::Render()
{
    robotInstancing->Render();
    for (Robot* robot : robots) robot->Render();
}

void RobotManager::PostRender()
{
    for (Robot* robot : robots) robot->PostRender(); //ĳ���Ϳ� UI�� ���� ��� ���
}

void RobotManager::SetTarget(Transform* target)
{
    this->target = target; // �Ŵ��� ���忡�� ����� ǥ�� : �ϰ����� ���� �ʿ��� �� �� ��
    //�� �κ� ���忡���� ǥ���� ���� ����
    for (Robot* robot : robots)
        robot->SetTarget(target);
}

bool RobotManager::IsCollision(Ray ray, Vector3& hitPoint)
{
    //�ܺ� ȣ���

    Contact contact;
    float minDistance = FLT_MAX;

    for (Robot* robot : robots)
    {
        //�ܺο��� �� ������ �κ��� �浹�ϸ�...
        if (robot->GetCollider()->IsRayCollision(ray, &contact))
        {
            if (contact.distance < minDistance) //�κ����� ���� ���� ��� ����
            {
                minDistance = contact.distance; // �������� ��� �ݿ�
                hitPoint = contact.hitPoint;
            }
        }
    }

    //�� �ݺ������� ã�� �Ÿ��� ������ �ʱⰪ���� �ǹ� �ְ� ������ �Ǻ�
    return minDistance != FLT_MAX; //�� ���ں��� �Ҽ��� Ŀ�� ���� �����ϱ�,
                                   //�ٸ��� = �κ� �߿� �������� ��򰡿� �ε��ƴ�

    // �� �Լ��� �����ϸ� �ϴ� �Ŵ��� ������ �浹�� ������ ��
    // -> ���� �¾Ҵ����� �߰��� �˾Ƴ��� �ش� robot�� �ʿ��� �Լ��� �ִٸ� �߰� ������ �����ָ� �ȴ�
    return false;
}

void RobotManager::Collision()
{
    //���� ������

    for (Robot* robot : robots)
    {
        //���⼭ �� robot ��ü�� �ܺ� ��ü �浹 ���θ� ����
        //������ �Ǹ� �ش� robot�� �߰� �Լ��� �����ϸ� �ȴ�

        //���� �ó����� : ���̿� ������ ��û��û�ϰ�
        if (KunaiManager::Get()->IsCollision(robot->GetCollider()))
        {
            robot->Hit();
            return; // ������ ���⼭ �����ص� ������Ʈ�� �� ã���� �״ϱ�
        }
    }
}

void RobotManager::Spawn()
{
    //���� ���� �����
    Vector3 dir;
    dir.x = Random(-1.0f, 1.0f);
    dir.z = Random(-1.0f, 1.0f);

    //�����Ÿ� ����� �Բ� ǥ���� �������� ������ �Ѵ�
    Vector3 randomPos = target->Pos() + (dir.GetNormalized() * 2000);

    // ������ ������ ���� ��ҿ��� �κ� �ϳ� ���� (������)
    for (Robot* robot : robots)
    {
        if (!robot->GetTransform()->Active()) // �κ��� ��ȸ ���ε� ��Ȱ��ȭ ���� ��ü�� ������
        {
            robot->Spawn(randomPos); // ���� �κ� ȣ��
            break; //�ݺ���(���� ����) ����
        }
    }
}
