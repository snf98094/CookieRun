#pragma once
#include "Level/Level.h"
#include "Image/ImageText.h"
#include "UI/NumberText.h"

class ScoreLevel : public Level
{
    RTTI_DECLARATIONS(ScoreLevel, Level)

public:
    ScoreLevel(int coin, int score);
    ~ScoreLevel();

    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    void MouseInputInit();
    void MouseInputCheck();

private:
    ImageText* scorePanel01 = nullptr;
    ImageText* scorePanel02 = nullptr;

    ImageText* scoreButton = nullptr;

    ImageText* coinIcon = nullptr;
    NumberText* coinText = nullptr;

    NumberText* scoreText = nullptr;

    HANDLE hInput;
    DWORD prevMode;
    INPUT_RECORD inputRecord;
    DWORD events;
};