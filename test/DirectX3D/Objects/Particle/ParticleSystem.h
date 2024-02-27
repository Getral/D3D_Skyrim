#pragma once

class ParticleSystem
{
    // ��ƼŬ �ý��� (Ȥ�� ���� ��ƼŬ) Ŭ����
    // �׸� �����͸� ����� �޾Ƽ� �ɼǿ� ���� ����ϴ� ���� Ŭ����

    // -> ���� ��ƼŬ�� ���� ��������, ���ϴ� �ɼǿ� ���� ��ƼŬ�� �����ؼ� �� �� �ִ�

private:
    struct InstanceData // ��ƼŬ ������ ������ ���� ������ ������
    {
        Matrix transform = XMMatrixIdentity();
    };

    struct ParticleData //��ƼŬ ��ü�� ������ = ��ü�� �ɼ�
    {
        // �Ϲ������� ��ƼŬ�� ����Ǵ� �پ��� �ɼ� ��, ���� ���������� ���̴� �ٽ� �κ��� �ۼ�
        // �߰��� �ʿ��� �ɼ��� ������ ���⼭ �ۼ�


        bool isLoop = false; // �ݺ��ϴ°�?
        bool isAdditive = true; //ȥ�� �����ΰ�?
        bool isBillboard = true; //������ ����ΰ�(ī�޶� ������� ������ ������ ���̴°�?)
        UINT count = 100; //��ƼŬ�� ��� ���� Ȥ�� ��ƼŬ �� ���� �ν��Ͻ��� ���� (�⺻�� ����)
        float duration = 1; //��ƼŬ=����Ʈ�� ���ӽð�
        Vector3 minVelocity = { -1, -1, -1 }; // �ּ� �ӷ� ���� (Ȥ�� ���� ������ - ��)
        Vector3 maxVelocity = { +1, +1, +1 }; // �ִ� �ӷ� ���� (Ȥ�� ���� ������ + ��)
        Vector3 minAcceleration; //�ּ� ���ӷ� (Ȥ�� �ӵ��� ��ȭ��)
        Vector3 maxAcceleration; //�ִ� ���ӷ� (Ȥ�� �ӵ��� ��ȭ��)
        Vector3 minStartScale = { 1, 1, 1 }; // ��ƼŬ ���� �� �ּ� ũ��
        Vector3 maxStartScale = { 1, 1, 1 }; // ��ƼŬ ���� �� �ִ� ũ��
        Vector3 minEndScale = { 1, 1, 1 }; // ��ƼŬ ���� �� �ּ� ũ��
        Vector3 maxEndScale = { 1, 1, 1 }; // ��ƼŬ ���� �� �ִ� ũ��
        float minSpeed = 1; //�ּ� ���� �̵� �ӷ� (Ȥ�� �ӷ��� ��� ���)
        float maxSpeed = 3; //�ִ� ���� �̵� �ӷ� (Ȥ�� �ӷ��� ��� ���)
        float minAngularVelocity = -10.0f; //�ּ� ���� ������
        float maxAngularVelocity = +10.0f; //�ִ� ���� ������
        float minStartTime = 0; //�ּ� ���� ���� �ð�
        float maxStartTime = 0; //�ִ� ���� ���� �ð�
        Float4 startColor = { 1, 1, 1, 1 }; //���� �� ����� ���� ����(Ȥ�� ���� ����)
        Float4 endColor = { 1, 1, 1, 1 }; //���� �� ����� ���� ����(Ȥ�� ���� ����)

        // -> ���� ����, ���̴� ���� ���� ������� �ʰ� �ǵ� ������ �ּ����� �ɼ��� �ۼ�
        // -> �� �ɼ��� �������� �� ���ڰ� ������� �� �������� �ɼ��� ����
    };

    //...�׷��� ������ ������� �� ������ (Ȥ�� ��ƼŬ ��ü �����)
    // ���� ���� ������ Ȯ���ϱ� ���� ����ü
    struct ParticleInfo
    {
        Transform transform; // �� ���� Ȥ�� ��ü �߽��� Ʈ������
        Vector3 velocity; //�� �����Ϳ��� �������� ���� �ӷ� ���� (=����, ���ؼӵ�)
        Vector3 acceleration; // �� �����Ϳ��� �������� ���� ���ӷ�
        Vector3 startScale; //...���۽� ũ��
        Vector3 endScale;   //...����� ũ��

        //�⺻�� �ִ� �Ҽ��� (���� ������ �ϸ� �⺻���� �����ϱ�)
        float speed = 1;
        float angularVelocity = 0;
        float startTime = 0;

        // -> ������� ���� �ɼ� Ȯ�� Ȥ�� (�ʿ��ϸ�) ���� � ���δ�
        // �� ���ڰ� ����̸� -> ���� �ϳ��ϳ��� �����ϴ� ����
        // ����� ����̸� -> ��ƼŬ ��ü�� �뺯�ϴ� ����
    
        //�켱�� �� ����ü�� �� ������ ������ Ȱ��
    };

public:
    ParticleSystem(string file);  // ���� �����̵�, �̹��� ���� �ε��̵�,
    ParticleSystem(wstring file); // �̹��� ���� ��ƼŬ�� ������ ���� ����.
    ~ParticleSystem();

    void Update();
    void Render();
    void GUIRender();

    void Play(Vector3 pos, Vector3 rot = Vector3()); // ��ƼŬ�� ����� ��ҿ�, ȸ������
                                    // ȸ�������� �ʿ��� ���� = �����尡 �ƴ� ���� �־
                                    // �Ű����� �⺻�� {0,0,0}�� ���� = �����尡 �⺻�̶�

    void Stop(); // �ܵ� Ŭ������ ���ߴ� �͵� �Լ��� ���� �ʿ��ϴ�

    bool IsActive() { return quad->Active(); } //������ Ȱ��ȭ ���ο��� ��ƼŬ�� Ȱ��ȭ�� �Ǵ�

private:
    void UpdatePhysical(); // ������ ��� = ���� ���� ������Ʈ
    void UpdateColor();    // ���� ������Ʈ
    void Init();           // ����� ����

    void LoadData(string file);  // C++�� ���� ���� �б�
                                 // : �ؽ�Ʈ �б� Ŭ������ ���� ������ ���� �б� (�ִ� ġ��)
    void LoadData(wstring file); // �����쿡 ���� ���� �б�
                                 // : �̹��� ���ҽ��� ���� �б�

private:
    //��ƼŬ�� �ʿ��� ��

    // ���� ���� : �̹��� �� ��ü
    Quad* quad; // �� �̹����� ���� �޴°�? -> �����尡 �ƴ� ���� �־ (���� ������ �ʿ�)
                // = ������Ʈ�� ���̴��� ���� �ʴ´�

    // ��ƼŬ �� �ν��Ͻ��� ���Ϳ� ����
    vector<InstanceData> instances; // �ν��Ͻ���
    vector<ParticleInfo> particleInfo; // ������� �� �ν��Ͻ��� ���� ��

    // �ν��Ͻ��� ��� ������ �������μ� �����ϱ� ���� ����
    VertexBuffer* instanceBuffer; // ���۰� ���� ���� ����

    ParticleData data; //�� ��ƼŬ�� ������ �ɼ�(�� �� ����)

    // ��ƼŬ�� ���� ����
    float lifeSpan = 0; //���ڵ��� ���� �ֱ� (���ӽð��� �ٸ� ǥ��)
    UINT drawCount = 0; //��ο� �� Ƚ��
    UINT particleCount = 100; // ��ƼŬ �� ���� ����

    //�̹��� ��¿�....
    BlendState* blendState[2];        //�̹��� ȥ�տ�(�ٸ� ���� �̹����� �����ϱ� ����)
    DepthStencilState* depthState[2]; //�̹��� ������(��ġ�� ���� ��Ȳ���� �̹��� ��� ����)

};

