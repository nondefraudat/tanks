#pragma once

#include "renderer.hxx"
#include <cstdint>

struct SDL_Window;
struct SDL_GLContextState;

class game : renderer {
public:
    void start() noexcept;

private:
    bool active = false;
    uint64_t time_buffer = 0;
    bool up = false, down = false,
            left = false, right = false;

    void process_events() noexcept;
    void process_key(int key, bool state) noexcept;
};
