#pragma once

#include <cstdint>
#include <glm/mat4x4.hpp>

class Program {
public:
    void Load() noexcept;
    void UpdateProjection(float width, float height) noexcept;
    void UpdateView(const glm::mat4 &view) noexcept;
    void Exec(uint32_t vao, const glm::mat4 &model) noexcept;
    void Release() noexcept;

private:
    uint32_t programLocation;
    uint32_t modelLocation, scaleLocation, viewLocaton, projectinLocation;

    void LoadShader(const char *shaderPath, uint32_t shaderType) noexcept;
    void InitLocatins() noexcept;
};
