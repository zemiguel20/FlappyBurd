#pragma once

#include "Core/Core.h"

class FlappyBurd : public App
{
protected:
    void Start() override;
    void Update() override;
    void Close() override;

public:
    FlappyBurd();
};