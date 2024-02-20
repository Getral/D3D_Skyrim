#include "Framework.h"
#include "Robot.h"

Robot::Robot(Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
    :transform(transform), instancing(instancing), index(index)
{
    //transform = new Transform(); //�𵨰� Ʈ�������� �ۿ��� ���� ���� �� �ڵ� ����

    //��Ʈ �����(Ȥ�� �ޱ�)
    root = new Transform();

    //�浹ü
    collider = new CapsuleCollider(30, 100); // <- ���� ���� 160
    collider->SetParent(root);
    collider->Rot().z = XM_PIDIV2 - 0.2f;
    collider->Pos() = { -15, 10, 0 };
    collider->SetActive(true); //�浹ü ���̱� ���� ���� �� �κ� false

    //���� �ۿ��� ������, �ȿ��� ������, �ν��Ͻ��� ���� ���ο� ����
    //���⼭ �ҷ����� (���⼭�� �ν��Ͻ� ����)

    motion = instancing->GetMotion(index);
    totalEvent.resize(instancing->GetClipSize()); //���� ���� ���� ���ڸ�ŭ �̺�Ʈ ������¡
    eventIters.resize(instancing->GetClipSize());

    //�̺�Ʈ ����
    SetEvent(STAND_UP, bind(&Robot::EndStandUp, this), 0.7f);
    SetEvent(HIT, bind(&Robot::EndHit, this), 0.9f);
    SetEvent(DYING, bind(&Robot::EndDying, this), 0.9f);

    FOR(totalEvent.size())
    {
        eventIters[i] = totalEvent[i].begin(); // ��ϵǾ� ���� �̺�Ʈ�� ������������ �ݺ��� ����
    }

    //ĳ���� UI �߰�
    hpBar = new ProgressBar(
        L"Textures/UI/hp_bar.png",
        L"Textures/UI/hp_bar_BG.png"
    );
    hpBar->SetActive(false);
}

Robot::~Robot()
{
    // ��ü ����
    delete collider;
    delete root;
    
    // �ӽ� ����
    delete transform;

    // ü�¹� ����
    delete hpBar;
}

void Robot::Update()
{
    //Ȱ��ȭ �ÿ��� ������Ʈ
    if (!transform->Active()) return;

    velocity = target->GlobalPos() - transform->GlobalPos(); // �ӷ±��� : ǥ���� �ڽ��� �Ÿ�

    ExecuteEvent(); // �̺�Ʈ�� ������ �ϸ� �����ϱ�
    Move(); //�����̱�
    UpdateUI(); //UI ������Ʈ

    root->SetWorld(instancing->GetTransformByNode(index, 3));
    collider->UpdateWorld(); //�浹ü ������Ʈ

}

void Robot::Render()
{
    //�𵨷μ��� ������ �� Ŭ���� �Ұ� �ƴ�
    //�� Ŭ������ ���� �浹ü�� å������ ��
    collider->Render();
}

void Robot::PostRender()
{
    hpBar->Render();
}

void Robot::Hit()
{
    //ü�¿� -
    curHP -= 20;
    hpBar->SetAmount(curHP / maxHP); // ü�� ������ ���� ü�¹� ����

    // ü���� ������ �ٴڳ���
    if (curHP <= 0)
    {
        SetState(DYING); //�װ�
        return;//�� �Լ� ����
    }

    // ���� �� �׾����� �� �κ���� �´� ���� ����
    curState = HIT;
    instancing->PlayClip(index, HIT);
    eventIters[HIT] = totalEvent[HIT].begin();
}

void Robot::Spawn(Vector3 pos)
{
    transform->SetActive(true); //��Ȱ��ȭ���ٸ� Ȱ��ȭ ����
    collider->SetActive(true);

    SetState(WALK); // ������ ��å

    curHP = maxHP;
    hpBar->SetAmount(curHP / maxHP);

    transform->Pos() = pos;
}

void Robot::SetTarget(Transform* target)
{
    this->target = target;
}

void Robot::SetEvent(int clip, Event event, float timeRatio)
{
    if (totalEvent[clip].count(timeRatio) > 0) return; // ���� ����� �̺�Ʈ�� ������ ����
    totalEvent[clip][timeRatio] = event;
}

void Robot::ExecuteEvent()
{
    int index = curState; //���� ���� �޾ƿ���
    if (totalEvent[index].empty()) return;
    if (eventIters[index] == totalEvent[index].end()) return;

    float ratio = motion->runningTime / motion->duration; //����� �ð� ������ ��ü ����ð�

    if (eventIters[index]->first > ratio) return; // ���� �ð��� ������ ���ؿ� �� ��ġ�� ����(�����)

    eventIters[index]->second(); //��ϵ� �̺�Ʈ ����
    eventIters[index]++;
}

// � ������ �����µ� + � ������ �������� ������ �̺�Ʈ
// -> ��ȯ �̺�Ʈ(Ʈ������) : ���ѻ��±��, Ȥ�� ĳ������ �ֱ⸦ �����ϱ� ���� ���� ���� �� �ϳ�
void Robot::EndStandUp()
{
    collider->SetActive(true); // Ȱ��ȭ Ȯ�λ��
    SetState(WALK); //�ȱ� ����
    //->�̷��� �ȴٰ� Ư�� ������ �����Ǹ� (Move �� if��)
    //  ->�� �� ���°� �ٲ� ���� �ִ� : �װ� ���� ������ ��ȭ
}

void Robot::EndHit()
{
    SetState(WALK); //�¾Ұ�, �� �׾���, ����������, �������
}

void Robot::EndDying()
{
    //���� �κ��� �� ���� ����
    transform->SetActive(false);//��Ȱ��ȭ
    collider->SetActive(false);
}

void Robot::SetState(State state)
{
    if (state == curState) return; // �̹� �� ���¶�� ���� ��ȯ �ʿ� ����

    curState = state; //�Ű������� ���� ���� ��ȭ
    instancing->PlayClip(index, (int)state); //�ν��Ͻ� �� �ڱ� Ʈ���������� ���� ���� ����
    eventIters[state] = totalEvent[state].begin(); //�̺�Ʈ �ݺ��ڵ� ��ϵ� �̺�Ʈ ���۽�������

    // ->�̷��� ���¿� ������ �ϳ��� �����صθ�
    // ->�� ĳ���ʹ� ���¸� �ٲ��ָ� �ൿ�� �׶��׶� �˾Ƽ� �ٲ��ش�
}

void Robot::Move()
{
    if (curState == STAND_UP) return; // ������� ���Ŀ��� �������� ����
    if (curState == HIT) return; // �°� ���� ���� �������� ����
    if (curState == DYING) return; //�װ� ���� ���� �������� ����
    if (velocity.Length() < 10) return; //ǥ���� ������ �޶������ ������ �ʿ� ����

    //�׸��� ���⼭ �ӷ� ������ �����ؾ� ������....�� if�� �̹� velocity�� �������
    //���� ������ update���� ��� �Ѵ�

    //���ŵ� velocity�� ���� ����� ����

    if (velocity.Length() < 1000) // ǥ���� �Ÿ��� ����� ����
    {
        speed = 100; //�� ��� ��������
        SetState(RUN);
    }
    else
    {
        speed = 50;
        SetState(WALK);
    }

    //�ӷ� ������ ��������, �⺻ �ӷ¸�ŭ, �ð� �����ŭ
    //->���̵��� �ø��� ���� ����� �Ʒ� �ӷ� ������ ����ȭ�� Ǯ�� �ȴ�
    transform->Pos() += velocity.GetNormalized() * speed * DELTA;
    transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI; // XY��ǥ ���� + ���Ĺ���(����ũ ����)
}

void Robot::UpdateUI()
{
    barPos = transform->Pos() + Vector3(0, 180, 0); // Y�� 180 : �� ũ�⿡ ����
                                                    //(���� �ٲ�� �� ���ڵ� �ٲ� ��)
    
    if (!CAM->ContainPoint(barPos))
    {
        //hpBar->Scale() = {0, 0, 0};
        hpBar->SetActive(false);
        return;
    }

    if (!hpBar->Active()) hpBar->SetActive(true);

    // ����Ʈ�� ���� �Լ��� ȣ���Ͽ� 2D �̹����� ��ġ�� ����
    hpBar->Pos() = CAM->WorldToScreen(barPos); // ��� ��������(=3D��) ��ü�� ����Ʈ(=2D)�� ����
                                               // �̷� ����� ĵ�����̶�� �Ѵ�

    float scale = 100 / velocity.Length(); // �ӽ� ũ�� ������ �����ؼ�, ǥ���� Ʈ�������� �Ÿ��� ����
                                           // UI ũ�Ⱑ �ִ� 100�ȼ����� �����ǰ� �Ѵ�

    scale = Clamp(0.1f, 1.0f, scale); // �ִ� �ּ� ������ �ٽ� �ش� (�ִ� ���� ���� ����)
                                      // ���� ����� ũ�⸦ �츮�� �ʹٸ� �� ��° �Ű������� �� ���� �ָ� �ȴ�

    hpBar->Scale() = { scale, scale, scale }; //����� ũ�� ������ ü�¹ٿ� ����

    hpBar->UpdateWorld(); // ������ ���� ������Ʈ
}
