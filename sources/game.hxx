#pragma once

#include "Renderer.hxx"
#include "World.hxx"
#include "Figure.hxx"

class Game {
    Game() noexcept;
    ~Game() noexcept;

public:
    static void Start() noexcept;

private:
    World world;
    Renderer renderer;
    Figure *figure;

    bool isActive = false;

    bool left = false, right = false,
            up = false, down = false;

    void Loop() noexcept;

    void ProcessEvents() noexcept;
    float Delta() noexcept;

    void ProcessKey(int key, bool state) noexcept;
};
