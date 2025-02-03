#include "MenuLevel.h"
#include "Actor/Player.h"

MenuLevel::MenuLevel()
{
    hInput = GetStdHandle(STD_INPUT_HANDLE);
    if (hInput == INVALID_HANDLE_VALUE)
        return;

    // �ܼ� �Է� ��� ����
    GetConsoleMode(hInput, &prevMode);
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

void MenuLevel::Update(float deltaTime)
{
    // �Է� �̺�Ʈ �б�
    ReadConsoleInput(hInput, &inputRecord, 1, &events);

    // ���콺 �̺�Ʈ���� Ȯ��
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
    // ��ư ���¸� Ȯ��
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