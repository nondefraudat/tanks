#pragma once

class SDL_Window;
class SDL_Surface;

class game {
    game() noexcept;
    ~game() noexcept;

public:
    static void start() noexcept;

private:
    bool active = false;
    int timeBuffer = 0;
    
    SDL_Window* window;
    SDL_Surface* surface;

    int x = 20, y = 20;

    void eventLoop() noexcept;

    void processEvents() noexcept;
    void render() noexcept;

    void processKeyEvent(int key) noexcept;
    void drawSquare() noexcept;
};
