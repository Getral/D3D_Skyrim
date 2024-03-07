#pragma once

class Sprite : public Particle
{
    // 스프라이트 : 작은 요정, 혹은 작은 그림, 혹은 작은 그림을 그려서 찍어낸 판자 간판
    //             프로그래밍에서는 2D 애니메이션 재생을 위해 같은 규격으로 만든 [여러 그림을
    //             한 파일로 묶어낸 것](=아틀라스)을 말한다

private:

    class SpriteBuffer : public ConstBuffer
    {
    private:
        struct Data
        {
            Vector2 maxFrame; // 애니메이션이므로 프레임이 필요
            Vector2 curFrame; // 현재 프레임
        };
        Data data;
    public:
        SpriteBuffer() : ConstBuffer(&data, sizeof(Data)) {}
        Data& Get() { return data; }
    };

public:
    Sprite(wstring imageFile,       // 이미지 파일
        float width,                // 그림의 가로
        float height,               // 그림의 세로
        UINT frameCol,              // 프레임의 열 = 가로의 개수
        UINT frameRow,              // 프레임의 행 = 세로의 개수
        bool isAdditive = false     // 화소누적 투명인가?
    );
    ~Sprite();

    void Update();
    void Render();
    void GUIRender();

    void Play(Vector3 pos);

private:
    void Create();

private:
    float time = 0;
    float speed = 1;
    float interval = 0.1f;
    UINT curFrameCount = 0;
    UINT maxFrameCount = 0;
    Vector2 size;

    SpriteBuffer* buffer;
    VertexUV vertex;


};

