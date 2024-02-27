#include "Framework.h"

Kunai::Kunai(Transform* transform) : transform(transform)
{
    transform->Scale() = { 2, 2, 2 }; // 크기 기본값은 1
                                      // 나중에 크기가 바뀌어야 하면 와서 수정하게

    collider = new SphereCollider();
    collider->SetParent(transform);

    collider->Scale() = { 2, 2, 2 }; //크기 기본값은 1.0
    collider->Pos() = {};            //위치 기본값 : 부모 위치
}

Kunai::~Kunai()
{
    delete collider;
}

void Kunai::Update()
{
    //비활성화 중에는 안 움직임
    if (!transform->Active()) return;

    time += DELTA; // 시간 경과에 따라 변수에 누적

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
    //활성화
    transform->SetActive(true);

    transform->Pos() = pos;
    direction = dir;

    //방향에 맞게 모델(=트랜스폼) 회전 적용
    transform->Rot().y = atan2(dir.x, dir.z) - XM_PIDIV2; //방향 적용 + 모델 정면에 따른 보정
                                                          //쿠나이 모델은 90도 돌아가 있었음
    //transform->Rot().y = atan2(dir.x, dir.z) - XMConvertToRadians(90);
    //                                           ↑ 각도를 호도로 바꿔주는 함수

    time = 0; //경과시간 리셋
}
