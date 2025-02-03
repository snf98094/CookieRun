#include "ScoreLevel.h"
#include "Engine/Engine.h"
#include "Level/GameLevel.h"

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

	MouseInputInit();
}

ScoreLevel::~ScoreLevel()
{
	delete scorePanel01;
	delete scorePanel02;
	delete scoreButton;
	delete coinIcon;
}

void ScoreLevel::Update(float deltaTime)
{
	MouseInputCheck();
}

void ScoreLevel::Draw()
{
	Super::Draw();

	scorePanel01->Print();
	scorePanel02->Print();

	scoreButton->Print();

	coinIcon->Print();
}

void ScoreLevel::MouseInputInit()
{
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	if (hInput == INVALID_HANDLE_VALUE)
		return;

	// 콘솔 입력 모드 설정
	GetConsoleMode(hInput, &prevMode);
	SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

void ScoreLevel::MouseInputCheck()
{

	// 입력 이벤트 읽기
	ReadConsoleInput(hInput, &inputRecord, 1, &events);

	// 마우스 이벤트인지 확인
	if (inputRecord.EventType == MOUSE_EVENT)
	{
		if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			Vector2 buttonPosition = *scoreButton->GetDrawingPosition();
			Vector2 buttonSize = scoreButton->GetSize();
			
			bool checkX, checkY;
			int x = inputRecord.Event.MouseEvent.dwMousePosition.X;
			int y = inputRecord.Event.MouseEvent.dwMousePosition.Y;
			checkX = x >= buttonPosition.x && x <= buttonPosition.x + buttonSize.x;
			checkY = y >= buttonPosition.y && y <= buttonPosition.y + buttonSize.y;

			if (checkX && checkY)
			{
				Engine::Get().LoadLevel(new GameLevel());
				SetConsoleMode(hInput, prevMode);
			}
		}
	}
}