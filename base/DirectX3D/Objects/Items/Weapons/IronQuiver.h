#pragma once
class IronQuiver : public Model
{
public:
    IronQuiver();
    ~IronQuiver();

    void Update();
    void Render();
    void GUIRender();


private:
    Model* ironquiver;

};

