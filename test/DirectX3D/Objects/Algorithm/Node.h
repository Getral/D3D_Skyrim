#pragma once

class Node : public BoxCollider // ������ �԰�ȭ, Ÿ��ȭ (A* �˰������� �߿� ���)
                                // ����� �� ���� �Ŷ�� ��� ���� �ȿ����� �԰��� �־�� �Ѵ�
{
    // ��� : ���� ������. A* �˰����򿡼� ��Ҹ� ��Ÿ���� ���ؼ� ����

public:
    friend class AStar;

    struct Edge //���� ����
    {
        int index;
        float cost;
    };

    enum State // �� ����(�� ���)�� ���¸� ������ ���� ����
    {
        NONE, //�ƹ� ���� ����
        OPEN, //�˻� ������ ����
        CLOSED, //�˻��� ���ưų�, �ϸ� �� �Ǵ� ����
        USING,  //���� �˻��� ����ϴ� ��
        OBSTACLE // ��ֹ�, ��뿡 �߰� ������ �ϰų�
                 // ���ʿ� �˻��� �ϸ� �� �Ǵ� ���� (���� �⺻ ����)
    };

    Node(Vector3 pos, int index);
    ~Node();

    void Render();

    void AddEdge(Node* node);

    float GetCost() { return f; } //�� ����� (����) �̵� ��� (A*������ �� ���Ͱ� �ʼ�)
    void SetState(State state) { this->state = state; }

private:
    int index = 0; //�� ����� �ε���
    int via = -1;  //�� ����� ������

    State state;   //�� ����� ���� ����
    vector<Edge*> edges; //��������

    //�̵���� (A* Ȥ�� �԰������� ����ϴ� �ټ��� �˰����򿡼� �̷��� ������ �̵���� ���)
    //         ...Ư�� ���� �ӵ��� �����ϴ� �˰������ϼ��� ������ ��� ���� ������ ���� ��
    float f = 0; // f : Final. ���� ���
    float g = 0; // g : Geometry. ������ ��ġ, Ȥ�� ������ ��ǥ �� ����� ��Ī�ϴ� ������
    float h = 0; // h : Huristic. ��� ������ �˰����� ���� �ٸ���, G�� F�� ������ �� �߰� ����
                 //     -> G Ȥ�� F�� ��ȭ�� �༭ ���� ���� �Ǵ�, Ȥ�� n�� ��꿡 Ȱ���ϴ� ��
                 //        �̵���� ���꿡 �߰� �ӵ��� ���Ϸ��� ����� ����
};
