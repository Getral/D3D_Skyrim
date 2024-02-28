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
    // ��δ� ���۰� ���� �־����� ���� ���ϸ� �ż�, �� Ŭ������ ������Ʈ�� ���� �ʿ����
    // �׷��� ������Ʈ�� �ִ� ���� : ���߿� ��忡 �߰��� �ð��� ȿ���� �ʿ������� ����
}

void Dijkstra::Render()
{
    for (DNode* node : nodes)
        node->Render(); // ������ �浹ü ������ ���� �Լ� (������)
}

int Dijkstra::FindCloseNode(Vector3 pos)
{
    //�־��� ��ġ���� ���� ����� �� (...�� �ε���)

    //���� ������
    float minDist = FLT_MAX; //������ �ִ� �Ÿ�
    int result = -1; //��� ����

    // ��� ã��

    FOR(nodes.size())
    {
        float distance = Distance(pos, nodes[i]->pos); // �� ���� �Ű������� ���� ���� �Ÿ�

        if (distance < minDist) // �ִܰŸ��� ���ŵǸ�
        {
            minDist = distance; //��� ���� ��
            result = i; //����� �ݿ� (i��°)
        }
    }

    // ������� ���� ����� �� �� �ϳ�
    // ���� ������ ���� �Ÿ��� ����� ��尡 ���԰ų�, (i >= 0)
    // ���ʿ� �׷� ���� �� ���迡 ���ų� (-1)

    // ��� ���̵� �ش� ����� ��ǻ�Ϳ� ��ȯ�� �ϸ� �ȴ� (�����ϱ�)

    return result;
}

int Dijkstra::FindMinCostNode()
{
    float minCost = FLT_MAX;
    int result = -1;

    FOR(nodes.size())
    {
        if (nodes[i]->isClosed) continue; //��尡 ���� ����� �ƴϸ� ��ġ��

        if (nodes[i]->cost < minCost) //��尡 ���� ���� �ִµ� (�������ε�)
            // ����� �ּҺ���� �����Ѵٸ�
        {
            minCost = nodes[i]->cost; // �̵���� ����
            result = i;
        }
    }

    return result;
}

void Dijkstra::SetEdgeInfo(int index)
{
    if (index == -1) return; //�� ��尡 �ν��Ͻ��� ���Ϳ� ������(-1) ����

    float cost = nodes[index]->cost; //��ϵ� �̵���� ��������

    for (DNode::Edge* edge : nodes[index]->edges) //�������� ��������
    {
        if (edge->cost + cost < edge->node->cost) //������ ���� ����� �� ��忡�� ����ߴµ�
            //��ϵǾ� �ִ� ����� �����Ѵٸ�

        {
            edge->node->cost = edge->cost + cost; // �� �Ҵ�
            edge->node->via = index;  // �������� �������� �� �Ű������� ���� �� ��ġ��
        }
    }
}

void Dijkstra::ResetNodes()
{
    for (DNode* node : nodes)
    {
        //�� Ŭ�������� �ߴ� ��� �� ������ ó������ �ǵ�����
        node->isClosed = false;
        node->via = -1;
        node->cost = FLT_MAX;
    }
}

vector<Vector3> Dijkstra::GetPath(int start, int end)
{
    // �����̳� �� ������ ��Ͽ� ������ �״�� ����(�� �� ��� ����)
    if (start == -1 || end == -1) return vector<Vector3>();

    ResetNodes(); // ��� ���� (ó�� ��������)

    // �Ű��������� ���� �ε����� �׿� �´� ��带 ã�Ƴ���
    int curIndex = start;
    nodes[curIndex]->cost = 0;
    nodes[curIndex]->via = start;

    //------------���� �� ����
    for (DNode* node : nodes)
    {
        SetEdgeInfo(curIndex); // ������ ���� �����ϱ�
        curIndex = FindMinCostNode(); // ���� �ε������� ���� ���� ������� �� �� �ִ� ��� ���ϱ�
    }

    // �� ��忡��, �ٸ� ���� �� �� �ִ� �ּҺ���� ���踦 ���Ѵ� (�������� �޾Ҵ� ġ��)

    // ������ �ް�, ���ο� ���� ����
    curIndex = end;
    vector<Vector3> path;

    //�������������� ���鼭
    while (curIndex != start)
    {
        //��ϵ� ���� ��� ���� ������ ����ְ� �ٽ� �� �ȿ� ��ϵ� �������� ������
        path.push_back(nodes[curIndex]->pos);
        curIndex = nodes[curIndex]->via;
    }

    //������� ����
    // 1. ��������� ���۵� �� ���� �� �������� �̵������ �� �� �ְ�
    // 2. �������� �ٽ� �����ߴٰ� ĥ ��, �ּ� �̵������ ���� ��ġ�� ������ �� �� �ִ�

    // ���⼭ ���� ��ġ�� ����(=���, ã�Ƴ� ��)�� ���� ó����, ������ ���(�����) �߰�
    path.push_back(nodes[start]->pos);

    return path;
}

void Dijkstra::CallSelectNode()
{
    //���콺 Ŭ��(Ȥ�� �ٸ� ���ܿ� ���ؼ���) ��带 �����ϱ�
    //���콺 ��ġ�� �������� ���

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
        if (node == selectedNode) continue; // �������� ���� ���� �� �� ��尡 ��ġ�ϸ� ��ġ��

        if (node->collider->IsRayCollision(ray, &contact))
        {
            node->AddEdge(selectedNode); // ��� ������ �������� �߰�
            selectedNode->AddEdge(node); // �� ������ ��� �������� �߰�
            selectedNode = nullptr; // ���� ���� ��� �ٽ� ����
            break;
        }
    }
}

void Dijkstra::CreateNode(Vector3 pos)
{
    // ȣ��� ��ҿ� �� ��� �����

    DNode* node = new DNode(pos); // �� ��� �����
    node->index = nodes.size(); //����� ������ ���� ������ ���� ��ȣ + 1
    nodes.push_back(node);    //�� ��带 ���Ϳ� �߰�

}
