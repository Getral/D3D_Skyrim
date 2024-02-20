#pragma once

class RobotManager : public Singleton<RobotManager>
{
private:
    UINT SIZE = 30; // 매니저 안에서 굴릴 로봇 대수
    float SPAWN_TIME = 2; // 로봇의 생성, 혹은 재생성에 필요한 시간

public:

    RobotManager();
    ~RobotManager();

    void Update();
    void Render();
    void PostRender();

    void SetTarget(Transform* target); //표적 설정

    bool IsCollision(Ray ray, Vector3& hitPoint); //충돌이 일어난 경우 판정

private:
    void Collision(); // 세부 충돌 판정 진행
    void Spawn();     // (재)생성

private:

    ModelAnimatorInstancing* robotInstancing;
    vector<Robot*> robots;

    Transform* target;

    float time = 0; //경과된 시간

};

