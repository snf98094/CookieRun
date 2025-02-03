#include "LoadingLevel.h"
#include "GameLevel.h"
#include "Engine/Engine.h"

LoadingLevel::LoadingLevel()
{
	image01 = new ImageText("Loading/Cookie_Loading_01", Color::White, false);
	int x = image01->GetSize().x;
	image02 = new ImageText("Loading/Cookie_Loading_02", Color::White, false);
	image02->SetDrawingPosition(Vector2(x, 0));
	image03 = new ImageText("Loading/Cookie_Loading_03", Color::White, false);
	image03->SetDrawingPosition(Vector2(x * 2, 0));
	image04 = new ImageText("Loading/Cookie_Loading_04", Color::White, false);
	image04->SetDrawingPosition(Vector2(x * 3, 0));
	image05 = new ImageText("Loading/Cookie_Loading_05", Color::White, false);
	image05->SetDrawingPosition(Vector2(x * 4, 0));
	image06 = new ImageText("Loading/Cookie_Loading_06", Color::White, false);
	image06->SetDrawingPosition(Vector2(x * 5, 0));
	image07 = new ImageText("Loading/Cookie_Loading_07", Color::White, false);
	image07->SetDrawingPosition(Vector2(x * 6, 0));
	image08 = new ImageText("Loading/Cookie_Loading_08", Color::White, false);
	image08->SetDrawingPosition(Vector2(x * 7, 0));

	hInput = GetStdHandle(STD_INPUT_HANDLE);
	if (hInput == INVALID_HANDLE_VALUE)
		return;

	// 콘솔 입력 모드 설정
	GetConsoleMode(hInput, &prevMode);
	SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

LoadingLevel::~LoadingLevel()
{
	delete image01;
	delete image02;
	delete image03;
	delete image04;
	delete image05;
	delete image06;
	delete image07;
	delete image08;
}

void LoadingLevel::Update(float deltaTime)
{
	// 입력 이벤트 읽기
	ReadConsoleInput(hInput, &inputRecord, 1, &events);

	// 마우스 이벤트인지 확인
	if (inputRecord.EventType == MOUSE_EVENT)
	{
		if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			Engine::Get().LoadLevel(new GameLevel());
	}
}

void LoadingLevel::Draw()
{
	image01->Print();
	image02->Print();
	image03->Print();
	image04->Print();
	image05->Print();
	image06->Print();
	image07->Print();
	image08->Print();
}