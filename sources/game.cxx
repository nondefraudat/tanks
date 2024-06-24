#include "Game.hxx"
#include <SDL3/SDL.h>

using namespace std;

Game::Game() noexcept {
    figure = world.Place(Figure());
    renderer.Target(&world);
    figure->Init();
    Camera camera;
    camera.Chase(figure);
    world.PlaceCamera(move(camera));
}

Game::~Game() noexcept {
    world.Release();
}

void Game::Start() noexcept {
    static Game game;
    game.Loop();
}

void Game::Loop() noexcept {
    isActive = true;
    while (isActive) {
        ProcessEvents();
        float delta = Delta();
        world.Update(delta);
        renderer.Render(delta);
    }
}

void Game::ProcessEvents() noexcept {
    SDL_Event eventBuffer;
    while (SDL_PollEvent(&eventBuffer)) {
        switch (eventBuffer.type)
        {
        case SDL_EVENT_QUIT:
            isActive = false;
            break;
        case SDL_EVENT_KEY_UP:
        case SDL_EVENT_KEY_DOWN:
            ProcessKey(eventBuffer.key.keysym.sym,
                    eventBuffer.key.state);
            break;
        }
    }
    if (left^right) {
        figure->Rotate(left ? 1.f : -1.f);
    }
    else {
        figure->Rotate(0.f);
    }
    if (up^down) {
        figure->Move(up ? 1.f : -1.f);
    }
    else {
        figure->Move(0.f);
    }
}

float Game::Delta() noexcept {
    static uint64_t timeCache = 0;
    uint64_t currentTime = SDL_GetTicks(); 
    uint64_t deltaTime = currentTime - timeCache;
    timeCache = currentTime;
    return float(deltaTime)/1000.f;
}

void Game::ProcessKey(int key, bool state) noexcept {
    switch (key)
    {
    case SDLK_UP:
        up = state;
        break;
    case SDLK_DOWN:
        down = state;
        break;
    case SDLK_LEFT:
        left = state;
        break;
    case SDLK_RIGHT:
        right = state;
        break;
    }
}
