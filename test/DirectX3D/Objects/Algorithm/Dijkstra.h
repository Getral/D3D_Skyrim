#pragma once

class Dijkstra
{
    //���ͽ�Ʈ�� �˰��� : ���� ���е� ���� �� ��θ� Ž���ؼ� ������� ��θ� ã��
    //                    ���� �˻�-���� Ʈ�� �˰���

private:
    //typedef Terrain LevelData;
    typedef TerrainEditor LevelData;

public:
    Dijkstra();
    ~Dijkstra();

    void Update();
    void Render();

    int FindCloseNode(Vector3 pos); // �Էµ� ��ġ���� ���� ����� ���(�� �ε���) ã��
    int FindMinCostNode();          // ���ǿ� ���� ���� ��� ���(�� �ε���) ã��
    
    void SetEdgeInfo(int index); // ������ ���� �Է��ϱ�

    void ResetNodes();

    vector<Vector3> GetPath(int start, int end); // ������� �������� �ָ� �߰��� ���� �� ����
                                                 // ���(��ġ)�� �������� �˷��ִ� ���Ž�� �Լ�

    void CallCreateNode(Vector3 pos) { CreateNode(pos); } //��� �����

    //������� ��带 �����ϰ� �����ϱ�
    void CallSelectNode();
    void CallLinkNode();

    //3D������ �ʿ��� ������ : ��� ���� ������ ��� (���� : �ͷ��� Ȥ�� �ͷ��� ������)
    void SetTerrain(LevelData* terrain) { this->terrain = terrain; }

private:
    void CreateNode(Vector3 pos); // ��� ����� (����Լ�, ���ο�)

private:
    LevelData* terrain; // ���� (�ڷ����� ����)

    vector<DNode*> nodes; //��� ���

    DNode* selectedNode = nullptr; // ���� ���� ��� (�⺻�� : ����)
};

