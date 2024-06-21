#include "Game.hxx"
#include <SDL3/SDL.h>

using namespace std;

Game::Game() noexcept {
    figure = world.Place(Figure());
    renderer.Target(&world);
    figure->Init(&renderer);
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
        uint64_t deltaTime = DeltaTime();
        world.Update(deltaTime);
        renderer.Render(deltaTime);
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
        case SDL_EVENT_KEY_DOWN:
            ProcessKey(eventBuffer.key.keysym.sym);
            break;
        }
    }
}

uint64_t Game::DeltaTime() noexcept {
    static uint64_t timeCache = 0;
    uint64_t currentTime = SDL_GetTicks(); 
    uint64_t deltaTime = currentTime - timeCache;
    timeCache = currentTime;
    return deltaTime;
}

void Game::ProcessKey(int key) noexcept {
    switch (key)
    {
    case SDLK_UP:
        figure->PushingForce(1.f);
        break;
    case SDLK_DOWN:
        figure->PushingForce(-1.f);
        break;
    case SDLK_LEFT:
        figure->RotatingForce(45.f);
        break;
    case SDLK_RIGHT:
        figure->RotatingForce(-45.f);
        break;
    }
}
