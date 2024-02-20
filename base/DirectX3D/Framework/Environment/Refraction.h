#pragma once

class Refraction
{
    // �Ϸ��� Ŭ����

public:
    Refraction(wstring normalFile); //�Ϸ��� �� ������ ���� �����ϱ� ���� �븻�� �ʿ�
    ~Refraction();

    void Update();
    void SetRefraction();

    void SetRender();
    void PostRender();

    void GUIRender();

private:
    WaterBuffer* waterBuffer;

    Texture* normalMap;

    //�̹��� ���縦 ���� ������
    RenderTarget* renderTarget;
    DepthStencil* depthStencil;

    //��ü �̹���
    class Quad* quad; //���� Ŭ������ ������ ���� ������ ������,
                      //���嵵 �ʼ��� �ε��� ���� ����

};

