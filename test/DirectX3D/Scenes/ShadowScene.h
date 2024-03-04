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

    Shadow* shadow; // �׽�Ʈ�� ȣ��. �ʿ��ϸ� �������(Environment) Ȥ�� �ٸ� �������� �ҷ��� �ȴ�
                    // ....Ȥ�� �� ��ü�� �ڱ� �׸��ڸ� ������ �־ ����....

    LightBuffer::Light* light; //�� ����ϱ�
};

