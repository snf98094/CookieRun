#pragma once
#include "Animation/Animator.h"

class GameLevel;
class MapObject;
class Item;
class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)

	enum class PlayerState
	{
		Idle,
		Move,
		Jump,
		DoubleJump,
		Slide
	};

public:
	Player(GameLevel* level);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void LateUpdate(float deltaTime) override;

	void Jump(float deltaTime);
	void SetState(PlayerState state);

	MapObject* OnCollisionObject(std::vector<MapObject*> objects);
	void OnCollisionItem(std::vector<Item*> items);

	void SetBig(bool isBig);

private:
	// GameLevel ����.
	GameLevel* level;

	// �÷��̾� ����.
	PlayerState state = PlayerState::Idle;
	// �⺻ ��ġ��.
	Vector2 defaultPosition = Vector2(105.0f, 321.0f);
	// ��� �ð�.
	float elapsedTime = 0.0f;

	// �÷��̾� �ִϸ�����.
	Animator playerAnimator;
	const char* move = "Move";
	const char* jump = "Jump";
	const char* doubleJump = "DoubleJump";
	const char* slide = "Slide";
	AnimationClip* animationClip = nullptr;

	// ���� ��ġ�� ��������� ����.
	Vector2 jumpPosition = defaultPosition;
	// �⺻ ���� �ӵ� ����.
	float defaultjumpSpeed = 500.0f;
	// ���� ���� �ӵ� ����.
	float newjumpSpeed = defaultjumpSpeed;
	// �߷� ����.
	float gravitation = 1200.0f;

	// �浹 ������Ʈ.
	MapObject* collisionObject = nullptr;

	// �Ŵ�ȭ.
	bool isBig = false;
	// �Ŵ�ȭ �ð�.
	float bigTime = 0.0f;

	// �÷��� �� ȹƯ�� ����.
	int coin = 0;
	// �÷��� �� ȹƯ�� ����.
	int score = 0;
};