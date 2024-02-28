#pragma once

class Shield : public Model
{
public:
    Shield();
    ~Shield();

    void Update();
    void Render();
    void GUIRender();

private:
    BoxCollider* collider;


};
