#pragma once
class Kunai
{
    //투사체 하나를 총괄하는 클래스

private:
    //열람시 필요한 주요 데이터 (설정값)
    float LIFE_SPAN = 5; // life span = 생애 주기, 혹은 세대 생멸 기간
                         // 프로그래밍에서는 임시로 생성된 객체가 자동 삭제
                         // 혹은 비활성화하기까지 걸리는 시간을 말한다

public:
    //호출용 함수
    Kunai(Transform* transform); //인스턴싱을 전제한 트랜스폼 매개 생성
    ~Kunai();

    void Update();
    void Render();

    void Throw(Vector3 pos, Vector3 dir);

    SphereCollider* GetCollider() { return collider; }
    Transform* GetTransform() { return transform; }
private:
    //멤버 함수

private:
    //멤버 변수

    Transform* transform;
    SphereCollider* collider;

    float speed = 1000;
    float time = 0; //생성된 시간

    Vector3 direction;
};

