#pragma once

#include <string>
#include <cstdint>
#include <glm/mat4x4.hpp>

class shader_program {
protected:
    glm::mat4 model = { 1.f }, temp_model,
            view = { 1.f }, projection;
    
    void init() noexcept;
    void bind() noexcept;

private:
    uint32_t gl_program;
    uint32_t model_id, view_id, projection_id;

    void load(const char *file_path, int shader_type) noexcept;
    std::string load(const char *file_path) noexcept;
};
