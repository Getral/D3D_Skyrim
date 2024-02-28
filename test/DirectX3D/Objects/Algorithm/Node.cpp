#include "Framework.h"

Node::Node(Vector3 pos, int index)
    : index(index)
{
    Pos() = pos; //(입출력과 규격 계산용)충돌체의 위치
    UpdateWorld();
}

Node::~Node()
{
    for (Edge* edge : edges)
        delete edge;
}

void Node::Render()
{
    //현재 노드의 상태별로 충돌체 색을 다르게 표현
    switch (state)
    {
    case Node::NONE:
        SetColor({ 0, 1, 1, 1 }); // 청록색
        break;
    case Node::OPEN:
        SetColor({ 0, 0, 1, 1 }); // 파란색
        break;
    case Node::CLOSED:
        SetColor({ 0, 0, 0, 1 }); // 까만색
        break;
    case Node::USING:
        SetColor({ 0, 1, 0, 1 }); // 초록색
        break;
    case Node::OBSTACLE:
        SetColor({ 1, 0, 0, 1 }); // 빨간색
        break;
    }

    BoxCollider::Render();
}

void Node::AddEdge(Node* node)
{
    Edge* edge = new Edge();
    edge->index = node->index;
    edge->cost = Distance(node->GlobalPos(), GlobalPos()); // 샘플 규칙 : 물리적 거리가 곧 이동비용

    edges.push_back(edge);
}
