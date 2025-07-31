#pragma once

#include "Actor/Actor.h"

/*
* �̵� ���� (�¿�).
* - �����ʿ��� �¾���� �������� �̵�.
* - ���ʿ��� �¾���� ���������� �̵�.
*/
class Enemy : public Actor
{
	// �̵� ���� ������.
	enum class MoveDirection
	{
		None = -1,
		Left,
		Right
	};

	RTTI_DECLARATIONS(Enemy, Actor)

public:
	Enemy();

	virtual void Tick(float deltaTime) override;

private:

	// �̵� ����.
	MoveDirection direction = MoveDirection::None;

	// �ӷ��� ����� �̵� ��ġ ����� ���� float ����.
	float xPosition = 0.0f;

	// �̵� ������.
	float moveSpeed = 5.0f;

	// Ÿ�̸� ����� ���� ����.
	// ��� �ð� ��� ����.
	float elapsedTime = 0.0f;

	// ��ǥ �ð� ��. (setTime, targetTime).
	float targetTime = 0.0f;
};