#include "MenuLevel.h"
#include "Actor/Player.h"

MenuLevel::MenuLevel()
{
    hInput = GetStdHandle(STD_INPUT_HANDLE);
    if (hInput == INVALID_HANDLE_VALUE)
        return;

    // 콘솔 입력 모드 설정
    GetConsoleMode(hInput, &prevMode);
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

void MenuLevel::Update(float deltaTime)
{
    // 입력 이벤트 읽기
    ReadConsoleInput(hInput, &inputRecord, 1, &events);

    // 마우스 이벤트인지 확인
    if (inputRecord.EventType == MOUSE_EVENT)
    {
        HandleMouseEvent(inputRecord.Event.MouseEvent);
    }
}

void MenuLevel::Draw()
{
}

void MenuLevel::HandleMouseEvent(MOUSE_EVENT_RECORD mouseEvent)
{
    // 버튼 상태를 확인
    if (mouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
    {
        std::cout << "Left mouse button clicked at ("
            << mouseEvent.dwMousePosition.X << ", "
            << mouseEvent.dwMousePosition.Y << ")\n";
    }
    else if (mouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
    {
        std::cout << "Right mouse button clicked at ("
            << mouseEvent.dwMousePosition.X << ", "
            << mouseEvent.dwMousePosition.Y << ")\n";
    }
}