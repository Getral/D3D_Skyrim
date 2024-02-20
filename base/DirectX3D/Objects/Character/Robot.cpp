#include "Framework.h"
#include "Robot.h"

Robot::Robot(Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
    :transform(transform), instancing(instancing), index(index)
{
    //transform = new Transform(); //모델과 트랜스폼을 밖에서 받을 때는 이 코드 끄기

    //루트 만들기(혹은 받기)
    root = new Transform();

    //충돌체
    collider = new CapsuleCollider(30, 100); // <- 대충 높이 160
    collider->SetParent(root);
    collider->Rot().z = XM_PIDIV2 - 0.2f;
    collider->Pos() = { -15, 10, 0 };
    collider->SetActive(true); //충돌체 보이기 싫을 때는 이 부분 false

    //모델이 밖에서 오는지, 안에서 만들지, 인스턴싱을 쓸지 여부에 따라
    //여기서 불러오기 (여기서는 인스턴싱 기준)

    motion = instancing->GetMotion(index);
    totalEvent.resize(instancing->GetClipSize()); //모델이 가진 동작 숫자만큼 이벤트 리사이징
    eventIters.resize(instancing->GetClipSize());

    //이벤트 세팅
    SetEvent(STAND_UP, bind(&Robot::EndStandUp, this), 0.7f);
    SetEvent(HIT, bind(&Robot::EndHit, this), 0.9f);
    SetEvent(DYING, bind(&Robot::EndDying, this), 0.9f);

    FOR(totalEvent.size())
    {
        eventIters[i] = totalEvent[i].begin(); // 등록되어 있을 이벤트의 시작지점으로 반복자 설정
    }

    //캐릭터 UI 추가
    hpBar = new ProgressBar(
        L"Textures/UI/hp_bar.png",
        L"Textures/UI/hp_bar_BG.png"
    );
    hpBar->SetActive(false);
}

Robot::~Robot()
{
    // 객체 삭제
    delete collider;
    delete root;
    
    // 임시 삭제
    delete transform;

    // 체력바 삭제
    delete hpBar;
}

void Robot::Update()
{
    //활성화 시에만 업데이트
    if (!transform->Active()) return;

    velocity = target->GlobalPos() - transform->GlobalPos(); // 속력기준 : 표적과 자신의 거리

    ExecuteEvent(); // 이벤트가 터져야 하면 수행하기
    Move(); //움직이기
    UpdateUI(); //UI 업데이트

    root->SetWorld(instancing->GetTransformByNode(index, 3));
    collider->UpdateWorld(); //충돌체 업데이트

}

void Robot::Render()
{
    //모델로서의 렌더는 이 클래스 소관 아님
    //이 클래스는 현재 충돌체만 책임지는 중
    collider->Render();
}

void Robot::PostRender()
{
    hpBar->Render();
}

void Robot::Hit()
{
    //체력에 -
    curHP -= 20;
    hpBar->SetAmount(curHP / maxHP); // 체력 비율에 따라 체력바 설정

    // 체력이 완전히 바닥나면
    if (curHP <= 0)
    {
        SetState(DYING); //죽고
        return;//이 함수 종료
    }

    // 아직 안 죽었으면 산 로봇답게 맞는 동작 수행
    curState = HIT;
    instancing->PlayClip(index, HIT);
    eventIters[HIT] = totalEvent[HIT].begin();
}

void Robot::Spawn(Vector3 pos)
{
    transform->SetActive(true); //비활성화였다면 활성화 시작
    collider->SetActive(true);

    SetState(WALK); // 가볍게 산책

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
    if (totalEvent[clip].count(timeRatio) > 0) return; // 선행 예약된 이벤트가 있으면 종료
    totalEvent[clip][timeRatio] = event;
}

void Robot::ExecuteEvent()
{
    int index = curState; //현재 상태 받아오기
    if (totalEvent[index].empty()) return;
    if (eventIters[index] == totalEvent[index].end()) return;

    float ratio = motion->runningTime / motion->duration; //진행된 시간 나누기 전체 진행시간

    if (eventIters[index]->first > ratio) return; // 진행 시간이 정해진 기준에 못 미치면 종료(재시작)

    eventIters[index]->second(); //등록된 이벤트 수행
    eventIters[index]++;
}

// 어떤 동작이 끝났는데 + 어떤 조건이 갖춰지면 수행할 이벤트
// -> 전환 이벤트(트랜지션) : 유한상태기계, 혹은 캐릭터의 주기를 관리하기 위한 좋은 수단 중 하나
void Robot::EndStandUp()
{
    collider->SetActive(true); // 활성화 확인사살
    SetState(WALK); //걷기 시작
    //->이렇게 걷다가 특정 조건이 만족되면 (Move 중 if문)
    //  ->그 때 상태가 바뀔 수도 있다 : 그것 또한 상태의 변화
}

void Robot::EndHit()
{
    SetState(WALK); //맞았고, 안 죽었고, 움찔했으니, 원래대로
}

void Robot::EndDying()
{
    //죽은 로봇은 할 일이 없다
    transform->SetActive(false);//비활성화
    collider->SetActive(false);
}

void Robot::SetState(State state)
{
    if (state == curState) return; // 이미 그 상태라면 굳이 변환 필요 없음

    curState = state; //매개변수에 따라 상태 변화
    instancing->PlayClip(index, (int)state); //인스턴싱 내 자기 트랜스폼에서 동작 수행 시작
    eventIters[state] = totalEvent[state].begin(); //이벤트 반복자도 등록된 이벤트 시작시점으로

    // ->이렇게 상태와 동작을 하나로 통합해두면
    // ->이 캐릭터는 상태만 바꿔주면 행동은 그때그때 알아서 바꿔준다
}

void Robot::Move()
{
    if (curState == STAND_UP) return; // 만들어진 직후에는 움직이지 않음
    if (curState == HIT) return; // 맞고 있을 때는 움직이지 않음
    if (curState == DYING) return; //죽고 있을 때는 움직이지 않음
    if (velocity.Length() < 10) return; //표적과 완전히 달라붙으면 움직일 필요 없음

    //그리고 여기서 속력 기준을 갱신해야 맞지만....위 if에 이미 velocity를 써버려서
    //변수 갱신은 update에서 대신 한다

    //갱신된 velocity에 따른 계산을 시작

    if (velocity.Length() < 1000) // 표적과 거리가 가까울 때는
    {
        speed = 100; //두 배로 빨라진다
        SetState(RUN);
    }
    else
    {
        speed = 50;
        SetState(WALK);
    }

    //속력 기준을 방향으로, 기본 속력만큼, 시간 경과만큼
    //->난이도를 올리고 싶은 사람은 아래 속력 기준의 정규화를 풀면 된다
    transform->Pos() += velocity.GetNormalized() * speed * DELTA;
    transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI; // XY좌표 방향 + 전후반전(문워크 방지)
}

void Robot::UpdateUI()
{
    barPos = transform->Pos() + Vector3(0, 180, 0); // Y축 180 : 모델 크기에 맞춤
                                                    //(모델이 바뀌면 이 숫자도 바꿀 것)
    
    if (!CAM->ContainPoint(barPos))
    {
        //hpBar->Scale() = {0, 0, 0};
        hpBar->SetActive(false);
        return;
    }

    if (!hpBar->Active()) hpBar->SetActive(true);

    // 뷰포트에 대한 함수를 호출하여 2D 이미지의 위치를 설정
    hpBar->Pos() = CAM->WorldToScreen(barPos); // 행렬 공간상의(=3D의) 물체를 뷰포트(=2D)에 투사
                                               // 이런 출력을 캔버싱이라고 한다

    float scale = 100 / velocity.Length(); // 임시 크기 변수를 지정해서, 표적과 트랜스폼의 거리에 따라
                                           // UI 크기가 최대 100픽셀까지 조절되게 한다

    scale = Clamp(0.1f, 1.0f, scale); // 최대 최소 범위를 다시 준다 (최대 범위 강제 가능)
                                      // 최초 계산의 크기를 살리고 싶다면 두 번째 매개변수를 더 많이 주면 된다

    hpBar->Scale() = { scale, scale, scale }; //도출된 크기 변수를 체력바에 적용

    hpBar->UpdateWorld(); // 조정된 정점 업데이트
}
