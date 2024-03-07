#pragma once
class DijkstraScene : public Scene
{
public:
    DijkstraScene();
    ~DijkstraScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:

    //Terrain* terrain;
    TerrainEditor* terrain;

    Dijkstra* dijkstra;

    FoxD* fox;
};

