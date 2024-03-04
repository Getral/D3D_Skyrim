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
    //여우 움직이기
    void Control();
    void Move();
    void Rotate();

    //상태 설정
    void SetState(State state);

    //경로 호출
    void SetPath();

private:

    State curState = IDLE;

    float moveSpeed = 100;
    float rotSpeed = 10;

    Vector3 velocity;
    Vector3 destPos;
    vector<Vector3> path;

    // 지형과 길찾기 알고리즘
    LevelData* terrain;
    Dijkstra* dijkstra;
};

