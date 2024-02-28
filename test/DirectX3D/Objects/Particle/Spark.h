#pragma once

class Spark : public Particle
{
private:
    //����ũ�� ������ �� �������� �������� : �� ������ ������
    struct VertexParticle // �� ����ũ ������ ����
    {
        Float3 position = {}; // ���Ͱ� �ƴ� Float3 (DX, Ȥ�� ���̴� ��꿡 �ٷ� ����)
        Float2 size = {};
        Float3 velocity = {};
    };

public:
    Spark(wstring imageFile, bool isAdditive = false);
                             // Additive : ��ǻ�Ϳ��� �׸��� �׸��� ��� �� �ϳ�
                             //            ��� ȭ�� ���� �̹��� ȭ���� ���� "���ؼ�" ����
                             //            -> �뷫 �̹����� ������鼭 ������������ ȿ���� ���´�
    ~Spark();

    void Update();
    void Render();
    void GUIRender();

    void Play(Vector3 pos);

private:
    void Create();
    void UpdateParticle();

private:

    float minRadius = 5;  //�ּ� �ݰ�
    float maxRadius = 10; //�ִ� �ݰ�

    float minSize = 0.1f; //�ּ� ũ��
    float maxSize = 1.0f; //�ִ� ũ��

    FloatValueBuffer* buffer;
    ColorBuffer* startColorBuffer; //���۽� ����
    ColorBuffer* endColorBuffer;   //����� ����

    // -> ��ƼŬ�� ��������� ������ Ư¡ : �ɼ��� �ϳ��� �������� �ʰ� ���� ������ ��������
    //                                     ��޵Ǵ� ��찡 ����

    VertexUV vertex; //��꿡 ����� �ӽ� �����Ͱ� �� ����

    vector<VertexParticle> vertices; //�� Ŭ������ ���� ������
};

