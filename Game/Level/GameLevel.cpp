#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/Enemy.h"

GameLevel::GameLevel()
{
	// �÷��̾� �߰�.
	AddActor(new Player());

	// Todo: �׽�Ʈ �뵵. �����غ� �� �����ؾ� ��.
	AddActor(new Enemy());
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
}

void GameLevel::Render()
{
	super::Render();
}