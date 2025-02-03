#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Actor/DrawableActor.h"
#include "Level/ScoreLevel.h"

GameLevel::GameLevel()
{
	map = new CreateMap(this);
	actors.push_back(map);

	player = new Player(this);
	actors.push_back(player);

	coinText = new NumberText();
	coinText->SetPosition(Vector2(Engine::Get().ScreenSize().x / 2 - 30, 10));
	coinText->SetNumber(0);
	actors.push_back(coinText);

	coinIcon = new ImageText("Item/Cookie_Coin", Color::LightYellow);
	coinIcon->SetDrawingPosition(Vector2(Engine::Get().ScreenSize().x / 2 - 60, 7));

	scoreText = new NumberText();
	scoreText->SetSortType(TextSortType::Right);
	scoreText->SetPosition(Vector2(Engine::Get().ScreenSize().x - 120, 10));
	scoreText->SetNumber(0);
	actors.push_back(scoreText);
}

GameLevel::~GameLevel()
{
	delete coinIcon;

	MapObject::InitStatic();
}

void GameLevel::Draw()
{
	Super::Draw();

	coinIcon->Print();
}

void GameLevel::AddCoin(int coin)
{
	this->coin += coin;
	coinText->SetNumber(this->coin);
}

void GameLevel::AddScore(int score)
{
	this->score += score;
	scoreText->SetNumber(this->score);
}

void GameLevel::LoadScoreLevel()
{
	Engine::Get().LoadLevel(new ScoreLevel(coin, score));
}