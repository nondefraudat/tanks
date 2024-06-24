#include "World.hxx"

#include <glm/ext.hpp>

using namespace glm;
using namespace std;

void World::PlaceCamera(Camera &&camera) noexcept {
    this->camera = camera;
}

Figure *World::Place(Figure &&figure) noexcept {
    figures.emplace_back(figure);
    return &figures.back();
}

void World::Update(float delta) noexcept {
    for (Figure &figure : figures) {
        figure.Update(delta);
    }
    camera.Update(delta);
}

void World::Release() noexcept {
    figures.clear();
}

Camera &World::GetCamera() noexcept {
    return camera;
}

std::list<Figure> &World::Figures() noexcept
{
    return figures;
}
