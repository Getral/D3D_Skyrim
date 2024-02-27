#include "Framework.h"

DNode::DNode(Vector3 pos)
{
    this->pos = pos; // 위치 기록
    
    cost; // 호출만 : 나중에 이동비용 책정 기준이나 조건이 생기면 여기서 작성 완성

    collider = new SphereCollider(5); //입출력용 충돌체 만들기
    collider->Pos() = pos;
    collider->UpdateWorld(); // 부모-자식 설정을 사실 해도 되지만
                             // 움직일 물체가 아니라서 그냥 단순하게

}

DNode::~DNode()
{
    for (Edge* edge : edges)
        delete edge;

    delete collider;
}

void DNode::Render()
{
    collider->Render();
}

void DNode::AddEdge(DNode* node)
{
    //새로운 인접지 데이터 준비
    Edge* edge = new Edge; //기본생성자를 이용한 포인터 인스턴스는 생성자 호출 필요 없음
    edge->node = node;

    //비용 계산 및 할당
    // -> 샘플 시나리오 : 이동비용은 곧 물리적 거리 그 자체다 (다른 기준은 없다)
    edge->cost = Distance(node->pos, pos);

    //벡터에 인접지 추가
    edges.push_back(edge);

    //이렇게 포인터로 추가된 인접지는 경우에 따라 다른 곳과도 또 연결 가능 (그래서 포인터)
}
