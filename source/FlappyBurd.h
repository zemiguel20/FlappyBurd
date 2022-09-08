#pragma once

#include "Core/Core.h"
using namespace Core;
#include "Bird.hpp"
#include "Background.hpp"
#include "ScrollingGround.hpp"
#include "ScrollingBarriers.hpp"

class FlappyBurd : public App
{
private:
    Camera2D *cam;
    Bird *player;
    Background *bg;
    ScrollingGround *sgrnd;
    ScrollingBarriers *sbrrs;

public:
    void Start() override;
    void Update() override;
    void Render() override;
    void Close() override;
};