#pragma once

class RobotManager : public Singleton<RobotManager>
{
private:
    UINT SIZE = 30; // �Ŵ��� �ȿ��� ���� �κ� ���
    float SPAWN_TIME = 2; // �κ��� ����, Ȥ�� ������� �ʿ��� �ð�

public:

    RobotManager();
    ~RobotManager();

    void Update();
    void Render();
    void PostRender();

    void SetTarget(Transform* target); //ǥ�� ����

    bool IsCollision(Ray ray, Vector3& hitPoint); //�浹�� �Ͼ ��� ����

private:
    void Collision(); // ���� �浹 ���� ����
    void Spawn();     // (��)����

private:

    ModelAnimatorInstancing* robotInstancing;
    vector<Robot*> robots;

    Transform* target;

    float time = 0; //����� �ð�

};

