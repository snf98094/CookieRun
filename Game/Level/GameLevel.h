#pragma once
#include "Level/Level.h"
#include "Actor/Player.h"
#include "Actor/CreateMap.h"
#include "UI/NumberText.h"
#include "Image/ImageText.h"

class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();
	~GameLevel();

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

	// 플레이 중 획특한 코인.
	int coin = 0;
	// 플레이 중 획특한 점수.
	int score = 0;
};