#pragma once

class Reflection
{
    // �ݻ� Ŭ����

public:
    Reflection(Transform* target); //target : �ݻ� ���x, ��ü(="������ ���")
    ~Reflection();

    void Update();
    void SetReflection();

    void SetRender();
    void PostRender();

    void GUIRender();

private:
    Transform* target; //�ݻ� ������ ���

    //�̹��� ���縦 ���� ������
    RenderTarget* renderTarget;
    DepthStencil* depthStencil;

    //�̹��� ��� ���� ������ ������ (�ʼ�x �������� �غ�)
    RasterizerState* rasterizerState[2];

    //�ݻ��� �ڸ��� ĸó�� ī�޶�
    Camera* camera;

    //��ü �̹���
    class Quad* quad; //���� Ŭ������ ������ ���� ������ ������,
                      //���嵵 �ʼ��� �ε��� ���� ����
};

