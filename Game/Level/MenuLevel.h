#pragma once
#include <Level/Level.h>

class MenuLevel : public Level
{
	RTTI_DECLARATIONS(MenuLevel, Level)

public:
    MenuLevel();

    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    void HandleMouseEvent(MOUSE_EVENT_RECORD mouseEvent);

private:
    HANDLE hInput;
    DWORD prevMode;

    INPUT_RECORD inputRecord;
    DWORD events;
};