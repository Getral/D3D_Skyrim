#include "Framework.h"
#include "AStar.h"

AStar::AStar(UINT width, UINT height)
    : width(width), height(height)
{
    heap = new Heap();

    //SetNode(); //기본 노드 세팅이 있다면 여기서 나중에 호출
                 //지금은 지형에 대응시킬 거라서 생성자에서는 노드 설치 안 함
}

AStar::~AStar()
{
    for (Node* node : nodes)
        delete node;
    delete heap;
}

void AStar::Update()
{
    if (KEY_PRESS(VK_LSHIFT)) // 시프트 키를 누른 상태라면
    {
        if (KEY_DOWN(VK_RBUTTON)) // 우클릭
        {
            Ray ray = CAM->ScreenPointToRay(mousePos);

            for (Node* node : nodes)
            {
                if (node->IsRayCollision(ray, nullptr))
                {
                    node->SetState(Node::OBSTACLE); // 장애물로 설정
                    AddObstacle(node); //장애물 목록에도 등록하기
                    break; // 반복종료
                }
            }
        }
    }
}

void AStar::Render()
{
    for (Node* node : nodes)
        node->Render(); //노드에 충돌체 설정이 켜져 있으면 렌더
}

void AStar::SetNode(Terrain* terrain)
{
    // 지형의 크기 (노드를 설치할 규모)
    //Vector2 mapSize = terrain->GetMaterial()->GetDiffuseMap()->GetSize(); //지도의 크기
    Vector2 mapSize = terrain->GetSize(); //지형 클래스에 직접 지정된 가로세로 받기

    // 노드 배치 간격 구하기
    interval.x = mapSize.x / width;
    interval.y = mapSize.y / height;

    // 노드 생성 자리를 벡터에서 예약
    nodes.reserve((width + 1) * (height + 1)); //벡터는 0부터 만드니까

    for (UINT z = 0; z <= height; ++z)
    {
        for (UINT x = 0; x <= width; ++x)
        {
            Vector3 pos = Vector3(x * interval.x, 0, z * interval.y);
            //pos.y = 0; // 기본값
            pos.y = terrain->GetHeight(pos); // A*는 직선이동이 아니라 노드들을 경유하기 때문에
                                             // 지형이 가지는 높이 변화에도 대응 가능

            //노드 추가
            nodes.push_back(new Node(pos, nodes.size())); //위치와, 벡터의 현재 마지막 순번을 차례로 부여
            nodes.back()->Scale() = { interval.x, 50, interval.y }; //간격을 적용하고, 위아래로 길게
            nodes.back()->UpdateWorld();

            // 높이에 변화가 있을 경우, 이 밑에 코드를 추가하면 된다
            // 샘플 시나리오 : 높은 곳은 곧 장애물이다
            if (pos.y > 0)
            {
                nodes.back()->SetState(Node::OBSTACLE); //장애물로 설정하고
                AddObstacle(nodes.back()); //장애물 추가 함수 호출
            }
        }
    }
    // 여기까지 오면 가로세로 번갈아 가면서 노드 설치가 끝난다

    SetEdge(); // 인접지 설정만 해주면 여기서 할 작업은 끝
}

int AStar::FindCloseNode(Vector3 pos)
{
    float minDist = FLT_MAX;
    int result = -1;

    for (UINT i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]->state == Node::OBSTACLE)
            continue; //장애물이거나, (샘플) 높이가 0보다 크면 취급 안 한다

        float distance = Distance(pos, nodes[i]->GlobalPos());
        if (distance < minDist) //최소거리가 갱신될 때마다
        {
            minDist = distance; //갱신결과 반영
            result = i; //결과에 인덱스 기록
        }
    }
    return result;
}

int AStar::FindRandomPos(Vector3 pos, float range)
{
    // 지정된 좌표에서 가까운 범위 내 랜덤 좌표를 찾아내기
    vector<Node*> findNodes;

    for (Node* node : nodes)
    {
        float distance = Distance(pos, node->GlobalPos());
        if (distance < range) findNodes.push_back(node); // 범위 내 노드 벡터에 추가하기
    }
    //여기까지 오면 범위 안의 모든 노드를 벡터로 받는다
    //여기서 아무거나 랜덤으로 하나 뽑기

    Node* findNode = findNodes[Random(0, findNodes.size())];

    return findNode->index; // 랜덤으로 나온 노드의 인덱스
}

void AStar::GetPath(IN int start, IN int end, OUT vector<Vector3>& path)
{
    // 노드 입력을 받지 못했을 때 그대로 종료
    if (start == -1 || end == -1) return;

    //종료되지 않았다면 = 두 노드, 출발지와 목적지를 잘 받은 것

    //->경로를 찾아내기 전에 먼저 "앞에 혹시 같은 알고리즘을 실행한 적이 있으면"
    //  해당 결과를 초기화하는 것부터 시작

    Reset(); // 알고리즘 리셋
    path.clear(); //매개변수로 받은 (결과가 저장되어야 할) 벡터도 내용을 모두 비운다

    //경로 계산 중에 사용할 지형 데이터도 준비하면서 초기화
    float _g = 0; //지형 데이터
    float _h = GetDiagonalManhattanDistance(start, end); // 휴리스틱
                                // 여기서의 휴리스틱(판단기준) = 격자 좌표 공간에서
                                // 목적지로 가는 직선 최단 경로 (가로, 세로, 격자 대각선 구성)

    //시작지점의 노드 데이터 설정
    nodes[start]->f = _g + _h; //최종비용 = 지형 + 휴리스틱
    nodes[start]->g = _g;
    nodes[start]->h = _h;
    nodes[start]->via = start; // -1(없음) 혹은 자기 자신으로
    nodes[start]->state = Node::OPEN; // 이 노드는 경로 연산에 들어갈 준비가 됐다

    //시작 노드를 힙에 넣어준다
    heap->Insert(nodes[start]); // 노드 벡터의 "출발지"번째 요소를 힙에 추가

    while (nodes[end]->state != Node::CLOSED)
            // 목적지의 상태가 연산종료(닫힘)이 될 때까지 경로 탐색
    {
        if (heap->Empty()) return; // 반복문 수행 중에(혹은 시작시) 힙이 비어 있으면 그대로 종료
                                   // 

        int curIndex = GetMinNode(); //주변에서 최소비용 노드 선택

        Extend(curIndex, end); //탐색 확장 (지금 찾은 최소비용 노드에서, 목적지를 향해)
        nodes[curIndex]->state = Node::CLOSED; // 반복문 중에 경로탐색을 수행한
                                               // 이 노드를 탐색 종료 상태로
    }

    // 여기까지 오면 -> 목적지까지 간 후 경로탐색이 끝난 상태이므로
    int curIndex = end; //인덱스를 목적지의 인덱스로

    // 다시 뒤에서부터 노드들을 찾아가면서 최단경로에 들어가는 노드를 경로에 포함
    while (curIndex != start) // 인덱스가 출발지로 돌아올 때까지
    {
        nodes[curIndex]->state = Node::USING; // 경로로 사용됨
        path.push_back(nodes[curIndex]->GlobalPos()); // 노드들의 위치를 경로 벡터에 추가
        curIndex = nodes[curIndex]->via; //선택했던 노드의 경유지로 넘어가서 경로 추가 계속
                                         // -> 경로 탐색 과정에서 경유지 설정까지 한다는 뜻
    }

    // 아래 코드는 원형 알고리즘(데익스트라)의 잔재이지만 쓰진 않는다
    // 이유 1. 노드 내 계산이라서
    //      2. 현재 이 알고리즘을 쓸 캐릭터가 3D에 있어서
    //         =경로가 복잡하면 몰라도, 아주 간단할 때는 굳이 "경로"를 계산할 필요가 없다
    //          (Pos() 주고 직선으로 가게 시키면 그만)
    // path.push_back(nodes[start]->GlobalPos());
}

void AStar::MakeDirectionPath(IN Vector3 start, IN Vector3 end, OUT vector<Vector3>& path)
{
    // 방향 경로 지정
    // 이 함수가 진짜 하는 일은 따로 있지만, 간접적으로 추가 정보를 하나 더 얻을 수 있어서 이렇게 명명

    // 도출된 경로를 따라 가거나, 도출 중인 경로에서 목적지까지 직선 거리를 내었다고 가정할 때
    // 해당 방향에서 발생한 "장애물로 인한 이동 불가능 경로"의 거리를 내기 위해 작성
    // -> 이 계산을 통해서.... 1. 장애물 경로
    //                        2. (1에서 간접도출) 어디서 어디까지가 장애물을 안 보고 가는가
    // ... 이렇게 둘 중 한 가지 정보를 얻을 수 있다

    //자를 인덱스 (개수) 준비
    int cutNodeNum = 0;

    Ray ray;
    ray.pos = start; //광원을 출발지로 일단 지정

    FOR(path.size()) //경로를 검사해서
    {
        if (!IsCollisionObstacle(start, path[i])) // 장애물을 해당 경로의 i번째까지 안 봤다면
        {
            cutNodeNum = path.size() - i - 1;
            break;

            //-> 장애물이 없으면 자를 게 없음
            //-> 장애물이 처음부터 있었으면 다 자름
        }
    }

    //위 반복문에서 찾아낸 cutNodeNum을 이용해서 장애물에 해당되는 노드를 지워버린다
    // 만약 위 조건문이 참을 가리는 거였으면 장애물을 안 만난다는 노드를 자른다

    FOR(cutNodeNum) //등록된, 잘라야 할 인덱스의 개수만큼
    {
        path.pop_back(); // 경로를 자른다 (뒤에서부터)
    }

    //같은 계산을 끝나는 지점에서도 다시 진행한다
    cutNodeNum = 0;
    ray.pos = end; // 광원은 이제 종점

    FOR(path.size()) // 여기까지 계산에서 줄어들었을지도 모르는 경로 개수만큼 다시 반복
    {
        if (!IsCollisionObstacle(end, path[path.size() - i - 1])) //벡터의 뒤에서부터 검사
        {
            cutNodeNum = path.size() - i - 1;
            break;
        }
    }

    FOR(cutNodeNum)
    {
        path.erase(path.begin()); // 앞에서부터 또 경로 지우기
    }

    // 여기까지 오면
    // 위 반복문 중 조건문의 조건이 참(장애물에 부딪침)이면 -> 장애물에 안 부딪친 노드를 삭제
    // 조건이 거짓이면 -> 장애물에 부딪친 만큼의 노드를 삭제
    
    // 어느 쪽이든 (장애물의 경로든, 장애물을 안 만난 경로든) 그 결과를
    // 이후 최초의 경로와 대조하면 두 가지 정보를 모두 얻을 수 있다

    // -> 다른 경로 연산에서 우선적으로 쓸 결과가 무엇이냐에 따라 조건 설정을 선택
}

bool AStar::IsCollisionObstacle(Vector3 start, Vector3 end)
{
    // 장애물 판정을 충돌로 진행

    //광선준비
    Ray ray(start, (end - start).GetNormalized());
    // 광원은 시작 지점, 방향은 시작에서 끝으로 가는 방향

    float distance = Distance(start, end); //시작에서 끝까지의 거리

    Contact contact; //접점 정보

    for (Collider* obstacle : obstacles) // 등록된 장애물을 처음부터 검사해서
    {
        if (obstacle->IsRayCollision(ray, &contact)) // 광선이 장애물에 부딪쳤다면
        {
            //접점과 광선의 거리를 또 내어보고
            if (contact.distance < distance) // 광원과 접점까지의 거리가, 두 위치 사이 거리보다 짧으면
            {
                return true; // 직선으로 가는 도중에 장애물을 만났다는 이야기가 된다
            }
        }
    }
    // 반복문 끝날 때까지 그런 충돌이 없었으면
    return false; // 아무 일도.... 없었다!
}

void AStar::AddObstacle(Collider* collider)
{
    obstacles.push_back(collider);
}

void AStar::SetEdge()
{
    //지역 내에서 쓰기 위한 "가로" 변수의 의미 재정의
    UINT width = this->width + 1;

    for (UINT i = 0; i < nodes.size(); ++i)
    {
        if (i % width != width - 1) // 오른쪽 끝이 아니라면
        {
            nodes[i]->AddEdge(nodes[i + 1]); // 자기 오른쪽 노드와 인접지 정보 교환
            nodes[i + 1]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - width) //맨 아래가 아니라면
        {
            nodes[i]->AddEdge(nodes[i + width]); // 자기 아래쪽 노드와 인접지 교환
            nodes[i + width]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - width && i % width != width - 1) //맨 아래도 아닌데 오른쪽 끝도 아니라면
        {
            nodes[i]->AddEdge(nodes[i + width + 1]); //자기 대각선 오른쪽 아래와 인접지 교환
            nodes[i + width + 1]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - width && i % width != 0) //맨 아래가 아니고, 왼쪽 끝이 아니다
        {
            nodes[i]->AddEdge(nodes[i + width - 1]); //자기 대각선 왼쪽 아래와 인접지 교환
            nodes[i + width - 1]->AddEdge(nodes[i]);
        }
    }
}

int AStar::GetMinNode()
{
    return heap->DeleteRoot()->index;

    //최소 비용 노드를 얻어야 하는데.....
    //힙에서 이미 벡터를 최소 비용 순으로 정렬을 항상 하고 있었다
    // -> 그러므로 힙 속 벡터의 0번 인덱스를 받으면 되지 않을까?

    // -> 그래서 힙의 루트(0번 인덱스)를 받아서 해당 노드의 인덱스를 제시
}

void AStar::Extend(int center, int end)
{
    // 최소 이동비용이 예상되는 인접 노드로 넘어가서, 다시 여기서 다음 경로를 찾기

    for (Node::Edge* edge : nodes[center]->edges) //매개변수로 받은 센터의 인접지 검사
    {
        int index = edge->index;

        if (nodes[index]->state == Node::CLOSED) continue; // 노드가 계산이 끝난 상태면 제치기
        if (nodes[index]->state == Node::OBSTACLE) continue; //장애물 그 자체여도 제치기

        //현재 검색 중인 노드의 지형과 휴리스틱 다시 계산
        // -> 이 과정에서 각 노드의 G와 H 계산 가능

        float _g = nodes[center]->g + edge->cost;
        float _h = GetDiagonalManhattanDistance(index, end);

        float _f = _g + _h;

        if (nodes[index]->state == Node::OPEN) // 노드가 현재 연산 중이라면
        {
            if (_f < nodes[index]->f) // 이동 비용을 비교하고 최소기록을 갱신하면
            {
                //해당 노드의 데이터를 반영한다
                nodes[index]->g = _g; //지형 갱신
                nodes[index]->f = _f; //최종비용 갱신
                nodes[index]->via = center; //이 노드의 경유지를 지금 여기로
            }
            //이렇게 반복문을 진행하면 센터에서 각 "최소비용 후보지"로 가는 곳을 다음 갈 곳으로 잠정 가능
        }
        else if (nodes[index]->state == Node::NONE) // 연산에 쓰인 적도 없었다면
        {
            //노드를 지금 열어서 연산에 추가
            nodes[index]->g = _g;
            nodes[index]->h = _h;
            nodes[index]->f = _f;
            nodes[index]->via = center;
            nodes[index]->state = Node::OPEN;

            //힙에 바로 추가해서 이동비용에 따른 정렬까지 진행
            heap->Insert(nodes[index]);

            //그럼 이 노드도 트리 안에서 정렬이 끝나, 최소비용인지 아닌지, 트리 내 어디로 갈 건지
            // 정렬로 결과를 낼 수 있다
        }
    }

    // 여기까지 진행되면 센터에서 목적지로 가는 최소비용 노드의 후보지가 나오게 된다
    // -> 다음에 해당 노드로 진행 가능 (확장 진행)
}

void AStar::Reset()
{
    // 진행했던 최단경로 도출 연산 결과를 지우기

    for (Node* node : nodes)
    {
        if (node->state != Node::OBSTACLE) //장애물은 계속 장애물이고, 그런 경우가 아니라면
        {
            node->state = Node::NONE; // 계산 이전 상태로 되돌리기
        }
    }
    heap->Clear(); // 힙 벡터도 모두 지우기
}

float AStar::GetManhattanDistance(int start, int end)
{
    //받은 인덱스에 대응하는 노드의 위치
    Vector3 startPos = nodes[start]->GlobalPos();
    Vector3 endPos = nodes[end]->GlobalPos();

    //위에서 나온 두 위치의 관계를 "거리"라는 이름으로 구한다
    Vector3 distance = endPos - startPos; //시작에서 끝으로 가는 벡터 그 자체

    return abs(distance.x) + abs(distance.z);
            //경로 벡터의 x값과 z값을 그대로 더해서 직각 거리를 만든다
}

float AStar::GetDiagonalManhattanDistance(int start, int end)
{
    //받은 인덱스에 대응하는 노드의 위치
    Vector3 startPos = nodes[start]->GlobalPos();
    Vector3 endPos = nodes[end]->GlobalPos();

    //위에서 나온 두 위치의 관계를 "거리"라는 이름으로 구한다
    Vector3 distance = endPos - startPos; //시작에서 끝으로 가는 벡터 그 자체

    float x = abs(distance.x); // 경로벡터의 x 좌표 (직각 가로 길이)
    float z = abs(distance.z); // 경로벡터의 z 좌표 (직각 세로 길이)

    // 더 긴 길이가 어느 쪽인지 구하기 (같으면 같은 대로 역시 결과가 나올 것)
    float maxDist = max(x, z); // 더 긴 좌표 길이
    float minDist = min(x, z); // 더 짧은 좌표 길이

    return (maxDist - minDist) + sqrt(minDist * minDist * 2);
        //대각선을 낼 수 없는 부분의 직선 거리와 대각선 길이를 합친다
}
