#include "Framework.h"
#include "Dijkstra.h"

Dijkstra::Dijkstra()
{
    nodes.clear();
}

Dijkstra::~Dijkstra()
{
    for (DNode* node : nodes)
        delete node;
}

void Dijkstra::Update()
{
    // 경로는 시작과 끝이 주어졌을 때만 구하면 돼서, 이 클래스는 업데이트가 딱히 필요없다
    // 그런데 업데이트가 있는 이유 : 나중에 노드에 추가로 시각적 효과가 필요할지도 몰라서
}

void Dijkstra::Render()
{
    for (DNode* node : nodes)
        node->Render(); // 순전히 충돌체 렌더를 위한 함수 (지금은)
}

int Dijkstra::FindCloseNode(Vector3 pos)
{
    //주어진 위치에서 가장 가까운 곳 (...의 인덱스)

    //시작 데이터
    float minDist = FLT_MAX; //측정된 최단 거리
    int result = -1; //결과 없음

    // 노드 찾기

    FOR(nodes.size())
    {
        float distance = Distance(pos, nodes[i]->pos); // 각 노드와 매개변수로 받은 곳의 거리

        if (distance < minDist) // 최단거리가 갱신되면
        {
            minDist = distance; //기록 갱신 후
            result = i; //결과를 반영 (i번째)
        }
    }

    // 여기까지 오면 결과는 둘 중 하나
    // 찍은 곳에서 가장 거리가 가까운 노드가 나왔거나, (i >= 0)
    // 애초에 그런 노드는 이 세계에 없거나 (-1)

    // 어느 쪽이든 해당 결과를 컴퓨터에 반환만 하면 된다 (정수니까)

    return result;
}

int Dijkstra::FindMinCostNode()
{
    float minCost = FLT_MAX;
    int result = -1;

    FOR(nodes.size())
    {
        if (nodes[i]->isClosed) continue; //노드가 연산 대상이 아니면 제치기

        if (nodes[i]->cost < minCost) //노드가 아직 열려 있는데 (연산대상인데)
            // 비용이 최소비용을 갱신한다면
        {
            minCost = nodes[i]->cost; // 이동비용 갱신
            result = i;
        }
    }

    return result;
}

void Dijkstra::SetEdgeInfo(int index)
{
    if (index == -1) return; //이 노드가 인스턴스의 벡터에 없으면(-1) 종료

    float cost = nodes[index]->cost; //기록된 이동비용 가져오기

    for (DNode::Edge* edge : nodes[index]->edges) //인접지를 가져오기
    {
        if (edge->cost + cost < edge->node->cost) //인접지 가는 비용을 이 노드에서 계산했는데
            //기록되어 있는 비용을 갱신한다면

        {
            edge->node->cost = edge->cost + cost; // 값 할당
            edge->node->via = index;  // 인접지의 경유지는 곧 매개변수로 받은 이 위치다
        }
    }
}

void Dijkstra::ResetNodes()
{
    for (DNode* node : nodes)
    {
        //이 클래스에서 했던 노드 속 연산을 처음으로 되돌리기
        node->isClosed = false;
        node->via = -1;
        node->cost = FLT_MAX;
    }
}

vector<Vector3> Dijkstra::GetPath(int start, int end)
{
    // 시작이나 끝 지점이 목록에 없으면 그대로 종료(텅 빈 경로 제공)
    if (start == -1 || end == -1) return vector<Vector3>();

    ResetNodes(); // 노드 리셋 (처음 설정으로)

    // 매개변수에서 현재 인덱스와 그에 맞는 노드를 찾아내기
    int curIndex = start;
    nodes[curIndex]->cost = 0;
    nodes[curIndex]->via = start;

    //------------보완 후 공유
    for (DNode* node : nodes)
    {
        SetEdgeInfo(curIndex); // 인접지 정보 세팅하기
        curIndex = FindMinCostNode(); // 현재 인덱스에서 가장 적은 비용으로 갈 수 있는 노드 구하기
    }

    // 각 노드에서, 다른 노드로 갈 수 있는 최소비용의 관계를 구한다 (시작점을 받았다 치고)

    // 종점을 받고, 새로운 벡터 세팅
    curIndex = end;
    vector<Vector3> path;

    //마지막에서부터 돌면서
    while (curIndex != start)
    {
        //기록된 제일 비용 적은 곳부터 집어넣고 다시 그 안에 기록된 경유지를 역추적
        path.push_back(nodes[curIndex]->pos);
        curIndex = nodes[curIndex]->via;
    }

    //여기까지 오면
    // 1. 출발지에서 시작된 각 노드와 그 갈래들의 이동비용을 알 수 있고
    // 2. 종점에서 다시 시작했다고 칠 때, 최소 이동비용을 가진 위치의 집합을 알 수 있다

    // 여기서 나온 위치의 집합(=경로, 찾아낸 길)의 가장 처음에, 최초의 노드(출발지) 추가
    path.push_back(nodes[start]->pos);

    return path;
}

void Dijkstra::CallSelectNode()
{
    //마우스 클릭(혹은 다른 수단에 의해서라도) 노드를 선택하기
    //마우스 위치를 기준으로 잡기

    Ray ray = CAM->ScreenPointToRay(mousePos);
    Contact contact;

    for (DNode* node : nodes)
    {
        if (node->collider->IsRayCollision(ray, &contact))
        {
            selectedNode = node;
            break;
        }
    }
}

void Dijkstra::CallLinkNode()
{
    if (selectedNode == nullptr) return;

    Ray ray = CAM->ScreenPointToRay(mousePos);
    Contact contact;

    for (DNode* node : nodes)
    {
        if (node == selectedNode) continue; // 선택중인 노드와 지금 막 고른 노드가 일치하면 제치기

        if (node->collider->IsRayCollision(ray, &contact))
        {
            node->AddEdge(selectedNode); // 노드 정보를 인접지로 추가
            selectedNode->AddEdge(node); // 내 정보도 노드 인접지에 추가
            selectedNode = nullptr; // 선택 중인 노드 다시 해제
            break;
        }
    }
}

void Dijkstra::CreateNode(Vector3 pos)
{
    // 호출된 장소에 새 노드 만들기

    DNode* node = new DNode(pos); // 새 노드 만들기
    node->index = nodes.size(); //노드의 순번은 벡터 마지막 순번 번호 + 1
    nodes.push_back(node);    //새 노드를 벡터에 추가

}
