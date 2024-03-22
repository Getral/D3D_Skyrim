#pragma once
class IronShield : public Armor
{
public:
    IronShield(string name, int type, int weight, int value,
        int armor_class, int armor_type, int def);
    ~IronShield();

    void Update();
    void Render();
    void GUIRender();


private:
    Model* ironshield;
    BoxCollider* collider;
};

