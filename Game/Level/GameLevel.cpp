#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/Enemy.h"
#include "Utils/Utils.h"

#include <Windows.h>

// �� ������ �� ����� ���� ��.
// ���⿡�� static�� private��.
static const char* enemyType[] =
{
	";:^:;",
	"zZwZz",
	"oO@Oo",
	"<-=->",
	")qOp(",
};

GameLevel::GameLevel()
{
	// �÷��̾� �߰�.
	AddActor(new Player());

	// Todo: �׽�Ʈ �뵵. �����غ� �� �����ؾ� ��.
	//AddActor(new Enemy());

	// Ÿ�̸� ����.
	enemySpawnTimer.SetTargetTime(Utils::RandomFloat(2.0f, 3.0f));
}

GameLevel::~GameLevel()
{
}

void GameLevel::BeginPlay()
{
	super::BeginPlay();
}

void GameLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// �� ����.
	enemySpawnTimer.Tick(deltaTime);

	// Ÿ�� �ƿ� Ȯ��.
	if (!enemySpawnTimer.IsTimeout())
	{
		return;
	}

	// Ÿ�̸� ����.
	enemySpawnTimer.Reset();
	enemySpawnTimer.SetTargetTime(Utils::RandomFloat(2.0f, 3.0f));

	// �� ���� ����.
	// �迭 ���� ���ϱ�.
	static int length = sizeof(enemyType) / sizeof(enemyType[0]);

	// �迭 �ε��� �������� ���ϱ�.
	int index = Utils::Random(0, length - 1);

	// ���� ������ y ��ġ �� �������� ���ϱ�.
	int yPosition = Utils::Random(1, 10);

	// �� ���� ����.
	AddActor(new Enemy(enemyType[index], yPosition));
}

void GameLevel::Render()
{
	super::Render();
}