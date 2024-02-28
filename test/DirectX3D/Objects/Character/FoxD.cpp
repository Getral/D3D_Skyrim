#include "Framework.h"

FoxD::FoxD() : ModelAnimator("Fox")
{
    ReadClip("Idle");
    ReadClip("Run", 0, "FoxTransform"); // 모델 파일에 있었던 뼈대를 수동으로 설정

    PlayClip(curState); // 가만히 있기부터 재생
    Pos() = { 5, 0, 5 };
    Scale() *= 0.5f;
}

FoxD::~FoxD()
{
    //객체를 밖에서 받을 거라 굳이 여기서 지울 필요가?
}

void FoxD::Update()
{
    Control();
    Move();
    Rotate();

    ModelAnimator::Update();

    //터레인, 데익스트라 : 밖에서 받을 거라서 굳이 여기서 업데이트할 필요가?
}

void FoxD::Render()
{
    ModelAnimator::Render();
}

void FoxD::Control()
{
    // 입력을 받아서 여우 움직이기

    if (KEY_DOWN('Q')) //Q를 누르면
    {
        //dijkstra->CallCreateNode(terrain->Picking()); //마우스 커서가 있던 곳에 새 노드 설치
        Vector3 pickPos;
        if (terrain->ComputePicking(pickPos))
            dijkstra->CallCreateNode(pickPos);
    }

    if (KEY_DOWN('E')) //E를 누르면
    {
        dijkstra->CallSelectNode(); //마우스 커서가 있던 곳의 노드를 선택 시작
    }

    if (KEY_UP('E')) //E에서 손을 떼면
    {
        dijkstra->CallLinkNode(); //선택된 노드가 있었고 지금 마우스 커서가 다은 노드에 닿았다면,
                                  // 두 노드를 이어서 길인 것처럼 인식
    }

    if (KEY_DOWN(VK_SPACE)) // 스페이스바를 누르면
    {
        SetPath(); // 경로를 설정
    }

}

void FoxD::Move()
{
    if (path.empty()) //경로 벡터가 비어 있는 경우
    {
        SetState(IDLE); //가만히 있기
        return; // 움직이지 않기
    }

    // 이 다음까지 왔다 = 경로에 가야 할 곳이 찍혀 있다

    SetState(RUN); //움직이기 + 달리는 동작 실행

    //벡터로 들어온 경로를 하나씩 찾아가면서 움직이기

    Vector3 dest = path.back(); // 나에게 이르는 경로의 마지막
                                // = 목적지로 가기 위해 가는 최초의 목적지
                                // 경로가 왜 거꾸로냐? -> 길찾기 알고리즘에서
                                // 경로를 위한 데이터 작성은 처음부터,
                                // 검산과 경로 추가는 뒤에서부터 했기 때문

    Vector3 direction = dest - GlobalPos(); //내 위치에서 목적지로 가기 = 방향

    direction.y = 0; // 직선 위주인 데익스트라 알고리즘 특징을 고려해서 높이를 0으로
                     // 지형 높이를 반영할 경우, 지형에서 GetHeight 같은 수단으로 높이 받아오기 추천

    if (direction.Length() < 0.5f) //대충 다 왔으면 (업데이트 호출 과정에서 계속 갱신)
    {
        path.pop_back(); //다 온 목적지를 벡터에서 빼기
    }

    //목적지로 가기 위한 실제 이동
    velocity = direction.GetNormalized(); //속력기준 (방향의 정규화)
    Pos() += velocity * moveSpeed * DELTA; //속력기준 * 실제 속력 * 시간경과...를 누적

}

void FoxD::Rotate()
{
    if (curState == IDLE) return; // 달리고 있는 중이 아니면 회전할 필요 없음

    Vector3 forward = Forward(); //모델 기준으로 앞 따오기
    Vector3 cross = Cross(forward, velocity); //방향차이에서 나온 법선

    if (cross.y < 0) // 법선이 밑이다 = 내가 목적 방향보다 오른쪽을 보는 중이다
    {
        Rot().y += rotSpeed * DELTA;
    }
    else if (cross.y > 0) //반대의 경우
    {
        Rot().y -= rotSpeed * DELTA;
    }
}

void FoxD::SetState(State state)
{
    if (state == curState) return;
    curState = state;
    PlayClip(state);
}

void FoxD::SetPath()
{
    int start = dijkstra->FindCloseNode(GlobalPos()); // 여우에서 가장 가까운 노드를 출발점으로
    int end = dijkstra->FindCloseNode(terrain->Picking()); // 마우스 커서 근처를 종점으로

    //위에서 만든 출발점과 종점을 잇는 경로를 길찾기 알고리즘에서 도출
    path = dijkstra->GetPath(start, end); // 경로만 내면 나머지는 Move 함수가 알아서 진행해줄 것
}
