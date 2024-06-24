#pragma once

#include "Figure.hxx"
#include "Camera.hxx"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <list>

class World {
public:
    void PlaceCamera(Camera &&camera) noexcept;

    Figure *Place(Figure &&figure) noexcept;
    void Update(float delta) noexcept;
    void Release() noexcept;
    
    Camera &GetCamera() noexcept;
    std::list<Figure> &Figures() noexcept;

private:
    Camera camera;
    std::list<Figure> figures;
};
