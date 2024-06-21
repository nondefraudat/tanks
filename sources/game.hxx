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

    void Loop() noexcept;

    void ProcessEvents() noexcept;
    uint64_t DeltaTime() noexcept;

    void ProcessKey(int key, bool state) noexcept;
};
