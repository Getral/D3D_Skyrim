#pragma once
class DragonShield : public Armor
{
public:
    DragonShield(string name, int type, int weight, int value,
        int armor_class, int armor_type, int def);
    ~DragonShield();

    void Update();
    void Render();
    void GUIRender();


private:
    Model* dragonshield;
    BoxCollider* collider;
};

