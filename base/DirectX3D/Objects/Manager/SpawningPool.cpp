#include "Framework.h"

SpawningPool::SpawningPool(Vector3 centerPos, float spawnRange, float spawnTime, UINT SIZE)
	: centerPos(centerPos), spawnRange(spawnRange), spawnTime(spawnTime), SIZE(SIZE)
{
	monsterInstancing = new ModelAnimatorInstancing("Robot");
	monsterInstancing->ReadClip("StandUp");
	monsterInstancing->ReadClip("Walk");
	monsterInstancing->ReadClip("Run");
	monsterInstancing->ReadClip("Hit");
	monsterInstancing->ReadClip("Dying");

	FOR(SIZE)
	{
		Transform* transform = monsterInstancing->Add();
		transform->SetActive(false);
		transform->Scale() *= 0.05f;
		Character::Status status;
		status.atk = 10;
		status.maxHp = 10;
		status.curHp = status.maxHp;
		status.speed = 10;
		Monster* monster = new Monster(transform, status);
		monsters.push_back(monster);
	}
}

SpawningPool::~SpawningPool()
{
	delete monsterInstancing;
	for (Monster* monster : monsters)
		delete monster;
}

void SpawningPool::Update()
{
	time += DELTA;

	if (time >= spawnTime)
	{
		time -= spawnTime;
		Spawn();
	}

	monsterInstancing->Update();

	for (Monster* monster : monsters)
		monster->Update();
}

void SpawningPool::Render()
{
	monsterInstancing->Render();
	for (Monster* monster : monsters) monster->Render();
}

void SpawningPool::GUIRender()
{
	monsterInstancing->GUIRender();
	for (Monster* monster : monsters) monster->GUIRender();
	ImGui::Text("Spawn Range : %f", spawnRange);
	ImGui::Text("Spawn Time : %f", spawnTime);
}

void SpawningPool::Spawn()
{
	//���� ���� �����
	Vector3 dir;
	dir.x = Random(-1.0f, 1.0f);
	dir.z = Random(-1.0f, 1.0f);

	//�����Ÿ� ����� �Բ� ǥ���� �������� ������ �Ѵ�
	Vector3 randomPos = centerPos + (dir.GetNormalized() * spawnRange);

	// ������ ������ ���� ��ҿ��� �κ� �ϳ� ���� (������)
	for (Monster* monster : monsters)
	{
		if (!monster->GetTransform()->Active()) // �κ��� ��ȸ ���ε� ��Ȱ��ȭ ���� ��ü�� ������
		{
			monster->Spawn(randomPos); // ���� �κ� ȣ��
			break; //�ݺ���(���� ����) ����
		}
	}
}
