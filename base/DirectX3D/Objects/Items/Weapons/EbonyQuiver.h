#pragma once

class EbonyQuiver : public Model
{
public:
    EbonyQuiver();
    ~EbonyQuiver();

    void Update();
    void Render();
    void GUIRender();


private:
    Model* ebonyquiver;
    CapsuleCollider* collider;
};