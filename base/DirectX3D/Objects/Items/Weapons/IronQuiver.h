#pragma once
class IronQuiver : public Model
{
    IronQuiver();
    ~IronQuiver();

    void Update();
    void Render();
    void GUIRender();


private:
    Model* ironquiver;

};

