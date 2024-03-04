#include "Framework.h"

RobotManager::RobotManager()
{
    //공통모델 생성
    robotInstancing = new ModelAnimatorInstancing("Robot");
    robotInstancing->ReadClip("StandUp"); //로봇의 상태와 동작 인덱스 순서 맞추기
    robotInstancing->ReadClip("Walk");
    robotInstancing->ReadClip("Run");
    robotInstancing->ReadClip("Hit");
    robotInstancing->ReadClip("Dying");

    //인스턴싱 내부에서 새 트랜스폼을 만든 후,
    //로봇을 만들어 트랜스폼을 일치시키기
    FOR(SIZE)
    {
        Transform* transform = robotInstancing->Add(); // 트랜스폼을 추가하고, 반환까지 받기
        transform->SetActive(false); //받아온 트랜스폼(=만들어진 새 로봇)의 활성화 설정
        Robot* robot = new Robot(transform, robotInstancing, i);
                                        //로봇 데이터를 만들어 트랜스폼, 모델, 인덱스 주기
        robots.push_back(robot); //로봇의 데이터를 벡터에 추가
    }

    //로봇 모델(공통), 트랜스폼(SIZE만큼) 트랜스폼 위치에서 연산할 진짜 로봇 데이터(SIZE만큼)
    //->들이 모두 준비된다
}

RobotManager::~RobotManager()
{
    delete robotInstancing;

    for (Robot* robot : robots)
        delete robot;
}

void RobotManager::Update()
{
    //내부용 함수 돌려보기

    // 1. 충돌 판정 진행
    Collision();

    // 2. (리)스폰 진행
    time += DELTA; //경과시간 누적

    if (time >= SPAWN_TIME) //경과 시간이 생성간격에 도달하면
    {
        time -= SPAWN_TIME;
        Spawn(); //생성(스폰)
    }

    //내부 함수 끝 -> 모델 업데이트
    robotInstancing->Update();

    for (Robot* robot : robots)
        robot->Update(); //로봇도 업데이트
}

void RobotManager::Render()
{
    robotInstancing->Render();
    for (Robot* robot : robots) robot->Render();
}

void RobotManager::PostRender()
{
    for (Robot* robot : robots) robot->PostRender(); //캐릭터에 UI가 있을 경우 대비
}

void RobotManager::SetTarget(Transform* target)
{
    this->target = target; // 매니저 입장에서 기록할 표적 : 일괄설정 등이 필요할 때 쓸 것
    //각 로봇 입장에서의 표적도 지금 설정
    for (Robot* robot : robots)
        robot->SetTarget(target);
}

bool RobotManager::IsCollision(Ray ray, Vector3& hitPoint)
{
    //외부 호출용

    Contact contact;
    float minDistance = FLT_MAX;

    for (Robot* robot : robots)
    {
        //외부에서 온 광선과 로봇이 충돌하면...
        if (robot->GetCollider()->IsRayCollision(ray, &contact))
        {
            if (contact.distance < minDistance) //로봇마다 접점 정보 모두 갱신
            {
                minDistance = contact.distance; // 갱신정보 계속 반영
                hitPoint = contact.hitPoint;
            }
        }
    }

    //위 반복문에서 찾은 거리가 최초의 초기값보다 의미 있게 적은가 판별
    return minDistance != FLT_MAX; //이 숫자보다 소수가 커질 수는 없으니까,
                                   //다르다 = 로봇 중에 누군가는 어딘가에 부딪쳤다

    // 위 함수를 수행하면 일단 매니저 내에서 충돌은 감지된 것
    // -> 누가 맞았는지를 추가로 알아내서 해당 robot에 필요한 함수가 있다면 추가 수행을 시켜주면 된다
    return false;
}

void RobotManager::Collision()
{
    //내부 판정용

    for (Robot* robot : robots)
    {
        //여기서 각 robot 개체와 외부 물체 충돌 여부를 판정
        //판정이 되면 해당 robot에 추가 함수를 수행하면 된다

        //샘플 시나리오 : 쿠나이에 맞으면 휘청휘청하게
        if (KunaiManager::Get()->IsCollision(robot->GetCollider()))
        {
            robot->Hit();
            return; // 어차피 여기서 종료해도 업데이트로 또 찾아줄 테니까
        }
    }
}

void RobotManager::Spawn()
{
    //랜덤 방향 만들기
    Vector3 dir;
    dir.x = Random(-1.0f, 1.0f);
    dir.z = Random(-1.0f, 1.0f);

    //생성거리 계수와 함께 표적의 주위에서 생성을 한다
    Vector3 randomPos = target->Pos() + (dir.GetNormalized() * 2000);

    // 위에서 정해진 랜덤 장소에서 로봇 하나 생성 (선착순)
    for (Robot* robot : robots)
    {
        if (!robot->GetTransform()->Active()) // 로봇을 조회 중인데 비활성화 중인 개체가 있으면
        {
            robot->Spawn(randomPos); // 개별 로봇 호출
            break; //반복문(생성 절차) 종료
        }
    }
}
