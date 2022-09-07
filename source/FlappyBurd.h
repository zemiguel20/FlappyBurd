#pragma once

#include "Core/Core.h" // THIS INCLUDE SHOULD BE ON TOP
using namespace Core;

#include "Bird.hpp"
#include "Background.hpp"

class FlappyBurd : public App
{
private:
    Camera2D *cam;  // Camera instance
    Bird *player;   // Player instance
    Background *bg; // Background sprite instance
public:
    void Start() override;
    void Update() override;
    void Render() override;
    void Close() override;
};