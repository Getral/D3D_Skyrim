#pragma once

class Sprite : public Particle
{
    // ��������Ʈ : ���� ����, Ȥ�� ���� �׸�, Ȥ�� ���� �׸��� �׷��� �� ���� ����
    //             ���α׷��ֿ����� 2D �ִϸ��̼� ����� ���� ���� �԰����� ���� [���� �׸���
    //             �� ���Ϸ� ��� ��](=��Ʋ��)�� ���Ѵ�

private:

    class SpriteBuffer : public ConstBuffer
    {
    private:
        struct Data
        {
            Vector2 maxFrame; // �ִϸ��̼��̹Ƿ� �������� �ʿ�
            Vector2 curFrame; // ���� ������
        };
        Data data;
    public:
        SpriteBuffer() : ConstBuffer(&data, sizeof(Data)) {}
        Data& Get() { return data; }
    };

public:
    Sprite(wstring imageFile,       // �̹��� ����
        float width,                // �׸��� ����
        float height,               // �׸��� ����
        UINT frameCol,              // �������� �� = ������ ����
        UINT frameRow,              // �������� �� = ������ ����
        bool isAdditive = false     // ȭ�Ҵ��� �����ΰ�?
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

