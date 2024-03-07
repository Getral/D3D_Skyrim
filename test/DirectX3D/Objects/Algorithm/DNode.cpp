#include "Framework.h"

DNode::DNode(Vector3 pos)
{
    this->pos = pos; // ��ġ ���
    
    cost; // ȣ�⸸ : ���߿� �̵���� å�� �����̳� ������ ����� ���⼭ �ۼ� �ϼ�

    collider = new SphereCollider(5); //����¿� �浹ü �����
    collider->Pos() = pos;
    collider->UpdateWorld(); // �θ�-�ڽ� ������ ��� �ص� ������
                             // ������ ��ü�� �ƴ϶� �׳� �ܼ��ϰ�

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
    //���ο� ������ ������ �غ�
    Edge* edge = new Edge; //�⺻�����ڸ� �̿��� ������ �ν��Ͻ��� ������ ȣ�� �ʿ� ����
    edge->node = node;

    //��� ��� �� �Ҵ�
    // -> ���� �ó����� : �̵������ �� ������ �Ÿ� �� ��ü�� (�ٸ� ������ ����)
    edge->cost = Distance(node->pos, pos);

    //���Ϳ� ������ �߰�
    edges.push_back(edge);

    //�̷��� �����ͷ� �߰��� �������� ��쿡 ���� �ٸ� ������ �� ���� ���� (�׷��� ������)
}
