#include "raylib.h"
#include "RayGui++.hpp"

/* Constructor */
RayGuipp::RayGuipp(Rectangle size) {
    _size = size;
}

void RayGuipp::setParent(Scene *parent) {
    this->_parent = parent;
}

Scene *RayGuipp::getParent() {
    return _parent;
}

Font RayGuipp::getFont() {
    return _parent->getFont();
}

/* Getters and setters */
Rectangle RayGuipp::getSize() {
    return _size;
}

bool RayGuipp::isActive() {
    return _active;
}

void RayGuipp::setActive(bool active) {
    _active = active;
}

bool RayGuipp::is_focused() {
    return _focused;
}

void RayGuipp::setFocused(bool focused) {
    if (focused && _onFocus)
        _onFocus();
    if (!focused && _onUnfocus)
        _onUnfocus();
    _focused = focused;
}

bool RayGuipp::hover() {
    return _hovered;
}

void RayGuipp::setHover(bool hovered) {
    if (hovered && !_hovered)
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    if (!hovered && _hovered)
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    _hovered = hovered;
}

void RayGuipp::onFocus(std::function<void()> function) {
    _onFocus = function;
}

void RayGuipp::onUnfocus(std::function<void()> function) {
    _onUnfocus = function;
}

std::string *RayGuipp::getId() {
    return &_id;
}

void RayGuipp::setId(std::string id) {
    _id = id;
}

std::vector<std::string> *RayGuipp::getClass() {
    return &_class;
}

void RayGuipp::addClass(std::string class_) {
    _class.push_back(class_);
}

void RayGuipp::setPos(Vector2 pos) {
    _size.x = pos.x;
    _size.y = pos.y;
}

Vector2 RayGuipp::getPos() {
    return {_size.x, _size.y};
}
