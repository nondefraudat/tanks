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
        case SDL_EVENT_KEY_DOWN:
            process_key(eventBuffer.key.keysym.sym);
            break;
        }
    }
}

void game::process_key(int key) noexcept {
    switch (key)
    {
    case SDLK_UP:
        move_test_figure({ 0.f, .1f, 0.f });
        break;
    case SDLK_DOWN:
        move_test_figure({ 0.f, -.1f, 0.f });
        break;
    case SDLK_LEFT:
        rotate_test_figure(.1f);
        break;
    case SDLK_RIGHT:
        rotate_test_figure(-.1f);
        break;
    }
}
