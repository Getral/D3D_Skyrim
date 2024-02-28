#pragma once

class ShadowScene : public Scene
{
public:
    ShadowScene();
    ~ShadowScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:

    Model* forest;
    //Model* human;
    ModelAnimator* human;

    Shadow* shadow; // 테스트용 호출. 필요하면 출력절차(Environment) 혹은 다른 과정에서 불러도 된다
                    // ....혹은 각 개체가 자기 그림자를 가지고 있어도 좋다....

    LightBuffer::Light* light; //빛 사용하기
};

