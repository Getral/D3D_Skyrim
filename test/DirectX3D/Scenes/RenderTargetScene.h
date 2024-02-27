#pragma once
class RenderTargetScene : public Scene
{
public:

    RenderTargetScene();
    ~RenderTargetScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:

    //시험용 출력 모델
    //ModelAnimator* model;
    Model* model;

    //렌더 타겟 기능
    RenderTarget* renderTarget;
    DepthStencil* depthStencil;

    //출력한 결과가 있어야 할 곳
    Quad* quad;
    //Sphere* quad;
    FloatValueBuffer* valueBuffer;
};

