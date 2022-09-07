#pragma once

#include "Core/Core.h" // THIS INCLUDE SHOULD BE ON TOP
using namespace Core;

// Game config global variables.
namespace Config
{
    const int REF_SCREEN_W = 360;
    const int REF_SCREEN_H = 640;

    const float SCROLL_VEL = 70.0f;
} // namespace Config

#include "Bird.hpp"
#include "Background.hpp"
#include "ScrollingGround.hpp"

class FlappyBurd : public App
{
private:
    Camera2D *cam;
    Bird *player;
    Background *bg;
    ScrollingGround *sgrnd;

public:
    void Start() override;
    void Update() override;
    void Render() override;
    void Close() override;
};