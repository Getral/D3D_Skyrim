#pragma once
class ParticleConfigScene : public Scene
{
    // ��ƼŬ ���� �� : �̹����� �ɼ��� ���� ��ƼŬ�� �ϳ��� ������ ���� ���Ϸ�
    //                 �����ϱ� ���� ��

private:
    UINT MAX_COUNT = 1000;

    // ��ƼŬ�� ���� �� �ɼ� �� ���� �����͸� �Űܿ´�
    // �ּ��� ���� ��ƼŬ �ý��� Ŭ�������� Ȯ��

    struct InstanceData
    {
        Matrix transform = XMMatrixIdentity();
    };

    struct ParticleData
    {
        bool isLoop = false;
        bool isAdditive = true;
        bool isBillboard = true;
        UINT count = 100;
        float duration = 1;
        Vector3 minVelocity = { -1, -1, -1 };
        Vector3 maxVelocity = { +1, +1, +1 };
        Vector3 minAcceleration;
        Vector3 maxAcceleration;
        Vector3 minStartScale = { 1, 1, 1 };
        Vector3 maxStartScale = { 1, 1, 1 };
        Vector3 minEndScale = { 1, 1, 1 };
        Vector3 maxEndScale = { 1, 1, 1 };
        float minSpeed = 1;
        float maxSpeed = 3;
        float minAngularVelocity = -10.0f;
        float maxAngularVelocity = +10.0f;
        float minStartTime = 0;
        float maxStartTime = 0;
        Float4 startColor = { 1, 1, 1, 1 };
        Float4 endColor = { 1, 1, 1, 1 };
    };

    struct ParticleInfo
    {
        Transform transform;
        Vector3 velocity;
        Vector3 acceleration;
        Vector3 startScale;
        Vector3 endScale;

        float speed = 1;
        float angularVelocity = 0;
        float startTime = 0;
    };

public:

    ParticleConfigScene();
    ~ParticleConfigScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:

    //��ƼŬ�� ������
    void UpdatePhysical();
    void UpdateColor();
    void Init();

    void Save(string file);
    void Load(string file);

    void EditTexture();
    void SaveDialog(); // dialog : ImGui���� Dialogue�� ǥ���� �� �̷��⵵ �Ѵ�
    void LoadDialog();

private:

    Quad* quad;

    vector<InstanceData> instances;
    vector<ParticleInfo> particleInfo;

    VertexBuffer* instanceBuffer;

    ParticleData data;

    float lifeSpan = 0;
    UINT drawCount = 0;
    UINT particleCount = 100;

    BlendState* blendState[2];
    DepthStencilState* depthState[2];

    // ���̺� �ε忡 ���� ���� ��θ�
    string projectPath;


};

