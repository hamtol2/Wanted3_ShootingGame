#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/Enemy.h"
#include "Actor/PlayerBullet.h"
#include "Actor/EnemyBullet.h"

#include "Engine.h"

#include "Utils/Utils.h"

#include <iostream>

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

	// �׽�Ʈ �뵵.
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
	SpawnEnemies(deltaTime);

	// �÷��̾� ź��� ���� �浹 ó��.
	ProcessCollisionPlayerBulletAndEnemy();

	// ���� ź��� �÷��̾��� �浹 ó��.
	ProcessCollisionPlayerAndEnemyBullet();
}

void GameLevel::SpawnEnemies(float deltaTime)
{
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

void GameLevel::ProcessCollisionPlayerBulletAndEnemy()
{
	// �÷��̾� ź�� ���� �迭.
	std::vector<PlayerBullet*> bullets;
	std::vector<Enemy*> enemies;

	// �� Ÿ���� ���͸� �˻��ؼ� �迭 ä���.
	for (Actor* const actor : actors)
	{
		PlayerBullet* bullet = actor->As<PlayerBullet>();
		if (bullet)
		{
			bullets.emplace_back(bullet);
			continue;
		}

		Enemy* enemy = actor->As<Enemy>();
		if (enemy)
		{
			enemies.emplace_back(enemy);
		}
	}

	// ����ó�� (���ص� ��Ȳ Ȯ��).
	if (bullets.size() == 0 || enemies.size() == 0)
	{
		return;
	}

	// �浹 ó��.
	for (auto* bullet : bullets)
	{
		for (auto* enemy : enemies)
		{
			// �� ���Ͱ� ���� ���ƴ��� Ȯ��.
			if (bullet->TestIntersect(enemy))
			{
				enemy->Destroy();
				bullet->Destroy();

				// ������ ȹ���߱� ������ ���� ���� ó���ؾ� ��.
				score = score + 1;
				continue;
			}
		}
	}
}

void GameLevel::ProcessCollisionPlayerAndEnemyBullet()
{
	Player* player = nullptr;
	std::vector<EnemyBullet*> bullets;

	for (Actor* const actor : actors)
	{
		// �� ź������ Ȯ�� �� �迭�� �߰�.
		EnemyBullet* bullet = actor->As<EnemyBullet>();
		if (bullet)
		{
			bullets.emplace_back(bullet);
			continue;
		}

		// �÷��̾� Ȯ��.
		if (!player)
		{
			player = actor->As<Player>();
		}
	}

	// ���ص� �Ǵ� ��Ȳ Ȯ��.
	if (bullets.size() == 0 || !player)
	{
		return;
	}

	// �浹 Ȯ��.
	for (auto* bullet : bullets)
	{
		if (player->TestIntersect(bullet))
		{
			// ���� ó�� (���� ����).
			isPlayerDead = true;
			playerDeadPosition.x = player->Position().x + player->Width() / 2;
			playerDeadPosition.y = player->Position().y;

			player->Destroy();
			bullet->Destroy();
			break;
		}
	}
}

void GameLevel::Render()
{
	super::Render();

	// ���� ���� �� ó��.
	if (isPlayerDead)
	{
		Utils::SetConsoleTextColor(Color::Red);
		Utils::SetConsolePosition(Vector2(playerDeadPosition.x, playerDeadPosition.y - 1));
		std::cout << "   .   ";

		Utils::SetConsolePosition(Vector2(playerDeadPosition.x, playerDeadPosition.y));
		std::cout << " .  .  .";

		Utils::SetConsolePosition(Vector2(playerDeadPosition.x, playerDeadPosition.y + 1));
		std::cout << "..:V:..";

		Utils::SetConsolePosition(Vector2(playerDeadPosition.x, playerDeadPosition.y + 2));
		std::cout << "Game Over!";

		// ��� ����(�뷫 2��).
		Sleep(2000);
		Engine::Get().Quit();
	}

	// ���ھ� �����ֱ�.
	// Score: 0 �̷����� ���ڿ� �����.
	char buffer[20] = { };
	sprintf_s(buffer, 20, "Score: %d", score);

	// ���.
	Utils::SetConsolePosition(Vector2(1, Engine::Get().Height() + 2));
	Utils::SetConsoleTextColor(Color::White);
	std::cout << buffer;
}