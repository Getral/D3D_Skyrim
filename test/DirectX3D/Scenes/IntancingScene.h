#pragma once

class IntancingScene : public Scene
{
public:
    IntancingScene();
    ~IntancingScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:

    ModelAnimatorInstancing* models;
    ModelInstancing* statics;

    int instanceID = 0;
    int clip = 0;
    
    int SIZE = 10;     
    int WIDTH = 9;
    int HEIGHT = 12;
};

