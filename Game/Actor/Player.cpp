#include "Player.h"
#include "Engine/Engine.h"
#include "Level/Level.h"
#include "Level/GameLevel.h"

Player::Player(GameLevel* level)
{
	AnimationClip* moveClip = new AnimationClip(move, 0.1f);
	moveClip->SetPlayPosition(defaultPosition);
	moveClip->AddImage(new ImageText("Character/Cookie_Move_01", Color::Yellow, true, true), 0.0f);
	moveClip->AddImage(new ImageText("Character/Cookie_Move_02", Color::Yellow, true, true), 0.33f);
	moveClip->AddImage(new ImageText("Character/Cookie_Move_03", Color::Yellow, true, true), 0.66f);
	moveClip->SetLoop(true);
	level->AddActor(moveClip);

	AnimationClip* jumpClip = new AnimationClip(jump, 0.1f);
	jumpClip->SetPlayPosition(defaultPosition);
	jumpClip->AddImage(new ImageText("Character/Cookie_Jump_01", Color::Yellow, true, true), 0.0f);
	jumpClip->AddImage(new ImageText("Character/Cookie_Jump_02", Color::Yellow, true, true), 0.5f);
	jumpClip->SetLoop(true);
	level->AddActor(jumpClip);

	AnimationClip* doubleJumpClip = new AnimationClip(doubleJump, 0.4f);
	doubleJumpClip->SetPlayPosition(defaultPosition);
	doubleJumpClip->AddImage(new ImageText("Character/Cookie_DoubleJump_01", Color::Yellow), 0.0f);
	doubleJumpClip->AddImage(new ImageText("Character/Cookie_DoubleJump_02", Color::Yellow), 0.195f);
	doubleJumpClip->AddImage(new ImageText("Character/Cookie_DoubleJump_03", Color::Yellow), 0.39f);
	doubleJumpClip->AddImage(new ImageText("Character/Cookie_DoubleJump_04", Color::Yellow), 0.585f);
	doubleJumpClip->AddImage(new ImageText("Character/Cookie_DoubleJump_05", Color::Yellow), 0.78f);
	doubleJumpClip->AddImage(new ImageText("Character/Cookie_DoubleJump_06", Color::Yellow), 0.975f);
	doubleJumpClip->SetLoop(false);
	level->AddActor(doubleJumpClip);

	AnimationClip* slideClip = new AnimationClip(slide, 0.1f);
	slideClip->SetPlayPosition(defaultPosition);
	slideClip->AddImage(new ImageText("Character/Cookie_Slide_01", Color::Yellow), 0.0f);
	slideClip->AddImage(new ImageText("Character/Cookie_Slide_02", Color::Yellow), 0.5f);
	slideClip->SetLoop(true);
	level->AddActor(slideClip);

	playerAnimator.AddClip(moveClip);
	playerAnimator.AddClip(jumpClip);
	playerAnimator.AddClip(doubleJumpClip);
	playerAnimator.AddClip(slideClip);

	SetState(PlayerState::Move);

	this->level = level;
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (state == PlayerState::Jump)
	{
		Jump(deltaTime);

		if (Engine::Get().GetKeyDown(VK_UP))
			SetState(PlayerState::DoubleJump);
	}
	else if (state == PlayerState::DoubleJump)
	{
		Jump(deltaTime);
	}
	else
	{
		if (Engine::Get().GetKeyDown(VK_UP))
			SetState(PlayerState::Jump);
		else if (Engine::Get().GetKey(VK_DOWN))
			SetState(PlayerState::Slide);
		else if (state == PlayerState::Slide)
			SetState(PlayerState::Move);
	}

	if (isBig)
	{
		bigTime -= deltaTime;
		if (bigTime < 0.0f && state == PlayerState::Move)
			SetBig(false);
	}
}

void Player::Draw()
{
}

void Player::LateUpdate(float deltaTime)
{
	if (!isBig)
	{
		collisionObject = OnCollisionObject(CreateMap::Get().GetActiveObjectList());
		if (collisionObject)
		{
			level->LoadScoreLevel();
			//Engine::Get().QuitGame();

			return;
		}
	}

	OnCollisionItem(CreateMap::Get().GetActiveItemList());
}

void Player::Jump(float deltaTime)
{
	if (jumpPosition.y > defaultPosition.y)
	{
		SetState(PlayerState::Move);
		return;
	}

	jumpPosition.y -= newjumpSpeed * deltaTime;
	newjumpSpeed -= gravitation * deltaTime;

	animationClip->SetPlayPosition(jumpPosition);
}

void Player::SetState(PlayerState state)
{
	this->state = state;

	switch (state)
	{
		case Player::PlayerState::Idle:
			break;

		case Player::PlayerState::Move:
			playerAnimator.Play(move);
			break;

		case Player::PlayerState::Jump:
			playerAnimator.Play(jump);

			jumpPosition = defaultPosition;
			newjumpSpeed = defaultjumpSpeed;

			playerAnimator.GetClip(jump)->SetPlayPosition(jumpPosition);
			break;

		case Player::PlayerState::DoubleJump:
			if (isBig)
				break;

			playerAnimator.Play(doubleJump);

			newjumpSpeed = defaultjumpSpeed;

			playerAnimator.GetClip(doubleJump)->SetPlayPosition(jumpPosition);
			break;

		case Player::PlayerState::Slide:
			if (isBig)
				break;

			Vector2 slidePosition = defaultPosition;
			slidePosition.y += 36;

			playerAnimator.GetClip(slide)->SetPlayPosition(slidePosition);
			playerAnimator.Play(slide);
			break;
	}

	animationClip = playerAnimator.GetCurrentClip();
}

MapObject* Player::OnCollisionObject(std::vector<MapObject*> objects)
{
	ImageText* playerImage = animationClip->GetImage();
	ImageSize* playerSize = playerImage->GetImageSize();
	Vector2 playerPosition = *playerImage->GetDrawingPosition();

	int playerRightX = playerPosition.x + playerImage->GetSize().x;
	int distance = 0;
	int magnitude = 0;

	MapObject* object = nullptr;
	// x축이 겹친 오브젝트 중 가까운 오브젝트 찾기.
	for (int i = 0; i < objects.size(); i++)
	{
		int drawingPositionX = objects[i]->GetImage()->GetDrawingPosition()->x;
		if (drawingPositionX == 0)
			continue;

		magnitude = drawingPositionX - playerRightX;
		if (distance > magnitude && magnitude * -1 < playerImage->GetSize().x * 2)
		{
			distance = magnitude;
			object = objects[i];
		}
	}

	if (!object)
		return nullptr;

	ImageText* objectImage = object->GetImage();
	ImageSize* objectSize = objectImage->GetImageSize();

	int objectPositionY = objectImage->GetDrawingPosition()->y;
	int objectheight = object->GetImage()->GetSize().y;

	int playerHeight = playerImage->GetSize().y;
	int playerIndex = objectPositionY + objectheight - playerPosition.y;
	int objectIndex = objectheight;
	int objectStart = objectheight - playerIndex;

	if (playerIndex > playerHeight)
		playerIndex = playerHeight;

	for (int i = 0; i < playerIndex; i++)
	{
		if (objectStart + i < 0)
			continue;

		if (playerSize->widths[i] == 0)
			continue;

		if (objectSize->widths[objectStart + i] == 0)
			continue;

		// 내 x좌표 최소/최대.
		int min = playerImage->GetDrawingPosition()->x + playerSize->offsets[i];
		int max = min + playerSize->widths[i];

		// 다른 액터의 x좌표 최소/최대.
		int otherMin = objectImage->GetDrawingPosition()->x + objectSize->offsets[objectStart + i];
		int otherMax = otherMin + objectSize->widths[objectStart + i];

		if (otherMin > max)
			continue;

		if (otherMax < min)
			continue;

		return object;
	}

	return nullptr;
}

void Player::OnCollisionItem(std::vector<Item*> items)
{
	Vector2 playerPosition = *animationClip->GetImage()->GetDrawingPosition();
	Vector2 playerSize = animationClip->GetImage()->GetSize();
	for (int i = 0; i < items.size(); i++)
	{
		Vector2 itemPosition = *items[i]->GetImage()->GetDrawingPosition();
		Vector2 itemSize = items[i]->GetImage()->GetSize();

		itemPosition.x += 30;
		itemSize.x -= 60;

		// AABB 충돌 체크
		bool isColliding =
			playerPosition.x < itemPosition.x + itemSize.x &&
			playerPosition.x + playerSize.x > itemPosition.x &&
			playerPosition.y < itemPosition.y + itemSize.y &&
			playerPosition.y + playerSize.y > itemPosition.y;

		if (isColliding)
		{
			items[i]->RemoveObject();
			if (items[i]->GetType() == ItemType::Jelly)
				level->AddScore(640);
			else if (items[i]->GetType() == ItemType::BearJelly)
				level->AddScore(1110);
			else if (items[i]->GetType() == ItemType::KingBearJelly)
				level->AddScore(7630);
			else if (items[i]->GetType() == ItemType::Coin)
				level->AddCoin(100);
			else if (items[i]->GetType() == ItemType::Big)
				SetBig(true);
		}
	}
}

void Player::SetBig(bool isBig)
{
	this->isBig = isBig;

	defaultPosition.y += isBig ? -78 : 78;

	auto moveImages = playerAnimator.GetClip(move)->GetImages();
	for (int i = 0; i < moveImages.size(); i++)
	{
		moveImages[i]->image->SetIsBig(isBig);
		Vector2* drawingPosition = moveImages[i]->image->GetDrawingPosition();
		drawingPosition->y = defaultPosition.y;
	}

	auto jumpImages = playerAnimator.GetClip(jump)->GetImages();
	for (int i = 0; i < jumpImages.size(); i++)
	{
		jumpImages[i]->image->SetIsBig(isBig);
		Vector2* drawingPosition = jumpImages[i]->image->GetDrawingPosition();
		drawingPosition->y = defaultPosition.y;
	}

	if (isBig)
		bigTime = 5.0f;
}
