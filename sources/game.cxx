#include "game.hxx"
#include <SDL3/SDL.h>
#include <cassert>

game::game() noexcept {
    assert(SDL_Init( SDL_INIT_VIDEO ) >= 0);
    window = SDL_CreateWindow("test", 400, 400, NULL);
    assert(window != nullptr);
    surface = SDL_GetWindowSurface(window);
    assert(surface != nullptr);
}

game::~game() noexcept {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void game::start() noexcept {
    game().eventLoop();
}

void game::eventLoop() noexcept {
    active = true;
    while (active) {
        processEvents();
        render();
    }
}

void game::processEvents() noexcept
{
    SDL_Event eventBuffer;
    while (SDL_PollEvent(&eventBuffer)) {
        switch (eventBuffer.type)
        {
        case SDL_EVENT_QUIT:
            active = false;
            break;
        case SDL_EVENT_KEY_DOWN:
            processKeyEvent(eventBuffer.key.keysym.sym);
            break;
        }
    }
}

void game::render() noexcept {
    int current = SDL_GetTicks();
    if (current - timeBuffer < (1000/12)) {
        return;
    }
    timeBuffer = current - timeBuffer;
    SDL_FillSurfaceRect(surface, nullptr, 0xAAAAAAAA);
    drawSquare();
    SDL_UpdateWindowSurface(window);
}

void game::processKeyEvent(int key) noexcept {
    switch (key)
    {
    case SDLK_UP:
        y -= 5;
        break;
    case SDLK_DOWN:
        y += 5;
        break;
    case SDLK_LEFT:
        x -= 5;
        break;
    case SDLK_RIGHT:
        x += 5;
        break;
    }
}

void game::drawSquare() noexcept {
    SDL_Rect rect { x - 8, y - 8, 16, 16 };
    SDL_FillSurfaceRect(surface, &rect, 0xFFFFFFFF);
}
