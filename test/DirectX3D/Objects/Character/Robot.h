#pragma once

// �κ� ĳ���� : ���� �ν��Ͻ� ����
//              ������ �ν��Ͻ����� ���� ���� �ְ� ���� �� ȣ���ϰ� ǥ���� �ָ� ������ ��

class Robot
{
private:
    enum State
    {
        STAND_UP,
        WALK,
        RUN,
        HIT,
        DYING
    };

public:
    // Robot(); // �⺻ ����
    Robot(Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
    ~Robot();

    //�� ���
    void Update();
    void Render();
    void PostRender();

    //�׼� : ���±�
    void Hit();

    //�׼� : �����Ǳ�
    void Spawn(Vector3 pos);

    //ǥ�� ����
    void SetTarget(Transform* target);

    Transform* GetTransform() { return transform; }
    CapsuleCollider* GetCollider() { return collider; }

private:
    void SetEvent(int clip, Event event, float timeRatio);
    void ExecuteEvent();

    void EndStandUp();
    void EndHit();
    void EndDying();

    void SetState(State state);

    void Move();
    void UpdateUI(); //ĳ���� UI�� ������ ���� ������Ʈ


private:

    Transform* transform;
    CapsuleCollider* collider;

    // TODO : ��, Ȥ�� ���� �ν��Ͻ�
    //        ���� ��� �����

    // ���� : �ν��Ͻ�
    ModelAnimatorInstancing* instancing;
    ModelAnimatorInstancing::Motion* motion;

    Transform* root;
    Transform* target;

    float speed = 50; //�ӷ� : �⺻ ����
    float maxHP = 100;
    float curHP = 100;

    Vector3 velocity; //�ӷ� : ���� ������

    UINT index; //�κ��� ���� �ε��� (�ν��Ͻ��� �ִٸ� �̰ɷ� ���� ���� ����)
    State curState = STAND_UP;

    //������Ʈ Ȥ�� �����ӿ� ���� �̺�Ʈ ����
    vector<map<float, Event>> totalEvent;
    vector<map<float, Event>::iterator> eventIters;

    ProgressBar* hpBar;
    Vector3 barPos; //ü�¹ٰ� ��ġ�� ��
};

