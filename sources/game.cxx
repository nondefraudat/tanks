#include "game.hxx"
#include <SDL3/SDL.h>

void game::start() noexcept {
    active = true;
    while (active) {
        process_events();
        Uint64 current_ticks = SDL_GetTicks();
        if (current_ticks - time_buffer > (1000/12)) {
            time_buffer = current_ticks;
            clear();
            render_test_figure();
            update();
        }
        if (up^down) {
            move_test_figure({ 0.f, 1e-3f*(up ? 1 : -1), 0.f });
        }
        if (left^right) {
            rotate_test_figure(2e-6f*(left ? 1 : -1));
        }
    }
}

void game::process_events() noexcept {
    SDL_Event eventBuffer;
    while (SDL_PollEvent(&eventBuffer)) {
        switch (eventBuffer.type)
        {
        case SDL_EVENT_QUIT:
            active = false;
            break;
        case SDL_EVENT_KEY_UP:
        case SDL_EVENT_KEY_DOWN:
            process_key(eventBuffer.key.keysym.sym,
                    eventBuffer.key.state);
            break;
        }
    }
}

#include <iostream>

void game::process_key(int key, bool state) noexcept {
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
