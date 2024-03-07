#pragma once

class Shadow
{
    // ���� Ÿ��, ���� ���ٽ� ȿ���� ������ Ŭ����
    // ���� ������� �����Ͽ�, ���忡 �� �� �� �����Ѵ�

public:
    Shadow(UINT width = 2000, UINT height = 2000);
    ~Shadow();

    void SetRenderTarget();
    void SetRender();
    void PostRender();
    void GUIRender();

private:
    void SetViewProjection(); //����Ʈ�� ȭ�� ���縦 ���� 3D��� ����

private:
    float scale = 100;

    RenderTarget* renderTarget;
    DepthStencil* depthStencil;

    ViewBuffer* viewBuffer;
    MatrixBuffer* projectionBuffer;

    UINT width;
    UINT height;

    //�׽�Ʈ�� ��ü. ���� ���� ���� �ʰ� Ŭ������ ������ �´�
    class Quad* quad;
};

