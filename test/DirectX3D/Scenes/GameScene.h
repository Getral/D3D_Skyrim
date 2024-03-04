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

    // 로봇 데이터 : 복수의 NPC를 매니저로 관리하려고 해서 주석처리
    //ModelAnimatorInstancing* robotInstancing;
    //Robot* robot;

    SkyBox* skyBox;
    Model* background;

    Model* model_N;
    Model* model_S;
    Model* model_E;
    Model* model_W;

    Model* fox;

    BlendState* blendState[2]; // 블렌드 상태 인스턴스 2개 만들기
                               // 블렌드 상태 클래스 : DX의 블렌드 상태 호출을 편하게 하기 위한 클래스
                               // 호출시, 기본 블렌드 설정에 의해 이미지에 기록된 배경색을
                               // 지우거나 다른 픽셀과 합쳐준다
                               // 2개 만드는 이유 : 하나는 이미지 렌더용, 하나는 복원용
};

