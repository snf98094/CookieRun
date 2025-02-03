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
	// GameLevel 변수.
	GameLevel* level;

	// 플레이어 상태.
	PlayerState state = PlayerState::Idle;
	// 기본 위치값.
	Vector2 defaultPosition = Vector2(105.0f, 321.0f);
	// 경과 시간.
	float elapsedTime = 0.0f;

	// 플레이어 애니메이터.
	Animator playerAnimator;
	const char* move = "Move";
	const char* jump = "Jump";
	const char* doubleJump = "DoubleJump";
	const char* slide = "Slide";
	AnimationClip* animationClip = nullptr;

	// 점프 위치를 적용시켜줄 변수.
	Vector2 jumpPosition = defaultPosition;
	// 기본 점프 속도 변수.
	float defaultjumpSpeed = 500.0f;
	// 적용 점프 속도 변수.
	float newjumpSpeed = defaultjumpSpeed;
	// 중력 변수.
	float gravitation = 1200.0f;

	// 충돌 오브젝트.
	MapObject* collisionObject = nullptr;

	// 거대화.
	bool isBig = false;
	// 거대화 시간.
	float bigTime = 0.0f;

	// 플레이 중 획특한 코인.
	int coin = 0;
	// 플레이 중 획특한 점수.
	int score = 0;
};