#pragma once

#include "Core/Core.h" // THIS INCLUDE SHOULD BE ON TOP
#include "Bird.hpp"

using namespace Core;

class FlappyBurd : public App
{
private:
    Bird *player;  // Player instance
    Camera2D *cam; // Camera instance

public:
    void Start() override;
    void Update() override;
    void Render() override;
    void Close() override;
};