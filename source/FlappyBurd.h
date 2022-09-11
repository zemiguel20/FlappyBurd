#pragma once

#define DEBUG
#include "Core/Core.h"
using namespace Core;
#include "Bird.hpp"
#include "Background.hpp"
#include "ScrollingGround.hpp"
#include "ScrollingBarriers.hpp"

#include "UI/RunUI.hpp"
#include "UI/StartPanelUI.hpp"
#include "UI/GameOverUI.hpp"

class FlappyBurd : public App
{
private:
    enum GameState
    {
        START,
        RUNNING,
        GAME_OVER
    };

    GameState state;

    Camera2D *cam;
    Bird *player;
    Background *bg;
    ScrollingGround *ground;
    ScrollingBarriers *barriers;

    int score;
    int highscore;
    void LoadHighscore();
    void SaveHighscore();

    Sound *scoreSound;

    Timer *startRunTimer;

    StartPanelUI *startPanelUI;
    RunUI *runUI;
    GameOverUI *gameoverUI;

public:
    void Start() override;
    void Update() override;
    void Render() override;
    void Close() override;
};