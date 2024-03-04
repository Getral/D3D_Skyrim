#pragma once

class Shadow
{
    // 렌더 타겟, 뎁스 스텐실 효과를 응용한 클래스
    // 모델을 흑백으로 변경하여, 월드에 한 번 더 투사한다

public:
    Shadow(UINT width = 2000, UINT height = 2000);
    ~Shadow();

    void SetRenderTarget();
    void SetRender();
    void PostRender();
    void GUIRender();

private:
    void SetViewProjection(); //뷰포트와 화면 투사를 위한 3D행렬 내기

private:
    float scale = 100;

    RenderTarget* renderTarget;
    DepthStencil* depthStencil;

    ViewBuffer* viewBuffer;
    MatrixBuffer* projectionBuffer;

    UINT width;
    UINT height;

    //테스트용 객체. 렌더 과정 보다 늦게 클래스가 읽혀야 맞다
    class Quad* quad;
};

