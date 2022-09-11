#pragma once

#include "Core/Core.h"
using namespace Core;

class UI
{
private:
    Font *font;

    Text *titleText;
    Text *runScoreText;
    Text *whiteLabelText;
    Text *yellowLabelText;

    GameState *state;
    Timer *startRunTimer;
    int *score;
    int *highscore;

public:
    UI(GameState &state, Timer &timer, int &score, int &highscore)
    {
        Log::Info("Loading UI");

        this->state = &state;
        this->startRunTimer = &timer;
        this->score = &score;
        this->highscore = &highscore;

        font = new Font("assets/04B_30__.TTF");

        titleText = new Text("", *font, 50, RED);

        whiteLabelText = new Text("", *font, 20, WHITE);
        yellowLabelText = new Text("", *font, 20, YELLOW);
        runScoreText = new Text("", *font, 30, WHITE);

        Log::Info("UI loaded");
    };

    ~UI()
    {
        Log::Info("Unloading UI");

        delete titleText;
        delete runScoreText;
        delete whiteLabelText;

        delete font;

        Log::Info("UI unloaded");
    };

    void Render()
    {
        if (*state == START)
        {
            titleText->text = "FLAPPY";
            titleText->Render(180, 100);
            titleText->text = "BURD";
            titleText->Render(180, 150);
            if (startRunTimer->Finished())
            {
                whiteLabelText->text = "Press SPACE to play";
                whiteLabelText->Render(180, 500);
            }
        }
        else if (*state == RUNNING)
        {
            runScoreText->text = std::to_string(*score);
            runScoreText->Render(180, 60);
        }
        else if (*state == GAME_OVER)
        {
            titleText->text = "GAME OVER";
            titleText->size = 40;
            titleText->Render(180, 180);

            DrawRectangle(Vector2(80.0f, 220.0f),
                          Vector2(280.0f, 420.0f),
                          BROWN);

            whiteLabelText->text = "SCORE";
            whiteLabelText->Render(180, 260);

            yellowLabelText->text = std::to_string(*score);
            yellowLabelText->Render(180, 290);

            whiteLabelText->text = "HIGHSCORE";
            whiteLabelText->Render(180, 350);

            yellowLabelText->text = std::to_string(*highscore);
            yellowLabelText->Render(180, 380);

            if (startRunTimer->Finished())
            {
                whiteLabelText->text = "Press SPACE to play";
                whiteLabelText->Render(180, 500);
            }
        }
    };
};