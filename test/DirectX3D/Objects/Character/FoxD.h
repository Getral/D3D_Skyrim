#pragma once

class FoxD : public ModelAnimator
{
private:
    enum State
    {
        IDLE, RUN
    };

    //typedef Terrain LevelData;
    typedef TerrainEditor LevelData;

public:
    FoxD();
    ~FoxD();

    void Update();
    void Render();

    void SetTerrain(LevelData* terrain) { this->terrain = terrain; }
    void SetDijkstra(Dijkstra* dijkstra) { this->dijkstra = dijkstra; }

private:
    //���� �����̱�
    void Control();
    void Move();
    void Rotate();

    //���� ����
    void SetState(State state);

    //��� ȣ��
    void SetPath();

private:

    State curState = IDLE;

    float moveSpeed = 100;
    float rotSpeed = 10;

    Vector3 velocity;
    Vector3 destPos;
    vector<Vector3> path;

    // ������ ��ã�� �˰���
    LevelData* terrain;
    Dijkstra* dijkstra;
};

