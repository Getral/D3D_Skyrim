#pragma once

class BladeSword : public Model
{
public:
    BladeSword();
    ~BladeSword();

    void Update();
    void Render();
    void GUIRender();

    BoxCollider* GetCollider() { return collider; }

private:
    BoxCollider* collider;


};

