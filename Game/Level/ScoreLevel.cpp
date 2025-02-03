#include "ScoreLevel.h"
#include "Engine/Engine.h"

ScoreLevel::ScoreLevel(int coin, int score)
{
	scorePanel01 = new ImageText("Cookie_Score_Panel_01");
	Vector2 panel01Position;
	panel01Position.x = Engine::Get().ScreenSize().x / 2 - scorePanel01->GetSize().x;
	panel01Position.y = 40;
	scorePanel01->SetDrawingPosition(panel01Position);

	scorePanel02 = new ImageText("Cookie_Score_Panel_02");
	Vector2 panel02Position;
	panel02Position.x = Engine::Get().ScreenSize().x / 2;
	panel02Position.y = 40;
	scorePanel02->SetDrawingPosition(panel02Position);

	scoreButton = new ImageText("Cookie_Score_Button");
	Vector2 buttonPosition;
	buttonPosition.x = Engine::Get().ScreenSize().x / 2 - scoreButton->GetSize().x / 2;
	buttonPosition.y = 356;
	scoreButton->SetDrawingPosition(buttonPosition);

	coinIcon = new ImageText("Item/Cookie_Coin", Color::LightYellow);
	coinIcon->SetDrawingPosition(Vector2(540, 274));

	coinText = new NumberText();
	coinText->SetSortType(TextSortType::Right);
	coinText->SetPosition(Vector2(660, 278));
	coinText->SetNumber(coin);
	actors.push_back(coinText);

	scoreText = new NumberText(TextSizeType::Large);
	scoreText->SetSortType(TextSortType::Middle);
	scoreText->SetPosition(Vector2(Engine::Get().ScreenSize().x / 2 - 56, 170));
	scoreText->SetNumber(score);
	actors.push_back(scoreText);
}

void ScoreLevel::Update(float deltaTime)
{
}

void ScoreLevel::Draw()
{
	Super::Draw();

	scorePanel01->Print();
	scorePanel02->Print();

	scoreButton->Print();

	coinIcon->Print();
}
