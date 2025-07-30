#pragma once

#include "Level/Level.h"

/*
* ���� ������ å��.
* - ������: �ణ�� �������� �����ؼ� ���� �ð����� �� ����.
* - �浹ó��: �÷��̾�-�� ź�� ������ �浹/��-�÷��̾� ź���� �浹 ó��(AABB).
* - ���� ����: �÷��̾ ���� ���ָ� 1���� ȹ��.
* - ���� ����: �÷��̾ ������ ���� ����.
* - ���� ��ǥ???????.
*/
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();
	~GameLevel();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;

private:

};