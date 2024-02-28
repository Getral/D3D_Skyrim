#pragma once
class GameScene : public Scene
{
public:

    GameScene();
    ~GameScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Naruto* naruto;

    // �κ� ������ : ������ NPC�� �Ŵ����� �����Ϸ��� �ؼ� �ּ�ó��
    //ModelAnimatorInstancing* robotInstancing;
    //Robot* robot;

    SkyBox* skyBox;
    Model* background;

    Model* model_N;
    Model* model_S;
    Model* model_E;
    Model* model_W;

    Model* fox;

    BlendState* blendState[2]; // ���� ���� �ν��Ͻ� 2�� �����
                               // ���� ���� Ŭ���� : DX�� ���� ���� ȣ���� ���ϰ� �ϱ� ���� Ŭ����
                               // ȣ���, �⺻ ���� ������ ���� �̹����� ��ϵ� ������
                               // ����ų� �ٸ� �ȼ��� �����ش�
                               // 2�� ����� ���� : �ϳ��� �̹��� ������, �ϳ��� ������
};

