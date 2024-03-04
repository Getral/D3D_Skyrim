#pragma once

class AStar
{
    // A* �˰��� : ���� �� ã�⿡ Ȱ��� �� ����-�˻� �˰���
public:

    AStar(UINT width = 10, UINT height = 10); //�԰��� �����鼭 ����
    ~AStar();

    void Update();
    void Render();

    void SetNode(){} // �⺻�� (������ ���� �ʴ� ��� ��ġ) - ����α�
    void SetNode(class Terrain* terrain); //������ ��� �޾� ��� ��ġ (���� ���� �Լ�) - �ۼ����
                                          //�� ������ ������ �ϴ���? -> ���ӿ��� �� �����̴ϱ�
                                          //�� class��? -> ������ ������ ��ã�⸦ ��� �ϴϱ�
                                          //���ɼ��� ������� ��ȣ������ ��������.

    int FindCloseNode(Vector3 pos); //�������� ��ǥ�� ���� ��Ȯ�� ��� ���
    int FindRandomPos(Vector3 pos, float range); //������� ���

    void GetPath(IN int start, IN int end, OUT vector<Vector3>& path); //��� ���� �� path�� �����ϱ�
    void MakeDirectionPath(IN Vector3 start, IN Vector3 end, OUT vector<Vector3>& path);
                            // ������� ����
                            // (�� ��Ȯ���� ��ֹ� ������ ���� ��������)
                            // 3D������ �ʼ� ����

    bool IsCollisionObstacle(Vector3 start, Vector3 end);
                            //���ۿ��� ������ �������� �̾��� ��, ��ֹ��� �ε�ġ�°�?

    void AddObstacle(Collider* collider); //��ֹ� �����߰� (Ŭ���� �� ȣ�⵵ ����)

private:
    void SetEdge(); // ������ �߰�
    int GetMinNode(); //�ּҺ�� ��� ���ϱ�
    void Extend(int center, int end); //������ ��ǥ���� �ֺ� ��ǥ ��ΰ���� �����ϱ�

    void Reset();

    float GetManhattanDistance(int start, int end);         // ����ư �Ÿ�
    float GetDiagonalManhattanDistance(int start, int end); // �缱�� ������ ����ư �Ÿ�
    
    // ����ư �Ÿ� (or �ý� �Ÿ�)
    // : �԰��� �ִ� �������� �Ÿ��� ����� ��, ����/�������� �Ÿ��� �����ϰ�(�����Ÿ� ��� �� ��)
    //   ��� ���� �԰ݿ� ���߾ ���ο� ���� (��쿡 ���� �缱 ����) �������� �Ÿ��� ���� ��
    //   Ȥ�� �׷��� �� �Ÿ� ��ġ�� ��Ī�Ѵ�

private:

    vector<Node*> nodes;
    Heap* heap;

    vector<Collider*> obstacles;

    UINT width, height;
    Vector2 interval; //��� ����. Vector3���� ������ ������ 2���� ��� ��ġ�� �� �Ŷ� Vector2


};

