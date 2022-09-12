#pragma once

#include "Core/Core.h"
using namespace Core;

enum GameState
{
    START,
    RUNNING,
    GAME_OVER
};

#include "Bird.hpp"
#include "Background.hpp"
#include "ScrollingGround.hpp"
#include "ScrollingBarriers.hpp"
#include "UI.hpp"

class FlappyBurd : public App
{
private:
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

    UI *ui;

public:
    void Start() override;
    void Update() override;
    void Render() override;
    void Close() override;
};