#pragma once

class Particle
{
    // ��ƼŬ : ���� �ؽ�ó ���� ��, Ȥ�� �ɰ��� ���� �κ��� �̿���
    //          Ư���� �׷��� ȿ���� �����ϱ� ���� ���� (����ũ, ��, ���� ��)

    // -> �۰� ������� ���� ǥ�� ���� ���� ���ÿ� ���ٴ� Ư¡
    //    + ���� ��� �������� ȿ���� ����� ������(������)�� Ư���� �ִ�

    // ���Ҿ� �� ��ƼŬ Ŭ������ ���� Ư�� ��ƼŬ ȿ���� ���� ���� �������̽��̴�
    // = ��¥ ���� ��ƼŬ �ƴ�, ����ũ�� �� ���� ��ü���� ��ƼŬ �ƴ�

protected: //�� Ŭ������ ��ӹ޾ƾ� �� ��¥ ���� ��ƼŬ�� �����Ƿ� ���⼱ ��� ��������

    UINT MAX_COUNT = 1000; // ��ƼŬ�� �ۿ��� ���� �ִ� ���� ����

public:
    Particle();
    ~Particle();

    // ����� ������ �� �θ� �Լ� (virtual�� ���µ� �����Լ��� �ƴ�)
    virtual void Update() {}
    virtual void Render();          // ���� �ۼ� ������ �θ��� �Լ��� ������ �ǰ�
    virtual void GUIRender() {}

    virtual void Play(Vector3 pos); // ���� �ۼ� ������ �θ��� �Լ��� ������ �ǰ�
    void Stop();                    // ���� ����� �θ� �⺻����

protected:
    bool isActive = false; // Ʈ�������� ��� Ȱ��ȭ ���δ� ���� ����
    UINT particleCount = 0; // ������ ���ڴ� ����
    Vector3 position;       // �����ġ

    Material* material;
    VertexBuffer* vertexBuffer;

    GeometryShader* geometryShader; // ������Ʈ�� ���̴��� ���� ���� �׸� �׸���

    //�׸� �׸���� ��»��¼���
    BlendState* blendState[2];
    DepthStencilState* depthState[2];

};

