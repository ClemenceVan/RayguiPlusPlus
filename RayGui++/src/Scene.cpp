#include "raylib.h"
#include "Scene.hpp"

// scene class implementation

Scene::Scene() { // might add some optional parameters here like font
    _font = GetFontDefault();
}

Scene::~Scene() {
    // for (auto& element : _elements) TO BE CHECKED IF NEEDED
    //     delete element;
}

Font Scene::getFont() {
    return _font;
}

RayGuipp* Scene::add(RayGuipp* element) {
    _elements.push_back(element);
    element->setParent(this);
    return element;
}

void Scene::remove(RayGuipp* element) {
    for (auto it = _elements.begin(); it != _elements.end(); it++) {
        if (*it == element) {
            _elements.erase(it);
            break;
        }
    }
}

void Scene::draw() {
    for (auto& element : _elements)
        element->draw();
}

void Scene::update() {
    check_focused();
    for (auto& element : _elements)
        element->update();
}

void Scene::unfocus() {
    for (auto& element : _elements)
        if (element->is_focused())
            element->setFocused(false);
}

void Scene::focus(RayGuipp* element) {
    unfocus();
    element->setFocused(true);
}

RayGuipp* Scene::getFocused() {
    for (auto& element : _elements)
        if (element->is_focused())
            return element;
    return nullptr;
}

void Scene::check_focused() {
    for (auto& elem : _elements)
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(GetMousePosition(), elem->getSize()))
                elem->setFocused(true);
            else
                elem->setFocused(false);
        } else {
            if (CheckCollisionPointRec(GetMousePosition(), elem->getSize()))
                elem->setHover(true);
            else
                elem->setHover(false);
        }
}

RayGuipp* Scene::getId(std::string id) {
    for (auto& element : _elements)
        if (element->getId() && *element->getId() == id)
            return element;
    return nullptr;
}

std::vector<RayGuipp*> Scene::getClass(std::string class_) {
    std::vector<RayGuipp*> elements;
    for (auto& element : _elements)
        for (auto& elem_class : *element->getClass())
            if (elem_class == class_)
                elements.push_back(element);
    return elements;
}