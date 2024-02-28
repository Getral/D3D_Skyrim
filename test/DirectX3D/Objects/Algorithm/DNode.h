#pragma once

class DNode
{
    // D-��� : ���ͽ�Ʈ�� �˰����򿡼� ��ġ ������ ����ϴ� Ŭ����

private:
    friend class Dijkstra; // ���� Ŭ���� : ���ͽ�Ʈ�� �˰�����

    //��ġ ������ �Բ� �־�� �ϴ� �ΰ� ����
    struct Edge // ���� ����
    {
        DNode* node; // ���� ������ �׷��� ���� D-����ΰ�?
        float cost;  // �� �������� ������ ����� �󸶳� ��°�?
    };

public:
    DNode(Vector3 pos); // �� ���� �׷��� ��� �ִ°�? (�Ű����� �ʼ�)
    ~DNode();

    void Render(); // �ʿ�� ������ �̿��� �� ���Ϸ��� �߰��ϴ� ���� �Լ�
    void AddEdge(DNode* node); //�ٸ� ������ �Ű������� �̾ ���� �������� ���

private:
    Vector3 pos; //�� ��尡 �ִ� ��ġ

    bool isClosed = false; // "�� ���� ������" ���� : Ž���� ������ ���� ����
                           // = ��ã�� ���� �߿� , ������ �� ������ ���� ��,
                           // �ߺ��̰ų�, �ٸ� ������ �־ �������� ���ƾ� �� �� �����Ƿ�
                           // �� �� ������ ���� ���θ� �Ǵ��ϱ� ���� ���� ������ ����, ����

    int index = 0; // ��尡 ���� ���� �� �� ��尡 ������ �־�� �� �ĺ���ȣ
    int via = -1;  // ��� Ž�� ��, �� ��忡 �̸������, ���Ŀ� ���� ������ ���
                   // = ��� Ž�� �� ������ "�� ��� ������ ���" : �⺻���� "�׷� �� ����"

    float cost = FLT_MAX; // �̵����

    vector<Edge*> edges;  // ���������� ����

    SphereCollider* collider; //�ð� Ȯ�ο� + �Է��� �� ���콺 �Է� �ޱ� ���� �뵵
};
