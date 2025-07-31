#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/Enemy.h"

GameLevel::GameLevel()
{
	// 플레이어 추가.
	AddActor(new Player());

	// Todo: 테스트 용도. 시험해본 후 제거해야 함.
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