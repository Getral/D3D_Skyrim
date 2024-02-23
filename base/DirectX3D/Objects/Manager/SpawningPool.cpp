#include "Framework.h"

SpawningPool::SpawningPool(ModelAnimatorInstancing* monsterInstancing, Vector3 centerPos, UINT SIZE, float spawnRange, float spawnTime)
	: monsterInstancing(monsterInstancing), centerPos(centerPos), SIZE(SIZE), spawnRange(spawnRange), spawnTime(spawnTime)
{
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
	//랜덤 방향 만들기
	Vector3 dir;
	dir.x = Random(-1.0f, 1.0f);
	dir.z = Random(-1.0f, 1.0f);

	//생성거리 계수와 함께 표적의 주위에서 생성을 한다
	Vector3 randomPos = centerPos + (dir.GetNormalized() * spawnRange);

	// 위에서 정해진 랜덤 장소에서 로봇 하나 생성 (선착순)
	for (Monster* monster : monsters)
	{
		if (!monster->GetTransform()->Active()) // 로봇을 조회 중인데 비활성화 중인 개체가 있으면
		{
			monster->Spawn(randomPos); // 개별 로봇 호출
			break; //반복문(생성 절차) 종료
		}
	}
}
