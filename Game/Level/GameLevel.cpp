#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/Enemy.h"
#include "Utils/Utils.h"

#include <Windows.h>

// 적 생성할 때 사용할 글자 값.
// 여기에서 static은 private임.
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
	// 플레이어 추가.
	AddActor(new Player());

	// Todo: 테스트 용도. 시험해본 후 제거해야 함.
	//AddActor(new Enemy());

	// 타이머 설정.
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

	// 적 생성.
	enemySpawnTimer.Tick(deltaTime);

	// 타임 아웃 확인.
	if (!enemySpawnTimer.IsTimeout())
	{
		return;
	}

	// 타이머 정리.
	enemySpawnTimer.Reset();
	enemySpawnTimer.SetTargetTime(Utils::RandomFloat(2.0f, 3.0f));

	// 적 생성 로직.
	// 배열 길이 구하기.
	static int length = sizeof(enemyType) / sizeof(enemyType[0]);

	// 배열 인덱스 랜덤으로 구하기.
	int index = Utils::Random(0, length - 1);

	// 적을 생성할 y 위치 값 랜덤으로 구하기.
	int yPosition = Utils::Random(1, 10);

	// 적 액터 생성.
	AddActor(new Enemy(enemyType[index], yPosition));
}

void GameLevel::Render()
{
	super::Render();
}