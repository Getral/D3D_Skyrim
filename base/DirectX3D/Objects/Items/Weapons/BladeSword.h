#pragma once

class BladeSword : public Model
{
public:
    BladeSword();
    ~BladeSword();

    void Update();
    void Render();
    void GUIRender();

private:
    BoxCollider* collider;


};
