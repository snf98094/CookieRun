#pragma once
#include "Level/Level.h"
#include "Actor/Player.h"
#include "Actor/CreateMap.h"
#include "Actor/NumberText.h"
#include "Image/ImageText.h"

class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	void AddCoin(int coin);
	void AddScore(int score);

	void LoadScoreLevel();

private:
	Player* player = nullptr;
	CreateMap* map = nullptr;
	NumberText* coinText = nullptr;
	ImageText* coinIcon = nullptr;
	NumberText* scoreText = nullptr;

	// �÷��� �� ȹƯ�� ����.
	int coin = 0;
	// �÷��� �� ȹƯ�� ����.
	int score = 0;
};